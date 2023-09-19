#include "main.h"

/**
 * che_chadeli - test if current char in buffer is a chain delimeter
 * @addres: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 on succssess, 0 on failure.
 */
int che_chadeli(addres_t *addres, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		addres->cmd_bufType = COM_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		addres->cmd_bufType = COM_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		addres->cmd_bufType = COM_CHIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _ifcont - a function that checks we should continue chaining or not.
 * @addres: struct
 * @buf: the char buffer.
 * @ptr: pointer for buffer address of current position.
 * @k: buffer starting position.
 * @len: length of buf
 *
 * Return: Nothing.
 */
void _ifcont(addres_t *addres, char *buf, size_t *ptr, size_t k, size_t len)
{
	size_t j = *ptr;

	if (addres->cmd_bufType == COM_AND)
	{
		if (addres->sta)
		{
			buf[k] = 0;
			j = len;
		}
	}
	if (addres->cmd_bufType == COM_OR)
	{
		if (!addres->sta)
		{
			buf[k] = 0;
			j = len;
		}
	}

	*ptr = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @addres: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(addres_t *addres)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start(addres->alias, addres->argv[0], '=');
		if (!node)
			return (0);
		free(addres->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		addres->argv[0] = p;
	}
	return (1);
}

/**
 * var_toke - a function that replaces vars in the tokenized string.
 * @addres: struct.
 *
 * Return: 1 on succssess, 0 on failure.
 */
int var_toke(addres_t *addres)
{
	int i = 0;
	list_t *node;
	char *a = addres->argv[i];

	while (a)
	{
		if (a[0] == '$' && a[1])
		{
			if (!_strcmp(a, "$?"))
			{
				str_change(&a, _strdup(num_converter(addres->sta, 10, 0)));
			}
			else if (!_strcmp(a, "$$"))
			{
				str_change(&a, _strdup(num_converter(getpid(), 10, 0)));
			}
			else
			{
				node = node_start(addres->env, &a[1], '=');
				if (node)
				{
					str_change(&a, _strdup(_strchr(node->str, '=') + 1));
				}
				else
				{
					str_change(&a, _strdup(""));
				}
			}
		}
		i++;
		a = addres->argv[i];
	}
	return (0);
}

/**
 * str_change - a function to replace string.
 * @prev: address of prev string
 * @new: new string
 *
 * Return: 1 on succssess, 0 on failure.
 */
int str_change(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}
