#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LENGTH 50

char** s_strtok(char* str) {
    char** word;
    int a = 0, t = 0;
    char token[LENGTH];
	int i;

    // Allocate memory for the array of character pointers
    word = malloc(LENGTH * sizeof(char*));

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            token[t] = str[i];
            t++;
        } else {
            token[t] = '\0';
            word[a] = malloc((t + 1) * sizeof(char)); // Allocate memory for each word
            strcpy(word[a], token);
            a++;
            t = 0;
        }
    }

    // Terminate the array with a NULL pointer
    word[a] = NULL;
    a++;
    word = realloc(word, a * sizeof(char *));
    return word;
}

int main() {
    char* strg = "hey this is a test";
    char** words = s_strtok(strg);
	int i;

    // Determine the length of the array by iterating until the NULL pointer
    int length = 0;
    while (words[length] != NULL) {
        length++;
    }

    // Print the words
    for (i = 0; i < length; i++) {
        printf("%s\n", words[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    for (i = 0; i < length; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
