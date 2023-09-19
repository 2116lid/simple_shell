#include "main.h"

/**
 * get_file - a function that gets the history file
 * @addres: struct
 *
 * Return: pointer of buf.
 */

char *get_file(addres_t *addres)
{
	char *buf, *dir;

	dir = new_getenv(addres, "HOME=");
	if (dir == NULL)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(NEW_FILE_HIST) + 2));
	if (buf == NULL)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, NEW_FILE_HIST);
	return (buf);
}

/**
 * hist_write - a function that creates a file, or appends to an existing file.
 * @addres: struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int hist_write(addres_t *addres)
{
	ssize_t fd;
	char *filename = get_file(addres);
	list_t *node = NULL;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = addres->newhi; node; node = node->next)
	{
		in_str(node->str, fd);
		wr_ch('\n', fd);
	}
	wr_ch(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _histR - reads history from file
 * @addres: the parameter struct
 *
 * Return: line_hist_num on success, 0 on failure.
 */
int _histR(addres_t *addres)
{
	int i, botm = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_file(addres);

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (buf == NULL)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			hist_list(addres, buf + botm, linecount++);
			botm = i + 1;
		}
	if (botm != i)
		hist_list(addres, buf + botm, linecount++);
	free(buf);
	addres->line_hist_num = linecount;
	while (addres->line_hist_num-- >= NEW_FILE_HIST_MAX)
		delete_node(&(addres->newhi), 0);
	_histnum(addres);
	return (addres->line_hist_num);
}

/**
 * hist_list - adds entry to a history linked list
 * @addres: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, line_hist_num
 *
 * Return: Always 0
 */
int hist_list(addres_t *addres, char *buf, int linecount)
{
	list_t *node = NULL;

	if (addres->newhi)
		node = addres->newhi;
	add_endnode(&node, buf, linecount);

	if (!addres->newhi)
		addres->newhi = node;
	return (0);
}

/**
 * _histnum - a function to number the history list.
 * @addres: Structure containing potential arguments.
 *
 * Return: the new line_hist_num
 */
int _histnum(addres_t *addres)
{
	list_t *node = addres->newhi;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (addres->line_hist_num = i);
}
