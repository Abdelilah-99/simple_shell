#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 1024
extern char **environ;
void triming_whitespace(char *str)
{
    int i;

    int start = 0, end = strlen(str) - 1;

    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
        start++;

    while (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')
        end--;

    for (i = 0; i <= end - start; i++)
        str[i] = str[start + i];

    str[i] = '\0';
}
void print_prompt()
{
    printf("$ ");
}

char *read_command()
{
    char *command = NULL;
    size_t command_length = 0;
    ssize_t characters_read = getline(&command, &command_length, stdin);

    if (characters_read <= 0)
    {
        if (characters_read == -1)
        {
            // End of file condition (Ctrl+D)
            printf("\n");
        }
        free(command);
        return NULL;
    }
    triming_whitespace(command);
    return command;
}
void tokenize_command(char *command, char **arguments)
{
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARGUMENTS - 1)
    {
        arguments[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    arguments[i] = NULL;
}

int find_executable_path(char *command, char *path, char *command_path)
{
    char *path_copy = strdup(path);
    struct stat file_stat;
    char *path_token = strtok(path_copy, ":");
    int command_found = 0;
    if (path_copy == NULL)
    {
        perror("strdup");
        free(path_copy);
        exit(EXIT_FAILURE);
    }

    while (path_token != NULL)
    {
        strcpy(command_path, path_token);
        strcat(command_path, "/");
        strcat(command_path, command);
        if (stat(command_path, &file_stat) == 0 && file_stat.st_mode & S_IXUSR)
        {
            command_found = 1;
            break;
        }

        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return command_found;
}

void execute_command(char *command_path, char **arguments)
{
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

int main()
{
    char *command = NULL;
    char *arguments[MAX_ARGUMENTS];
    char *path = getenv("PATH");
    char command_path[MAX_COMMAND_LENGTH];

    while (1)
    {
        char **env = environ;
        int command_found = find_executable_path(arguments[0], path, command_path);
        print_prompt();
        command = read_command();
        if (command == NULL)
        {
            break;
        }

        if (command[0] == '#')
        {
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

        tokenize_command(command, arguments);

        if (command[0] == '/')
        {
            struct stat file_stat;
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
            if (!command_found)
            {
                printf("Error: Command not found or not executable: %s\n", arguments[0]);
                continue;
            }
        }

        execute_command(command_path, arguments);
    }

    free(command);
    return 0;
}
