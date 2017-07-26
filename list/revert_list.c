#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __LIST{
    struct __LIST *next;
    struct __LIST *last;
    int num;
}List, *PList;

static int create_list(PList *list)
{
    PList new_list = NULL;
    PList p_cur = NULL;
    int cnt = 13;
    int i = 0;

    if(NULL != *list){
        fprintf(stdout, "Maybe list been created\n");
        return -1;
    }
    new_list = (PList)malloc(sizeof(List));     // head node for list
    if(NULL == new_list){
        perror("malloc failed");
        return -1;
    }
    memset(new_list, 0x00, sizeof(List));
    *list = new_list;
    p_cur = *list;

    for(i = 0; i < cnt; i ++){
        new_list = (PList)malloc(sizeof(List));
        if(NULL == new_list){
            perror("malloc failed");
            // TODO:  
        } 
        new_list->num = i + 33;
        p_cur->next = new_list;
        new_list->last = p_cur;
        p_cur = p_cur->next;
        (*list)->num ++;               // number of nodes
    }
    if(cnt == i){
        p_cur = NULL;
    }

    return 0;
}

static int print_list(PList list)
{
    PList p_cur = NULL;

    if(NULL == list){
        fprintf(stdout, "list is null\n");
        return -1;
    }

    p_cur = list;
    fprintf(stdout, "Has %d nodes: ", p_cur->num);
    for(p_cur = p_cur->next; NULL != p_cur; p_cur = p_cur->next){
        fprintf(stdout, " %d", p_cur->num);
    }
    fprintf(stdout, "\n");

    return 0;
}

static int revert_list(PList *list)
{
    PList p_cur = NULL;
    PList p_next = NULL;

    if(NULL == *list || NULL == (*list)->next){
        fprintf(stdout, "list is null or only header node\n");
        return -1;
    }
    p_cur = (*list)->next;
    while(NULL != p_cur){
        p_next = p_cur->next;

        if(*list == p_cur->last){
            p_cur->next = NULL;
            p_cur = p_next;
            continue;
        }

        p_cur->last = (*list);
        p_cur->next = (*list)->next;
        (*list)->next = p_cur;

        p_cur = p_next;
    }

    return 0;
}

static int destroy_list(PList list)
{
    PList p_cur = NULL;
    PList p_last = NULL;

    if(NULL == list){
        fprintf(stdout, "List has been destroy\n");
        return 0;
    }

    p_last = list;
    for(p_cur = list->next; NULL != p_cur; p_cur = p_cur->next){
        free(p_last);
        p_last = p_cur;
    }
    free(p_last);

    return 0;
}

int main(int argc, char *argv[])
{
    PList list;

    list = NULL;
    if(0 != create_list(&list)){
        return 0;
    }
    print_list(list);

    revert_list(&list);

    print_list(list);

    destroy_list(list);
    list = NULL;

    return 0;
}
