#ifndef MYSHELL_H
#define MYSHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 1024

char *read_command(void);
void remove_newline(char *str);
char *get_token(char *command);
void execute_command(char *token);
void exit_shell();
char *triming_whitespace(char *str);
#endif
