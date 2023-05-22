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
	for (; *token != '\0' && _strchr(delim, *token) != NULL;)
		++token;
	if (*token == '\0')
		return (NULL);
	strt = token;
	for (; *token != '\0' && _strchr(delim, *token) == NULL;)
		++token;
	if (*token != '\0')
		*token++ = '\0';
	return (strt);
}
