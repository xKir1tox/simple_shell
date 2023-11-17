#include "shell.h"

/**
 * the_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int the_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_fetcher(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = env_fetcher(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_comparstr(info->argv[1], "-") == 0)
	{
		if (!env_fetcher(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(env_fetcher(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = env_fetcher(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_show_error(info, "can't cd to ");
		_showstr(info->argv[1]), _showchr('\n');
	}
	else
	{
		environ_setter(info, "OLDPWD", env_fetcher(info, "PWD="));
		environ_setter(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * the_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int the_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			_show_error(info, "Illegal number: ");
			_showstr(info->argv[1]);
			_showchr('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * the_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int the_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

