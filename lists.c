#include "shell.h"
/**
 * add_node - adds a node at the beginning
 * @head: address of pointer to  the head node
 * @str: str's field of a node
 * @num: index os node used  *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newHead;

	if (!head)
		return (NULL);
	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = num;
	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * ins_node_end - inserts a node to the end of a list
 * @head: address of a pointer to the head node
 * @str: str's node field
 * @num: index of the node
 * Return: list's size
 */
list_t *ins_node_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * print_list_str - prints str elements of list_t linked list
 * @h: pointer to start node
 * Return: list's node
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_node_at_index - deletes node at a given index
 * @head: address of pointer to first node
 * @index: index of node to be deleted *
 * Return: on success 1, on failure 0
 */
int del_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeLists - frees all lists
 * @head_ptr: pointer to head node
 * Return: void
 */
void freeLists(list_t **head_ptr)
{
	list_t *node, *nxt_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*head_ptr = NULL;
}
