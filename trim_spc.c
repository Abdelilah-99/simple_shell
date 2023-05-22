#include "shell.h"

/**
 * trim_whitespace - trminig whitespace, tabs, and new line
 * @str: string
 */

void trim_whitespace(char *str)
{
	int s = 0, e = _strlen(str) - 1;
	int i;

	for (; str[s] == ' ' || str[s] == '\t' || str[s] == '\n';)
		s++;
	for (; str[e] == ' ' || str[e] == '\t' || str[e] == '\n';)
		e--;
	i = 0;
	while (i <= e - s)
	{
		str[i] = str[s + i];
		i++;
	}
	str[i] = '\0';
}
