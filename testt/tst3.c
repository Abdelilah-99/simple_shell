#include "myshell.h"

int main()
{
	char *command;
	char *token;

	while (1)
	{
		command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
		if (command == NULL)
		{
			perror("malloc");
			break;
		}
		command = read_command();
		if (command == NULL)
		{
			break;
		}

		token = triming_whitespace(command);
		if (token == NULL || strlen(token) == 0)
		{
			free(command);
			continue;
		}

		execute_command(token);

		free(command);
	}

	return 0;
}
#include "myshell.h"

void execute_command(char *token)
{
	
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// Child process
		char **argv = malloc(2 * sizeof(char *));
		if (argv == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		argv[0] = token;
		argv[1] = NULL;

		execve(token, argv, NULL);

		// execve only returns if an error occurs
		perror("execve");
		free(argv); // Free argv if execve fails
		exit(EXIT_FAILURE);
	}
	else
	{
		// Parent process
		wait(NULL);
	}
}
#include "myshell.h"

char *get_token(char *command)
{
	char *token;

	token = strtok(command, "");
	if (token == NULL)
	{
		return NULL; // Empty command
	}

	return token;
}
#include "myshell.h"

char *read_command(void)
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t characters_read;

	printf("$ ");
	command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
	if (command == NULL)
	{
		return NULL;
	}
	characters_read = getline(&command, &command_length, stdin);
	if (characters_read == -1)
	{
		// Handle end of file condition (Ctrl+D)
		free(command);
		return NULL;
	}

	return command;
}
#include "myshell.h"

char *triming_whitespace(char *str)
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

    return str;
}
