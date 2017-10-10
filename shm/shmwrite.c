/****************************************************************************************
  * author            : tom
  * date              : 20171010
  * description       : source code for shm testing (SYSV)
  *                      and Posix shared memory: shm_open/ftruncate/mmap/shm_unlink
****************************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shmdata.h"

int main(int argc, char *argv[])
{
    int running = 1;
    void *shm = NULL;
    struct shared_use_st *shared = NULL;
    char buffer[BUFSIZ + 1];
    int shmid;

    shmid = shmget((key_t)SHM_KEY, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if(-1 == shmid){
        perror("shmget failed");
        return 0;
    }

    shm = shmat(shmid, (void*)0, 0);
    if((void*)-1 == shm){
        perror("shmat failed");
        goto out;
    }
    printf("Memory attached at %p\n", shm);

    shared = (struct shared_use_st*)shm;
    while(running){
        while(shared->written == 1){
            sleep(1);
            printf("Waiting...\n");
        }
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared->text, buffer, TEXT_SZ);
        shared->written = 1;
        if(strncmp(buffer, "end", 3) == 0)
            running = 0;
    }
    if(-1 == shmdt(shm)){
        perror("shmdt failed");
        goto out;
    }
    sleep(2);

out:
    return 0;
}
