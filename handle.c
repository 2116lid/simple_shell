#include "main.h"

/**
 * cust_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void cust_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		cust_putchar(str[i]);
		i++;
	}
}

/**
 * cust_putchar - a function to write the character a to stderr
 * @a: character to be printed.
 *
 * Return: On success 1, -1 on failure.
 *
 */
int cust_putchar(char a)
{
	static int i;
	static char buf[BUF_SIZE_W];

	if (a == BUF_FLUSH || i >= BUF_SIZE_W)
	{
		write(2, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * wr_ch - a function to write the character a to given fd.
 * @a: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1, -1 on failure.
 *
 */
int wr_ch(char a, int fd)
{
	static int i;
	static char buf[BUF_SIZE_W];

	if (a == BUF_FLUSH || i >= BUF_SIZE_W)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * in_str - a function that prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: char num.
 */
int in_str(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += wr_ch(*str++, fd);
	}
	return (i);
}
