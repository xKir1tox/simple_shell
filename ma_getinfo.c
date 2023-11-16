#include "shell.h"

/**
 * info_remover - initializes info_t struct
 * @info: struct address
 */
void info_remover(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_setter - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void info_setter(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = side_str(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_my_alias(info);
		rep_my_vars(info);
	}
}

/**
 * info_set_free - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void info_set_free(info_t *info, int all)
{
	_str_free_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			lists_are_free(&(info->env));
		if (info->history)
			lists_are_free(&(info->history));
		if (info->alias)
			lists_are_free(&(info->alias));
		_str_free_array(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

