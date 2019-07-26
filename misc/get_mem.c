/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：get_mem.c
*   Author    ：hptsf
*   Date      ：2019-07-25
*   Descriptor：
*
================================================================*/


#include <stdio.h>
#include <string.h>

static int dump_func(int a, int b)
{
    int c = 0;
    int d = 10;
    int e = 100;
    int f = 10000;

    f = a + b + e + d + e + f;

    return f;
}

static void get_mem(char **ptr)
{
    char ch[100];

    memset(ch, 0xA5, 100);

    strcpy(ch, "Hello");

    *ptr = &(ch[0]);
}

int main(int argc, char *argv[])
{
    char *ptr;

    get_mem(&ptr);

    dump_func(10, 20);

    printf("%4s", ptr);

    return 0;
}
