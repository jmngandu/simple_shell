#include "shell.h"


/**
 * hsh - the prompt loop 
 * @info: the info struct
 * @av: an array of null terminated strings
 * Return: 0 on success, 1 on failure
 */
int hsh(info_t *info, char **av)
{
	ssize_t ret = 0;
	int builtin_return = 0;

	while (ret != -1 && builtin_return != -2)
	{
		init_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		ret = get_input(info);
		if (ret != -1)
		{
			set_info(info, av);
			builtin_return = get_builtin(info);
			if (builtin_return == -1)
				get_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	create_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * get_builtin - gets a builtin cmd
 * @info: the info struct
 * Return: -1 if builtin fails,
 *			0 when builtin is successfully,
 *			1 when builtin found but fails,
 *			-2 when builtin signals exit()
 */
int get_builtin(info_t *info)
{
	int i, builtin_ret = -1;
	builtin_table built_tbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _help},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; built_tbl[i].type; i++)
		if (_strcmp(info->argv[0], built_tbl[i].type) == 0)
		{
			info->line_count++;
			builtin_ret = built_tbl[i].func(info);
			break;
		}
	return (builtin_ret);
}

/**
 * get_cmd - looks for a command in PATH
 * @info: info struct
 * Return: void
 */
void get_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = get_location(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && check_cmd(info, info->argv[0]))
			_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * _fork - creates a child process
 * @info: info struct
 * Return: void
 */
void _fork(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, find_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
