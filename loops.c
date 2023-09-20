#include "shell.h"
/**
 * hsh - shell
 * @adrs:struct para
 * @av:vector
 * Return: 0 or -1
 */
int hsh(adrs_t *adrs, char **av)
{
	ssize_t num = 0;
	int bu_ret = 0;

	while (num != -1 && bu_ret != -2)
	{
		delete_adrs(adrs);
		if (_active(adrs))
			_put("$ ");
		put_char(-1);
		num = _getinput(adrs);
		if (num != -1)
		{
			intialization_adrs(adrs, av);
			bu_ret = search_builtin(adrs);
			if (bu_ret == -1)
				search_command(adrs);
		}
		else if (_active(adrs))
			_putchar('\n');
		free_adrs(adrs, 0);
	}
	create_hist(adrs);
	free_adrs(adrs, 1);
	if (!_active(adrs) && adrs->status)
		exit(adrs->status);
	if (bu_ret == -2)
	{
		if (adrs->ernum == -1)
			exit(adrs->status);
		exit(adrs->ernum);
	}
	return (bu_ret);
}

/**
 * search_builtin - search
 * @adrs:struct parameter
 * Return: -1 , 1 0 or 2
 */
int search_builtin(adrs_t *adrs)
{
	int j, bui_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_hist},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (str_cmp(adrs->argv[0], builtintbl[j].type) == 0)
		{
			adrs->count++;
			bui_ret = builtintbl[j].func(adrs);
			break;
		}
	return (bui_ret);
}

/**
 * search_command - search cmd
 * @adrs:struct parameter
 */
void search_command(adrs_t *adrs)
{
	char *path = NULL;
	int j, i;

	adrs->path = adrs->argv[0];
	if (adrs->flag == 1)
	{
		adrs->count++;
		adrs->flag = 0;
	}
	for (j = 0, i = 0; adrs->arg[j]; j++)
		if (!_delimeter(adrs->arg[j], " \t\n"))
			i++;
	if (!i)
		return;

	path = _search(adrs, get_env(adrs, "PATH="), adrs->argv[0]);
	if (path)
	{
		adrs->path = path;
		split_fork(adrs);
	}
	else
	{
		if ((_active(adrs) || get_env(adrs, "PATH=")
			|| adrs->argv[0][0] == '/') && _command(adrs, adrs->argv[0]))
			split_fork(adrs);
		else if (*(adrs->arg) != '\n')
		{
			adrs->status = 127;
			display_error(adrs, "not found\n");
		}
	}
}

/**
 * split_fork - splitter
 * @adrs:parameter
 */
void split_fork(adrs_t *adrs)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(adrs->path, adrs->argv, get_environ(adrs)) == -1)
		{
			free_adrs(adrs, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(adrs->status));
		if (WIFEXITED(adrs->status))
		{
			adrs->status = WEXITSTATUS(adrs->status);
			if (adrs->status == 126)
				display_error(adrs, "Permission denied\n");
		}
	}
}
