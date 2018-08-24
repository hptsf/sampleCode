/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   File Name ：quick_sort.c
*   Author    ：tombinfan
*   Date      ：2018-07-17
*   Descriptor：
*
================================================================*/


#include "quick_sort.h"

#define SORT_RECURSIVE          1

#define ARRAY_LENGTH            20

#if (0 == SORT_RECURSIVE)
typedef struct __SORT_RANGE{
    int s;
    int e;
}SortRange_t;
#endif

static int g_array[ARRAY_LENGTH] = 
{
    40, 30, 58, 29, 66, 103, 73, 83, 11, 32,
    63, 42, 55, 15, 39, 98, 112, 67, 88, 53
};

static void print_array(int const *p_array, int len)
{
    if(NULL == p_array || len < 0)
        return;

    for(int i = 0; i < len; i ++){
        fprintf(stdout, "%3d ", p_array[i]);
        if(0 == (i + 1 % 8))
            fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
}
#if (0 == SORT_RECURSIVE)
void quick_sort_norecursive(int *p_array, int len)
{
    SortRange_t *range = NULL;
    int index = 0;
    int x = 0;
    int l = 0;
    int r = 0;

    if(NULL == p_array || len < 0)
        return;

    range = (SortRange_t *)malloc(len * sizeof(SortRange_t));
    if(NULL == range){
        perror("malloc failed");
        return;
    }
    range[index].s = 0;
    range[index].e = len - 1;
    index++;

    while(index){
        SortRange_t p_temp;
        index--;
        p_temp.s = range[index].s;
        p_temp.e = range[index].e;

        if(p_temp.s >= p_temp.e)
            continue;
        x = p_array[p_temp.s];
        l = p_temp.s;
        r = p_temp.e;
        while(l < r){
            while(l < r && p_array[r] >= x)
               r--;
           if(l < r){
               p_array[l] = p_array[r];
               l++;
           } 

           while(l < r && p_array[l] < x)
               l++;
           if(l < r){
                p_array[r] = p_array[l];
                r--;
           }
        }
        p_array[l] = x;

        range[index].s = p_temp.s;
        range[index].e = l - 1;
        index++;

        range[index].s = l + 1;
        range[index].e = p_temp.e;
        index++;
    }

    free(range);
    range = NULL;
}
#else
int adjust_array(int *s, int l, int r)
{
    int i = l;
    int j = r;
    int x = s[l];

    while(i < j){
        while(i < j && s[j] >= x)
            j--;
        if(i < j){
            s[i] = s[j];
            i++;
        }

        while(i < j && s[i] < x)
            i++;
        if(i < j){
            s[j] = s[i];
            j--;
        }
    }

    s[i] = x;
    return i;
}

void quick_sort(int *s, int l, int r)
{
    if(l < r){
        int i = adjust_array(s, l, r);
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}
#endif
int main(int argc, char *argv[])
{
    fprintf(stdout, "The original: \n");
    print_array((const int *)&g_array, ARRAY_LENGTH);

#if (0 == SORT_RECURSIVE)
    quick_sort_norecursive((int *)&g_array, ARRAY_LENGTH);
#else
    quick_sort((int *)&g_array, 0, ARRAY_LENGTH - 1);
#endif
    fprintf(stdout, "After quick sort: \n");
    print_array((const int *)&g_array, ARRAY_LENGTH);

    return 0;
}
