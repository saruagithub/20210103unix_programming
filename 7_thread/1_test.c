/*************************************************************************
	> File Name: 1_test.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sat 20 Mar 2021 10:37:32 AM CST
 ************************************************************************/

#include "head.h"

void *print(void *arg) {
    printf("In Thread!\n");
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, print, NULL);
    usleep(1);
    return 0;
}
