/*There are countless complications to deal with such as one directory being in two output directories. Marking files that
have been dealt with. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
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
//A function to divide a file into different parts.

int main(int argc, char **argv){
    if(argc!=3){
        printf("Usage: %s [directory] [max directory size]");
        return EXIT_FAILURE;
    }

}