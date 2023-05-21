#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 1024

int main()
{
    char *command = NULL;
    size_t command_length = 0;
    ssize_t characters_read;
    struct stat file_stat;
    char command_path[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    char *token;
    char *path = getenv("PATH");
    char *path_copy;
    char *path_token;
    int i;
    int command_found;
    pid_t pid;
    extern char **environ;
    char **env = environ;
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

        // Remove the trailing newline character
        if (command[characters_read - 1] == '\n')
        {
            command[characters_read - 1] = '\0';
        }
        if (command[0] == '#')
        {
            free(command);
            continue;
        }
        if (strcmp(command, "env") == 0)
        {
            while (*env != NULL)
            {
                printf("%s\n", *env);
                env++;
            }
            continue;
        }
        token = strtok(command, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGUMENTS - 1)
        {
            arguments[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        arguments[i] = NULL;

        if (command[0] == '/')
        {
            if (stat(arguments[0], &file_stat) == 0)
            {
                strcpy(command_path, arguments[0]);
            }
            else
            {
                printf("Error: Command not found or not executable: %s\n", arguments[0]);
                continue;
            }
        }
        else
        {
            if (path == NULL)
            {
                printf("Error: Failed to get PATH environment variable.\n");
                continue;
            }

            path_copy = strdup(path);
            if (path_copy == NULL)
            {
                perror("strdup");
                exit(EXIT_FAILURE);
            }

            path_token = strtok(path_copy, ":");
            command_found = 0;

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
                printf("Error: Command not found or not executable: %s\n", arguments[0]);
                continue;
            }
        }

        pid = fork();
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
