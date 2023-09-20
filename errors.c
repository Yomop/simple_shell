#include "shell.h"

/**
 * _eputs - print input string.
 * @str: string to print.
 * Return: Nothing.
 */

void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - Character c to be written to stderr.
 * @c: Character to print.
 * Return: 1 on success.
 * On error, return -1, and errno is appropriately set.
 */

int _eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putfd - Write character c to given filedescriptor.
 * @c: Character to print.
 * @fd: Filedescriptor to write to.
 * Return: 1 on success.
 * On error, return -1, and errno is appropriately set.
 */

int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - Print input string.
 * @str: String to print.
 * @fd: Filedescriptor to write to.
 * Return: Number of chararacters.
 */

int _putsfd(char *str, int fd)
{
	int b = 0;

	if (!str)
		return (0);
	while (*str)
	{
		b += _putfd(*str++, fd);
	}
	return (b);
}
