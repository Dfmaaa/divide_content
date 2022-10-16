#pragma pack(1);
struct fnode{
  char *content;
  struct fnode *next;
};
#pragma pack(0);
typedef struct fnode fnode;
void insert(fnode **,char *);
void delete_list(fnode *);