/*************************************************************************
	> File Name: server.c
	> Author: wangxue
	> Mail: 
	> Created Time: Fri 19 Mar 2021 03:50:38 PM CST
 ************************************************************************/

#include "head.h"
#include "chat.h"

// create the shared memory, and prepare resources for char room

struct Msg *shared_memory = NULL;

int main() {
    int shmid;
    key_t key = ftok(".", 202103);
    // create shared memory
    if ((shmid =  shmget(key, sizeof(struct Msg), IPC_CREAT | 0666)) < 0) {
        perror("shmget error");
        exit(1);
    }
    if ((shared_memory = (struct Msg *)shmat(shmid, NULL, 0)) < 0) {
        perror("shmat error");
        exit(1);
    }
    // server setup first, init all resources
    // get mutex and signal that shared between processes
    memset(shared_memory, 0, sizeof(struct Msg));
    pthread_mutexattr_t m_attr;
    pthread_mutexattr_init(&m_attr);
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED); // = 1
    pthread_mutex_init(&shared_memory->mutex, &m_attr);

    pthread_condattr_t c_attr;
    pthread_condattr_init(&c_attr);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&shared_memory->cond, &c_attr);

    // init Msg, client send and server get
    while(1) {
        pthread_mutex_lock(&shared_memory->mutex);
        printf("server got the mutex!\n");
        pthread_cond_wait(&shared_memory->cond, &shared_memory->mutex);
        printf("server got the cond signal\n");
        printf("<%s> : %s. \n", shared_memory->name, shared_memory->msg);
        // keep data clean for next Msg
        memset(shared_memory->msg, 0, sizeof(shared_memory->msg));
        pthread_mutex_unlock(&shared_memory->mutex);
    }
}
