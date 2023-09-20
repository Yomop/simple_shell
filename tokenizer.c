#include "shell.h"

/**
 * **strtow - split a string into words.
 * @str: input string.
 * @d: delimeter string.
 * Return: a pointer to an array of strings, NULL on failure.
 */

char **strtow(char *str, char *d)
{
	int i, j, a, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		a = 0;
		while (!is_delim(str[i + a], d) && str[i + a])
			a++;
		s[j] = malloc((a + 1) * sizeof(char));
		if (!s[j])
		{
			for (a = 0; a < j; a++)
				free(s[a]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			s[j][b] = str[i++];
		s[j][b] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - split a string into words.
 * @str: input string.
 * @d: delimeter.
 * Return: a pointer to an array of strings, NULL on failure.
 */

char **strtow2(char *str, char d)
{
	int i, j, a, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		a = 0;
		while (str[i + a] != d && str[i + a] && str[i + a] != d)
			a++;
		s[j] = malloc((a + 1) * sizeof(char));
		if (!s[j])
		{
			for (a = 0; a < j; a++)
				free(s[a]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			s[j][b] = str[i++];
		s[j][b] = 0;
	}
	s[j] = NULL;
	return (s);
}
