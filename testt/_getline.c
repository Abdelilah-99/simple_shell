#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
void _getline(void)
{
	char buffer[BUFFER_SIZE];
	int buffpos, buffsize;
	char *input_str = NULL;
	char current_char;
	int input_len = 0;

	for (;;)
	{
		if (buffpos >= buffsize)
		{
			buffsize = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffpos = 0;
			if (buffsize == 0)
				return (input_str);
			else if (buffsize < 0)
			{
				perror("read");
				return (NULL);
			}
		}
		current_char = buffer[buffpos];
		buffpos++;
		if (current_char == '\n')
		{
			input_str = realloc(input_str, input_len + 1);
			input_str[input_len] = '\0';
			return (input_str);
		}
		else
		{
			input_str = realloc(input_str, input_len + 1);
			input_str[input_len] = current_char;
			input_len++;
		}
	}
}
