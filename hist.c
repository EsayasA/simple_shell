#include "shell.h"
/**
 * renew_hist - renew
 * @adrs:struct para
 * Return:counted
 */
int renew_hist(adrs_t *adrs)
{
	list_t *node = adrs->hist;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (adrs->histcount = j);
}
/**
 * print_history - from file
 * @adrs:struct para
 * Return:file
 */
char *print_history(adrs_t *adrs)
{
	char *buff, *dir;

	dir = get_env(adrs, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(dir) + str_len(HF) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, dir);
	str_cat(buff, "/");
	str_cat(buff, HF);
	return (buff);
}
/**
 * display_hist - reads history
 * @adrs:struct para
 * Return:count if success
 */
int display_hist(adrs_t *adrs)
{
	int j, ls = 0, coun = 0;
	ssize_t d, rlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fn = print_history(adrs);

	if (!fn)
		return (0);

	d = open(fn, O_RDONLY);
	free(fn);
	if (d == -1)
		return (0);
	if (!fstat(d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rlen = read(d, buff, fsize);
	buff[fsize] = 0;
	if (rlen <= 0)
		return (free(buff), 0);
	close(d);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			his_list(adrs, buff + ls, coun++);
			ls = j + 1;
		}
	if (ls != j)
		his_list(adrs, buff + ls, coun++);
	free(buff);
	adrs->histcount = coun;
	while (adrs->histcount-- >= 4096)
		del_indx(&(adrs->hist), 0);
	renew_hist(adrs);
	return (adrs->histcount);
}
/**
 * his_list - to nw one
 * @adrs:struct parsameter
 * @buff:buffer
 * @linecount:count
 * Return:0
 */
int his_list(adrs_t *adrs, char *buff, int linecount)
{
	list_t *n = NULL;

	if (adrs->hist)
		n = adrs->hist;
	add_node(&n, buff, linecount);

	if (!adrs->hist)
		adrs->hist = n;
	return (0);
}
/**
 * create_hist - file
 * @adrs:struct para
 * Return:1 or -1
 */
int create_hist(adrs_t *adrs)
{
	ssize_t d;
	char *fn = print_history(adrs);
	list_t *n = NULL;

	if (!fn)
		return (-1);

	d = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (d == -1)
		return (-1);
	for (n = adrs->hist; n; n = n->next)
	{
		print_char(n->str, d);
		write_char('\n', d);
	}
	write_char(-1, d);
	close(d);
	return (1);
}
