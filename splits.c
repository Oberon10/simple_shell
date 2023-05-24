#include "shell.h"

char **_strtok(char *line, char *delim);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

/**
* token_len - function that locates the delimiter index marking the end
* of the first token contained within the string.
* @str: this is the string to be searched.
* @delim: this is the delimiter character.
*
* Return: returns the delimiter index marking the end of the initial
* token pointer to the str.
*/
int token_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
* count_tokens - function that counts the number of delimited words
* contained within a string.
* @str: this is the string to be searched.
* @delim: this is the delimiter character.
*
* Return: returns the number of words contained within str.
*/
int count_tokens(char *str, char *delim)
{
	int i, tokens = 0, len = 0;

	for (i = 0; *(str + i); i++)
	{
		len++;
	}

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += token_len(str + i, delim);
		}
	}

	return (tokens);
}

/**
* _strtok - function that tokenizes a string.
* @line: this is the string to be tokenized
* @delim: this is the delimiter charater to tokenize te string by
*
* Return: returns a pointer to an array containing the tokenized word
*/
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, tokens, j, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
	{
		return (NULL);
	}
	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (ptr == NULL)
	{
		return (NULL);
	}

	for (j = 0; j < tokens; j++)
	{
		while (line[i] == *delim)
		{
			i++;
		}

		letters = token_len(line + i, delim);

		ptr[j] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[j])
		{
			for (i -= 1; i >= 0; i --)
			{
				free(ptr[i]);
			}
			free(ptr);
			return (NULL);
		}
		for (l = 0; l < letters; l++)
		{
			ptr[j][l] = line[i];
			i++;
		}

		ptr[j][l] = '\0';
	}
	ptr[j] = NULL;
	ptr[j + 1] = NULL;

	return (ptr);
}
