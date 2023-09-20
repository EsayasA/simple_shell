#include "shell.h"
/**
 * _listf - to free
 * @ptr:pointer
 * Return:void
 */
void _listf(list_t **ptr)
{
	list_t *n, *next_node, *hd;

	if (!ptr || !*ptr)
		return;
	hd = *ptr;
	n = hd;
	while (n)
	{
		next_node = n->next;
		free(n->str);
		free(n);
		n = next_node;
	}
	*ptr = NULL;
}
/**
 * rah_esu - to add node
 * @hd:head
 * @s:string
 * @n:number
 * Return:size
 */
list_t *rah_esu(list_t **hd, const char *s, int n)
{
	list_t *new_head;

	if (!hd)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	my_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = n;
	if (s)
	{
		new_head->str = str_dup(s);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *hd;
	*hd = new_head;
	return (new_head);
}
/**
 * del_indx - delete
 * @hd:pointer
 * @indx:index
 * Return: 1 on success, 0 on failure
 */
int del_indx(list_t **hd, unsigned int indx)
{
	list_t *n, *prev_node;
	unsigned int j = 0;

	if (!hd || !*hd)
		return (0);

	if (!indx)
	{
		n = *hd;
		*hd = (*hd)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *hd;
	while (n)
	{
		if (j == indx)
		{
			prev_node->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		j++;
		prev_node = n;
		n = n->next;
	}
	return (0);
}
/**
 * add_node - add
 * @head:address
 * @s:string
 * @num:num
 * Return:size
 */
list_t *add_node(list_t **head, const char *s, int num)
{
	list_t *new_node, *n;

	if (!head)
		return (NULL);

	n = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	my_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (s)
	{
		new_node->str = str_dup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * display_str - print linked list
 * @hd:pointer
 * Return:size
 */
size_t display_str(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		_put(hd->str ? hd->str : "(nil)");
		_put("\n");
		hd = hd->next;
		j++;
	}
	return (j);
}

