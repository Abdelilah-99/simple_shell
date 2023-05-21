#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 50

int main() {
    char *line = NULL;
    size_t len = 0;
    int x = 0;
    ssize_t read;
    char *token;
    char *arr = malloc(L * sizeof(char));
    
    printf("Enter a line of text:\n");
    read = getline(&line, &len, stdin);

    if (read != -1) {
        token = strtok(line, " ");
        
        while (token != NULL) {
            int lg = strlen(token);
            arr[x] = malloc((lg + 1) * sizeof(char));
            strcpy(arr[x], token);
            printf("%s\n", arr[x]);
            token = strtok(NULL, " ");
            x++;
        }
    }
    
    int i = 0;
    while (arr[i] != NULL) {
        printf("elem %d: %s\n", i + 1, arr[i]);
        i++;
    }
    
    // Free the allocated memory
    for (i = 0; i < x; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return 0;
}
