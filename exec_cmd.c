#include "shell.h"

/**
 * execute_command - execute command
 * @command: commsand from the input
 * Return: executiong of the command if it existe
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
	if (_strcmp(command[0], "exit") == 0)
	{
		adv_exit(command);
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
