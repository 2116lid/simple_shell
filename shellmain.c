#include "main.h"

/**
 * shmain - a function which is the shell's main part.
 * @addres: the return addres struct.
 * @av: argv.
 *
 * Return: 0 on success, 1 on failure.
 */
int shmain(addres_t *addres, char **av)
{
	ssize_t m = 0;
	int cobui_in = 0;

	while (m != -1 && cobui_in != -2)
	{
		ad_new(addres);
		if (interact(addres))
			_puts("$ ");
		cust_putchar(BUF_FLUSH);
		m = get_nline(addres);
		if (m != -1)
		{
			ad_set(addres, av);
			cobui_in = built_search(addres);
			if (cobui_in == -1)
				com_path(addres);
		}
		else if (interact(addres))
			_putchar('\n');
		ad_free(addres, 0);
	}
	hist_write(addres);
	ad_free(addres, 1);
	if (!interact(addres) && addres->sta)
		exit(addres->sta);
	if (cobui_in == -2)
	{
		if (addres->error_cod == -1)
			exit(addres->sta);
		exit(addres->error_cod);
	}
	return (cobui_in);
}

/**
 * built_search - a function that searches for a builtin command.
 * @addres: the return addres struct.
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int built_search(addres_t *addres)
{
	int i, co_bui = -1;
	build_custom builtintbl[] = {
		{"exit", new_exit},
		{"env", new_env},
		{"help", new_help},
		{"history", new_history},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{"cd", com_nd},
		{"alias", new_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(addres->argv[0], builtintbl[i].type) == 0)
		{
			addres->er_count++;
			co_bui = builtintbl[i].func(addres);
			break;
		}
	return (co_bui);
}

/**
 * com_path - a function to find a command.
 * @addres: the return addres struct
 *
 * Return: Nothing.
 */
void com_path(addres_t *addres)
{
	char *path = NULL;
	int i, j;

	addres->path = addres->argv[0];
	if (addres->ercount_flag == 1)
	{
		addres->er_count++;
		addres->ercount_flag = 0;
	}
	for (i = 0, j = 0; addres->arg[i]; i++)
		if (!_delimeter(addres->arg[i], "  \n"))
			j++;
	if (!j)
		return;

	path = _searchpath(addres, new_getenv(addres, "PATH="), addres->argv[0]);
	if (path)
	{
		addres->path = path;
		_comfork(addres);
	}
	else
	{
		if ((interact(addres) || new_getenv(addres, "PATH=")
					|| addres->argv[0][0] == '/') && det_executable(addres, addres->argv[0]))
			_comfork(addres);
		else if (*(addres->arg) != '\n')
		{
			addres->sta = 127;
			err_msg(addres, "not found\n");
		}
	}
}

/**
 * _comfork - a function that forks  an exec thread to run command.
 * @addres: the return addres for struct.
 *
 * Return: Nothing.
 */
void _comfork(addres_t *addres)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: fork call failed.");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(addres->path, addres->argv, cpy_environ(addres)) == -1)
		{
			ad_free(addres, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(addres->sta));
		if (WIFEXITED(addres->sta))
		{
			addres->sta = WEXITSTATUS(addres->sta);
			if (addres->sta == 126)
				err_msg(addres, "Permission denied\n");
		}
	}
}
