/*================================================================
*   Copyright (C) 2018 Ltd. All rights reserved.
*   
*   File Name ：coredump.c
*   Author    ：tombinfan
*   Date      ：2018-08-27
*   Descriptor：
*
================================================================*/


#include "coredump.h"

int main(int argc, char *argv[])
{
    int a = 100;
    int b = 0;

    int c = a / b;

    fprintf(stdout, "c = %d\n", c);

    return 0;
}
