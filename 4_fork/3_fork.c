/*************************************************************************
	> File Name: 3_fork.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan 14 16:00:55 2021
 ************************************************************************/

#include <stdio.h>
#include <sys/wait.h>
#include "head.h"

int main() {
    pid_t pid[10];
    for(int i = 0; i < 10; i++){
        pid[i] = fork();
        printf("pid = %d\n", pid[i]);
    }
    return 0;
}
