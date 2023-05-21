#include "shell.h"

/**
 * find_command_path - find command's path
 * @command: input
 * @path: path
 * Return: command in a path
 */

char *find_command_path(char *command, char *path)
{
	struct stat file_stat;

	if (command[0] == '/')
	{
		if (stat(command, &file_stat) == 0)
			return (_strdup(command));
		else
			return (NULL);
	}
	else
	{
		if (path == NULL)
		{
			_puts("Error: Failed to get PATH environment variable. ");
			_puts("\n");
			return (NULL);
		}
		return (trvs_path(command, path));
	}
}
