#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
*
token_len - locates the delimiter index marking the end
* of the first token contained within the string.
*@str: the string to be searched.
*@delim: the delimiter character.
*
*return: the delimiter index marking the end of the initial token pointer to the str.
*/
int token_len (char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}
/**
*count_tokens - counts the number of delimited words contained within a string.
*@str: the string to be searched.
*@delim: the delimiter character.
*
*return: the number of words contained within str.
*/
int count_tokens (char *str, char 8delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
* _strtok - Tokenizess a string.
*@line: The string.
*@delim: The delimiter charater to tokenize te string by.
* Return: A pointer to an array containing the tokenized word
*/
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, token, t, letters, l;

	tokens = count_tokens(line, delim);
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

	letters = token_len(line +index, delim);

	ptr[t] = malloc(sizeof(char0 * (letters + 1));
	if (!ptr[t])
	{
		for (index -= 1; index >= 0; index --)
			free(ptr[index];
			index++;
	}

	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
