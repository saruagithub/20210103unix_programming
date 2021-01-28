/*************************************************************************
	> File Name: 5_exec.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan 14 17:23:57 2021
 ************************************************************************/

#include<stdio.h>
#include "head.h"

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork wrong");
        exit(1);
    }
    if (pid == 0) {
        // child run exec
        execlp("vim", "vim", "5_exec.c", NULL);
        sleep(1000);
        printf("In End \n");
    } else {
        wait(NULL);
        printf("parent!\n");
        sleep(5);
    }
    return 0;
}
