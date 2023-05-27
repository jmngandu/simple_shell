#include "shell.h"

/**
 * my_free - frees a pointer and NULLs the address
 * @ptr: address of  pointer to be freed
 * Return: 1 if freed, else 0.
 */
int my_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
