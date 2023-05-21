#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 1024

void print_environment();
void trim_whitespace(char *str);
void execute_command(char *command, char *path);
void parse_arguments(char *command, char *arguments[], int max_arguments);
void execute_child(char *command_path, char *arguments[]);
char *find_cd_path(char *command, char *path);
char *command_path(char *directory, char *command);
char *search_dir(char *command, char *directories);
void run_shell();

void print_environment()
{
	extern char **environ;
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

void trim_whitespace(char *str)
{
	int start = 0, end = strlen(str) - 1;
	int i;

	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;

	while (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')
		end--;

	for (i = 0; i <= end - start; i++)
		str[i] = str[start + i];

	str[i] = '\0';
}

void execute_command(char *command, char *path)
{
	char *arguments[MAX_ARGUMENTS];
	char *command_path = find_cd_path(arguments[0], path);
	pid_t pid = fork();
	parse_arguments(command, arguments, MAX_ARGUMENTS);
	if (strcmp(command, "env") == 0)
	{
		print_environment();
		return;
	}
	if (command_path == NULL)
	{
		printf("Error: Command not found or not executable: %s\n", arguments[0]);
		return;
	}
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_child(command_path, arguments);
	}
	else
	{
		wait(NULL);
	}
}

void parse_arguments(char *command, char *arguments[], int max_arguments)
{
	char *token = strtok(command, " ");
	int i = 0;
	while (token != NULL && i < max_arguments - 1)
	{
		arguments[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;
}

void execute_child(char *command_path, char *arguments[])
{
	execve(command_path, arguments, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

char *find_cd_path(char *command, char *path)
{
	if (command[0] == '/')
	{
		struct stat file_stat;
		if (stat(command, &file_stat) == 0)
		{
			return strdup(command);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		if (path == NULL)
		{
			printf("Error: Failed to get PATH environment variable.\n");
			return NULL;
		}

		return search_dir(command, path);
	}
}

char *command_path(char *directory, char *command)
{
	char path[MAX_COMMAND_LENGTH];
	struct stat file_stat;
	snprintf(path, sizeof(path), "%s/%s", directory, command);
	if (stat(path, &file_stat) == 0 && file_stat.st_mode & S_IXUSR)
	{
		return strdup(path);
	}
	return NULL;
}

char *search_dir(char *command, char *directories)
{
	char *path_copy = strdup(directories);
	char *path_token = strtok(path_copy, ":");
	char *cmd_path = NULL;
	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	while (path_token != NULL)
	{
		cmd_path = command_path(path_token, command);
		if (cmd_path != NULL)
		{
			break;
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	if (cmd_path == NULL)
	{
		printf("Error: Command not found or not executable: %s\n", command);
		return NULL;
	}
	return strdup(cmd_path);
}

void run_shell()
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t characters_read;

	while (1)
	{
		printf("$ ");
		command = malloc(32 * sizeof(char));
		if (command == NULL)
		{
			free(command);
			break;
		}
		characters_read = getline(&command, &command_length, stdin);

		if (characters_read <= 0)
		{
			if (characters_read == -1)
			{
				// End of file condition (Ctrl+D)
				printf("\n");
			}
			break;
		}
		trim_whitespace(command);

		if (command[0] == '#')
		{
			free(command);
			continue;
		}

		execute_command(command, getenv("PATH"));

		free(command);
	}
}

int main()
{
	run_shell();
	return 0;
}
