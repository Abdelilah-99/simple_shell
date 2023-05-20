#include "shell.h"

/**
 * execute_command - execute command
 * @command: command from the input
 * Return: executiong of the command if it existe
 */

void execute_command(char *command)
{
char *arguments[MAX_ARGUMENTS], *token, *command_path;
int i = 0;
pid_t pid;
token = _strtok(command, " ");
if (_strcmp(command, "env") == 0)
{
print_environment();
return;
}
for (; token != NULL && i < MAX_ARGUMENTS - 1; i++)
{
arguments[i] = token;
token = _strtok(NULL, " ");
}
arguments[i] = NULL;
if (_strcmp(command, "exit") == 0)
{
print_exit(arguments);
return;
}
comman_path = find_command_path(arguments[0], _getenv("PATH"));
if (command_path == NULL)
{
_puts("Error: Command not found or not executable: ");
_puts(arguments[0]);
_puts("\n");
return;
}
pid = fork();
if (pid == -1)
perror("fork"), exit(EXIT_FAILURE);
else if (pid == 0)
{
execve(command_path, arguments, NULL);
perror("execve", exit(EXIT_FAILURE);
}
else
wait(NULL);
}

