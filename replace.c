#include "shell.h"
/**
 * strpl - string replacing
 * @old_size: old string adrsess
 * @new_size: adresses of new string
 * Return:0 if not 1 if replaced
 */
int strpl(char **old_size, char *new_size)
{
	free(*old_size);
	*old_size = new_size;
	return (1);
}
/**
 * chain_che - it checks if the delimeter is chain
 * @adrs: arguement string
 * @buffer: the buffer charchter
 * @h: position current
 * Return: 0 if not 1 if chain
 */
int chain_che(adrs_t *adrs, char *buffer, size_t *h)
{
	size_t i = *h;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		adrs->cmd_buf_type = 1;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		adrs->cmd_buf_type = 2;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		adrs->cmd_buf_type = 3;
	}
	else
		return (0);
	*h = i;
	return (1);
}
/**
 * token_var - var replacing
 * @adrs: arguement structure
 * Return:  0 if not 1 if replaced
 */
int token_var(adrs_t *adrs)
{
	int j = 0;
	list_t *point;

	for (j = 0; adrs->argv[j]; j++)
	{
		if (adrs->argv[j][0] != '$' || !adrs->argv[j][1])
			continue;

		if (!str_cmp(adrs->argv[j], "$?"))
		{
			strpl(&(adrs->argv[j]),
				str_dup(conv_num(adrs->status, 10, 0)));
			continue;
		}
		if (!str_cmp(adrs->argv[j], "$$"))
		{
			strpl(&(adrs->argv[j]),
				str_dup(conv_num(getpid(), 10, 0)));
			continue;
		}
		point = start_indx(adrs->env, &adrs->argv[j][1], '=');
		if (point)
		{
			strpl(&(adrs->argv[j]),
				str_dup(str_ch(point->str, '=') + 1));
			continue;
		}
		strpl(&adrs->argv[j], str_dup(""));

	}
	return (0);
}
/**
 * checker - it checks if we continue or stop
 * @adrs: arguement string
 * @buffer: buffer
 * @h: current position adress
 * @j: position starting
 * @length: buffers length
 * Return: Void
 */
void checker(adrs_t *adrs, char *buffer, size_t *h, size_t j, size_t length)
{
	size_t k = *h;

	if (adrs->cmd_buf_type == 2)
	{
		if (adrs->status)
		{
			buffer[j] = 0;
			k = length;
		}
	}
	if (adrs->cmd_buf_type == 1)
	{
		if (!adrs->status)
		{
			buffer[j] = 0;
			k = length;
		}
	}

	*h = k;
}

/**
 * token_replace - replaces string tokenized
 * @adrs: argument string
 * Return: 0 if not 1 if replaced
 */
int token_replace(adrs_t *adrs)
{
	int j;
	list_t *point;
	char *h;

	for (j = 0; j < 10; j++)
	{
		point = start_indx(adrs->alias, adrs->argv[0], '=');
		if (!point)
			return (0);
		free(adrs->argv[0]);
		h = str_ch(point->str, '=');
		if (!h)
			return (0);
		h = str_dup(h + 1);
		if (!h)
			return (0);
		adrs->argv[0] = h;
	}
	return (1);
}
