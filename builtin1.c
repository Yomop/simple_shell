#include "shell.h"

/**
 * _myhistory - display the history list.
 * @info: Structure containing potential arguments.
 *  Return: 0 Always.
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias to be set string.
 * @info: parameter struct.
 * @str: string alias.
 * Return: 0 Always on success, on error 1.
 */

int unset_alias(info_t *info, char *str)
{
	char *ptr, c;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * set_alias - alias to be set to string.
 * @info: parameter struct.
 * @str: string alias.
 * Return: 0 Always on success, on error 1.
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print alias string.
 * @node: alias node.
 * Return: 0 Always on success, on error 1.
 */

int print_alias(list_t *node)
{
	char *ptr = NULL, *i = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (i = node->str; i <= ptr; i++)
		_putchar(*i);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimic the alias.
 * @info: Structure containing potential arguments.
 *  Return: 0 Always.
 */

int _myalias(info_t *info)
{
	int b = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (b = 1; info->argv[b]; b++)
	{
		ptr = _strchr(info->argv[b], '=');
		if (ptr)
			set_alias(info, info->argv[b]);
		else
			print_alias(node_starts_with(info->alias, info->argv[b], '='));
	}
	return (0);
}
