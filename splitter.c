#include "shell.h"
/**
 * split_str2 - string splitter
 * @s: string
 * @dm: delimeter
 * Return: a pointer
 */
char **split_str2(char *s, char dm)
{
	int i, j, k, n, number = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != dm && s[i + 1] == dm) ||
		    (s[i] != dm && !s[i + 1]) || s[i + 1] == dm)
			number++;
	if (number == 0)
		return (NULL);
	str = malloc((1 + number) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < number; j++)
	{
		while (s[i] == dm && s[i] != dm)
			i++;
		k = 0;
		while (s[i + k] != dm && s[i + k] && s[i + k] != dm)
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			str[j][n] = s[i++];
		str[j][n] = 0;
	}
	str[j] = NULL;
	return (str);
}
/**
 * split_str - string spliter with delimiter
 * @s: string
 * @dm:delimeter
 * Return: a ptr
 */

char **split_str(char *s, char *dm)
{
	int i, j, k, n, number = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!dm)
		dm = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!_delimeter(s[i], dm) && (_delimeter(s[i + 1], dm) || !s[i + 1]))
			number++;

	if (number == 0)
		return (NULL);
	str = malloc((1 + number) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < number; j++)
	{
		while (_delimeter(s[i], dm))
			i++;
		k = 0;
		while (!_delimeter(s[i + k], dm) && s[i + k])
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			str[j][n] = s[i++];
		str[j][n] = 0;
	}
	str[j] = NULL;
	return (str);
}
