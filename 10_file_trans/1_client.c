/*************************************************************************
	> File Name: 1_client.c
	> Author: wangxue
	> Mail: 
	> Created Time: Mon 12 Jul 2021 08:59:36 PM CST
 ************************************************************************/

#include "head.h"
#include "cmd.h"
int sockfd;
void logout(int signum) {
    close(sockfd);
    printf("ByeBye\n");
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, port;
    char buff[512] = {0}, ip[20] = {0}, name[20] = "xue";

    if (argc != 3) {
        fprintf(stderr, "usage: %s ip port\n", argv[0]);
        exit(1);
    }
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);

    signal(SIGINT, logout);

    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect error");
        exit(1);
    }

    send(sockfd, name, strlen(name), 0); // send my name to server
    if (recv(sockfd, buff, sizeof(buff), 0) <= 0 ) {
        perror("recv error");
        exit(1);
    }
    // server send me the reply, saved in buff
    printf("server reply: %s\n", buff); 
    // server reply 0/1, no/yes, we can check again here
    while(1) {
        char cmd[1024] = {0};
        int flag = 0;
        scanf("%[^\n]s", cmd);
        getchar();
        if (!strlen(cmd)) continue;
        // s a.txt, recv-r
        if (strlen(cmd) == 1 && cmd[0] == 'r') {
            flag |= RECV;
            printf("Here receive!\n");
        } else if (cmd[0] == 's' && cmd[1] == ' ') {
            flag |+ SEND;
            char file[512] = {0};
            strcpy(file, cmd + 2);
            printf("filename = %s\n", file);
            // send pic to server, single link (not double link)
        } else {
            flag |= NORMAL;
            send(sockfd, (char *)&flag, sizeof(int), 0);
            send(sockfd, cmd, strlen(cmd), 0);
        }

        /*
        scanf("%[^\n]s", buff);
        getchar();
        if (!strlen(buff)) continue;
        send(sockfd, buff, strlen(buff), 0); 
        // empty the buff
        bzero(buff, sizeof(buff));
        recv(sockfd, buff, sizeof(buff), 0);
        printf("Server: %s\n", buff);
        bzero(buff, sizeof(buff));
        */
    }
}

