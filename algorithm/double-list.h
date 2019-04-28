/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：double-list.h
*   Author    ：hptsf
*   Date      ：2019-03-13
*   Descriptor：
*
================================================================*/


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct __DOUBLE_LIST{
    struct __DOUBLE_LIST *next;
    struct __DOUBLE_LIST *last;
    int value;
}DoubleList_t, *pDoubleList_t;
