#include "shell.h"

void sign_handler(int sign);

/**
 * sign_handler - function that prints a new prompt upon a signal
 * @sign: The signal that calls the prompt
 */
void sign_handler(int sign)
{
	char *new_prompt = "\n$ ";

	(void)sign;
	signal(SIGINT, sign_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * exec - function that executes a command in a child process
 * @args: array list of arguments
 * @front: pointer to pointer to the beginning of args
 *
 * Return: throws a corresponding error code upon error.
 * O/w - exit value of the last executed command.
 */
int exec(char **args, char **front)
{
	pid_t child_pid;
	int flag = 0, ret = 0, status;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_loc(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_err(args, 126));
		else
		{
			ret = (create_err(args, 127));
		}
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
			{
				free(cmd);
			}
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
			{
				ret = (create_err(args, 126));
			}
			env_free();
			args_free(args, front);
			alias_list_free(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
	{
		free(cmd);
	}
	return (ret);
}

/**
 * main - a program that runs a simple UNIX commandline interpreter
 * @argc: The number of command line arguments to the program
 * @argv: The argument vector. array of the arguments
 *
 * Return: Always 0 (Succes)
 */
int main(int argc, char *argv[])
{
	int ret1, ret = 0;
	int *exe_ret = &ret1;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sign_handler);

	*exe_ret = 0;
	environ = envcopy();
	if (!environ)
	{
		exit(-100);
	}
	if (argc != 1)
	{
		ret = proc_file_cmd(argv[1], exe_ret);
		env_free();
		alias_list_free(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT_)
		{
			ret = args_handler(exe_ret);
		}
		env_free();
		alias_list_free(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = args_handler(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT_)
		{
			if (ret == END_OF_FILE)
			{
				write(STDOUT_FILENO, new_line, 1);
			}
			env_free();
			alias_list_free(aliases);
			exit(*exe_ret);
		}
	}

	env_free();
	alias_list_free(aliases);
	return (*exe_ret);
}
