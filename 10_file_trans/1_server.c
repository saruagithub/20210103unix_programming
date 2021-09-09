/*************************************************************************
	> File Name: 1_server.c
	> Author: wangxue
	> Mail: 
	> Created Time: Sun 11 Jul 2021 10:15:47 PM CST
 ************************************************************************/

#include "head.h"
#include "cmd.h"
#define MAX_EVENTS 10
#define MAX_CLIENT 100

struct Client {
    char name[20];
    int fd;
    int online; //whether online
};

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
    
    //save all users
    struct Client *users = (struct Client *)malloc(sizeof(struct Client) * MAX_CLIENT); 

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
                char name[20] = {0};
                socklen_t len = sizeof(client);
                if ((sockfd = accept(server_listen, (struct sockaddr *) &client, &len)) < 0) {
                    perror("accept");
                    exit(1);
                }
                printf("LogIn %s login...\n", inet_ntoa(client.sin_addr));
                make_nonblock(sockfd);

                // get the login user Name?
                if (recv_str_nonblock(sockfd, name, sizeof(name), 10000) != 0) {
                    printf("Login error: %s did not send his name... deleted..\n", inet_ntoa(client.sin_addr));
                    close(sockfd);
                    continue;
                }
                // send msg to client that you login successfully
                send(sockfd, "welcome!", sizeof("welcome"), 0);
                users[sockfd].fd = sockfd;
                strcpy(users[sockfd].name, name);
                users[sockfd].online = 1;

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = sockfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
                    perror("epoll_ctl: conn_sock");
                    exit(1);
                 }
                // user login from addr
                printf("LogIn %s login on %s...\n",name, inet_ntoa(client.sin_addr));
            } else {
                //do_use_fd(events[n].data.fd);
                // char buff[1024] = {0}; 
                // now client send the cmd flag
                int flag = 0;
                char buff[1024] = {0};
                int rsize = 0, fd = events[n].data.fd;
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                getpeername(fd, (struct sockaddr *) &client, &len);
                // receive the data
                if ((rsize = recv(fd, (char *)&flag, sizeof(flag), 0)) <= 0) {
                    printf("LogOut %s logout...\n", inet_ntoa(client.sin_addr));
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
                    if (flag & SEND) {
                        // client want to send
                        printf("Client want to send data...\n");
                    } else if (flag & RECV) {
                        printf("Client want to recv data...\n");
                    } else {
                        recv(fd, buff, sizeof(buff), 0);
                        printf("<%s>: %s\n", users[fd].name, buff);
                    }
                }
            }
        }
    } 
    return 0;
}
