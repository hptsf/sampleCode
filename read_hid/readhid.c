/*================================================================
*   Copyright (C) 2018 Ltd. All rights reserved.
*   
*   File Name ：readhid.c
*   Author    ：tombinfan
*   Date      ：2018-08-31
*   Descriptor：
*
================================================================*/


#include "readhid.h"

#define USB_HID_PATH_DEFAULT        "/dev/hidraw3"
#define BUFF_LENGTH                 1024

static int run_flag = 0;

static void sig_handler(int key)
{
    fprintf(stdout, "\n");
    run_flag = 0;
}

static int print_buf(const unsigned char* buf, int len)
{
    int i = 0;

    for(i = 0; i < len; i ++){
        fprintf(stdout, "%02x ", buf[i]);
        if(0 == (i + 1) % 48)
            fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

int main(int argc, char *argv[])
{
    int fd = -1;
    unsigned char buf[BUFF_LENGTH];
    int ret = -1;
    int i = 0;
    int efd;
    int n;
    struct epoll_event event;
    struct epoll_event *events;
    struct hidraw_devinfo devinfo;
    int down = 0;
    unsigned int x_pos = 0;
    unsigned int y_pos = 0;

    if(argc < 2){
        fd = open(USB_HID_PATH_DEFAULT, O_RDONLY);
    }else{
        fd = open(argv[1], O_RDONLY);
    }
    if(fd < 0){
        perror("open usb hid failed");
        return 0;
    }
    memset(buf, 0x00, BUFF_LENGTH);

    ret = ioctl(fd, HIDIOCGRAWINFO, &devinfo);
    if(0 != ret){
        perror("ioctl failed");
        goto out;
    }
    printf("Vid = %04x, Pid = %04x\n", (unsigned short)devinfo.vendor, (unsigned short)devinfo.product);

    efd = epoll_create(1);
    if(-1 == efd){
        perror("epoll failed");
        goto out;
    }

    event.data.fd = fd;
    event.events = EPOLLERR | EPOLLHUP | EPOLLIN | EPOLLRDHUP;
    ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event);
    if(-1 == ret){
        perror("opll ctl failed");
        goto out;
    }
    events = calloc(64, sizeof(event));

    run_flag = 1;
    signal(SIGINT, sig_handler);
    do{
#if 0
        ret = read(fd, buf, BUFF_LENGTH);
        if(ret < 0){
            perror("read failed");
            goto out;     
        }

        for(i = 0; i < ret; i ++){
            fprintf(stdout, "%02X ", buf[i]);
        }
        fprintf(stdout, "\n");
#else
        n = epoll_wait(efd, events, 64, -1);
        for(i = 0; i < n; i ++){
            if(events[i].events & (EPOLLERR | EPOLLHUP)) {
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
                continue;
            }
            if(events[i].events & EPOLLIN) {
                memset(buf, 0x00, BUFF_LENGTH);
                ret = read(events[i].data.fd, buf, BUFF_LENGTH);
                if(ret < 0){
                    if(EAGAIN != errno){
                        perror("read event failed");
                        close(events[i].data.fd);
                    }
                    continue;
                }else{
                    down = buf[1];
                    x_pos = (buf[4] << 8) | buf[3];
                    y_pos = (buf[6] << 8) | buf[5];
                    fprintf(stdout, "%s get data[%d][%8s, x: %u, y: %u\n", __func__, ret, down ? "press" : "release", x_pos, y_pos);
//                    print_buf(buf, ret);
                }
            }
        }
#endif
    }while(run_flag);
    free(events);

out:
    close(fd);
    return 0;
}
