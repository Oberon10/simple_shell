#include "shell.h"

char *_itoa(int num);
int create_err(char **args, int error);
int num_len(int num);

/**
 * num_len - function that counts the digit length of a number
 * @num: this is the number to measure
 *
 * Return: returns the length of the digit
 */
int num_len(int num)
{
	int len = 1;
	unsigned int n;

	if (num < 0)
	{
		len++;
		n = num * -1;
	}
	else
	{
		n = num;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * _itoa - function that converts an integer to a string
 * @num: this is the integer number
 *
 * Return: returns the converted string
 */
char *_itoa(int num)
{
	char *buf;
	unsigned int n;
	int len = num_len(num);

	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
	{
		return (NULL);
	}
	buf[len] = '\0';

	if (num < 0)
	{
		n = num * -1;
		buf[0] = '-';
	}
	else
	{
		n = num;
	}
	len--;
	do {
		buf[len] = (n % 10) + '0';
		n /= 10;
		len--;
	} while (n > 0);

	return (buf);
}

/**
 * create_err - function that writes a custom error message to stderr
 * @args: an array of command line arguments
 * @error: this is the error value
 *
 * Return: returns the error value
 *
 * Description: This function writes a custom error message to
 * stderr and returns the error value
 */
int create_err(char **args, int error)
{
	char *err;

	switch (error)
	{
	case -1:
		err = env_error(args);
		break;
	case 1:
		err = err_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
		{
			err = err_2_exit(++args);
		}
		else if (args[0][0] == ';' || args[0][0] == '&' ||
				args[0][0] == '|')
		{
			err = err_2_syntax(args);
		}
		else
		{
			err = err_2_cd(args);
		}
		break;
	case 126:
		err = err_126(args);
		break;
	case 127:
		err = err_127(args);
		break;
	}
	write(STDERR_FILENO, err, _strlen(err));

	if (err)
	{
		free(err);
	}
	return (error);
}
