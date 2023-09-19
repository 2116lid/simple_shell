#include "main.h"

/**
 * **strtow - a function that splits a string into words.
 * @str: the input string
 * @deil: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *deil)
{
	int i, j, k, m, count = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!deil)
		deil = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_delimeter(str[i], deil) && (_delimeter(str[i + 1], deil)
				     || !str[i + 1]))
			count++;

	if (count == 0)
		return (NULL);
	r = malloc((1 + count) * sizeof(char *));
	if (!r)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (_delimeter(str[i], deil))
			i++;
		k = 0;
		while (!_delimeter(str[i + k], deil) && str[i + k])
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = str[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}

/**
 * **new_strtow - a function that splits a string into words
 * @str: the input string
 * @deil: delimeter used
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **new_strtow(char *str, char deil)
{
	int i, j, k, m, count = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != deil && str[i + 1] == deil) ||
				    (str[i] != deil && !str[i + 1]) || str[i + 1] == deil)
			count++;
	if (count == 0)
		return (NULL);
	r = malloc((1 + count) * sizeof(char *));
	if (!r)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (str[i] == deil && str[i] != deil)
			i++;
		k = 0;
		while (str[i + k] != deil && str[i + k] && str[i + k] != deil)
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = str[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}
