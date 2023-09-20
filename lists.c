#include "shell.h"
/**
 * get_indx - get index
 * @hd:address
 * @n:pointer
 * Return:index
 */
ssize_t get_indx(list_t *hd, list_t *n)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == n)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}
/**
 * ptr_ls - print
 * @hd:pointer
 * Return:size
 */
size_t ptr_ls(const list_t *hd)
{
	size_t j = 0;

	while (hd)
	{
		_put(conv_num(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_put(hd->str ? hd->str : "(nil)");
		_put("\n");
		hd = hd->next;
		j++;
	}
	return (j);
}
/**
 * list_len - length
 * @ptr:pointer
 * Return:size
 */
size_t list_len(const list_t *ptr)
{
	size_t j = 0;

	while (ptr)
	{
		ptr = ptr->next;
		j++;
	}
	return (j);
}
/**
 * display_for_str - print
 * @hd:pointer
 * Return:string
 */
char **display_for_str(list_t *hd)
{
	list_t *n = hd;
	size_t j = list_len(hd), k;
	char **str;
	char *s;

	if (!hd || !j)
		return (NULL);
	str = malloc(sizeof(char *) * (j + 1));
	if (!str)
		return (NULL);
	for (j = 0; n; n = n->next, j++)
	{
		s = malloc(str_len(n->str) + 1);
		if (!s)
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}

		s = str_cpy(s, n->str);
		str[j] = s;
	}
	str[j] = NULL;
	return (str);
}
/**
 * start_indx - start
 * @n:pointer
 * @pre:as checker
 * @ch:character
 * Return:null
 */
list_t *start_indx(list_t *n, char *pre, char ch)
{
	char *ptr = NULL;

	while (n)
	{
		ptr = be_gin(n->str, pre);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (n);
		n = n->next;
	}
	return (NULL);
}


