/*************************************************************************
	> File Name: test.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan  7 21:17:53 2021
 ************************************************************************/

#include <stdio.h>

int main() {
    int age;
    // 0 stdin file
    make_nonblock(0);
    sleep(5);
    int ret = scanf("%d", &age);
    printf("age is %d years <%d> \n", age, ret);
    perror("scanf");
    return 0;
}

