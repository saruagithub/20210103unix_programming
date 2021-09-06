/*************************************************************************
	> File Name: head.h
	> Author: wangxue
	> Mail: 
	> Created Time: Thu Jan  7 20:38:59 2021
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <sys/time.h>

#include <sys/wait.h>
#include <sys/file.h>

// 6_shm
#include <sys/ipc.h>
#include <sys/shm.h>

//mutex
#include <pthread.h>

//socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"
#include "tcp_server.h"
#include "tcp_client.h"

#include <sys/epoll.h>
#endif
