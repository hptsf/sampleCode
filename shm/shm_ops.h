#ifndef __SHM_OPS_H__
#define __SHM_OPS_H__

#define TEXT_SZ     1048576
  
typedef struct __SHARED_USE_ST
{  
    int written;                // flag, non-zero for read, zero for write
    int length;                 // the length of text
    char text[TEXT_SZ];         // the raw data
}ShareData, *PShareData;

void* shm_init(unsigned int shm_key);
int shm_uninit(void* shm);
int shm_write(void *shm, const char *buf, int len, int timeout); // seconds
int shm_read(void *shm, char *buf, int len, int timeout);        // seconds

#endif
