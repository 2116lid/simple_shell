#include "main.h"

/**
 * det_executable - a function used to determine if a file
 * is executable.
 * @addres: the addres struct.
 * @path: path to file
 *
 * Return: 1 on succssess, 0 on failure.
 */
int det_executable(addres_t *addres, char *path)
{
	struct stat st;

	(void)addres;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * ch_duplicate - a function for duplication characters.
 * @pathstr: the PATH of the string.
 * @first: the first index
 * @last: the last index
 *
 * Return: pointer to new buf.
 */
char *ch_duplicate(char *pathstr, int first, int last)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = first; j < last; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * _searchpath - finds this cmd in the PATH string
 * @addres: the addres struct
 * @pathstr: the PATH string
 * @com: the com to find
 *
 * Return: path on succssess, NULL on failure.
 */
char *_searchpath(addres_t *addres, char *pathstr, char *com)
{
	int i = 0, pos_now = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(com) > 2) && see_string(com, "./"))
	{
		if (det_executable(addres, com))
			return (com);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = ch_duplicate(pathstr, pos_now, i);
			if (!*path)
				_strcat(path, com);
			else
			{
				_strcat(path, "/");
				_strcat(path, com);
			}
			if (det_executable(addres, path))
				return (path);
			if (!pathstr[i])
				break;
			pos_now = i;
		}
		i++;
	}
	return (NULL);
}
