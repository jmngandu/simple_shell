#include "shell.h"

/**
 * init_info - initializes info_t struct
 * @info: struct address
 */
void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - sets info_t struct
 * @info: struct address
 * @av: argument 
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
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

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees struct fields
 * @info: struct address
 * @all: true whe n freeing all fields
 */
void free_info(info_t *info, int all)
{
	sfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLists(&(info->env));
		if (info->history)
			freeLists(&(info->history));
		if (info->alias)
			freeLists(&(info->alias));
		sfree(info->environ);
			info->environ = NULL;
		my_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
