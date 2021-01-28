/*************************************************************************
	> File Name: 2_fork.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan 14 11:38:32 2021
 ************************************************************************/

#include <stdio.h>
#include <sys/wait.h>
#include "head.h"

int main() {
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        perror("fork() memory not enough");
        exit(1);
    }
    if (pid == 0) {
        sleep(5);
        printf("child process!\n");
        return 1;
    } else {
        wait(&status);
        printf("parent process, wait status = %d\n", status);
    }
    return 0;
}
