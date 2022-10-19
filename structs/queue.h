#define QUEUE_END 1
#pragma pack(1)
struct qnode{
  DIR *d;
  struct qnode *parent;
  struct qnode *next;
};
#pragma pack(0)
typedef struct qnode qnode;
void enqueue(DIR *,qnode**,qnode**);
qnode dequeue(qnode**, int*);