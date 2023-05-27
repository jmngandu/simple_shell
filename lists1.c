#include "shell.h"

/**
 * lists_len - finds length of a linked list
 * @h: address to the pointer to first node
 * Return: list's size
 */
size_t lists_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_of_strings - returns an array of strings of a lis
 * @head: address to the pointer to first node
 * Return: an array of strings
 */
char **list_of_strings(list_t *head)
{
	list_t *node = head;
	size_t i = lists_len(head), j;
	char **strs;
	char *s;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_strlen(node->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		s = _strcpy(s, node->str);
		strs[i] = s;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList - prints all elements of a linked list
 * @h: address to the pointer to first node
 * Return: list's szie
 */
size_t printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_ - returns node whose string starts with a givenprefix
 * @node: addresspointer to list head
 * @prefix: string to get
 * @c: the characte after prefix to find
 * Return: match node
 */
list_t *node_starts_(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a certain node
 * @head: adresspointer to list head
 * @node: adress topointer to the node
  * Return:nodes index or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

