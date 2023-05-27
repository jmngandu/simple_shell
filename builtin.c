#include "shell.h"

/**
 * _myexit - 	quits the shell
 * @info: info struct
 *  Return: quits shell with a given exit status
 */
int _myexit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = err_atoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_err(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes  directory
 * @info: info struct
 *  Return: 0 on success
 */
int _cd(info_t *info)
{
	char *str, *dir, buff[1024];
	int chdir_return;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("getcwd failure \n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_return =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_return =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		print_err(info, "unable to change directory");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help - help
 * @info: info struct
 *  Return: 0
 */
int _help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("Not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
