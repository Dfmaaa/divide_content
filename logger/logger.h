#define MAX_ERR_MSG 500
#define STDERR 2
#define STDOUT 1
#define ERR_WRITE_INTERNAL(E) write(STDERR,E,MAX_ERR_MSG)
typedef unsigned char* ERR_MESSAGE;