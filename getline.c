#include "shell.h"
/**
 * buffer - chained buffer
 * @adrs:struct parameter
 * @buff:address
 * @len:lengh
 * Return:reading size
 */
ssize_t buffer(adrs_t *adrs, char **buff, size_t *len)
{
	ssize_t num = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, handle);
#if USE_GETLINE
		num = getline(buff, &len_p, stdin);
#else
		num = get_line(adrs, buff, &len_p);
#endif
		if (num > 0)
		{
			if ((*buff)[num - 1] == '\n')
			{
				(*buff)[num - 1] = '\0';
				num--;
			}
			adrs->flag = 1;
			rem_comm(*buff);
			his_list(adrs, *buff, adrs->histcount++);
			{
				*len = num;
				adrs->cmd_buf = buff;
			}
		}
	}
	return (num);
}

/**
 * _getinput - get from the user
 * @adrs:struct parameter
 * Return:reading size
 */
ssize_t _getinput(adrs_t *adrs)
{
	static char *buff;
	static size_t k, l, length;
	ssize_t num = 0;
	char **buff_p = &(adrs->arg), *ptr;

	_putchar(-1);
	num = buffer(adrs, &buff, &length);
	if (num == -1)
		return (-1);
	if (length)
	{
		l = k;
		ptr = buff + k;

		checker(adrs, buff, &l, k, length);
		while (l < length)
		{
			if (chain_che(adrs, buff, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= length)
		{
			k = length = 0;
			adrs->cmd_buf_type = 0;
		}

		*buff_p = ptr;
		return (str_len(ptr));
	}

	*buff_p = buff;
	return (num);
}

/**
 * buffer_reader - buffer reader
 * @adrs:struct parameter
 * @buff: buffer
 * @j:numbers
 * Return:num
 */
ssize_t buffer_reader(adrs_t *adrs, char *buff, size_t *j)
{
	ssize_t num = 0;

	if (*j)
		return (0);
	num = read(adrs->fd, buff, 1024);
	if (num >= 0)
		*j = num;
	return (num);
}

/**
 * get_line - accepts input command
 * @adrs:struct parameter
 * @pt:pointer
 * @length:length
 * Return:size
 */
int get_line(adrs_t *adrs, char **pt, size_t *length)
{
	static char buff[1024];
	static size_t j, len;
	size_t i;
	ssize_t num = 0, s = 0;
	char *ptr = NULL, *new_p = NULL, *ch;

	ptr = *pt;
	if (ptr && length)
		s = *length;
	if (j == len)
		j = len = 0;

	num = buffer_reader(adrs, buff, &len);
	if (num == -1 || (num == 0 && len == 0))
		return (-1);

	ch = str_ch(buff + j, '\n');
	i = ch ? 1 + (unsigned int)(ch - buff) : len;
	new_p = re_alloc(ptr, s, s ? s + i : i + 1);
	if (!new_p)
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		strn_cat(new_p, buff + j, i - j);
	else
		strn_cpy(new_p, buff + j, i - j + 1);

	s += i - j;
	j = i;
	ptr = new_p;

	if (length)
		*length = s;
	*pt = ptr;
	return (s);
}

/**
 * handle - to avoid control c
 * @sig_num:number
 */
void handle(__attribute__((unused))int sig_num)
{
	_put("\n");
	_put("$ ");
	_putchar(-1);
}
