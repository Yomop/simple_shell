#include "shell.h"

/**
 * _memset - fill memory with a byte.
 * @s: pointer to the memory.
 * @b: byte to fill.
 * @n: amount of bytes to be filled.
 * Return: pointer to the memory.
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - free a string of strings.
 * @pp: string of strings.
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocate memory.
 * @ptr: pointer to previous malloc'ated block.
 * @old_size: byte size of previous block.
 * @new_size: byte size of new block.
 * Return: pointer.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
