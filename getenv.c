#include "shell.h"

/**
 * find_environ - prints a list of environ
 * @info: info struct
 * Return: 0
 */
char **find_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_of_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - unsets an environment
 * @info: potential arguements for info struct.
 *  Return: 1 on success, 0 on failure
 * @val: the vvalue to find environ
 */
int _unsetenv(info_t *info, char *val)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !val)
		return (0);

	while (node)
	{
		p = starts_(node->str, val);
		if (p && *p == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), i);
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
 * _setenv - sets environments
 * @info: Structure holding potential arguments
 * @variable: the environment variable
 * @value: the value
 *  Return: 0
 */
int _setenv(info_t *info, char *variable, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buff = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, variable);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		p = starts_(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	ins_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

