#include "shell.h"

/**
 **str_cpy - copies a string to another buffer
 *@dest: the destination string
 *@src: the source string
 *@n: the num of char to be copied
 *Return: concatenated string
 */
char *str_cpy(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 **str_cat - concatenates  strings
 *@dest: first string
 *@src: second string
 *@n: the num of chars  used
 *Return: the concatenated string
 */
char *str_cat(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (str);
}

/**
 **str_chr - finds a character in a string
 *@str: the string to be passed
 *@ch: the character to be searched
 *Return: (s) a pointer to  s
 */
char *str_chr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
