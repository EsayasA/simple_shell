#include "shell.h"
/**
 * main - main function
 * @ac:count
 * @av:vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	adrs_t adrs[] = { ADRS_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_input(av[0]);
				print_input(": 0: Can't open ");
				print_input(av[1]);
				put_char('\n');
				put_char(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		adrs->fd = fd;
	}
	fill_list(adrs);
	display_hist(adrs);
	hsh(adrs, av);
	return (EXIT_SUCCESS);
}
