#include "shell.h"

char *env_error(char **args);
char *err_2_cd(char **args);
char *err_2_syntax(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);
/**
 * env_error - function that creates an env error messages for the shell
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *env_error(char **args)
{
	int len;
	char *err, *hist_str;

	hist_str = _itoa(hist);
	if (hist_str == NULL)
	{
		return (NULL);
	}
	args--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (err);
}

/**
 * err_1 - function that creates an error message for alias on the shell
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *err_1(char **args)
{
	char *err;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		return (NULL);
	}
	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");

	return (err);
}

/**
 * err_2_exit - function that creates shell exit error message
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *err_2_exit(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (NULL);
	}
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * err_2_cd - function that creates shell errors error message
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *err_2_cd(char **args)
{
	int len;
	char *err, *hist_str;

	hist_str = _itoa(hist);
	if (hist_str == NULL)
	{
		return (NULL);
	}
	if (args[0][0] == '-')
	{
		args[0][2] = '\0';
	}
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	if (args[0][0] == '-')
	{
		_strcat(err, ": cd: Illegal option ");
	}
	else
	{
		_strcat(err, ": cd: can't cd to ");
	}
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * err_2_syntax - function that creates syntax errors error message
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *err_2_syntax(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (NULL);
	}
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": Syntax error: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" unexpected\n");

	free(hist_str);
	return (err);
}
