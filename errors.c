#include "shell.h"

/**
 *_eputs - prints an err string
 * @str: the err to be printed
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes a character  to stderr
 * @c: character tobe printed*
 * Return: 1 on success, On error -1
 */
int _eputchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	buff[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given file_d
 * @c: character tobe printend
 * @fd: The file to write to *
 * Return: On success 1. -1 on error
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _putsfd - prints string entered by the user
 * @str: string to print
 * @fd: filedescriptor t\
 * Return: num of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
