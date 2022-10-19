//modified https://github.com/Dfmaaa/queue-in-C
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
extern void (*alloc)(size_t);
extern void (*dalloc)(void *);
void enqueue(DIR *d, qnode **queue_head, qnode **tail){
    if(*queue_head==NULL){
        *queue_head=(qnode*)alloc(sizeof(qnode));
        if(*queue_head==NULL){
            perror("[alloc]");
            exit(EXIT_FAILURE);
        }
        (**queue_head).d=d;
        (**queue_head).parent=NULL;
        (**queue_head).next=NULL;
        *tail=*queue_head;
        return;
    }
    qnode *save_head=*queue_head;
    *queue_head=(qnode*)alloc(sizeof(qnode));
    if(*queue_head==NULL){
            perror("[alloc]");
            exit(EXIT_FAILURE);
    }
    (**queue_head).d=d;
    (**queue_head).parent=NULL;
    (**queue_head).next=save_head;
    (*save_head).parent=*queue_head;
}
qnode dequeue(qnode **tail, int *SIGEND){
    qnode retstruct=**tail;
    if((**tail).parent==NULL){
        dalloc(*tail);
        *SIGEND=QUEUE_END;
    }
    else{
        *tail=(**tail).parent;
        dalloc((**tail).next);
    }
    return retstruct;
    }