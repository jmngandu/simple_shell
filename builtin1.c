#include "shell.h"

/**
 * _history - displays the history list.
 * @info: info struct
 *  Return: 0
 */
int _history(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * unset_alias - sets alias 
 * @info:  struct
 * @str:  str alias
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr, c;
	int retn;

	ptr = str_chr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	retn = del_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_(info->alias, str, -1)));
	*ptr = c;
	return (retn);
}

/**
 * set_alias - sets alias
 * @info: struct
 * @str: alias to string
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = str_chr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (ins_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints string alias
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = str_chr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - my own alias builtin (man alias)
 * @info: Structure info.
 *  Return: 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
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
		ptr = str_chr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_(info->alias, info->argv[i], '='));
	}

	return (0);
}

