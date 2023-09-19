#include "main.h"

/**
 * ad_new - a function to initialize addres_t struct
 * @addres: address for struct
 */
void ad_new(addres_t *addres)
{
	addres->arg = NULL;
	addres->argv = NULL;
	addres->path = NULL;
	addres->argc = 0;
}

/**
 * ad_set - a function for initializing addres_t struct.
 * @addres: address for struct.
 * @av: argv.
 */
void ad_set(addres_t *addres, char **av)
{
	int i = 0;

	addres->fname = av[0];
	if (addres->arg)
	{
		addres->argv = strtow(addres->arg, " \t");
		if (!addres->argv)
		{
			addres->argv = malloc(sizeof(char *) * 2);
			if (addres->argv)
			{
				addres->argv[0] = _strdup(addres->arg);
				addres->argv[1] = NULL;
			}
		}
		for (i = 0; addres->argv && addres->argv[i]; i++)
			;
		addres->argc = i;

		replace_alias(addres);
		var_toke(addres);
	}
}

/**
 * ad_free - a function that frees addres_t struct fields.
 * @addres: address for struct.
 * @n: all fields
 */
void ad_free(addres_t *addres, int n)
{
	_strfree(addres->argv);
	addres->argv = NULL;
	addres->path = NULL;
	if (n)
	{
		if (!addres->cmd_buf)
			free(addres->arg);
		if (addres->env)
			all_free(&(addres->env));
		if (addres->newhi)
			all_free(&(addres->newhi));
		if (addres->alias)
			all_free(&(addres->alias));
		_strfree(addres->environ);
			addres->environ = NULL;
		free_ptr((void **)addres->cmd_buf);
		if (addres->readfd > 2)
			close(addres->readfd);
		_putchar(BUF_FLUSH);
	}
}
