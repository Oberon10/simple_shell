#include "shell.h"


/**
* _strlen - function that returns the length of the string.
* @str : a apointer to the characters string.
*
*return : the length of thr character string.
*/
int _strlen(const char *str)
{
	int length = 0;
	
	if (!str)
	{
		return (length);
	}
	for (length = 0; str[length]; length++)
		;
	
	return (length);
}

/**
* _strcpy - cpoies the string pointed to the src, including the
*	terminating null byte, to the buffer pointed by des
* @dest: pointer to the destination of the copied string.
* @src: pointer to the source string
*
* Return: returns pointer to dest.
*/
char *_stcpy(char *dest, const char *src)
{
	size_t i;
	
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcat - function that concatenates two strings
* @dest: pointer to the destination string.
* @src: pointer to source string.
*
* Return : returns pointer to destination string.
*/
char *_strcat(char *dest, const char * src)
{
	char *desTemp;
	const char *srcTemp;
	
	desTemp = dest;
	srcTemp = src;

	while (*desTemp != '\0')
	{
		desTemp++;
	}

	while ((*srcTemp) != '\0')
	{
		*desTemp++ = *srcTemp++;
	}
	*desTemp = '\0';
	return (dest);
}

/**
* _strncat - function that concatenates two strings where n number
* of bytes are copies from source.
* @dest: pointer to destination string
* @src: pointer to the source string
* @n: the n number of bytes where string are copied
*
* Return: pointer to destination string.
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t dest_len = _strlen(dest);

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';

	return (dest);
}
