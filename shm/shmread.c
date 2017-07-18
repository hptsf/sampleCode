#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"

int main(int argc, char *argv[])
{
    int running = 1;
    void *shm = NULL;
    struct shared_use_st *shared;
    int shmid;

    shmid = shmget((key_t)SHM_KEY, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if(-1 == shmid){
        perror("shmget failed");
        return 0;
    }
    shm = shmat(shmid, 0, 0);
    if((void*)-1 == shm){
        perror("shmat failed");
        goto out;
    }
    printf("\nMemory attached at %d-%p\n", shmid, shm);

    shared = (struct shared_use_st*)shm;
    shared->written = 0;
    while(running){
        if(shared->written != 0){
            fprintf(stdout, "You wrote: %s", shared->text);
            sleep(rand() % 3);
            shared->written = 0;
            if(strncmp(shared->text, "end", 3) == 0)
                running = 0;
        }
        else{
            sleep(1);
        }
    }

    if(-1 == shmdt(shm)){
        perror("shmdt failed");
        goto out;
    }

out:
    if(shmctl(shmid, IPC_RMID, 0) == -1){
        perror("remove shm failed");
    }

    return 0;
}

