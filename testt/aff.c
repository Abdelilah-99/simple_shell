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
void execute_command(char *command);
char *find_command_path(char *command, char *path);
int search_command_in_paths(char *command, char *path_copy, struct stat *file_stat);
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

void execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS], *token, *command_path;
	int i = 0;
	pid_t pid;
	token = strtok(command, " ");
	if (strcmp(command, "env") == 0)
	{
		print_environment(); // Call the print_environment function
		return;
	}
	for (; token != NULL && i < MAX_ARGUMENTS - 1; i++)
	{
		arguments[i] = token;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;
	command_path = find_command_path(arguments[0], getenv("PATH"));
	if (command_path == NULL)
	{
		printf("Error: Command not found or not executable: %s\n", arguments[0]);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork"), exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command_path, arguments, NULL);
		perror("execve"), exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

int search_command_in_paths(char *command, char *path_copy, struct stat *file_stat)
{
	char command_path[MAX_COMMAND_LENGTH];
	char *path_token = strtok(path_copy, ":");
	int command_found = 0;

	while (path_token != NULL)
	{
		strcpy(command_path, path_token);
		strcat(command_path, "/");
		strcat(command_path, command);
		if (stat(command_path, file_stat) == 0 && file_stat->st_mode & S_IXUSR)
		{
			command_found = 1;
			break;
		}
		path_token = strtok(NULL, ":");
	}

	return command_found;
}

char *find_command_path(char *command, char *path)
{
	struct stat file_stat;
	char command_path[MAX_COMMAND_LENGTH], *path_copy;
	char *command_path_copy;

	if (command[0] == '/')
	{
		if (stat(command, &file_stat) == 0)
			strcpy(command_path, command);
		else
			return NULL;
	}
	else
	{
		if (path == NULL)
		{
			printf("Error: Failed to get PATH environment variable.\n");
			return NULL;
		}
		path_copy = strdup(path);
		if (path_copy == NULL)
			perror("strdup"), exit(EXIT_FAILURE);

		if (!search_command_in_paths(command, path_copy, &file_stat))
		{
			free(path_copy);
			return NULL;
		}

		free(path_copy);
	}

	command_path_copy = strdup(command_path);
	if (command_path_copy == NULL)
		perror("strdup"), exit(EXIT_FAILURE);

	return command_path_copy;
}

void run_shell()
{
    char *command = NULL;
    size_t command_length = 0;
    ssize_t characters_read;

    while (1)
    {
        printf("$ ");

        characters_read = getline(&command, &command_length, stdin);

        if (characters_read <= 0)
        {
            if (characters_read == -1)
            {
                // End of file condition (Ctrl+D)
                printf("\n");
                free(command); // Free the allocated memory
                break;
            }
        }
        trim_whitespace(command);

        if (command[0] == '#' || command[0] == '\0')
        {
            continue;
        }

        execute_command(command);
    }
}

int main()
{
    run_shell();
    return 0;
}
