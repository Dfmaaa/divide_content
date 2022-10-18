/*There are countless complications to deal with such as one directory being in two output directories. Marking files that
have been dealt with. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <dirent.h>
#include "structs/file_list.h"
#define DIVF_SUCCESS 1
#define DIVF_FAILURE 0
//users can change these
#define SCMP_SUCCESS 0
#define ALLOC_FAILURE NULL
//global statistical variables
uint64_t num_done=0;
//function pointers that can be changed by client
int (*scmp)(const char *, const char *)=strcmp;
void (*alloc)(size_t)=malloc;
void (*dalloc)(void *)=free;
void sig_h(int s){
    signal(s,SIG_IGN);
    printf("%llu files have been dealt with. Exit?(Y/N)\n",num_done);
    if(getchar()='Y')signal(sig, sig_h);
}
/*A function to divide a file into different parts.
This function was necessary for huge files. This is a very general implementation. Meaning it's not only
for files. The struct name can be misleading but it is a way of saying that is the only purpose of the struct
in our program.*/
int divide_f(char *fname, uint64_t max,fnode **head ){
    int handle=open(fname,O_RDONLY);
    if(handle==-1)return DIVF_FAILURE;
    struct stat ls;
    if(fstat(handle,&ls)==-1){
      close(handle);
      return DIVF_FAILURE;
    }
    *head=NULL;
    char *f_string=(char*)mmap(NULL,ls.st_size,PROT_READ, MAP_PRIVATE, handle, 0);
    char *s;
    uint64_t parts=(int)(ls.st_size/(float)max);
    uint64_t counter=0;
    uint64_t numfc=0;
    while(numfc++<parts){
        while(counter++<max-1)s[counter]=f_string[counter];
        s[counter]='\0';
        insert(head,s);
        counter=0;
    }
    return DIVF_SUCCESS;
}
int main(int argc, char **argv){
    if(argc!=3){
        printf("Usage: %s [directory] [max directory size]");
        return EXIT_FAILURE;
    }
    
}