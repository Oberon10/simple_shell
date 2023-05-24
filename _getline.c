#include "shell.h"


void re_assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t a);

/**
 * _realloc - function that reallocates a memory block using malloc and free
 * @ptr: a pointer to the previously allocated memory
 * @old_size: the allocated space for ptr, it's size in bytes
 * @new_size: the new memory block, it's size
 *
 * Return: returns ptr if the new_size equals to old_size
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *block;
	char *filler, *ptr_cpy;
	unsigned int i;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (ptr == NULL)
	{
		block = malloc(new_size);
		if (block == NULL)
		{
			return (NULL);
		}
		return (block);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_cpy = ptr;
	block = malloc(sizeof(*ptr_cpy) * new_size);
	if (block == NULL)
	{
		free(ptr);
		return (NULL);
	}
	filler = block;
	for (i = 0; i < old_size && i < new_size; i++)
	{
		filler[i] = *ptr_cpy++;
	}
	free(ptr);
	return (block);
}

/**
 * re_assign_lineptr - function that reassigns the lineptr variable for
 * _getline
 * @lineptr: this is a buffer to store an input string
 * @n: this is the size of the lineptr
 * @buffer: the temp memory area to assign the lineptr
 * @a: the size of the buffer
 */
void re_assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t a)
{
	if (*lineptr == NULL)
	{
		if (a > 120)
		{
			*n = a;
		}
		else
		{
			*n = 120;
		}
		*lineptr = buffer;
	}
	else if (*n < a)
	{
		if (a > 120)
		{
			*n = a;
		}
		else
		{
			*n = 120;
		}
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getine - function that reads input from stdin
 * @lineptr: a temporary area to store command line input
 * @n: this is the size of the lineptr
 * @stream: the std input stream to read input from
 *
 * Return: returns the number of bytes nread
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t ret;
	static ssize_t input;
	char c = 'x', *buff;
	int r;

	if (input == 0)
	{
		fflush(stream);
	}
	else
	{
		return (-1);
	}
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
	{
		return (-1);
	}

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
		{
			buff = _realloc(buff, input, input + 1);
		}
		buff[input] = c;
		input++;
	}
	buff[input] = '\0';
	re_assign_lineptr(lineptr, n, buff, input);

	ret = input;
	if (r != 0)
	{
		input = 0;
	}
	return (ret);
}
