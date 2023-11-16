#include "shell.h"

/**
 * _the_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _the_env(info_t *info)
{
	string_list_printer(info->env);
	return (0);
}

/**
 * env_fetcher - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *env_fetcher(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begain_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _the_env_setter - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _the_env_setter(info_t *info)
{
	if (info->argc != 3)
	{
		_showstr("Incorrect number of arguements\n");
		return (1);
	}
	if (environ_setter(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _the_env_declear - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _the_env_declear(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_showstr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		environ_declear(info, info->argv[i]);

	return (0);
}

/**
 * _the_env_list_oop - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _the_env_list_oop(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		incrs_end_noods(&node, environ[i], 0);
	info->env = node;
	return (0);
}

