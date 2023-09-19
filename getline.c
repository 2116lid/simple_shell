#include "main.h"

/**
 * com_chain_buf - buffers chained commands
 * @addres: the struct.
 * @buf: pointer to buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t com_chain_buf(addres_t *addres, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_a = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, blo_ctrl);
#if R_FLINE
		r = getline(buf, &len_a, stdin);
#else
		r = _getline(addres, buf, &len_a);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			addres->ercount_flag = 1;
			comm_replace(*buf);
			hist_list(addres, *buf, addres->line_hist_num++);
			{
				*len = r;
				addres->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_nline - a function that gets a line minus the newline.
 * @addres: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_nline(addres_t *addres)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(addres->arg), *p;

	_putchar(BUF_FLUSH);
	r = com_chain_buf(addres, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		_ifcont(addres, buf, &j, i, len);
		while (j < len)
		{
			if (che_chadeli(addres, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			addres->cmd_bufType = COM_OM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @addres: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(addres_t *addres, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(addres->readfd, buf, BUF_SIZE_R);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @addres: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(addres_t *addres, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE_R];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(addres, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _cust_reallo(p, s, s ? s + k : k + 1);
	if (new_p == NULL)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * blo_ctrl - a function that blocks ctrl-C.
 * @n_blo: the signal number
 *
 * Return: Nothing.
 */
void blo_ctrl(__attribute__((unused))int n_blo)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
