/*************************************************************************
	> File Name: 1_client.c
	> Author: wangxue
	> Mail: 
	> Created Time: Mon 12 Jul 2021 08:59:36 PM CST
 ************************************************************************/

#include "head.h"

int main(int argc, char **argv) {
    int sockfd, port;
    char buff[512] = {0}, ip[20] = {0};

    if (argc != 3) {
        fprintf(stderr, "usage: %s ip port\n", argv[0]);
        exit(1);
    }
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);
    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect error");
        exit(1);
    }

    while(1) {
        scanf("%[^\n]s", buff);
        getchar();
        if (!strlen(buff)) continue;
        send(sockfd, buff, strlen(buff), 0); 
        bzero(buff, sizeof(buff));
    }
}

