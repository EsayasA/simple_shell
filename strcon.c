#include "shell.h"
/**
 * _putchar - print the standard output
 * @d: The char to display
 * Return: 1 sucess-1 error errno set proply.
 */
int _putchar(char d)
{
	static int j;
	static char buffer[1024];

	if (d == -1 || j >= 1024)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (d != -1)
		buffer[j++] = d;
	return (1);
}
/**
 * str_cpy - string copying
 * @d: destination
 * @s: source
 * Return:destination
 */
char *str_cpy(char *d, char *s)
{
	int j = 0;

	if (d == s || s == 0)
		return (d);
	while (s[j])
	{
		d[j] = s[j];
		j++;
	}
	d[j] = 0;
	return (d);
}
/**
 *_put - display string input
 *@s: string to display
 * Return: None
 */
void _put(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}
/**
 * str_dup - dupplicatin string
 * @s: string to duplicate
 * Return: ptr to string
 */
char *str_dup(const char *s)
{
	int len = 0;
	char *val;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	val = malloc(sizeof(char) * (len + 1));
	if (!val)
		return (NULL);
	for (len++; len--;)
		val[len] = *--s;
	return (val);
}
