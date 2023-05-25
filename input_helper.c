#include "shell.h"


/**
* args_getter - function that retrieve a command from input.
* @line: This is a buffer that stores command.
* @exe_ret: This returns the value of the last command
*
* Return: returns NULL if any error occurs or a pointer to store command.
*/
char *args_getter(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
	{
		free(line);
	}

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
	{
		return (NULL);
	}
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prompt, 2);
		}
		return (args_getter(line, exe_ret));
	}

	line[read - 1] = '\0';
	var_replacement(&line, exe_ret);
	line_handler(&line, read);

	return (line);
}

/**
* args_caller - function that partitions operators from commands
* and calls them.
* @front: this is an array of arguments.
* @args: A pointer to pointer to the beginning of args.
* @exe_ret: this is the return value of the parent process last executed
* command.
*
* Return: returns the value of the last executed command.
*/

int args_caller(char **args, char **front, int *exe_ret)
{
	int ret, i;

	if (!args[0])
	{
		return (*exe_ret);
	}
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = aliases_replace(args);
			ret = args_runner(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
				{
					free(args[i]);
				}
				return (ret);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = aliases_replace(args);
			ret = args_runner(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
				{
					free(args[i]);
				}
				return (ret);
			}
		}
	}
	args = aliases_replace(args);
	ret = args_runner(args, front, exe_ret);
	return (ret);
}

/**
* args_runner - function that calls the execution of a command.
* @args: this is an array of command line arguments.
* @front: pointer to pointer to the beginning of args.
* @exe_ret : the return value of the parent process last executed command
*
* Return: returns the return value of the last executed command
*/
int args_runner(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{

		ret = builtin(args + 1, front);
		if (ret != EXIT_)
		{
			*exe_ret = ret;
		}
	}
	else
	{
		*exe_ret = exec(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}

	return (ret);
}

/**
* args_handler - function that gets call and runs the execcution of commands
* @exe_ret: this is the return the value of the parent of thr process last
* command executed.
*
* Return: when end-of-file is read, returns END_OF_FILE (-2).
* if the input cannot be tokenized, returns -1
* otherwise returns the exit value of the last executed command.
*/

int args_handler(int *exe_ret)
{
	int ret = 0, i;
	char **args, *line = NULL, **front;

	line = args_getter(line, exe_ret);
	if (!line)
	{
		return (END_OF_FILE);
	}

	args = _strtok(line, " ");
	free(line);
	if (args == NULL)
	{
		return (ret);
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
	if (args != NULL)
	{
		ret = args_caller(args, front, exe_ret);
	}

	free(front);
	return (ret);
}

/**
* args_checker - function that checks if there are any leading
* ";",";;","&&" or "||"
* @args: this is a 2D pointer to tokenized commands and arguments.
* Return : returns -2 if a ";", "&&", or "||" is palced  at an invalid positn
* Otherwise returns 0
*
* Description: checks for separators and splits the command and then execute
*/
int args_checker(char **args)
{
	size_t i;
	char *curr, *next;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
			{
				return (create_err(&args[i], 2));
			}
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' ||
						next[0] == '|'))
			{
				return (create_err(&args[i + 1], 2));
			}
		}
	}
	return (0);
}
