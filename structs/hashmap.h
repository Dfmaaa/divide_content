#define II 0x341ff //random hex
#define CI 0x754ff //random hex
union hnode{
    struct{
        char *key;
        int value;
    }ci;
    struct{
        int key;
        int value;
    }ii;
};
typedef union hnode hnode;
typedef unsigned short HCODE;