#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

#include "graph.h"
#include "min_heap.h"
#define SIZE 20

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
    double time_adjacency;

    generate_graph_adjacency(g,SIZE);

    for(int i = 0;i < SIZE;i++){ 
        for(int j = 0;j < SIZE;j++){
            printf("%3d ",g->m[i][j]);
        }
        printf("\n");
    }

    int arr[g->nvertices],prev[g->nvertices];

    time_adjacency = wtime();
    dijkstra(g,5,arr,prev);
    time_adjacency = wtime() - time_adjacency;


    printf("\n");
    printf("min distance:\n");
    for(int n = 1;n < SIZE;n++){
        printf("%d ",arr[n]);
    }
    printf("\n");

    printf("\ntime function dijkstra -> %f\n",time_adjacency);

    graph_free(g);
    
    return 0;
}