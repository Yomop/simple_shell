#include "shell.h"

/**
 * is_chain - check if current char in buffer is a chain delimeter.
 * @info: parameter struct.
 * @buf: char buffer.
 * @p: address of current position in buf.
 * Return: 1 if chain delimeter, 0 otherwise.
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - check chain.
 * @info: parameter struct.
 * @buf: char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 * Return: Void.
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	*p = k;
}

/**
 * replace_alias - replace an alias in the tokenized string.
 * @info: parameter struct.
 * Return: 1 if replaced, 0 otherwise.
 */

int replace_alias(info_t *info)
{
	int k;
	list_t *node;
	char *p;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace vars in the tokenized string.
 * @info: parameter struct.
 * Return: 1 if replaced, 0 otherwise.
 */

int replace_vars(info_t *info)
{
	int k = 0;
	list_t *node;

	for (k = 0; info->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;

		if (!_strcmp(info->argv[k], "$?"))
		{
			replace_string(&(info->argv[k]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[k], "$$"))
		{
			replace_string(&(info->argv[k]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[k][1], '=');
		if (node)
		{
			replace_string(&(info->argv[k]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[k], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replace string.
 * @old: address of old string.
 * @new: new string.
 * Return: 1 if replaced, 0 otherwise.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
