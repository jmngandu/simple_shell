#include "shell.h"

/**
 * _strcpy - copies a string to anothe buffr
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - creates a copy of a string string
 * @str: the string to be duplicated
 * Return: pointer tonew duplicated string
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
 *_puts - outputs an a string to the standard output
 *@str: the string to be printed to the standard output
 * Return: void
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - writes a character c to stdout
 * @c: The character to supplied *
 * Return: 1 on success, -1, on error
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

