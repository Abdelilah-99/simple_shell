#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
extern char **environ;
char *_getenv(const char *name);
char *_strcpy(char *dest, char *src);
int _putchar(char c);
void _puts(char *str);
int main()
{
	char *command = NULL;
	size_t command_length = 0;
	ssize_t characters_read;
	int i = 0;
	int j = 0;
	for (;;)
	{
		j = 0;
		_puts("simple_shell> ");
		characters_read = getline(&command, &command_length, stdin);
		if (characters_read <= 0)
		{
			if (characters_read == -1)
			{
				// End of file condition (Ctrl+D)
				_puts("\n");
			}
			break;
		}
		if (command == NULL)
		{
			continue;
		}
		// Remove the trailing newline character
		if (command[characters_read - 1] == '\n')
			command[characters_read - 1] = '\0';
		while (isspace(command[j]))
			j++;
		if (command[j] == '\0')
			continue;
		char *arguments[MAX_ARGUMENTS];
		char *token = strtok(command, " ");
		int i = 0;

		while (token != NULL && i < MAX_ARGUMENTS)
		{
			arguments[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		arguments[i] = NULL;
		struct stat file_stat;
		char command_path[MAX_COMMAND_LENGTH];

		if (command[0] == '/')
		{
			struct stat file_stat;
			if (stat(arguments[0], &file_stat) == 0)
			{
				_strcpy(command_path, arguments[0]);
			}
			else
			{
				_puts("command not found: ");
				_puts(arguments[0]);
				_puts("\n");
				continue;
			}
		}
		else
		{
			char *path = _getenv("PATH");
			if (path == NULL)
			{
				_puts("Failed to get PATH environment variable.\n");
				continue;
			}

			char *path_copy = strdup(path);
			if (path_copy == NULL)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}

			char *path_token = strtok(path_copy, ":");
			int command_found = 0;

			while (path_token != NULL)
			{
				strcpy(command_path, path_token);
				strcat(command_path, "/");
				strcat(command_path, arguments[0]);
				if (stat(command_path, &file_stat) == 0 && file_stat.st_mode & S_IXUSR)
				{
					command_found = 1;
					break;
				}

				path_token = strtok(NULL, ":");
			}

			free(path_copy);

			if (!command_found)
			{
				_puts("command not found: ");
				_puts(arguments[0]);
				_puts("\n");
				continue;
			}
		}

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			execve(command_path, arguments, NULL);

			// execve only returns if there's an error
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
char *_getenv(const char *name)
{
	// search for name in the environment list
	for (int i = 0; environ[i]; i++)
	{
		// get the variable name from the environment list
		char *env_name = environ[i];

		// compare the variable name with the given name
		if (strncmp(env_name, name, strlen(name)) == 0)
		{
			// return the value of the variable
			return strchr(env_name, '=') + 1;
		}
	}

	// variable not found
	return NULL;
}
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
int _putchar(char c)
{
	return (write(1, &c, 1));
}
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	while (dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
