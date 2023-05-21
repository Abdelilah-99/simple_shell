#include "shell.h"
/**
 * _strtok - do the same whsat strtok do
 * @str: string
 * @delim: delimeter
 * Return: returning
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	char *strt;

	if (str)
		token = str;
	else if (!token)
		return (NULL);
	while (*token != '\0' && _strchr(delim, *token) != NULL)
		++token;
	if (*token == '\0')
		return (NULL);
	strt = token;
	while (*token != '\0' && _strchr(delim, *token) == NULL)
		++token;
	if (*token != '\0')
		*token++ = '\0';
	return (strt);
}
