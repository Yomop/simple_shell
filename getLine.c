#include "shell.h"

/**
 * input_buf - buffers chained commands.
 * @info: parameter struct.
 * @buf: address of buffer.
 * @len: address of len var.
 * Return: bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t k = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &len_p, stdin);
#else
		k = _getline(info, buf, &len_p);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0'; /* remove trailing newline */
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}

/**
 * get_input - get a line minus the newline.
 * @info: parameter struct.
 * Return: bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		p = buf + a; /* get pointer for return */

		check_chain(info, buf, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - read a buffer.
 * @info: parameter struct.
 * @buf: buffer.
 * @i: size.
 * Return: a.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - get the next line of input from STDIN.
 * @info: parameter struct.
 * @ptr: address of pointer to buffer, preallocated or NULL.
 * @length: size of preallocated ptr buffer if not NULL.
 * Return: t.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t k;
	ssize_t r = 0, t = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		t = *length;
	if (a == len)
		a = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, t, t ? t + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (t)
		_strncat(new_p, buf + a, k - a);
	else
		_strncpy(new_p, buf + a, k - a + 1);

	t += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = t;
	*ptr = p;
	return (t);
}

/**
 * sigintHandler - block ctrl-C.
 * @sig_num: the signal number.
 * Return: void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
