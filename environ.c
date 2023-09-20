#include "shell.h"

/**
 * _myenv - print current environment.
 * @info: Structure containing potential arguments.
 * Return: 0 Always.
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - get value of an environ variable.
 * @info: Structure containing potential arguments.
 * @name: environ variable name.
 * Return: the value.
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a new environ variable to be initialized,
 *             or an existing one to be modified.
 * @info: Structure containing potential arguments.
 *  Return: 0 Always.
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an environ variable.
 * @info: Structure containing potential arguments.
 * Return: 0 Always.
 */

int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);
	return (0);
}

/**
 * populate_env_list - Populate env linked list.
 * @info: Structure containing potential arguments.
 * Return: 0 Always.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}
