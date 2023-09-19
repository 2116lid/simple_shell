#include "main.h"

/**
 * com_nd - changes the current working directory
 * @addres: pointer to struct containing environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int com_nd(addres_t *addres)
{
	char *s, *directory, buffer[1024];
	int chret;

	s = getcwd(buffer, 1024);
	if (s == NULL)
		_puts("Error: command failed\n");
	if (addres->argv[1] == NULL)
	{
		directory = new_getenv(addres, "HOME=");
		if (directory == NULL)
			chret = dir_null(addres);
		else
			chret = chdir(directory);
	}
	else if (_strcmp(addres->argv[1], "-") == 0)
		chret = handle_dash(addres, s);
	else
		chret = chdir(addres->argv[1]);
	if (chret == -1)
		err_chdir(addres);
	else
		env_uptodate(addres, buffer);
	return (0);
}

/**
 * dir_null - a function to handle directory is NULL
 * @addres: pointer to struct containing environment variables
 *
 * Return: result of chdir call
 */
int dir_null(addres_t *addres)
{
	char *directory;

	directory = new_getenv(addres, "PWD=");
	if (directory != NULL)
		return (chdir(directory));
	else
		return (chdir("/"));
}

/**
 * handle_dash - a function to handle argument if "-".
 * @addres: pointer to struct containing environment variables
 * @s: current working directory
 *
 * Return: result of chdir call
 */
int handle_dash(addres_t *addres, char *s)
{
	char *directory;

	if (new_getenv(addres, "OLDPWD=") == NULL)
	{
		_puts(s);
		_putchar('\n');
		return (1);
	}
	else
	{
		directory = new_getenv(addres, "OLDPWD=");
		_puts(directory);
		_putchar('\n');
		if (directory != NULL)
			return (chdir(directory));
		else
			return (chdir("/"));
	}
}

/**
 * err_chdir - a function to handle error from chdir call
 * @addres: pointer to struct containing environment variables
 * Return: Nothing.
 */
void err_chdir(addres_t *addres)
{
	err_msg(addres, "Directory change failed ");
	cust_puts(addres->argv[1]), cust_putchar('\n');
}

/**
 * env_uptodate - a function that updates environment variables.
 * @addres: pointer to struct containing environment variables
 * @buffer: buffer for getcwd call.
 * Return: Nothing.
 *
 */
void env_uptodate(addres_t *addres, char buffer[1024])
{
	_setenv(addres, "OLDPWD", new_getenv(addres, "PWD="));
	_setenv(addres, "PWD", getcwd(buffer, 1024));
}
