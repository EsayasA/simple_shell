#include "shell.h"
/**
 * my_cd - change dir
 * @adrs:struct para
 * Return: Always 0
 */
int my_cd(adrs_t *adrs)
{
	char *str, *dir, buff[1024];
	int chdir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_put("TODO: >>getcwd failure emsg here<<\n");
	if (!adrs->argv[1])
	{
		dir = get_env(adrs, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env(adrs, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(adrs->argv[1], "-") == 0)
	{
		if (!get_env(adrs, "OLDPWD="))
		{
			_put(str);
			_putchar('\n');
			return (1);
		}
		_put(get_env(adrs, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(adrs, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(adrs->argv[1]);
	if (chdir_ret == -1)
	{
		display_error(adrs, "can't cd to ");
		print_input(adrs->argv[1]), put_char('\n');
	}
	else
	{
		env_set(adrs, "OLDPWD", get_env(adrs, "PWD="));
		env_set(adrs, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
/**
 * my_exit - exit command
 * @adrs:struct parameter
 * Return:1 or -2
 */
int my_exit(adrs_t *adrs)
{
	int check;

	if (adrs->argv[1])
	{
		check = error_atoi(adrs->argv[1]);
		if (check == -1)
		{
			adrs->status = 2;
			display_error(adrs, "Illegal number: ");
			print_input(adrs->argv[1]);
			put_char('\n');
			return (1);
		}
		adrs->ernum = error_atoi(adrs->argv[1]);
		return (-2);
	}
	adrs->ernum = -1;
	return (-2);
}
/**
 * my_help - to change directory
 * @adrs:struct para
 * Return:Always 0
 */
int my_help(adrs_t *adrs)
{
	char **arg_array;

	arg_array = adrs->argv;
	_put("help call works. Function not yet implemented \n");
	if (0)
		_put(*arg_array);
	return (0);
}

