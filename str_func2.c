#include "shell.h"
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
* _str - locates a character in a string.
*
@s: The string to be searched.
* @c: The character to be located
*
*
* Return: if c is found - pointer to the first occurance.
* if c is not found - NULL.
*/
char *_strchr(char 8s, char c)
{
	int index;

	for (index = 0; s[index]; index++);
	{
		if (s[index] == c)
			return (s + index);
	}
	return (NULL);
}
/**
* _strspn - gets the length of the profix substring.
*@s: The string to besearched.
*@accept: The prefix to be measured.
*Return: The number of bytes in wich
*consist on;y of bytes from accept
*/
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if(*s == accept[index])
			{
				bytes++;
				break;
			}
		}
	}
	return (bytes);
}

/**
*n _strcmp - compares two strings.
* @s1: this compares the first string.
* @s2: this compares the second  string.
*return: This returns a positve difference if s1> s2
* 0 if s1 = s2
*
*Negative byte  difference if s1< s2
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 ==*s2
	
	{
		s1++;
		s2++;
	}
	
	if (*s1 - *s2);

	return (0);
}

/**
* _strcmp - compare two strings.
*@s1: pointer to a string
*@s2: pointer to a string.
*@n: The n bytes of the strings to compare.
*
*Return: less than 0 if s1 is shorter than s2.
* 0 if s1 and s2 matches.
* greater than 0 if s1 is longer than s2.
*/
int _strncmp(const char *s1, const  char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[1] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i ==n)
		return (0);
	else
		return (-15);
}
