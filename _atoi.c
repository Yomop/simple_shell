#include "shell.h"

/**
 * interactive - if shell is interactive, return true.
 * @info: struct address.
 * Return: 1, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - check char if is a delimeter.
 * @c: char to check.
 * @delim: delimeter string.
 * Return: if true return 1, if false return 0.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - alphabet to check.
 * @c: character to input.
 * Return: if c is an alphabet return 1, 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - to convert a string to an integer.
 * @s: string to convert.
 * Return: 0 if no number is string.
 */

int _atoi(char *s)
{
	int r, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (r = 0; s[r] != '\0' && flag != 2; r++)
	{
		if (s[r] == '-')
			sign *= -1;

		if (s[r] >= '0' && s[r] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[r] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
