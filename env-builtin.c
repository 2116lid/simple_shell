#include "main.h"

/**
 * new_env - a function to print the current environment.
 * @addres: structure of arguments.
 * Return: 0 on succssess.
 */
int new_env(addres_t *addres)
{
	str_only(addres->env);
	return (0);
}

/**
 * new_getenv - a function to get the value of environ.
 * @addres: Structure containing potential arguments.
 * @envna: the name for environ.
 *
 * Return: NULL on succssess and pointer on failure.
 */
char *new_getenv(addres_t *addres, const char *envna)
{
	list_t *node;
	char *ptr;

	node = addres->env;

	while (node)
	{
		ptr = see_string(node->str, envna);
		if (ptr != NULL)
		{
			if (*ptr != 0)
			{
				return (ptr);
			}
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * new_setenv - a function  to create a new environment,
 * or modify an existing one.
 * @addres: Structure of arguments.
 *
 * Return: 0 on sucssess, 1 on failure.
 */
int new_setenv(addres_t *addres)
{
	if (addres->argc != 3)
	{
		cust_puts("Please make sure the number of your arguments is correct.\n");
		return (1);
	}
	if (_setenv(addres, addres->argv[1], addres->argv[2]))
		return (0);
	return (1);
}

/**
 * new_unsetenv - a function to remove the environment.
 * @addres: structure of arguments.
 *
 * Return: 0 on sucssess, 1 on failure.
 */
int new_unsetenv(addres_t *addres)
{
	int i;

	if (addres->argc == 1)
	{
		cust_puts("Please make sure the number of your arguments is correct.\n");
		return (1);
	}
	for (i = 1; i <= addres->argc; i++)
		_unsetenv(addres, addres->argv[i]);

	return (0);
}

/**
 * _env_list - a function that populates the env single linked list.
 * @addres: structure of arguments.
 * Return: 0 on sucssess and Nothing on failure.
 */
int _env_list(addres_t *addres)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_endnode(&node, environ[i], 0);
	addres->env = node;
	return (0);
}
