#include "logger.h"
#include <fnctl.h>
#include <sys/types.h>
#include <sys/stat.h>
void append_msg(const ERR_MESSAGE e,const char *logf){
    int f=open(logf,O_WRONLY |O_APPEND | O_CREAT);
    if(f==-1){
        ERR_WRITE_INTERNAL("Can't open log file.");
        return;
    }
    write(logf,e,MAX_ERR_MSG);
    close(f);
}
void clear_log(const char *logf){
    int f=open(logf,O_WRONLY | O_CREAT);
    close(f);
}