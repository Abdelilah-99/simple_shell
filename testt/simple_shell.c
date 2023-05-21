#include "simple_shell.h"
/**
 * 
 * 
*/
int main (void)
{
	char *line = NULL;
	size_t len = 0;
	int read;
	char *token;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		_puts("$ ");
		read = getline(&line, &len, stdin);
		if (read != -1)
		{
			
		}
		else
			break;
	}
	return (0);
}
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
int _putchar(char c)
{
return (write(1, &c, 1));
}
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
