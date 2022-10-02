#include <sys/types.h>	
#include <unistd.h>	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128

char* read_string(pid_t fd) {
    char* buffer = calloc(sizeof(char), BUFFER_SIZE);
    char c;
    if (read(fd, &c, 1) <= 0) {
        return NULL;
    }
    if (c == '\0') {
        return NULL;
    }
    int i = 0;
    buffer[i++] = c;
    while (read(fd, &c, 1) > 0){
        if (( c != '\0') && (c != '\n')) {
            buffer[i++] = c;
        }
        else{
            break;
        }
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

        if (string == NULL) {
            break;
        }

        int n = strlen(string);
        char* string_rev = reverse(string, n);

        write(1, string_rev, n);

        char newline = '\n';
        write(1, &newline, 1);
    }
}