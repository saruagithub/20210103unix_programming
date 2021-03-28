/*************************************************************************
	> File Name: 1_test.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sat 20 Mar 2021 10:37:32 AM CST
 ************************************************************************/

#include "head.h"

struct MyArg{
    char name[20];
    int age;
};

void *print(void *arg) {
    struct MyArg *p;
    p = (struct MyArg *)arg;
    printf("In Thread!, name = %s, age = %d \n",p->name, p->age);
}

int main() {
    pthread_t thread;
    char name[20] = "wangxue";
    int age = 22;
    struct MyArg args;

    strcpy(args.name, name);
    args.age = age;

    pthread_create(&thread, NULL, print, &args);
    usleep(1);
    return 0;
}
