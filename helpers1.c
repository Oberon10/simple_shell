#include "shell.h"

ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * line_handler - function that partitions a line, read from stdin as needed
 * @line: pointer to a single line that is read from the stdin
 * @read: this is the length of the line
 *
 * Description: spaces are inserted to separate ";", "||", and "&&" replaces
 * "#" with '\0'
 */
void line_handler(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char prev, curr, next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
	{
		return;
	}
	new_line = malloc(new_len + 1);
	if (new_line == NULL)
	{
		return;
	}
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		curr = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			prev = old_line[i - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev
						!= ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
				{
					new_line[j++] = ' ';
				}
				new_line[j++] = ';';
				if (next != ' ')
				{
					new_line[j++] = ' ';
				}
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
				{
					new_line[j++] = ' ';
				}
				else if (prev == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
				{
					new_line[j++] = ' ';
				}
				else if (prev == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
			{
				new_line[j++] = ' ';
			}
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
			{
				new_line[j++] = ' ';
			}
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - function that gets the new length of a partioned line by
 * ";", "||", "&&&", or "#"
 * @line: this is the line to be checked
 *
 * Return: this is the length of the new line
 */
ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char curr, next;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		next = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[i - 1] != ' ' &&
						line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
				{
					new_len++;
				}
				if (next != ' ')
				{
					new_len++;
				}
			}
			else
			{
				logical_ops(&line[i], &new_len);
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
			{
				new_len++;
			}
			if (next != ' ' && next != ';')
			{
				new_len++;
			}
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - function that checks a line for logical operators "||" or
 * "&&"
 * @line: pointer to a character in the line to be checked
 * @new_len: pointer to the new_len in get_new_len function
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '&' && next != ' ')
		{
			(*new_len)++;
		}
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '|' && next != ' ')
		{
			(*new_len)++;
		}
	}
}
