#include "shell.h"
/**
 * at_oi - it changes from alphabet to integer
 * @str: the given string
 * Return: 1 if it changes or 0 if not
 */
int at_oi(char *str)
{
	int j, f = 0, sign = 1, result;
	unsigned int value = 0;

	for (j = 0;  str[j] != '\0' && f != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			f = 1;
			value *= 10;
			value += (str[j] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		result = -value;
	else
		result = value;

	return (result);
}
/**
 * _active - it checks if the mode is interactive or not
 * @adrs: argument string
 * Return: 0 if it not 1 if interactive
 */
int _active(adrs_t *adrs)
{
	return (isatty(STDIN_FILENO) && adrs->fd <= 2);
}
/**
 * _alphabet - it checks weather it is alphabet or not
 * @d: the input character
 * Return: 1 if it is or if not
 */
int _alphabet(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _delimeter - check the charif is delimeter
 * @d: char t check if it is delimeter
 * @dm: it is the given string
 * Return: 1 if it is 0 if not
 */
int _delimeter(char d, char *dm)
{
	while (*dm)
		if (*dm++ == d)
			return (1);
	return (0);
}
