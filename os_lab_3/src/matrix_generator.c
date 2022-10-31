#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char *itoa(int x) {
int n = 1;
int a = abs(x);
while (a >= 10) {
a /= 10;
n++;
}
char *result;
if (x < 0) {
result = calloc(sizeof(char), n + 1);
a = abs(x);
for (int i = n; i > 0; --i) {
result[i] = a % 10 + 48;
a /= 10;
}
result[0] = '-';
}
else {
result = calloc(sizeof(char), n);
a = x;
for (int i = n - 1; i >= 0; --i) {
result[i] = a % 10 + 48;
a /= 10;
}
}
return result;
}

int main(int argc, const char **argv) {
if (argc != 3) {
char *err = "Error: invalid arguments\n";
write(2, err, strlen(err));
exit(EXIT_FAILURE);
}
int filedes;
if ((filedes = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0) {
perror(argv[2]);
exit(EXIT_FAILURE);
}
srand(clock());
int x;
const char *numb = argv[1];
write(filedes, numb, strlen(numb));
char nl = '\n';
write(filedes, &nl, 1);
int num = atoi(argv[1]);
for (int i = 0; i < num * num; ++i) {
x = rand() % 200000 - 100000;
char *numb = itoa(x);
write(filedes, numb, strlen(numb));
char space = ' ';
write(filedes, &space, 1);
}
close(filedes);
}