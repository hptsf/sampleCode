/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：double-list.c
*   Author    ：hptsf
*   Date      ：2019-03-13
*   Descriptor：double-list: non-loop, non-sorted, maybe have same-value note
*
================================================================*/


#include "double-list.h"

static int free_db_list(pDoubleList_t pList)
{
    pDoubleList_t temp = NULL;
    pDoubleList_t freeNote = NULL;

    temp = pList;
    freeNote = pList->next;

    while(NULL != freeNote){
        freeNote = freeNote->next;
        temp = temp->next;
    }

    freeNote = temp;
    temp = temp->last;

    while(NULL != temp){
        temp->next = NULL;
        free(freeNote);

        pList->value --;

        freeNote = temp;
        temp = temp->last;
    }

    if(NULL == temp && NULL != freeNote){
        free(freeNote);
    }

    return 0;
}

static void print_db_list(pDoubleList_t pList)
{
    pDoubleList_t temp = NULL;

    if(NULL == pList){
        return;
    }

    fprintf(stdout, "There has %d elements:\n", pList->value);
    temp = pList->next;
    while(NULL != temp){
        fprintf(stdout, "%03d ", temp->value);
        temp = temp->next;
    }

    fprintf(stdout, "\n");
}

static int delete_elem_db_list(pDoubleList_t pList, int val)
{
    pDoubleList_t temp = NULL;
    pDoubleList_t del = NULL;

    if(NULL == pList){
        return -1;
    }

    temp = pList;
    while(NULL != temp->next){
        if(val != temp->next->value){
            temp = temp->next;
            continue;
        }

        del = temp->next;

        del->next->last = del->last;
        del->last = NULL;
        temp->next = del->next;
        del->next = NULL;
        free(del);
        pList->value --;

    //  break;                      // continue to del the same-value note
    }
}

static int insert_db_list(pDoubleList_t pList, int num)
{
    pDoubleList_t temp = NULL;
    pDoubleList_t newNote = NULL;

    newNote = (pDoubleList_t)malloc(sizeof(DoubleList_t));
    if(NULL == newNote ){
        fprintf(stdout, "malloc failed %s\n", strerror(errno));
        return -1;
    }
    temp = pList;
    while(NULL != temp->next){    // goto end
        temp = temp->next;
    }

    newNote->value = num;
    newNote->next = temp->next;
    temp->next = newNote;
    newNote->last = temp;

    pList->value ++;

    return 0;
}

int main(int argc, char *argv[])
{
    pDoubleList_t pList;

    int value[] = {10, 80, 33, 55, 99, 22, 104, 32, 45};
    int i = 0;
    int val = 0;

    pList = (pDoubleList_t)malloc(sizeof(DoubleList_t));
    if(NULL == pList){
        fprintf(stdout, "malloc failed %s\n", strerror(errno));
        return 0;
    }

    memset(pList, 0x00, sizeof(DoubleList_t));
    for(i = 0; i < sizeof(value)/sizeof(value[0]); i++){
        insert_db_list(pList, value[i]);
    }
    print_db_list(pList);

    fprintf(stdout, "Input number which you want to delete: ");
    scanf("%d", &val);
    delete_elem_db_list(pList, val);
    print_db_list(pList);

    fprintf(stdout, "Will free the doublelist note\n");
    free_db_list(pList);
    pList = NULL;
    fprintf(stdout, "free doublelist done\n");

    return 0;
}
