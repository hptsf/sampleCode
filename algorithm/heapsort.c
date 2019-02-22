/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*   
*   File Name ：heapsort.c
*   Author    ：hptsf
*   Date      ：2019-02-22
*   Descriptor：
*
================================================================*/


#include "heapsort.h"

static void print(int *arr, int n)
{
    int i = 0;

    for(i = 0; i < n; i++){
        fprintf(stdout, "%3d ", arr[i]);
    }
    fprintf(stdout, "\n");
}
 
static void swap_num(int *num_a, int *num_b)
{
    int temp = *num_b;

    *num_b = *num_a;
    *num_a = temp;
}
 
static void heap_adjust(int *array, int i, int nLength)
{
    int nChild = 0;
    int nTemp = 0;

    for (nTemp = array[i]; 2 * i + 1 < nLength; i = nChild){
        // left child's pos is parent's * 2 + 1, and right is left + 1
        nChild = 2 * i + 1;
        // get bigger in left and right child
        if (nChild != nLength - 1 && array[nChild + 1] > array[nChild])
            ++nChild;

        if (nTemp < array[nChild]){
            array[i] = array[nChild];
        }
        else{
            break;
        }
    }

    array[i] = nTemp;
}

static void heap_sort(int *array, int length)
{
    int i = 0;

    fprintf(stdout, "Start first half: \n");
    // To create a big heap; first hal: which has child must;
    for (i = (length >> 1) - 1; i >= 0; --i){
        heap_adjust(array, i, length);
        print(array, 10);
    }

    fprintf(stdout, "Start global sorting: \n");
    // from last to first one
    for (int i = length - 1; i > 0; --i){
        swap_num(&array[0], &array[i]);
        heap_adjust(array, 0, i);
        print(array, 10);
    }
}
 
int main(int argc, const char *argv[])
{
    int arr_test[10] = {71, 18, 151, 138, 160, 63, 174, 169, 79, 78};

    fprintf(stdout, "Before heap sort: \n");
    print(arr_test, 10);
    heap_sort(arr_test, 10);

    fprintf(stdout, "After heap sort : \n");
    print(arr_test, 10);

    return 0;
}

