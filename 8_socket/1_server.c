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

    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    while(1) {
        if ((sockfd = accept(server_listen, (struct sockaddr_in *)&client, &len)) < 0) {
            perror("accept error");
            exit(1);
        }
        // after three hands
        printf("<%s> is online \n", inet_ntoa(client.sin_addr));
        pid_t pid;
        if ((pid = fork()) < 0) {
            exit(1);
        }
        //  always get the messages
        if (pid == 0) {
            close(server_listen);
            while(1) {
                char buff[512] = {0};
                char tobuff[1024] = {0};
                size_t ret = recv(sockfd, buff, sizeof(buff), 0);
                if (ret <= 0) {
                    printf("<%s> is offline!\n", inet_ntoa(client.sin_addr));
                    close(sockfd);
                    exit(1); //child exit
                }
                printf("<%s> recv: %s\n",inet_ntoa(client.sin_addr), buff);
                // reply the message
                sprintf(tobuff, "I've received your message %s \n", buff);
                send(sockfd, tobuff, strlen(tobuff), 0);
            }
        } else {
            printf("Parent do noting\n");
            close(sockfd);
            // same sockfd with child, the influence ??
        }
    }
}
