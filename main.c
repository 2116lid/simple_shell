#include "main.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	addres_t addres[] = { ADDRES_INIT };
	int fd = 2;

	fd = fd + 3;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				cust_puts(av[0]);
				cust_puts(": 0: Can't open ");
				cust_puts(av[1]);
				cust_putchar('\n');
				cust_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		addres->readfd = fd;
	}
	_env_list(addres);
	_histR(addres);
	shmain(addres, av);
	return (EXIT_SUCCESS);
}
