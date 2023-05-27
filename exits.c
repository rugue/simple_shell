#include "shell.h"

/**
 **_strncpy - copying a string
 *@dest: destination str to be copied to
 *@src: source string
 *@n: amount of chars to be copied
 *Return: concatenatd str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, j;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		j = a;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - this concatenates two strings
 *@dest: this is the 1st string
 *@src: the 2nd string
 *@n: amount of bytes to be used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, j;
	char *s = dest;

	a = 0;
	j = 0;
	while (dest[a] != '\0')
		a++;
	while (src[j] != '\0' && j < n)
	{
		dest[a] = src[j];
		a++;
		j++;
	}
	if (j < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - this locates a char in a str
 *@s: string to be parsed
 *@c: the character to look for
 *Return: a pointer to memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
/** updated exits.c **/
