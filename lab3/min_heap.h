typedef struct{
  int key;
  int value;
}heapnode;

typedef struct{
  int *index;
  int maxsize;
  int nnodes;
  heapnode *nodes;
}heap;

heap* heap_create(int maxsize);

void heap_free(heap *h);

void heap_swap(heapnode *a,heapnode *b,heap *h);

int heap_insert(heap *h,int key,int value);

heapnode heap_extract_min(heap *h);

void heap_heapify(heap *h,int index);

int heap_decrease_key(heap *h,int index,int key);