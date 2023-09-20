#include "main.h"

/**
 * interact - returns true if shell is in interactive mode.
 * @addres: address for struct.
 *
 * Return: True if interact mode, False on failure.
 */
int interact(addres_t *addres)
{
	bool _term = isatty(STDIN_FILENO);

	bool low_fd = addres->readfd <= 2;

	return (_term && low_fd);
}

/**
 * _delimeter - assesses for  delimeter.
 * @e: a character that is going to be checked.
 * @deli: the delimeter string
 * Return: 1 on sucssess, 0 on Failure.
 */
int _delimeter(char e, char *deli)
{
	int i;

	for (i = 0; deli[i] != '\0'; i++)
	{
		if (deli[i] == e)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * alpha - checks for alphabetes.
 * @c: The character to input.
 * Return: 1 on sucssess, 0 on failure.
 */

int alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
