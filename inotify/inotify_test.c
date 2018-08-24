/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   File Name ：inotify_test.c
*   Author    ：tombinfan
*   Date      ：2018-08-24
*   Descriptor：
*
================================================================*/


#include "inotify_test.h"

int logFlag = 0;

int main(int argc,char **argv)
{
    int fd;
    char filename[] = "printlog";
    char readbuf[8] = {0};
    int read_count = 0;

    int inotifyFd,wd,j;
    char buf[BUF_LEN];
    ssize_t numRead;
    char *p;
    struct inotify_event *event;
    int flags;

    if(argc < 2 ){
        printf("error\n");
        return 0;
    }

    inotifyFd = inotify_init();
    if(inotifyFd == -1){
        printf("inotify init failed\n");
        return 0;
    }

    wd = inotify_add_watch(inotifyFd, argv[1], IN_ALL_EVENTS);      // IN_MODIFY, IN_ACCESS, IN_OPEN, IN_CREATE, IN_DELETE and so on
    if(wd == -1){
        printf("error\n");
    }

    printf("Watching %s using wd %d\n", argv[1], wd);

    while(1){
        numRead = read(inotifyFd,buf,BUF_LEN);
        if (numRead == -1 && errno != EAGAIN){
           perror("read");
        }

        printf("\nRead %ldbytes from inotify fd\n", (long)numRead);
        for( p = buf; p < buf + numRead; ){
            event = (struct inotify_event *)p;
            
            fprintf(stdout, "event mask: %08X\n", event->mask);
            if(event->mask & IN_ACCESS){
                fprintf(stdout, "in access\n");
            }
            if(event->mask & IN_MODIFY){
                fprintf(stdout, "in modify\n");
            }
            if(event->mask & IN_OPEN){
                fprintf(stdout, "in open\n");
            }
            if(event->mask & IN_CREATE){
                fprintf(stdout, "in create\n");
            }
            if(event->mask & IN_DELETE){
                fprintf(stdout, "in delete\n");
            }
            if(event->mask & IN_CLOSE){
                fprintf(stdout, "in close\n");
            }
            if(event->mask & IN_MOVE){
                fprintf(stdout, "in move\n");
            }

            p += sizeof(struct inotify_event) + event->len; 
        }
    }

    inotify_rm_watch(inotifyFd, wd);

    return 0;
}
