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
    command = malloc(32 * sizeof(char));
    if (command == NULL) {
        free(command);
        break;
    }
    characters_read = getline(&command, &command_length, stdin);

    if (characters_read == -1) {
        // Handle end of file condition (Ctrl+D)
        printf("\n");
        free(command);
        break;
    }

    // Remove the trailing newline character
    

    token = strtok(command, " ");
    if (token == NULL) {
        free(token);
        free(command);
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
        free(argv[0]); // Free argv if execve fails
        free(command);
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL);
    }
    
    free(command); // Free memory before the next iteration
}

    return 0;
}
