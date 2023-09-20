#include "shell.h"
/**
 * env_set - it starts a new enviroment
 * @adrs: argument string
 * @variable: variable
 * @output: the value to the variable
 * Return: zero
 */
int env_set(adrs_t *adrs, char *variable, char *output)
{
	char *buffer = NULL;
	list_t *point;
	char *h;

	if (!variable || !output)
		return (0);

	buffer = malloc(str_len(variable) + str_len(output) + 2);
	if (!buffer)
		return (1);
	str_cpy(buffer, variable);
	str_cat(buffer, "=");
	str_cat(buffer, output);
	point = adrs->env;
	while (point)
	{
		h = be_gin(point->str, variable);
		if (h && *h == '=')
		{
			free(point->str);
			point->str = buffer;
			adrs->newf = 1;
			return (0);
		}
		point = point->next;
	}
	add_node(&(adrs->env), buffer, 0);
	free(buffer);
	adrs->newf = 1;
	return (0);
}
/**
 * get_environ - it gives the array string
 * @adrs: argument string
 * Return: zero
 */
char **get_environ(adrs_t *adrs)
{
	if (!adrs->environ || adrs->newf)
	{
		adrs->environ = display_for_str(adrs->env);
		adrs->newf = 0;
	}

	return (adrs->environ);
}

/**
 * env_unset - deletes the variable
 * @adrs: argument string
 * @variable:variable
 * Return: 0 if not 1 if it removes
 */
int env_unset(adrs_t *adrs, char *variable)
{
	list_t *point = adrs->env;
	size_t j = 0;
	char *h;

	if (!point || !variable)
		return (0);

	while (point)
	{
		h = be_gin(point->str, variable);
		if (h && *h == '=')
		{
			adrs->newf = del_indx(&(adrs->env), j);
			j = 0;
			point = adrs->env;
			continue;
		}
		point = point->next;
		j++;
	}
	return (adrs->newf);
}
