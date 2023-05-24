#include "shell.h"
/**
 * print_environment - environ a pointer to an arrays and
 * each array poisnt to string
*/
void print_environment(void)
{
	char **env = environ;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		_puts(env[i]);
		_puts("\n");
	}
}
