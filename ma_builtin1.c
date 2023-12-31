#include "shell.h"

/**
 * unset_alias -string is sets to alias
 * @info: parameter of struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _chars_str(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = index_noods_deleter(&(info->alias),
		index_noods_fetcher(info->alias, what_noods_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _the_history - show or displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _the_history(info_t *info)
{
	lists_printer(info->history);
	return (0);
}
/**
 * set_alias - is setting alias  to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _chars_str(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (incrs_end_noods(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - do (prints) an alias as string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _chars_str(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _the_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _the_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _chars_str(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(what_noods_start(info->alias, info->argv[i], '='));
	}

	return (0);
}

