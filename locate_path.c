#include "shell.h"

char *fill_dir_path(char *path);


/**
 * get_loc - function that locates command in the PATH
 * @cmd: this is the command to locate
 *
 * Return: returns NULL if an error occurs or the cmd can't be located
 * otherwise returns the full path of the command
 */
char *get_loc(char *cmd)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
	{
		return (NULL);
	}

	dirs = get_dir_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!temp)
		{
			return (NULL);
		}

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			list_free(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}
	list_free(head);
	return (NULL);
}

/**
 * fill_path_dir - function that copies path but also replaces leading/
 * sandwiched/trailing colons (:) with current working directory
 * @path: this is the colon-separated list of directories
 *
 * Return: returns a copy of path with any leading/sandwiched/trailing colons
 * replaced with the current working directory
 */
char *fill_path_dir(char *path)
{
	char *path_cpy, *pwd;
	int i, len = 0;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] ==
					'\0')
			{
				len += _strlen(pwd) + 1;
			}
			else
			{
				len++;
			}
		}
		else
		{
			len++;
		}
	}
	path_cpy = malloc(sizeof(char) * (len + 1));
	if (!path_cpy)
	{
		return (NULL);
	}
	path_cpy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_cpy, pwd);
				_strcat(path_cpy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_cpy, ":");
				_strcat(path_cpy, pwd);
			}
			else
			{
				_strcat(path_cpy, ":");
			}
		}
		else
		{
			_strncat(path_cpy, &path[i], 1);
		}
	}
	return (path_cpy);
}

/**
 * get_dir_path - function that tokenizes a colon-separated list of director
 * ies into a list_s linked list
 * @path: this is the colon_separated list of directories
 *
 * Return: returns pointer to the initialized linked list
 */
list_t *get_dir_path(char *path)
{
	char **dirs, *path_cpy;
	list_t *head = NULL;
	int i;

	path_cpy = fill_path_dir(path);
	if (path_cpy == NULL)
	{
		return (NULL);
	}
	dirs = _strtok(path_cpy, ":");
	free(path_cpy);
	if (!dirs)
	{
		return (NULL);
	}
	for (i = 0; dirs[i]; i++)
	{
		if (add_node_end(&head, dirs[i]) == NULL)
		{
			list_free(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);
	return (head);
}
