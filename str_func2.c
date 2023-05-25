#include "shell.h"

char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strlen(const char *str);

/**
* _strchr - locates a character in a string.
*
* @str: this is the string to be searched.
* @c: this is the character to be located
*
* Return: if c is found - pointer to the first occurance.
* if c is not found - NULL.
*/
char *_strchr(char *str, char c)
{
	int index;

	for (index = 0; str[index]; index++)
	{
		if (str[index] == c)
		{
			return (str + index);
		}
	}
	return (NULL);
}

/**
* _strspn - gets the length of the profix substring.
* @str: The string to besearched.
* @accept: The prefix to be measured.
* Return: returns the number of bytes in which
* consist only of bytes from accept
*/
int _strspn(char *str, char *accept)
{
	int bytes = 0;
	int index;

	while (*str)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*str == accept[index])
			{
				bytes++;
				break;
			}
		}
	}
	return (bytes);
}

/**
* _strcmp - compares two strings.
* @str1: this compares the first string.
* @str2: this compares the second  string.
* Return: This returns a positve difference if s1> s2
* 0 if s1 = s2
* Negative byte  difference if s1< s2
*/
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
	{
		return (*str1 - *str2);
	}
	return (0);
}

/**
* _strncmp - compare two strings.
* @str1: pointer to a string
* @str2: pointer to a string.
* @n: The n bytes of the strings to compare.
*
* Return: less than 0 if s1 is shorter than s2.
* 0 if s1 and s2 matches.
* greater than 0 if s1 is longer than s2.
*/
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[1] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
	{
		return (0);
	}
	else
	{
		return (-15);
	}
}
