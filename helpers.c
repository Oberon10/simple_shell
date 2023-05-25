#include "shell.h"

char *get_pid(void);
char *get_env_val(char *begin, int len);

/**
 * args_free - function that frees up the memory taken by args
 * @args: an array of characters containing command line arguments
 * @front: pointer to pointer to the beginning of args
 */
void args_free(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
	{
		free(args[i]);
	}
	free(front);
}

/**
 * get_pid - function that gets the current process Id
 *
 * Return: returns the current ID or NULL on failure
 */
char *get_pid(void)
{
	char *buff;
	ssize_t file;
	size_t i = 0;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Can't read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[i] != ' ')
	{
		i++;
	}
	buff[i] = '\0';

	close(file);
	return (buff);
}

/**
 * get_env_val - function that gets the corresponding value to an environment
 * variable
 * @begin: this is the environment variable to search for
 * @len: this is the length of the environment variable to search for
 *
 * Return: returns an empty string if the variable is not found
 */
char *get_env_val(char *begin, int len)
{
	char *temp, *var, *replace = NULL;
	char **var_addr;

	var = malloc(len + 1);
	if (!var)
	{
		return (NULL);
	}
	var[0] = '\0';
	_strncat(var, begin, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
		{
			temp++;
		}
		temp++;
		replace = malloc(_strlen(temp) + 1);
		if (replace)
		{
			_strcpy(replace, temp);
		}
	}

	return (replace);
}

/**
 * var_replacement - function that handles variable replacement
 * @line: pointer to pointer to command and arguments
 * @exe_ret: pointer to the return value of the last executed command
 *
 * Description: Replaces $$ with the current Process ID (PID), $? with
 * the return value of the last executed program, and environment variables
 * preceded by $ with their corresponding value
 */
void var_replacement(char **line, int *exe_ret)
{
	char *replace = NULL, *old_line = NULL, *new_line;
	int len, j, k = 0;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replace = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replace = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the var name to be searched */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
				{
					;
				}
				len = k - (j + 1);
				replace = get_env_val(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replace)
					+ _strlen(&old_line[k] + 1));
			if (!line)
			{
				return;
			}
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replace)
			{
				_strcat(new_line, replace);
				free(replace);
				replace = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
