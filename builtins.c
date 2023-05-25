#include "shell.h"

int (*get_builtin(char *cmd))(char **args, char **ahead);
int shell_exit(char **args, char **ahead);
int shell_cd(char **args, char __attribute__((__unused__)) **ahead);
int shell_help(char **args, char __attribute__((__unused__)) **ahead);
int create_err(char **args, int error);

/**
 * get_builtin - function that matches a command with a corresponding shell
 * builtin function
 * @cmd: This is the command to match
 *
 * Return: returns a function pointer to the corresponding builtin
 */
int (*get_builtin(char *cmd))(char **args, char **ahead)
{
builtin_t functs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};

	int i;

	for (i = 0; functs[i].name; i++)
	{
		if (_strcmp(functs[i].name, cmd) == 0)
		{
			break;
		}
	}
	return (functs[i].f);
}

/**
 * shell_exit - function that terminates the program on the shell
 * @args: array of arguments holding the exit value
 * @ahead: pointer to pointer to the beginning of args
 *
 * Return: returns -3 if there are no arguments
 * -2 if the given exit value is invalid
 * otherwise exits with the given status value
 *
 * Descriptin: the program exits back to the main function upon returning -3
 */
int shell_exit(char **args, char **ahead)
{
	int i, len = 10;
	unsigned int num = 0, max;

	max = 1 << (sizeof(int) * 8 - 1);
	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len && args[0][i] >= '0' && args[0][i] <= '9')
			{
				num = (num * 10) + (args[0][i] - '0');
			}
			else
			{
				return (create_err(--args, 2));
			}
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
	{
		return (create_err(--args, 2));
	}
	args -= 1;
	args_free(args, ahead);
	env_free();
	alias_list_free(aliases);
	exit(num);
}

/**
 * shell_cd - function that changes the current working directory of the shell
 * @args: an array of command line arguments
 * @ahead: pointer to pointer to the beginning of args
 *
 * Return: returns -2 if the given string is not a directory.
 * returns -1 if an error occurs. otherwise returns 0
 */
int shell_cd(char **args, char __attribute__((__unused__)) **ahead)
{
	char *new_line = "\n", **path_info;
	char *pwd = NULL, *oldpwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
	{
		return (-1);
	}
	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
				{
					(chdir(*_getenv("OLDPWD") + 7));
				}
			}
			else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 &&
					S_ISDIR(dir.st_mode) &&
					((dir.st_mode & S_IXUSR) != 0))
			{
				chdir(args[0]);
			}
			else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
		{
			chdir(*(_getenv("HOME")) + 5);
		}
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		return (-1);
	}

	path_info = malloc(sizeof(char *) * 2);
	if (!path_info)
	{
		return (-1);
	}
	path_info[0] = "OLDPWD";
	path_info[1] = oldpwd;
	if (shell_setenv(path_info, path_info) == -1)
	{
		return (-1);
	}
	path_info[0] = "PWD";
	path_info[1] = pwd;
	if (shell_setenv(path_info, path_info) == -1)
	{
		return (-1);
	}
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(path_info);
	return (0);
}

/**
 * shell_help - function that displays information about shell builtin commands
 * @args: An array of command line arguments
 * @ahead: pointer to pointer to the beginning of arguments
 *
 * Return: returns -1 if an error occurs. otherwise returns 0
 */
int shell_help(char **args, char __attribute__((__unused__)) **ahead)
{
	if (!args[0])
	{
		all_help();
	}
	else if (_strcmp(args[0], "alias") == 0)
	{
		alias_help();
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		cd_help();
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		exit_help();
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		env_help();
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		setenv_help();
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		unsetenv_help();
	}
	else if (_strcmp(args[0], "help") == 0)
	{
		help_help();
	}
	else
	{
		write(STDERR_FILENO, name, _strlen(name));
	}
	return (0);
}
