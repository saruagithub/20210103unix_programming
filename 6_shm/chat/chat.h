/*************************************************************************
	> File Name: chat.h
	> Author: wangxue
	> Mail: 
	> Created Time: Fri 19 Mar 2021 03:46:00 PM CST
 ************************************************************************/

#ifndef _CHAT_H
#define _CHAT_H
struct Msg {
    char name[20];
    char msg[1024];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}
#endif
