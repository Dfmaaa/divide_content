#define II 0x341ff //random hex
#define CI 0x754ff //random hex
#define HCODE_INV_MSG "Invalid HCODE. Using CI. Please see list of HCODEs defined in logger/logger.h\n"
union hnode{
    struct{
        char *key;
        int value;
        union hnode *next;
    }ci;
    struct{
        int key;
        int value;
        union hnode *next;
    }ii;
};
typedef union hnode hnode;
typedef unsigned short HCODE;
void insert(hnode **, void *, void *, HCODE);
void delete(hnode *, HCODE);
void* get(hnode *,void *,HCODE);