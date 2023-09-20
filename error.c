#include "shell.h"
/**
 * display_error - displays error msg
 * @adrs:struct parameter
 * @s:string
 * Return:0 on success or  -1 on error
 */
void display_error(adrs_t *adrs, char *s)
{
	print_input(adrs->name);
	print_input(": ");
	display_decimal(adrs->count, STDERR_FILENO);
	print_input(": ");
	print_input(adrs->argv[0]);
	print_input(": ");
	print_input(s);
}
/**
 * rem_comm - use to remove s[ecial character
 * @buff:pointer to string
 * Return:0;
 */
void rem_comm(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
/**
 * display_decimal - displays in decimal form
 * @inpt:input
 * @fd:filedescriptor
 * Return:character bezhi
 */
int display_decimal(int inpt, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, coun = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = put_char;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__putchar('-');
		coun++;
	}
	else
		_abs_ = inpt;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + curr / j);
			coun++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	coun++;

	return (coun);
}
/**
 * error_atoi - string to integer
 * @str:string
 * Return:res
 */
int error_atoi(char *str)
{
	int j = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			res *= 10;
			res += (str[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 * conv_num - convert number
 * @num:the number
 * @b:any base
 * @f:controller
 * Return:converted string
 */
char *conv_num(long int num, int b, int f)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(f & 2) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = f & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

