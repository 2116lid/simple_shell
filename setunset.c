#include "main.h"

/**
 * cpy_environ - a function that returns the string
 * array copy of our environ.
 * @addres: structure of arguments.
 *
 * Return: 0 on succssess.
 */
char **cpy_environ(addres_t *addres)
{
	if (!addres->environ || addres->chd_env)
	{
		addres->environ = _to_string(addres->env);
		addres->chd_env = 0;
	}

	return (addres->environ);
}

/**
 * _unsetenv - a function that removes an environment variable.
 * @addres: structure of arguments.
 * @variable: the string env var property.
 * Return: 1 on succssess, 0 on failure.
 *
 */
int _unsetenv(addres_t *addres, char *variable)
{
	list_t *node;
	size_t i;
	char *p;

	if (!addres || !variable || !addres->env)
		return (0);

	for (i = 0, node = addres->env; node != NULL; i++, node = node->next)
	{
		p = see_string(node->str, variable);
		if (p && *p == '=')
		{
			addres->chd_env = delete_node(&(addres->env), i);
			i = 0;
			node = addres->env;
		}
	}
	return (addres->chd_env);
}

/**
 * _setenv - a function to Initialize a new environment variable.
 * @addres: Structure of arguments.
 *
 * @variable: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(addres_t *addres, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (buf == NULL)
		return (1);
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = addres->env;
	while (node)
	{
		p = see_string(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			addres->chd_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_endnode(&(addres->env), buf, 0);
	free(buf);
	addres->chd_env = 1;
	return (0);
}
