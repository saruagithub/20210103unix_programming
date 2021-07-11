/*************************************************************************
	> File Name: tcp_client.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sun 11 Jul 2021 09:48:34 PM CST
 ************************************************************************/

#include "head.h"

int socket_connect(char *ip, int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return sockfd;
}

