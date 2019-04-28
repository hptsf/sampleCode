/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：heap_sort.c
*   Author    ：hptsf
*   Date      ：2019-04-27
*   Descriptor：
*
================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define NUM_LENGTH      12

void print_num(int *num, int len)
{
    int i = 0;

    if(NULL == num || len <= 0){
        return;
    }

    for(i = 0; i < len; i ++){
        fprintf(stdout, "%03d ", num[i]);
        fflush(stdout);
#if 0
        if(0 == (i + 1) % 10){
            fprintf(stdout, "\n");
        }
#endif
}

    fprintf(stdout, "\n");
}

int num_swap(int *num1, int *num2)
{
    int temp = 0;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;

    return 0;
}

int adjust_heap(int *num, int len)
{
   int m = (len - 1) >> 1;

   while(m >= 0){
       int l = (m << 1) + 1;
       int r = (m << 1) + 2;

       if(l <= len && num[l] > num[m])
           num_swap(&num[l], &num[m]);
       if(r <= len && num[r] > num[m])
           num_swap(&num[r], &num[m]);

       m --;
   }

   return 0;
}

void heap_sort(int *num, int len)
{
    int i = 0;
    int max = 0;

    for(i = len - 1; i >= 0; i --){
        adjust_heap(num, i);
        num_swap(&num[0], &num[i]);

        print_num(num, len);
    }
}

int main(int argc, char *argv[])
{
    int num[NUM_LENGTH] = { 10, 33, 22, 400, 420, 322, 777, 23, 87, 98, 12, 2 };

    fprintf(stdout, "The origin num: \n");
    print_num(num, NUM_LENGTH);

    heap_sort(num, NUM_LENGTH);

    fprintf(stdout, "heap sorted: \n");
    print_num(num, NUM_LENGTH);

    return 0;
}
