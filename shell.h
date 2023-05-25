#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024
#define BUFSIZE 1024
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 1024

extern char **environ;
int _strlen(char *s);
void _puts(char *str);
char *_strcpy(char *dest, const char *src);
char *_getenv(char *name);
int _putchar(char c);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
void print_environment(void);
void trim_whitespace(char *str);
void execute_command(char *command);
char *find_command_path(char *command, char *path);
void run_shell(void);
char *trvs_path(char *command, char *path);
void print_exit(char *arr[]);
int _atoi(char *s);
char *_strchr(const char *str, int c);
int _strncmp(char *s1, char *s2, size_t n);
char *_strtok(char *str, const char *delim);
int is_number(const char *str);
int _isdigit(int c);

#endif
