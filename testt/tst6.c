#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
void _puts(char *str);
int _putchar(char c);
int main() {
    char *command = NULL;
    size_t command_length = 0;
    ssize_t characters_read;

    while (1) {
        _puts("$ ");

        characters_read = getline(&command, &command_length, stdin);

        if (characters_read == -1) {
            // Handle end of file condition (Ctrl+D)
			free(characters_read)
            _puts("\n");
            break;
        }

        // Remove the trailing newline character
        if (command[characters_read - 1] == '\n') {
            command[characters_read - 1] = '\0';
        }

        char *arguments[MAX_ARGUMENTS];
        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            arguments[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        arguments[i] = NULL;

        char *path = getenv("PATH");
        if (path == NULL) {
            printf("Error: Failed to get PATH environment variable.\n");
            continue;
        }

        char *path_copy = (char *)malloc(strlen(path) + 1);
        if (path_copy == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(path_copy, path);

        char *path_token = strtok(path_copy, ":");
        int command_found = 0;

        char command_path[MAX_COMMAND_LENGTH];
        while (path_token != NULL) {
            strcpy(command_path, path_token);
            strcat(command_path, "/");
            strcat(command_path, arguments[0]);

            struct stat file_stat;
            if (stat(command_path, &file_stat) == 0 && file_stat.st_mode & S_IXUSR) {
                command_found = 1;
                break;
            }

            path_token = strtok(NULL, ":");
        }

        free(path_copy);

        if (!command_found) {
            printf("Error: Command not found or not executable: %s\n", arguments[0]);
            continue;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execve(command_path, arguments, NULL);

            // execve only returns if there's an error
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }
    }

    free(command);
    return 0;
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
