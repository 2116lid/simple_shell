#include "main.h"

/**
 * new_history - a function used to display the history list.
 * @addres: Structure arguments.
 *  Return: 0 on succssess.
 */
int new_history(addres_t *addres)
{
	_listall(addres->newhi);
	return (0);
}

/**
 * unset_alias - a function to set alias to string.
 * @addres: struct argument.
 * @str: alias string..
 *
 * Return: 0 on success, 1 on failure.
 */
int unset_alias(addres_t *addres, char *str)
{
	char *ptr, c;
	int n;

	ptr = _strchr(str, '=');
	if (ptr == NULL)
		return (1);
	c = *ptr;
	*ptr = 0;
	n = delete_node(&(addres->alias),
		get_indexnode(addres->alias, node_start(addres->alias, str, -1)));
	*ptr = c;
	return (n);
}

/**
 * set_alias - a function to set alias to string.
 * @addres: struct.
 * @str: alias string.
 *
 * Return: 0 on success, 1 on failure.
 */
int set_alias(addres_t *addres, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (ptr == NULL)
		return (1);
	if (!*++ptr)
		return (unset_alias(addres, str));

	unset_alias(addres, str);
	return (add_endnode(&(addres->alias), str, 0) == NULL);
}

/**
 * ali_str - a function to print an alias string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on failure.
 */
int ali_str(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * new_alias - mimics the alias builtin.
 * @addres: Structure containing potential arguments.
 *  Return: 0 on sucssess.
 */
int new_alias(addres_t *addres)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (addres->argc == 1)
	{
		node = addres->alias;
		while (node)
		{
			ali_str(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; addres->argv[i]; i++)
	{
		p = _strchr(addres->argv[i], '=');
		if (p)
			set_alias(addres, addres->argv[i]);
		else
			ali_str(node_start(addres->alias, addres->argv[i], '='));
	}

	return (0);
}
