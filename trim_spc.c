#include "shell.h"

/**
 * trim_whitespace - trmsinig whitespace, tabs, and new line
 * @str: string
 */

void trim_whitespace(char *str)
{
	int s = 0, e = _strlen(str) - 1;
	int i;

	while (str[s] == ' ' || str[s] == '\t' || str[s] == '\n')
		s++;
	while (str[e] == ' ' || str[e] == '\t' || str[e] == '\n')
		e--;
	for (i = 0; i <= e - s; i++)
		str[i] = str[s + i];
	str[i] = '\0';
}
