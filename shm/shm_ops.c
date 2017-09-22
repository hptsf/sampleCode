#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shm_ops.h"

void* shm_init(unsigned int shm_key)
{
    int shmid = -1;
    void *shm = NULL;
    PShareData *share = NULL;

    shmid = shmget((key_t)shm_key, sizeof(ShareData), 0666 | IPC_CREAT);
    if(-1 == shmid){
        perror("shmget failed");
        return NULL;
    }

    shm = shmat(shmid, (void*)0, 0);
    if((void*)-1 == shm){
        perror("shmat failed");
        return NULL;
    }

    memset(shm, 0x00, sizeof(ShareData));
    fprintf(stdout, "Memory attached at %p\n", shm);
    return shm;
}

int shm_uninit(void *shm)
{
    if(NULL == shm)
        return -1;

    if(-1 == shmdt(shm)){
        perror("shmdt failed");
        return -1;
    }
    shm = NULL;

    return 0;
}

int shm_write(void *shm, const char *buf, int len, int timeout)
{
    PShareData share = NULL;
    int to = timeout;

    if(NULL == shm || NULL == buf || len <= 0){
        fprintf(stdout, "%s param invalid\n", __FUNCTION__);
        return -1;
    }
    share = (PShareData)shm;

    do{
        if(1 == share->written){
            usleep(100000);     // 100ms
        }else{
            break;
        }
    }while(--timeout > 0);
    if(to && timeout <= 0){
#if DEBUG
        fprintf(stdout, ".");
        fflush(stdout);
#endif
        return -1;
    }

    memset(share->text, 0x00, TEXT_SZ);
    len = len > TEXT_SZ ? TEXT_SZ : len;
    memcpy(share->text, buf, len);
    share->written = 1;
    share->length = len;

    return len;
}

int shm_read(void *shm, char *buf, int len, int timeout)
{
    PShareData share = NULL;
    int to = timeout;

    if(NULL == shm || NULL == buf || len <= 0){
        fprintf(stdout, "%s param invalid\n", __FUNCTION__);
        return -1;
    }
    share = (PShareData)shm;

    do{
        if(0 == share->written){
           usleep(100000);
        }else{
            break;
        }
    }while(--timeout > 0);
    if(to && timeout <= 0){
#if DEBUG
        fprintf(stdout, ".");
        fflush(stdout);
#endif
        return -1;
    }

    len = len > share->length ? share->length : len;
    memcpy(buf, share->text, len);
    share->written = 0;

    return len;
}

