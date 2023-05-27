#include "shell.h"

/**
 * input_buff - buffers  commands
 * @info: par struct
 * @buff: address of the buffer
 * @len: address of then len var
 * Return: bytes read by the function
 */
ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t rc = 0;
	size_t length_p = 0;

	if (!len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandle);
#if USE_GETLINE
		rc = getline(buff, &len_p, stdin);
#else
		rc = _getline(info, buff, &length_p);
#endif
		if (rc > 0)
		{
			if ((*buff)[rc - 1] == '\n')
			{
				(buff)[rc - 1] = '\0';
				rc--;
			}
			info->linecount_flag = 1;
			change_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*len = rc;
				info->cmd_buf = buff;
			}
		}
	}
	return (rc);
}

/**
 * get_input - gets a line without the newline
 * @info: param struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t rc = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rc = input_buff(info, &buff, &len);
	if (rc == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (rc);
}

/**
 * read_buff - read buffer
 * @info: param struct
 * @buf: the buffer
 * @i: size
 * Return: bytes
 */
ssize_t read_buff(info_t *info, char *buf, size_t *i)
{
	ssize_t rc = 0;

	if (*i)
		return (0);
	rc = read(info->readfd, buf, READ_BUF_SIZE);
	if (rc >= 0)
		*i = rc;
	return (rc);
}

/**
 * _getline - a replica of getline
 * @info: param struct
 * @ptr: address of pointer to buffe
 * @length: size of preallocated ptr
 * Return: bytes
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t rc = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	rc = read_buff(info, buff, &len);
	if (rc == -1 || (rc == 0 && len == 0))
		return (-1);

	c = str_chr(buff + i, '\n');
	j = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		str_cat(new_p, buff + i, j - i);
	else
		str_cpy(new_p, buff + i, j - i + 1);

	s += j - i;
	i = j;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandle - blocks ctrl-C
 * @sig_n: the signal number
 * Return: void
 */
void sigintHandle(_attribute_((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
