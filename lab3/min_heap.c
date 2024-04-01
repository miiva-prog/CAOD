#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<time.h>
#include<sys/time.h>

#include "min_heap.h"
#include "graph.h"

int getrand(int min,int max)
{
    return (double)rand()/(RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

heap *heap_create(int maxsize) 
{
    heap *h;

    h = malloc(sizeof(*h));

    if(h != NULL){
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->index = (int *) malloc(sizeof(int) * (maxsize + 1));
        h->nodes = (heapnode *) malloc(sizeof(*h->nodes) * (maxsize + 1));
        if(h->nodes == NULL){
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(heap *h) 
{
    free(h->index);
    free(h->nodes);
    free(h);
}

void heap_swap(heapnode *a, heapnode *b, heap *h) 
{
    heapnode temp = *a;
    *a = *b;
    *b = temp;

    int tmp = h->index[a->value];
    h->index[a->value] = h->index[b->value];
    h->index[b->value] = tmp;
}

int heap_insert(heap *h, int key, int value) 
{
    if(h->nnodes >= h->maxsize)
        return -1;
    
    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;
    h->index[value] = h->nnodes;
    for(int i = h->nnodes;i > 1 && h->nodes[i].key < h->nodes[i / 2].key; i = i / 2)
        heap_swap(&h->nodes[i], &h->nodes[i / 2],h);

    return 0;
}

heapnode heap_extract_min(heap *h) 
{
    if(h->nnodes == 0)     
        return (heapnode) {0,0};
    
    heapnode minnode = h->nodes[1];

    h->nodes[1] = h->nodes[h->nnodes];
    h->index[h->nodes[h->nnodes].value] = 1;
    h->nnodes--;

    heap_heapify(h,1);

    return minnode;
}

void heap_heapify(heap *h, int index) 
{
    while(1){
        int left = 2 * index;
        int right = 2 * index + 1;

        int least = index;
        if(left <= h->nnodes && h->nodes[left].key < h->nodes[index].key) 
            least = left;
        
        if(right <= h->nnodes && h->nodes[right].key < h->nodes[least].key) 
            least = right;
        
        if(least == index) 
            break;
        
        heap_swap(&h->nodes[index], &h->nodes[least], h);
        index = least;
    }
}

int heap_decrease_key(heap *h, int index, int key) 
{
    index = h->index[index];

    if(h->nodes[index].key < key) 
        return -1;
    
    h->nodes[index].key = key;

    for(;index > 1 && h->nodes[index].key < h->nodes[index / 2].key;index = index / 2)
        heap_swap(&h->nodes[index], &h->nodes[index / 2],h);
    
    return index;
}

int main()
{
    srand(time(NULL));

    double time_add = wtime();
    heap *hp = heap_create(1000000);

    for(int n = 1;n < 1000000;n++){
        int add = heap_insert(hp,rand() % n,n + 1);

        if(n % 50000 == 0){
            time_add = wtime() - time_add;
            printf("time -> %.6lf | count -> %d\n",time_add,n);
            time_add = wtime();
        }
    } 

    return 0;
}