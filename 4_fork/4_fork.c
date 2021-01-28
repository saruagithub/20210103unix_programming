/*************************************************************************
	> File Name: 4_fork.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan 14 16:30:42 2021
 ************************************************************************/

#include <stdio.h>
#include <sys/wait.h>
#include "head.h"

int main() {
    pid_t pid;
    int i;
    for (i = 1; i <= 10; i++) {
        if ((pid = fork()) < 0) {
            perror("fork wrong");
            exit(1);
        }
        //if(pid == 0) break;
    }
    printf("I am the %d child\n", i);
    sleep(5);
    return 0;
}
