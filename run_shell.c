#include "shell.h"

/**
 * run_shell - rune tshe shell project
 */
void run_shell(void)
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t ch_read;
	int is_inter = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_inter)
			_puts("$ ");
		ch_read = getline(&command, &command_length, stdin);
		if (ch_read == -1)
		{
			if (ch_read == EOF)
			{
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_SUCCESS);
			}
		}
		trim_whitespace(command);
		if (command[0] == '\0')
			continue;
		execute_command(command);
		if (!is_inter)
			break;
	}
	free(command);
}
