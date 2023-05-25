#include "shell.h"

char **envcopy(void);
void env_free(void);
char **_getenv(const char *var);

/**
 * envcopy - function that creates a copy of the environment
 *
 * Return: returns NULL if an error occurs.
 * otherwise returns pointer to pointer to the new copy
 */
char **envcopy(void)
{
	char **new_env;
	int i;
	size_t n;

	for (n = 0; environ[n]; n++)
		;
	new_env = malloc(sizeof(char *) * (n + 1));
	if (new_env == NULL)
	{
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
			{
				free(new_env[i]);
			}
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[i], environ[i]);
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * env_free - function that frees copy of the environment
 *
 * Return: void
 */
void env_free(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		free(environ[i]);
	}
	free(environ);
}

/**
 * _getenv - function that gets an environment variable from the PATH
 * @var: this is the name of the env variable to be fetched
 *
 * Return: returns NULL if the environment variable doesn't exist
 * Otherwise returns a pointer to the env variable.
 */
char **_getenv(const char *var)
{
	int len, i;

	len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
		{
			return (&environ[i]);
		}
	}
	return (NULL);
}
