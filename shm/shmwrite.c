#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shm_ops.h"

#define SHM_KEY     12345
#define BUFF_LEN    256

int main(int argc, char *argv[])
{
    int running = 1;
    void *shm = NULL;
    char buf[BUFF_LEN];

    shm = shm_init(SHM_KEY);
    if(NULL == shm){
        perror("shm init failed");
        return 0;
    }

    while(running){
        fprintf(stdout, "Input a string: ");
        fgets(buf, BUFF_LEN, stdin);
        shm_write(shm, buf, BUFF_LEN, 2);
        if(0 == strncmp(buf, "end", 3))
            running = 0;
    }

    shm_uninit(shm);
    return 0;
}
