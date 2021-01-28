/*************************************************************************
	> File Name: 1_add.c
	> Author: wangxue
	> Mail: 
	> Created Time: Wed Jan 27 15:39:28 2021
 ************************************************************************/

#include "head.h"

#define INS 5

struct Num {
    int now;
    int sum;
    pthread_mutex_t mutex;
};

struct Num *share_memory;

void do_add(int id) {
    while(1) {
        // lock
        pthread_mutex_lock(&share_memory->mutex);
        if (share_memory->now > 1000) {
            pthread_mutex_unlock(&share_memory->mutex);
            break;
        }
        share_memory->sum += share_memory->now;
        share_memory->now++;
        pthread_mutex_unlock(&share_memory->mutex);
        printf("the %dth child do add, now = %d, sum = %d\n", id, share_memory->now, share_memory->sum);
        //fflush(stdout);
        // usleep(100);
    }
    exit(0);
}

int main() {
    pid_t pid;
    int x = 0, shmid;
    // create the key
    key_t key = ftok(".", 2021);
    // get share memory segment id
    if ((shmid = shmget(key, sizeof(struct Num), IPC_CREAT | IPC_EXCL | 0666)) < 0) {
        perror("shmget error\n");
        exit(1);
    }
    //get memory address by shmid
    share_memory = (struct Num *) shmat(shmid, NULL, 0);
    if (share_memory < 0) {
        perror("share_memory error\n");
        exit(1);
    }
    share_memory->now = 0;
    share_memory->sum = 0;

    // parent lock
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    // set pthread shared
    pthread_mutexattr_setpshared(&attr, 1);
    pthread_mutex_init(&share_memory->mutex, &attr);

    // create INS  child process
    for(int i = 1; i <= INS; i++) {
        if ((pid = fork()) < 0) {
            perror("fork error\n");
            exit(1);
        }
        x = i;
        if (pid == 0) break;
    }
    if (pid == 0) {
        // add 1-100 by child
        do_add(x);
    } else {
        for(int i = 1; i <= INS; i++) {
            wait(NULL);
        }
    }
    printf("share_memory->sum = %d\n", share_memory->sum);
    shmdt(share_memory);
    return 0;
}
