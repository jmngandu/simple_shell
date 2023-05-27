#include "shell.h"

/**
 * is_interactive - returns true when shell is on interactive mode
 * @info: struct address
 * Return: 1 when on interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks whether a char is a delimeter
 * @ch: char to check
 * @delim: the delimeter
 * Return: 1 on true, 0 on false
 */
int is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - checks whether acharacter is an alphabet
 *@ch: character to check
 *Return: 1 if alphabetic, 0 if not
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number
 */

int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

