/*************************************************************************
	> File Name: 1_server.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sun 11 Jul 2021 10:15:47 PM CST
 ************************************************************************/

#include "head.h"

int main(int argc, char **argv) {
    int server_listen, sockfd, port;
    if (argc != 2) {
        fprintf(stderr, "usage: %s port!\n", argv[0]);
        exit(1);
    }
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        exit(1);
    }

    //while(1) {
    if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
        perror("accept error");
        exit(1);
    }
    printf("something is online \n");
    // 不停收信息，不然一次连接只收到一条
    while(1) {
        char buff[512] = {0};
        recv(sockfd, buff, sizeof(buff), 0);
        printf("recv: %s\n", buff);
    }
    //}
}
