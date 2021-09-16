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

int recv_str_nonblock(int sockfd, char *buff, long size, int timeout) {
    // receive name to put into buff, by select
    fd_set rfds; //read fd
    struct timeval tv;
    int retval;

    //empty
    FD_ZERO(&rfds);
    //add fd
    FD_SET(sockfd, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = timeout;

    // nfds: the highest-numbered file descriptor + 1
    retval = select(sockfd+1, &rfds, NULL, NULL, &tv);
    if (retval <= 0) {
        return -1;
    } else {
        //recv data
        int recvsize = recv(sockfd, buff, size, 0);
        if (recvsize <= 0) {
            return -1;
        }
    }
    return 0;
}
