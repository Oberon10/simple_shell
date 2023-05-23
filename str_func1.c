#include "shell.h"

int _strlen(const char *s);
char *__strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
* _strlen - Return the length of the string.
*@s : a apointer to the characters string.
*
*return : the length of thr character string.
*/
int _strlen(const char *s)
{
	int length = 0;
	
	if (!s)
		return (length);
	for (lenght = 0; s[lenght]; lenght++)
	
	return (length);
}

/**
*_strcpy  : cpoies the string pointed to the src, including the
*	terminating null byte, to the buffer pointed by des
*@dest: pointer to the destination of the copied string.
*
*Return: Pointer to dest.
*/
char *_stcpy(char *dest, const char *src)
{
	size_t i;
	
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
		dest[i] = '\0';
		return (dest);
}
/**
* _strcat - concatenate two strings
*@dest pointer to the destination string.
*@src: pointer to source string.
*
*Return : pointer to destination string.
*/
char *_strcat(char *dest, const char * src)
{
	char *desTemp;
	const char *srcTemp;
	
	descTemp = dest;
	srcTemp = src;

	while (*destTemp != '\0')
		destTempt++;

	while (*srcTemp ! ='\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
*_strncat - concatenate two strings where n number
* of bytes are copies from source.
*@dest: pointer to destination string.
*return: pointer to destination string.
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i<n && scr[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = src[i];
	
	dest[dest_len +i] = '\0';

	return (dest);
}
