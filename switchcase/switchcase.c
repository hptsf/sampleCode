/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：switchcase.c
*   Author    ：hptsf
*   Date      ：2019-07-24
*   Descriptor：
*
================================================================*/


#include  "../comm.h"

int main(int argc, char *argv[])
{
    char ch = 0x00;

    if(2 != argc){
        fprintf(stdout, "Usage: cmd param[a|b|c|d]\n");
        return 0;
    }

    ch = argv[1][0];

    switch(ch){
    case 'a':
        fprintf(stdout, "get param [a]\n");
        break;

    case 'b':
        fprintf(stdout, "get param [b]\n");
        break;

    case 'c':
        fprintf(stdout, "get param [c]\n");
        break;

    case 'd':
        fprintf(stdout, "get param [d]\n");
        break;

    default:
        fprintf(stdout, "Invalid param\n");
        break;
    }

    fprintf(stdout, "Will exit\n");

    return 0;
}
