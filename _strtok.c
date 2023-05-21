#include "shell.h"
/**
 * _strtok - do the same whsat strtok do
 * @str: string
 * @delim: delimeter
 * Return: returning
 */
char *_strtok(char *str, char *delim)
{
	static char *token;
	static char *next_token;
	char *start = NULL;
	char *end = NULL;

	if (str != NULL)
	{
		token = str;
		next_token = NULL;
	}
	if (token == NULL)
		return (NULL);
	start = token;

	while (*token != '\0')
	{
		if (is_delimiter(*token, delim))
		{
			*token = '\0';
			end = token;
			token++;
			break;
		}
		token++;
	}
	if (end == NULL)
		end = token;
	if (*token == '\0')
		token = next_token;
	else
		next_token = token;
	return (start);
}
