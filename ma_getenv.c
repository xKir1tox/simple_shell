#include "shell.h"

/**
 * environ_declear - Declear an environment variable
 * @info: Structure have  potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int environ_declear(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begain_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = index_noods_deleter(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * environ_getter - get ot return the string array clone or copy of the environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **environ_getter(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = lists_are_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * environ_setter - Intigrate  a new environment variable,
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int environ_setter(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_lenthofstr(var) + _lenthofstr(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_cantostr(buf, "=");
	_cantostr(buf, value);
	node = info->env;
	while (node)
	{
		p = begain_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	incrs_end_noods(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

