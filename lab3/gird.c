#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

#include "graph.h"
#include "min_heap.h"
#define SIZE 100

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

int main() 
{
    srand(time(NULL));

    graph *g = graph_create(SIZE * SIZE);
    double time_gird;

    generate_graph_gird(g,SIZE);
    
    int arr[g->nvertices];
    int prev[g->nvertices];

    time_gird = wtime();
    dijkstra(g,1,arr,prev);
    time_gird = wtime() - time_gird;

    printf("\n");
    printf("min distance:\n");
    for(int n = 1;n < SIZE;n++){
        printf("%d ",arr[n]);
    }
    printf("\n");

    printf("\ntime function dijkstra -> %f\n",time_gird);

    graph_free(g);
    
    return 0;
}