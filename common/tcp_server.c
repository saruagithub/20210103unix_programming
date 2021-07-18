/*************************************************************************
	> File Name: tcp_server.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sun 11 Jul 2021 09:00:15 PM CST
 ************************************************************************/

#include "head.h"

int socket_create(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        return -1;
    }
    if (listen(sockfd, 20) < 0) {
        return -1;
    }

    return sockfd;
}
