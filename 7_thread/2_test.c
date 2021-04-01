/*************************************************************************
	> File Name: 2_test.c
	> Author: wangxue
	> Mail: 
	> Created Time: Thu 01 Apr 2021 04:31:24 PM CST
 ************************************************************************/

#include "head.h"
#include "2_thread_pool.h"

#define THREAD 5
#define QUEUE 50

void *do_work(void *arg) {
    pthread_detach(pthread_self());
    // detach my from other pthread (other girlfriend)
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while(1) {
        char *str = task_queue_pop(taskQueue);
        printf("<%d>: %s \n", pthread_self(), str);
    }
}

int main() {
    pthread_t tid[THREAD];
    struct task_queue taskQueue;
    task_queue_init(&taskQueue, QUEUE);
    // custmer seat, save str
    char buff[QUEUE][1024] = {0};

    // create pthread
    for (int i = 0; i < THREAD; i++) {
        pthread_create(&tid[i], NULL, do_work, (void *)&taskQueue);
    }

    int sub = 0;
    // 循环读文件并将一行一行的压入栈中
    while (1) {
        FILE *fp = fopen("./1_test.c", "r");
        if (fp == NULL) {
            perror("fopen error\n");
            exit(1);
        }
        // read data
        while (fgets(buff[sub++], 1024, fp) != NULL) {
            task_queue_push(&taskQueue, buff[sub]);
            if (sub == QUEUE) {
                sub = 0;
            }
            // customers are full, just waiting
            if (taskQueue.total == taskQueue.size) {
                while(1) {
                    // pthread is go out
                    if (taskQueue.total < taskQueue.size) break;
                    usleep(10000);
                }
            }
        }
        fclose(fp);
    }

    return 0;
}
