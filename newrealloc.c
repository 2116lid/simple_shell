#include "main.h"

/**
 * cust_memset - a custom memset, fills memory with a constant byte
 * @ptr: a pointer to memory area.
 * @byte: the byte to fill.
 * @n: the amount of bytes.
 * Return: the pointer ptr
 */
char *cust_memset(char *ptr, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * _strfree - a function that frees a string.
 * @sri: the string of string to be freed.
 * Return: Nothing.
 *
 */
void _strfree(char **sri)
{
	char **a = sri;

	if (sri == NULL)
		return;
	while (*sri)
		free(*sri++);
	free(a);
}

/**
 * _cust_reallo - a function to reallocate a block of memory
 * @ptr: pointer to previous malloc.
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: Nothing.
 */
void *_cust_reallo(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *d;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	d = malloc(new_size);
	if (d == NULL)
		return (NULL);

	if (prev_size < new_size)
	{
		while (prev_size--)
			d[prev_size] = ((char *)ptr)[prev_size];
	}
	else
	{
		while (new_size--)
			d[new_size] = ((char *)ptr)[new_size];
	}
	free(ptr);
	return (d);
}
