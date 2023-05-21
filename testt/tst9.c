#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char *command = NULL;
    size_t command_length = 0;
    ssize_t characters_read;
    char *token;
    pid_t pid;

    while (1) {
        printf("$ ");
        command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
        if (command == NULL) {
            perror("malloc");
            break;
        }
        characters_read = getline(&command, &command_length, stdin);

        if (characters_read == -1) {
            // Handle end of file condition (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        if (command[characters_read - 1] == '\n') {
            command[characters_read - 1] = '\0';
        }

        token = strtok(command, " ");
        if (token == NULL) {
            continue; // Empty command, prompt again
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            free(command);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char **argv = malloc(2 * sizeof(char *));
            if (argv == NULL) {
                perror("malloc");
                free(command);
                exit(EXIT_FAILURE);
            }
            argv[0] = token;
            argv[1] = NULL;

            execve(token, argv, NULL);

            // execve only returns if an error occurs
            perror("execve");
            free(argv); // Free argv if execve fails
            free(command);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }

        free(command); // Free memory allocated for command
    }

    return 0;
}
