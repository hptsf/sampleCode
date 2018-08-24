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

int main(int argc,char **argv)
{
    int inotifyFd = -1;
    int wd = -1;
    char buf[BUF_LEN];
    ssize_t numRead = 0;
    char *p = NULL;
    struct inotify_event *event = NULL;

    if(argc < 2 ){
        fprintf(stdout, "Usage cmd dir_path|file_path\n");
        return 0;
    }

    inotifyFd = inotify_init();
    if(-1 == inotifyFd){
        fprintf(stdout, "inotify init failed\n");
        return 0;
    }

    wd = inotify_add_watch(inotifyFd, argv[1], IN_ALL_EVENTS);      // IN_MODIFY, IN_ACCESS, IN_OPEN, IN_CREATE, IN_DELETE and so on
    if(-1 == wd){
        fprintf(stdout, "inotify add watch failed\n");
        return 0;
    }

    fprintf(stdout, "Watching %s using wd %d\n", argv[1], wd);
    while(1){
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (-1 == numRead && EAGAIN != errno){
            perror("read failed");
            break;
        }

        fprintf(stdout, "\nRead %ldbytes from inotify fd\n", (long)numRead);
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
