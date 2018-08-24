/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   File Name ：inotify_test.h
*   Author    ：tombinfan
*   Date      ：2018-08-24
*   Descriptor：
*
================================================================*/


#pragma once

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <fcntl.h>

#define BUF_LEN 1024
