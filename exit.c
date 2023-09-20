#include "shell.h"
/**
 *str_ch - it finds character in string
 *@str: string
 *@d: it arguement char
 *Return: char in the string
 */
char *str_ch(char *str, char d)
{
	do {
		if (*str == d)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
/**
 *strn_cpy - string copy
 *@d: destination
 *@s: source
 *@n: number of character
 *Return:concatenation value
 */
char *strn_cpy(char *d, char *s, int n)
{
	int j, k;
	char *str = d;

	j = 0;
	while (s[j] != '\0' && j < n - 1)
	{
		d[j] = s[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			d[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 *strn_cat - string concatnation
 *@d: destination
 *@s: source
 *@n: numbers of integers
 *Return: the concatenated result
 */
char *strn_cat(char *d, char *s, int n)
{
	int j, k;
	char *str = d;

	j = 0;
	k = 0;
	while (d[j] != '\0')
		j++;
	while (s[k] != '\0' && k < n)
	{
		d[j] = s[k];
		j++;
		k++;
	}
	if (k < n)
		d[j] = '\0';
	return (str);
}

