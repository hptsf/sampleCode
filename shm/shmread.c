#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "shm_ops.h"

#define SHM_KEY     12345
#define BUFF_LEN    256

int main(int argc, char *argv[])
{
    int running = 1;
    void *shm = NULL;
    char buf[BUFF_LEN];
    int len = -1;

    shm = shm_init(SHM_KEY);
    if(NULL == shm){
        perror("shm init failed");
        return 0;
    }

    do{
        memset(buf, 0x00, BUFF_LEN);
        len = shm_read(shm, buf, BUFF_LEN, 3);
        if(len < 0){
            continue;
        }
        fprintf(stdout, "Get a msg: %s\n", buf);
        if(strncmp(buf, "end", 3) == 0)
            running = 0;
    }while(running);

    shm_uninit(shm);
    return 0;
}

