#include "shell.h"

/**
 * shell_env - function that prints the current environment
 * @args: an array of command line arguments passed to the program
 * @ahead: pointer to pointer to the beginning of arguments
 *
 * Return: returns -1 if an error occurs. otherwise returns 0
 *
 * Description: This function prints one variable per line in the
 * variable='value' format
 */
int shell_env(char **args, char __attribute__((__unused__)) **ahead)
{
	char new_line = '\n';
	int i;

	if (!environ)
	{
		return (-1);
	}
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - function that changes or adds an environment variable
 * to the PATH
 * @args: an array containing command line arguments
 * @ahead: pointer to pointer to the beginning of args
 * Description: args[1] is the name of the new or existing PATH variable
 * args[2] is the value to set the new or changed variable to.
 * Return: returns -1 if an error occurs. otherwise returns 0
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **ahead)
{
	int i;
	size_t size;
	char **env_var = NULL, **new_env, *new_val;

	if (!args[0] || !args[1])
	{
		return (create_err(args, -1));
	}
	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + );
	if (!new_value)
	{
		return (create_err(args, -1));
	}
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_val);
		return (create_err(args, -1));
	}

	for (index = 0; environ[i]; i++)
	{
		new_env[i] = environ[i];
	}
	free(environ);
	environ = new_env;
	environ[i] = new_val;
	envrion[i + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - function that deletes an environment variable from
 * the PATH
 * @args: an array containing command line arguments
 * @ahead: pointer to pointer to the beginning of args
 * Description: args[1] is the PATH to be removed
 *
 * Return: returns -1 if an error occurs. otherwise returns 0
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **ahead)
{
	int idx, idx2;
	char **env_var, **new_env;
	size_t n;

	if (!args[0])
	{
		return (create_err(args, -1));
	}
	env_var = _getenv(args[0]);
	if (!env_var)
	{
		return (0);
	}
	for (n = 0; environ[n]; n++)
		;
	new_env = malloc(sizeof(char *) * n);
	if (!new_env)
	{
		return (create_err(args, -1));
	}
	for (idx = 0; idx2 = 0; environ[idx]; idx++)
	{
		if (*env_var == environ[idx])
		{
			free(*env_var);
			continue;
		}
		new_env[idx2] = environ[idx];
		idx2++;
	}
	free(environ);
	environ = new_env;
	environ[n - 1] = NULL;

	return (0);
}
