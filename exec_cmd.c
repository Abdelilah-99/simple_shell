#include "shell.h"

/**
 * execute_command - execute a cmd
 * @command: cmd from the input
 * Return: executing of the command
 */

void execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS], *token, *command_path = NULL;
	int i = 0;
	pid_t pid;

	token = strtok(command, " ");
	if (_strcmp(command, "env") == 0)
	{
		print_environment();
		return;
	}
	for (; token != NULL && i < MAX_ARGUMENTS - 1; i++)
	{
		arguments[i] = token;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;
	if (_strcmp(command, "exit") == 0)
	{
		free(command);
		print_exit(arguments);
		return;
	}
	command_path = find_command_path(arguments[0], _getenv("PATH"));
	if (command_path == NULL)
	{
		_puts("Error: Command not found or not executable");
		_puts("\n");
		return;
	}
	pid = fork();
	if (pid == -1)
		perror("fork"), exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		execve(command_path, arguments, environ);
		perror("execve"), exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	free(command_path);
}
