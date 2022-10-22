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
#include <ftw.h>
#include <pthread.h>
#include "structs/file_list.h"
#include "statistics/plot.h"
#include "structs/queue.h"
#include "logger/logger.h"
#define DIVF_SUCCESS 1
#define DIVF_FAILURE 0
//users can change these
#define SCMP_SUCCESS 0
#define ALLOC_FAILURE NULL
#define CD_PERMS S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
//global statistical variables
uint64_t num_done=0;
//function pointers that can be changed by client
int (*scmp)(const char *, const char *)=strcmp;
void (*alloc)(size_t)=malloc;
void (*dalloc)(void *)=free;
char* (*concat)(const char *, const char *)=sstrcat; //only function pointer that uses custom function.
size_t (*slen)(const char *)=strlen;
char* (*split)(char *restrict, const char *restrict)=strtok; //NOTE: should be like strtok.
uint64_t max;
extern char grid[20][60];
char *output_directory;
void sig_h(int s){
    signal(s,SIG_IGN);
    printf("%llu files have been dealt with. Exit?(Y/N)\n",num_done);
    if(getchar()='Y')signal(sig, sig_h);
}
char  *sstrcat(const char *cp1, const char *cp2){
    int len1=slen(cp1);
    int len2=slen(cp2);
    char *new_str=(char *)alloc(sizeof(char)*(len1+len2+1));
    int globcount, ocount=0;
    while(cp1[ocount]!='\0'){
    new_str[globcount++]=cp1[ocount++];
    }
    ocount=0;
    while(cp2[ocount]!='\0'){
    new_str[globcount++]=cp2[ocount++];
    }
    new_str[globcount]='\0';
    return new_str;
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
int __is_dir(const char *c){
    struct stat s;
    stat(c, &s);
    return s.st_mode==S_IFDIR;
}
void traverse(DIR *d, char *path, char *cd){
    struct dirent *trv;
    uint64_t size_counter=0;
    char *clean_f;
    while((trv=readdir(d))!=NULL){
        //if directory
        if(__is_dir((*trv).d_name)){
            char *sl=concat(path,"/");
            traverse(opendir((*trv).d_name),concat(sl,(*trv).d_name));
            dalloc(sl);
            dalloc(path);
        }
        //if file
        else{
            int handle=open((*trv).d_name,O_RDONLY);
            if(handle==-1){
                clean_f=(*trv).d_name;
                goto clean;
                if(getchar()=='Y'){
                    recursive_delete_d(output_directory);
                    puts("Done.");
                    exit(EXIT_FAILURE);
                 }
            }
            struct stat ls;
            if(fstat(handle,&ls)==-1){
                clean_f=(*trv).d_name;
                goto clean;
                close(handle);
                return;
            }
        }
    }
    clean:
        printf("Can't open %s. Clean?(Y/N)\n",clean_f);
        if(getchar()=='Y'){
            recursive_delete_d(output_directory);
            puts("Done.");
            exit(EXIT_FAILURE);
        }
}
void recursive_delete_d(const char *c){
    if (nftw(c, rmfiles,10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS)<0){
        perror("[nftw]");
        exit(EXIT_FAILURE);
    }
}
static int rmfiles(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb){
    if(remove(pathname)<0){
        perror("[remove]");
        return -1;
    }
    return 0;
}
void create_nested_dirs(const char *path){
    char *d=split(path,"/");
    char *s=d;
    char *ss;
    mkdir(d,CD_PERMS);
    while((d=split(NULL,"/"))!=NULL){
        ss=s; //Sorry.
        s=concat(s,"/");
        dalloc(ss);
        ss=s; // ;) Elegant solution, am I right?
        s=concat(s,d);
        mkdir(s,CD_PERMS);
    }
    dalloc(s);
}
int main(int argc, char **argv){
    if(argc!=3){
        printf("Usage: %s [directory] [max directory size]");
        return EXIT_FAILURE;
    }
    max=strtol(argv[2]);
}