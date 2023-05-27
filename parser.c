#include "shell.h"

/**
 * check_cmd - checks whether supplied input is executable command
 * @info: struct info
 * @path: is the files path
 * Return: 1 on success, 0 on fail
 */
int check_cmd(info_t *info, char *path)
{
	struct stat sc;

	(void)info;
	if (!path || stat(path, &sc))
		return (0);

	if (sc.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * cpy_chars - creates a copy of characters
 * @strpath: the strings path
 * @start: first index
 * @end: last index
 *
 * Return: the new buffer
 */
char *cpy_chars(char *strpath, int start, int end)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < end; i++)
		if (strpath[i] != ':')
			buff[j++] = strpath[i];
	buff[j] = 0;
	return (buff);
}

/**
 * get_location - gets the command path
 * @info:  info struct
 * @strpath: the PATH string
 * @command: the command
 * Return: full path to the command
 */
char *get_location(info_t *info, char *strpath, char *command)
{
	int i = 0, current = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((_strlen(command) > 2) && starts_(command, "./"))
	{
		if (check_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!strpath[i] || strpath[i] == ':')
		{
			path = cpy_chars(strpath, current, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (check_cmd(info, path))
				return (path);
			if (!strpath[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}

