#include "shell.h"

/**
 * my_hist - show all lists
 * @adrs:struct parameter
 * Return:0
 */
int my_hist(adrs_t *adrs)
{
	ptr_ls(adrs->hist);
	return (0);
}

/**
 * unset_alias - unset alias
 * @adrs:struct parameter
 * @s:string
 * Return:0 on success
 */
int unset_alias(adrs_t *adrs, char *s)
{
	char *ptr, ch;
	int res;

	ptr = str_ch(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	res = del_indx(&(adrs->alias),
		get_indx(adrs->alias, start_indx(adrs->alias, s, -1)));
	*ptr = ch;
	return (res);
}

/**
 * alias_set - set alias
 * @adrs:struct parameter
 * @s:string
 * Return:0 on success
 */
int alias_set(adrs_t *adrs, char *s)
{
	char *ptr;

	ptr = str_ch(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(adrs, s));

	unset_alias(adrs, s);
	return (add_node(&(adrs->alias), s, 0) == NULL);
}

/**
 * list_alias - to print
 * @n:node
 * Return:0 on success
 */
int list_alias(list_t *n)
{
	char *ptr = NULL, *a = NULL;

	if (n)
	{
		ptr = str_ch(n->str, '=');
		for (a = n->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_put(ptr + 1);
		_put("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - the alias
 * @adrs:struct parameter
 *  Return:0 always
 */
int my_alias(adrs_t *adrs)
{
	int j = 0;
	char *ptr = NULL;
	list_t *n = NULL;

	if (adrs->argc == 1)
	{
		n = adrs->alias;
		while (n)
		{
			list_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (j = 1; adrs->argv[j]; j++)
	{
		ptr = str_ch(adrs->argv[j], '=');
		if (ptr)
			alias_set(adrs, adrs->argv[j]);
		else
			list_alias(start_indx(adrs->alias, adrs->argv[j], '='));
	}

	return (0);
}
