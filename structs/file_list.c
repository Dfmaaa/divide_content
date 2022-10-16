#include "file_list.h"
#include <stdio.h>
#include <stdlib.h>
extern void (*alloc)(size_t);
extern void (*dalloc)(void *);
void insert(fnode **head, char *content){
    if(*head==NULL){
        *head=(fnode*)alloc(sizeof(fnode));
        if(*head==NULL){
            perror("[malloc]");
            return;
        }
        (**head).content=content;
        (**head).next=NULL;
        return;
    }
    fnode *selected=*head;
    while((*selected).next!=NULL)selected=(*selected).next;
    (*selected).next=(fnode*)alloc(sizeof(fnode));
    if((*selected).next==NULL){
        perror("[malloc]");
        return;
    }
    (*(*selected).next).content=content;
    (*(*selected).next).next=NULL;
}
void delete_list(fnode *l){
    fnode *save,*current=l;
    while(current!=NULL){
        save=(*current).next;
        dalloc(current);
        current=save;
    }
}