#include "shell.h"

/**
 **_strncpy - Copy a string.
 *@dest: destination string to copy.
 *@src: source string.
 *@n: amount of chars to be copied.
 *Return: concatenated string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenate strings.
 *@dest: first string.
 *@src: second string.
 *@n: amount of bytes to be used.
 *Return: concatenated string.
 */

char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - locate a char in a string.
 *@s: String to parse.
 *@c: char to look for.
 *Return: a pointer to the memory.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
