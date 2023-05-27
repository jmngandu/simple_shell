#include "shell.h"

/**
 * err_atoi - converts a given string to  int
 * @s: string to convert
 * Return: converted number
 *       -1 on error
 */
int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints an err msg
 * @info: info struct
 * @errstr: string containing  error type
 * Return: 0 if no nums, converted num else
 *        -1 on error
 */
void print_err(info_t *info, char *errstr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_dec - function prints a (integer) / base 10
 * @input: the input enteres
 * @fd: the filedescriptor
 * Return: num of chars printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, j = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		j++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			j++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	j++;

	return (j);
}

/**
 * convert_num - my own itoa
 * @num: the number to be converted
 * @base: base value
 * @flags: arguments flags
 * Return: a string on success
 */
char *convert_num(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * change_comments - changes first instance of '#' with '\0'
 * @buff: address of the string to change
 * Return:  0;
 */
void change_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

