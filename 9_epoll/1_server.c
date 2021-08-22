/*************************************************************************
	> File Name: 1_server.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sun 11 Jul 2021 10:15:47 PM CST
 ************************************************************************/

#include "head.h"
#define MAX_EVENTS 10

int main(int argc, char **argv) {
    int server_listen, sockfd, port, epollfd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];
    if (argc != 2) {
        fprintf(stderr, "usage: %s port!\n", argv[0]);
        exit(1);
    }
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        exit(1);
    }

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create error");
        exit(1);
    }
    ev.events = EPOLLIN;
    ev.data.fd = server_listen;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev) == -1) {
        perror("epoll_ctl listen_sock erroe!");
        exit(1);
    }
    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(1);
        }
        // have results
        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == server_listen) {
                // process network link
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                if ((sockfd = accept(server_listen, (struct sockaddr *) &client, &len)) < 0) {
                    perror("accept");
                    exit(1);
                }
                printf("LogIn %s login...\n", inet_ntoa(client.sin_addr));
                make_nonblock(sockfd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = sockfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(1);
                 }
            } else {
                //do_use_fd(events[n].data.fd);
                char buff[1024] = {0};
                int rsize = 0, fd = events[n].data.fd;
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                getpeername(fd, (struct sockaddr *) &client, &len);
                if ((rsize = recv(fd, buff, sizeof(buff), 0)) <= 0) {
                    printf("LogOut %s logout...\n", inet_ntoa(client.sin_addr));
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
                    printf("%s : %s \n", inet_ntoa(client.sin_addr), buff);
                    send(fd, buff, strlen(buff), 0);
                }
            }
        }
    } 
    return 0;
}
