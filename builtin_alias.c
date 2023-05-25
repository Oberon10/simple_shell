#include "shell.h"

int shell_alias(char **args, char __attribute__((__unused__)) **ahead);
void set_alias(char *name, char *val);
void print_alias(alias_t *alias);

/**
 * shell_alias - function that prints all or specific aliases, or sets aliases
 * @args: an array of command line arguments
 * @ahead: pointer to pointer to the beginning of arguments
 *
 * Return: returns -1 if an error occurs. otherwise returns 0
 */
int shell_alias(char **args, char __attribute__((__unused__)) **ahead)
{
	int ret = 0, i;
	char *val;
	alias_t *tmp = aliases;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		val = _strchr(args[i], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
			{
				ret = create_err(args + i, 1);
			}
		}
		else
		{
			set_alias(args[i], val);
		}
	}
	return (ret);
}

/**
 * set_alias - function that will either set an existing alias name with a new
 * value 'value' or creates a new alias with 'name' and 'value'
 * @name: this is the name of the alias
 * @val: this is the value of the alias. '=' is the first character
 */
void set_alias(char *name, char *val)
{
	int len, j, k;
	char *new_val;
	alias_t *tmp = aliases;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
	{
		return;
	}

	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
		{
			new_val[k++] = val[j];
		}
	}
	new_val[k] = '\0';
	while (tmp)
	{
		if (_strcmp(name, tmp->name) == 0)
		{
			free(tmp->val);
			tmp->val = new_val;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		alias_add_end(&aliases, name, new_val);
	}
}

/**
 * print_alias - function that prints alias in the name='value' format
 * @alias: this is a pointer to an alias
 *
 * Return: void
 */
void print_alias(alias_t *alias)
{
	char *alias_str;
	int len;

	len = _strlen(alias->name) + _strlen(alias->val) + 4;
	alias_str = malloc(sizeof(char) * (len + 1));
	if (!alias_str)
	{
		return;
	}
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->val);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, len);
	free(alias_str);
}

/**
 * repl_aliases - function that searches through the arguments and replace
 * any matching alias with their value
 * @args: 2-Dimensional array pointer to the arguments
 * Description: searches through arguments and replace any matching alias with
 * their value and returns a pointer to the args
 *
 * Return: pointer to the arguments
 */
char **aliases_replace(char **args)
{
	alias_t *tmp;
	int i;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
	{
		return (args);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[i], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) *
						(_strlen(tmp->val) + 1));
				if (!new_val)
				{
					args_free(args, args);
					return (NULL);
				}
				_strcpy(new_val, tmp->val);
				free(args[i]);
				args[i] = new_val;
				i--;
				break;
			}
			tmp = tmp->next;
		}
	}
	return (args);
}
