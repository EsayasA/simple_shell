#include "shell.h"
/**
 * str_cat - concatnation of strings
 * @d: destination
 * @s: buffer source
 * Return: ptr buffer
 */
char *str_cat(char *d, char *s)
{
	char *val = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (val);
}
/**
 * str_len - it gives len
 * @str: is string
 * Return: j
 */
int str_len(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}
/**
 * be_gin - it checks if the n and h
 * @h: search string
 * @n: it is substring
 * Return:  NULL or address
 */
char *be_gin(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}
/**
 * str_cmp - it compares two strings.
 * @str1: string1
 * @str2: string2
 * Return: negative if str1 < str2,
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}


