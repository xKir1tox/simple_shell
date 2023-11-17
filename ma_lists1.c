#include "shell.h"

/**
 * lists_are_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **lists_are_strings(list_t *head)
{
	list_t *node = head;
	size_t i = lists_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_lenthofstr(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * lists_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t lists_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * lists_printer - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t lists_printer(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(_ex_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * index_noods_fetcher - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t index_noods_fetcher(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * what_noods_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *what_noods_start(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begain_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
