#include "shell.h"

int cant_open(char *file_path);
int proc_file_cmd(char *file_path, int *exe_ret);

/**
* cant_open - function that checks if the file doesn't exist or lacks proper
* permissions, print a cant open error.
* @file_path: this is the path to the supposed file.
*
* Return: returns 127.
*/

int cant_open(char *file_path)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (hist_str == NULL)
	{
		return (127);
	}
	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": Can't open ");
	_strcat(err, file_path);
	_strcat(err, "\n");

	free(hist_str);
	write(STDERR_FILENO, err, len);
	free(err);
	return (127);
}

/**
 * proc_file_cmd - function that takes a file and attempts to run the
 * commands stored within it
 * @file_path: this is the path to the file
 * @exe_ret: this is the return value of the last executed command
 *
 * Return: returns 127 if the file couldn't be opened
 */
int proc_file_cmd(char *file_path, int *exe_ret)
{
	int ret;
	unsigned int i, line_size = 0, old_size = 120;
	char buff[120];
	char *line, **args, **front;
	ssize_t file, n_read;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (line == NULL)
	{
		return (-1);
	}
	do {
		n_read = read(file, buff, 119);
		if (n_read == 0 && line_size == 0)
		{
			return (*exe_ret);
		}
		buff[n_read] = '\0';
		line_size += n_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buff);
		old_size = line_size;
	} while (n_read);

	for (i = 0; line[i] == '\n'; i++)
	{
		line[i] = ' ';
	}
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
			{
				line[i] = ' ';
			}
		}
	}
	var_replacement(&line, exe_ret);
	line_handler(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (args == NULL)
	{
		return (0);
	}
	if (args_checker(args) != 0)
	{
		*exe_ret = 2;
		args_free(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = args_caller(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	ret = args_caller(args, front, exe_ret);

	free(front);
	return (ret);
}
