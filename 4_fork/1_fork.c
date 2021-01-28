/*************************************************************************
	> File Name: 1_fork.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan 14 10:50:25 2021
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char name[200] = {0};
    scanf("%s", name);
    printf("%s", name);
    fork();
    return 0;
}
