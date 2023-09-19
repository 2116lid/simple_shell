#include "main.h"

/**
 * _newatoi - a function that converts a string to an integer
 * @s: the string to be converted
 * Return: -1 on failure, int on succssess.
 */
int _newatoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * err_msg - a function that prints an error message.
 * @addres: the parameter & return addres struct
 * @estr: string containing specified error type
 * Return: Nothing.
 *
 */
void err_msg(addres_t *addres, char *estr)
{
	cust_puts(addres->fname);
	cust_puts(": ");
	deci_out(addres->er_count, STDERR_FILENO);
	cust_puts(": ");
	cust_puts(addres->argv[0]);
	cust_puts(": ");
	cust_puts(estr);
}

/**
 * deci_out - a function to print a integers.
 * @numin: the input.
 * @fd: the filedescriptor.
 *
 * Return: number of characters printed
 */
int deci_out(int numin, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, result = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = cust_putchar;
	if (numin < 0)
	{
		_abs_ = -numin;
		__putchar('-');
		result++;
	}
	else
		_abs_ = numin;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			result++;
		}
		current = current % i;
	}
	__putchar('0' + current);
	result++;

	return (result);
}

/**
 * num_converter - a function to convert lowercase and unsigned.
 * @num: number used.
 * @b: base.
 * @flags: argument flags.
 *
 * Return: pointer to string.
 */
char *num_converter(long int num, int b, int flags)
{
	static char *array;
	static char buffer[50];
	char s = 0;
	char *p;
	unsigned long number = num;

	if (!(flags & _TOSIGNED) && num < 0)
	{
		number = -num;
		s = '-';

	}
	array = flags & _TOUPPER ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[number % b];
		number = number / b;
	} while (number != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * comm_replace - a function that removes comments with '\0'.
 * @buf: address of string.
 *
 */
void comm_replace(char *buf)
{
	int j = 0;

	while (buf[j] != '\0')
	{
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
		j++;
	}
}
