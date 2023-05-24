#include "shell.h"

/**
 * run_shell - run tshe shell project
 */
void run_shell(void)
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t ch_read;

	while (1)
	{
		command = malloc(32 * sizeof(char));
		if (command == NULL)
			break;
		if (isatty(STDIN_FILENO))
			_puts("$ ");
		ch_read = getline(&command, &command_length, stdin);
		if (ch_read <= 0)
		{
			if (ch_read == -1)
			break;
		}
		trim_whitespace(command);
		if (command[0] == '\0')
			continue;
		execute_command(command);
	}
		free(command);
}
