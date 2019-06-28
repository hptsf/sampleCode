/*================================================================
*   Copyright (C) 2018 Ltd. All rights reserved.
*   
*   File Name ：readhid.h
*   Author    ：tombinfan
*   Date      ：2018-08-31
*   Descriptor：
*
================================================================*/


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/hidraw.h>
#include <sys/ioctl.h>
