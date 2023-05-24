#include "shell.h"

/**
 * trvs_path - traverse paths in PATH
 * @command: input
 * @path: path of PsATH
 * Return: command with it's path
 */
char *trvs_path(char *command, char *path)
{
	struct stat file_stat;
	char command_path[MAX_COMMAND_LENGTH];
	char *path_token;
	char *path_copy = _strdup(path);

	command_path[0] = '\0';
	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		_strcpy(command_path, path_token);
		_strcat(command_path, "/");
		_strcat(command_path, command);
		if (stat(command_path, &file_stat) == 0 && file_stat.st_mode & S_IXUSR)
		{
			free(path_copy);
			return (_strdup(command_path));
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
