#include "shell.h"

/**
 * get_history -  the finds history file
 * @info: parame struct
 * Return: string containg history file
 */

char *get_history(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * create_history - creates or appends to an existing file
 * @info: the param struct
 * Return: 1 on success,  -1 on failure
 */
int create_history(info_t *info)
{
	ssize_t fd;
	char *file = get_history(info);
	list_t *node = NULL;

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the param struct
 * Return: history count on success, 0 on failure
 */
int read_history(info_t *info)
{
	int i, last = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history(info);

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
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(info, buff + last, lc++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buff + last, lc++);
	free(buff);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		del_node_at_index(&(info->history), 0);
	number_history(info);
	return (info->histcount);
}

/**
 * build_history_list - appends entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	ins_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * number_history - numbers the history linked list afresh after changes
 * @info: Structure containing potential arguments
 * Return: the new history count
 */
int number_history(info_t *info)
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
