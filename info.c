#include "shell.h"
/**
 * free_adrs - it gives freedom to the field
 * @adrs: struct arguement structure
 * @var: freeeing the field
 */
void free_adrs(adrs_t *adrs, int var)
{
	_free(adrs->argv);
	adrs->argv = NULL;
	adrs->path = NULL;
	if (var)
	{
		if (!adrs->cmd_buf)
			free(adrs->arg);
		if (adrs->env)
			_listf(&(adrs->env));
		if (adrs->hist)
			_listf(&(adrs->hist));
		if (adrs->alias)
			_listf(&(adrs->alias));
		_free(adrs->environ);
			adrs->environ = NULL;
		buffer_free((void **)adrs->cmd_buf);
		if (adrs->fd > 2)
			close(adrs->fd);
		_putchar(-1);
	}
}
/**
 * delete_adrs - it delete the strucure
 * @adrs: argument string
 */
void delete_adrs(adrs_t *adrs)
{
	adrs->arg = NULL;
	adrs->argv = NULL;
	adrs->path = NULL;
	adrs->argc = 0;
}

/**
 * intialization_adrs - it starts the structure
 * @adrs: arguement string
 * @p: vector arguement
 */
void intialization_adrs(adrs_t *adrs, char **p)
{
	int j = 0;

	adrs->name = p[0];
	if (adrs->arg)
	{
		adrs->argv = split_str(adrs->arg, " \t");
		if (!adrs->argv)
		{

			adrs->argv = malloc(sizeof(char *) * 2);
			if (adrs->argv)
			{
				adrs->argv[0] = str_dup(adrs->arg);
				adrs->argv[1] = NULL;
			}
		}
		for (j = 0; adrs->argv && adrs->argv[j]; j++)
			;
		adrs->argc = j;

		token_replace(adrs);
		token_var(adrs);
	}
}
