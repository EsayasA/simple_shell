#include "shell.h"
/**
 * fill_list - fill linked list
 * @adrs:parameter
 * Return:0
 */
int fill_list(adrs_t *adrs)
{
	list_t *n = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node(&n, environ[j], 0);
	adrs->env = n;
	return (0);
}
/**
 * get_env - bring the environ var
 * @adrs:struct para
 * @n:name
 * Return:value
 */
char *get_env(adrs_t *adrs, const char *n)
{
	list_t *no = adrs->env;
	char *ptr;

	while (no)
	{
		ptr = be_gin(no->str, n);
		if (ptr && *ptr)
			return (ptr);
		no = no->next;
	}
	return (NULL);
}

/**
 * my_setenv - initializer
 * @adrs:struct parameter
 * Return:0
 */
int my_setenv(adrs_t *adrs)
{
	if (adrs->argc != 3)
	{
		print_input("Incorrect number of arguements\n");
		return (1);
	}
	if (env_set(adrs, adrs->argv[1], adrs->argv[2]))
		return (0);
	return (1);
}
/**
 * my_env - to print
 * @adrs:struct para
 * Return:0
 */
int my_env(adrs_t *adrs)
{
	display_str(adrs->env);
	return (0);
}
/**
 * my_unsetenv - to remove
 * @adrs:struct parameter
 * Return:0
 */
int my_unsetenv(adrs_t *adrs)
{
	int j;

	if (adrs->argc == 1)
	{
		print_input("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= adrs->argc; j++)
		env_unset(adrs, adrs->argv[j]);

	return (0);
}

