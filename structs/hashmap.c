//NOTE: One should always use the same HCODE throughout the life of a HashMap. Not doing so would result in unpredictable output. 
#include "hashmap.h"
#include "../logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void (*alloc)(size_t);
extern void (*dalloc)(void *);
extern char* glob_log_n;
void insert(hnode **head, void *k,void *v, HCODE h){
    if(*head==NULL){
        *head=(hnode*)alloc(sizeof(hnode));
        if(*head==NULL){
            perror("[alloc]");
            return;
        }
        switch(h){
            case CI:
                (**head).ci.key=(char*)k;
                (**head).ci.value=*(int*)v;
                (**head).ci.next=NULL;
            case II:
                (**head).ii.key=*(int*)k;
                (**head).ii.value=*(int*)v;
                (**head).ii.next=NULL;
            default:
                append_msg(HCODE_INV_MSG,glob_log_n);
                (**head).ci.key=(char*)k;
                (**head).ci.value=*(int*)v;
                (**head).ci.next=NULL;
        }  
    }
    hnode *selected=*head;
    switch(h){
        case CI:
            while((*selected).ci.next!=NULL)selected=(*selected).ci.next;
            (*selected).ci.next=(hnode*)alloc(sizeof(hnode));
            hnode *cn=(*selected).ci.next;
            if(cn==NULL){
                perror("[alloc]");
                return;
            }
            (*cn).ci.key=(char*)k;
            (*cn).ci.value=*(int*)v;
            (*cn).ci.next=NULL;
        case II:
            while((*selected).ii.next!=NULL)selected=(*selected).ii.next;
            (*selected).ii.next=(hnode*)alloc(sizeof(hnode));
            hnode *cn=(*selected).ii.next;
            if(cn==NULL){
                perror("[alloc]");
                return;
            }
            (*cn).ii.key=*(int*)k;
            (*cn).ii.value=*(int*)v;
            (*cn).ii.next=NULL;
        default:
            append_msg(HCODE_INV_MSG,glob_log_n);
            while((*selected).ci.next!=NULL)selected=(*selected).ci.next;
            (*selected).ci.next=(hnode*)alloc(sizeof(hnode));
            hnode *cn=(*selected).ci.next;
            if(cn==NULL){
                perror("[alloc]");
                return;
            }
            (*cn).ci.key=(char*)k;
            (*cn).ci.value=*(int*)v;
            (*cn).ci.next=NULL;
    }
}
//assuming user would never need to remove individual keys because that feature is not relevant to the program.
void delete(hnode *head, HCODE h){
    hnode *selected=head;
    hnode *save;
    switch(h){
        case CI:
            while(selected!=NULL){
                save=(*selected).ci.next;
                dalloc(selected);
                selected=save;
            }
        case II:
            while(selected!=NULL){
                save=(*selected).ii.next;
                dalloc(selected);
                selected=save;
            }
        default:
            append_msg(HCODE_INV_MSG,glob_log_n);
            while(selected!=NULL){
                save=(*selected).ci.next;
                dalloc(selected);
                selected=save;
            }
    }
}
void* get(hnode *head, void *k, HCODE h){
    hnode *selected=head;
    switch(h){
        case CI:
            char *tc=(char*)k;
            while(selected!=NULL){
                if(strcmp((*selected).ci.key,tc)==0)return (void*)&(*selected).ci.value;
                selected=(*selected).ci.next;
            }
        case II:
            int tc=*(int*)k;
            while(selected!=NULL){
                if((*selected).ii.key==tc)return (void*)&(*selected).ii.value;
                selected=(*selected).ii.next;
            }
        default:
            append_msg(HCODE_INV_MSG,glob_log_n);
            char *tc=(char*)k;
            while(selected!=NULL){
                if(strcmp((*selected).ci.key,tc)==0)return (void*)&(*selected).ci.value;
                selected=(*selected).ci.next;
            }
    }
    return NULL;
}