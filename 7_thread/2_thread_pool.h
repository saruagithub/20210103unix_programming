/*************************************************************************
	> File Name: 2_thread_pool.h
	> Author: wangxue
	> Mail: 
	> Created Time: Thu 01 Apr 2021 11:14:18 AM CST
 ************************************************************************/

#ifndef _2_THREAD_POOL_H
#define _2_THREAD_POOL_H

struct task_queue {
    //Customer space, circular queue
    int size;
    char **data;
    int total;
    // total people
    int head;
    // first customer 
    int tail;
    // last customer
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int size);
void task_queue_push(struct task_queue *taskQueue, char *str);
char* task_queue_pop(struct task_queue *taskQueue);
#endif
