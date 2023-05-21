#include "shell.h"
/**
 * print_environment - environ a pointer to an arrays and
 * each array point to string
*/
void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		_puts(*env);
		_puts("\n");
		env++;
	}
}
