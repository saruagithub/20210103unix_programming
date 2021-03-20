/*************************************************************************
	> File Name: client.c
	> Author: wangxue
	> Mail: 
	> Created Time: Fri 19 Mar 2021 04:26:35 PM CST
 ************************************************************************/

#include "head.h"
#include "chat.h"

struct Msg *share_memory = NULL;
int main(int argc, char **argv) {
    int opt, shmid;
    char name[20] = {0};
    // get name from command args
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                strcpy(name, optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -n name \n", argv[0]);
                exit(1);
        }
    }

    key_t key = ftok(".", 202103);
    if ((shmid = shmget(key, sizeof(struct Msg), IPC_CREAT | 0666)) < 0) {
        perror("shmget error");
        exit(1);
    }
    if ((share_memory = shmat(shmid, NULL, 0)) < 0) {
        perror("shmat error");
        exit(1);
    }

    while(1) {
        char msg[1024] = {0};
        scanf("%[^\n]s", msg);
        getchar(); // eath \n
        printf("msg is %s\n", msg);
        if (!strlen(msg)) continue;
        while(1) {
            if (!strlen(share_memory->msg)) {
                pthread_mutex_lock(&share_memory->mutex);
                break;
            }
        }
        //pthread_mutex_lock(&share_memory->mutex);
        printf("Sending: %s ...\n", msg);
        strcpy(share_memory->msg, msg);
        strcpy(share_memory->name, name);
        pthread_cond_signal(&share_memory->cond);
        pthread_mutex_unlock(&share_memory->mutex);
        printf("Client signaled the cond\n");
    }
    return 0;
}
