#include "main.h"

/**
 * new_exit - a function to exit our shell.
 * @addres: Structure of arguments.
 * Return: 1 on succssess and -2 on failure.
 */
int new_exit(addres_t *addres)
{
	int check_ex;

	if (addres->argv[1] == NULL)
	{
		addres->error_cod = -1;
		return (-2);
	}

	check_ex = _newatoi(addres->argv[1]);

	if (check_ex == -1)
	{
		addres->sta = 2;
		err_msg(addres, "not valid number: ");
		cust_puts(addres->argv[1]);
		cust_putchar('\n');
		return (1);
	}

	addres->error_cod = check_ex;
	return (-2);
}

/**
 * new_help - a function to change the current directory of the process.
 * @addres: Struct.
 * Return: 0 on succssess.
 */
int new_help(addres_t *addres)
{
	char **_argar;

	_argar = addres->argv;
	_puts("Is your function implemented? ,BUT help call is working\n");
	if (0)
		_puts(*_argar);
	return (0);
}
