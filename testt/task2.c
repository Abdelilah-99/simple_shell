#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main()
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t characters_read;
	pid_t pid;

	while (1)
	{
		char *arguments[MAX_ARGUMENTS];
		char *token;
		int i = 0;

		printf("simple_shell> ");
		command = malloc(32 * sizeof(char));
		if (command == NULL)
		{
			free(command);
			break;
		}
		characters_read = getline(&command, &command_length, stdin);

		if (characters_read == -1)
		{
			// Handle end of file condition (Ctrl+D)
			printf("\n");
			break;
		}
		
		// Remove the trailing newline character
		if (command[characters_read - 1] == '\n')
		{
			command[characters_read - 1] = '\0';
		}

		token = strtok(command, " ");

		while (token != NULL && i < MAX_ARGUMENTS - 1)
		{
			arguments[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		arguments[i] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			execve(arguments[0], arguments, NULL);

			// execve only returns if an error occurs
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			wait(NULL);
		}
	}

	free(command);
	return 0;
}
