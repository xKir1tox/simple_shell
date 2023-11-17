#include "shell.h"
/**
 * in_find_builtin - in finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int in_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", the_exit},
		{"env", _the_env},
		{"help", the_help},
		{"history", _the_history},
		{"setenv", _the_env_setter},
		{"unsetenv", _the_env_declear},
		{"cd", the_cd},
		{"alias", _the_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_comparstr(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * in_hsh - in hsh main for shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int in_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_remover(info);
		if (_interact_mode(info))
			_puts("$ ");
		_showchr(BUF_FLUSH);
		r = input_fetcher(info);
		if (r != -1)
		{
			info_setter(info, av);
			builtin_ret = in_find_builtin(info);
			if (builtin_ret == -1)
				vo_find_cmd(info);
		}
		else if (_interact_mode(info))
			_putchar('\n');
		info_set_free(info, 0);
	}
	history_file_writer(info);
	info_set_free(info, 1);
	if (!_interact_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * vo_fork_cmd - dublicate and  forks exec thread run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void vo_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, environ_getter(info)) == -1)
		{
			info_set_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_show_error(info, "Permission denied\n");
		}
	}
}
/**
 * vo_find_cmd - get or find command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void vo_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_is_delmed(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_prs_path(info, env_fetcher(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		vo_fork_cmd(info);
	}
	else
	{
		if ((_interact_mode(info) || env_fetcher(info, "PATH=")
					|| info->argv[0][0] == '/') && in_cmd(info, info->argv[0]))
			vo_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_show_error(info, "not found\n");
		}
	}
}
