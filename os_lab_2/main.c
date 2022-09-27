#include <fcntl.h>	
#include <sys/stat.h>	
#include <sys/types.h>	
#include <unistd.h>	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 128

char* const child_args[] = {"child", NULL};
char* child_env[] = { NULL };

char* read_string(pid_t fd) {
    char* buffer = calloc(sizeof(char), BUFFER_SIZE);
    if (read(fd, buffer, BUFFER_SIZE) <= 0) {
        return NULL;
    }
    char *string = calloc(sizeof(char), strlen(buffer) - 1);
    strncpy(string, buffer, strlen(buffer) - 1);
    free(buffer);
    return string;
}

int main() {
    char* filename1 = read_string(0);
    char* filename2 = read_string(0);


    pid_t fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    pid_t filedes1, filedes2;

    if ((filedes1 = open(filename1, O_WRONLY)) < 0) {
        perror(filename1);
        exit(1);
    }

    if ((filedes2 = open(filename2, O_WRONLY)) < 0) {
        perror(filename2);
        exit(2);
    }

    pid_t P1 = fork();

    if (P1 < 0) {
        perror("fork");
        exit(3);
    }

    else if (P1 != 0) {
        pid_t P2 = fork();
        if (P2 < 0) {
            perror("fork");
            exit(4);
        }
        else if (P2 != 0) {
            char* string = read_string(0);
            if (string == NULL) {
                kill(P1, SIGKILL);
                kill(P2, SIGKILL);
                return 0;
            }
            while (string != NULL) {
                int n = strlen(string);
                if (n > 10) {
                    write(fd2[1], string, n);
                }
                else {
                    write(fd1[1], string, n);
                }
                string = read_string(0);
            }
        }
        else {
            if (dup2(fd2[0], 0) < 0) {
                perror("Redirection error");
                exit(9);
            }
            if (dup2(filedes2, 1) < 0) {
                perror("Redirection error");
                exit(10);
            }
            execve(child_args[0], child_args, child_env);
            perror("execve");
            exit(11);
        }
    }

    else {
        if (dup2(fd1[0], 0) < 0) {
            perror("Redirection error");
            exit(6);
        }
        if (dup2(filedes1, 1) < 0) {
            perror("Redirection error");
            exit(7);
        }
        execve(child_args[0], child_args, child_env);
        perror("execve");
        exit(8);
    }
}