#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void redirect(int fd1, int fd2) {
    int backup = dup(fd2);
    dup2(fd1, fd2);
    close(fd1);
    close(backup);
}