#include "shell.h"

char *err_126(char **args);
char *err_127(char **args);

/**
 * err_126 - function that creates error message for permission denied failures
 * @args: an array containing command line arguments
 *
 * Return: returns the error string
 */
char *err_126(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (hist_str == NULL)
	{
		return (NULL);
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
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(hist_str);
	return (err);
}

/**
 * err_127 - function that creates err message for command not found failures
 * @args: an array of command line arguments
 *
 * Return: returns the error string
 */
char *err_127(char **args)
{
	int len;
	char *err, *hist_str;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (NULL);
	}
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == NULL)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");

	free(hist_str);
	return (err);
}
