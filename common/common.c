/*************************************************************************
	> File Name: common.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan  7 20:37:41 2021
 ************************************************************************/

#include "head.h"
int make_nonblock(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    // 保留原有的flag，再添加上非阻塞的flag，所以用or
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}

int make_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    // ~末尾keep 0, 其他位不变
    flag &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}
