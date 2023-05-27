#include "shell.h"

/**
 * _strlen - finds the no. of chars in a string
 * @s: the string to check
 * Return: number of characters in string
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - compares two strangs.
 * @s1: first string to compare
 * @s2: 2nd string to compare
 *
 * Return: -1 if s1 < s2, 1 if s1 > s2, 0 if s1 is same as s2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_ - checks whther a needle begins with haystack
 * @hay_stack: string to be searched
 * @needle: the substring to be searched 
 * Return: address to the next char of haystack or NULL
 */
char *starts_(const char *hay_stack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * _strcat - concatenates two supplied strings
 * @dest: the destination memory
 * @src: the source memory
 * Return: pointer to the destination memory
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
