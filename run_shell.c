#include "shell.h"

/**
 * run_shell - rune tshe shell project
 */
void run_shell(void)
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t ch_read;
	int is_inter = isatty(STDIN_FILENO), i;

	while (1)
	{
		if (is_inter)
			_puts("$ ");
		ch_read = getline(&command, &command_length, stdin);
		if (ch_read == -1)
		{
			if (ch_read == EOF)
				break;
			else
			{
				perror("getline");
				exit(0);
			}
		}
		trim_whitespace(command);
		if (command[0] == '\0')
			continue;
		for (i = 0; command[i]; i++)
		{
			if (command[i] == '#')
				command[i] = '\0';
		}
		execute_command(command);
	}
	free(command);
}
