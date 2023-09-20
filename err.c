#include "shell.h"
/**
 * print_char - prints character
 * @s:string
 * @fd:filedescriptor
 * Return:number of char
 */
int print_char(char *s, int fd)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += write_char(*s++, fd);
	}
	return (j);
}
/**
 * put_char - puts character
 * @ch:character
 * Return:1 if successful
 */
int put_char(char ch)
{
	static int j;
	static char buff[1024];

	if (ch == -1 || j >= 1024)
	{
		write(2, buff, j);
		j = 0;
	}
	if (ch != -1)
		buff[j++] = ch;
	return (1);
}
/**
 * print_input - print input
 * @s:string
 */
void print_input(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		put_char(s[j]);
		j++;
	}
}
/**
 * write_char - writes character
 * @ch:character
 * @fd:filedescriptor
 * Return: On success 1
 */
int write_char(char ch, int fd)
{
	static int j;
	static char buff[1024];

	if (ch == -1 || j >= 1024)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (ch != -1)
		buff[j++] = ch;
	return (1);
}
