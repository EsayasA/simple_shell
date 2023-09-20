#include "shell.h"
/**
 * _search - it searches the path in string
 * @adrs: argument string
 * @patht: path
 * @command: command finder
 * Return: NULL or path of the string
 */
char *_search(adrs_t *adrs, char *patht, char *command)
{
	int j = 0, current = 0;
	char *path;

	if (!patht)
		return (NULL);
	if ((str_len(command) > 2) && be_gin(command, "./"))
	{
		if (_command(adrs, command))
			return (command);
	}
	while (1)
	{
		if (!patht[j] || patht[j] == ':')
		{
			path = _duplicate(patht, current, j);
			if (!*path)
				str_cat(path, command);
			else
			{
				str_cat(path, "/");
				str_cat(path, command);
			}
			if (_command(adrs, path))
				return (path);
			if (!patht[j])
				break;
			current = j;
		}
		j++;
	}
	return (NULL);
}
/**
 * _command - is executable command
 * @adrs: argument string
 * @path: it gives files path
 * Return: 0if not found 1 if the path found
 */
int _command(adrs_t *adrs, char *path)
{
	struct stat st;

	(void)adrs;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _duplicate - it is character duplication
 * @path: string path
 * @s: it is point starter
 * @end: final point
 * Return: pointer to the buffer
 */
char *_duplicate(char *path, int s, int end)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = s; i < end; i++)
		if (path[i] != ':')
			buffer[j++] = path[i];
	buffer[j] = 0;
	return (buffer);
}
