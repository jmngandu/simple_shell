#include "shell.h"
/**
 **_memset - stores in a memory a constant byte
 *@s: pointer to the memory 
 *@b: byte to fill a string with
 *@n: amt of bytes to be filled
 *Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * sfree - frees a string of strings
 * @ps: string of strings
 */
void sfree(char **ps)
{
	char **a = ps;

	if (!ps)
		return;
	while (*ps)
		free(*ps++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc allocated block
 * @prev_size: byte size of prev block
 * @new_size: byte size of the new block
 * Return: pointer to old memory.
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}

