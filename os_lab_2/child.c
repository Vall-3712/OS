#include <sys/types.h>	
#include <unistd.h>	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128

char* read_string(pid_t fd) {
    char* buffer = calloc(sizeof(char), BUFFER_SIZE);
    if (read(fd, buffer, BUFFER_SIZE) <= 0) {
        return NULL;
    }
    char *string = calloc(sizeof(char), strlen(buffer));
    strncpy(string, buffer, strlen(buffer));
    free(buffer);
    return string;
}

char* reverse(char *string, int n) {
    char* string_rev = calloc(sizeof(char), n);
    for (int i = n - 1; i >= 0; i--) {
        string_rev[n - i - 1] = string[i];
    }
    return string_rev;
}

int main() {
    while (1) {
        char* string = read_string(0);

        int n = strlen(string);
        char* string_rev = reverse(string, n);

        write(1, string_rev, n);

        char newline = '\n';
        write(1, &newline, 1);
    }
}