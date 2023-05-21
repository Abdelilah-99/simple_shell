#include "shell.h"
/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second
 * Return: 0 if eqsual
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * _strcat - concatenation
 * @d: destination
 * @s: source
 * Return: concatenation
 */

char *_strcat(char *d, char *s)
{
	char *tem = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;

	*d = *s;
	return (tem);
}
/**
 * _strdup - duplicate a string
 * @str: string
 * Return: pointer to the copy
 */
char *_strdup(const char *str)
{
	char *s;
	int l = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	s = malloc(sizeof(char) * (l + 1));
	if (!s)
		return (NULL);
	for (l++; l--;)
		s[l] = *--str;
	return (s);
}
/**
 * _strchr - finds a match of char in a string
 * @str: string
 * @c: integer
 * Return: a pointer to the first occurence of the specified char
 */
char *_strchr(char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strncmp - compares two string up to a specified umber of chars
 * @s1: first string;
 * @s2: second string;
 * @n:max of chars
 * Return: 0 if equal
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
