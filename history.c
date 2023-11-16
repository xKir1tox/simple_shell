#include "shell.h"

/**
 * history_file_catcher - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *history_file_catcher(info_t *info)
{
	char *buf, *dir;

	dir = env_fetcher(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_lenthofstr(dir) + _lenthofstr(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_cantostr(buf, "/");
	_cantostr(buf, HIST_FILE);
	return (buf);
}

/**
 * history_file_writer - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int history_file_writer(info_t *info)
{
	ssize_t fd;
	char *filename = history_file_catcher(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_showsfd(node->str, fd);
		_showfd('\n', fd);
	}
	_showfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * history_file_reader - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int history_file_reader(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file_catcher(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list_builder(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		history_list_builder(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		index_noods_deleter(&(info->history), 0);
	history_numb_changer(info);
	return (info->histcount);
}

/**
 * history_list_builder - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int history_list_builder(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	incrs_end_noods(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * history_numb_changer - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int history_numb_changer(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

