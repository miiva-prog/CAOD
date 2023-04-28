#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "min_heap.h"

void dijkstra(graph *g,int src,int *d,int *prev) 
{
    heapnode v; 
    heap *h = heap_create(g->nvertices);
    
    for(int i = 1; i <= g->nvertices; i++){ 
        if(i == src)
            d[i] = 0;
        else
            d[i] = INT_MAX;
        
        prev[i] = -1;
        heap_insert(h,d[i],i);
    }

    for(int i = 1;i <= g->nvertices;i++){
        v = heap_extract_min(h);
        g->visited[v.value - 1] = 1;
        for(int j = 1;j <= g->nvertices;j++){
            if(graph_get_edge(g,v.value - 1,j) && !g->visited[j - 1]){
                if(d[v.value] + graph_get_edge(g,v.value - 1,j) < d[j]){ 
                    d[j] = d[v.value] + graph_get_edge(g,v.value - 1,j);
                    heap_decrease_key(h,j,d[j]);
                    prev[j] = v.value;
                }
            }
        }
    }
    heap_free(h);
}

void generate_graph_adjacency(graph *g,int size)
{
    for(int i = 0;i <size - 1;i++){
        for(int j = i + 1;j < size;j++){
            if((i + j) % 2 == 0)
                graph_set_edge(g,i,j,getrand(5,size)); 
        }
    }   
}

void generate_graph_gird(graph *g,int size)
{
    for(int i = 0;i < size * size;i++){
        if(((i + 1) < size * size) && ((i + 1) % size != 0)) 
            graph_set_edge(g,i,i + 1,getrand(2,30));
        
        if((i + size) < size * size)
            graph_set_edge(g, i,i + size,getrand(2,30));
    }
}

graph* graph_create(int nvertices)
{
    graph *g;

    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int*) * nvertices);

    for(int i = 0;i < nvertices;i++){
        g->m[i] = malloc(sizeof(int) * nvertices);
    }

    g->visited = malloc(sizeof(int) * nvertices);
    graph_clear(g); 

    return g;
}

void graph_clear(graph *g)
{
    for(int i = 1;i < g->nvertices;i++){
        for(int j = 0; j < g->nvertices; j++){
            g->m[i][j] = 0;
        }
    }
}

void graph_free(graph *g)
{
    free(g->visited);

    for(int i = 0; i  < g->nvertices; i++){
        free(g->m[i]);
    }

    free(g->m);
    free(g);
}

void graph_set_edge(graph *g,int i,int j,int w)
{
    g->m[i][j] = w;
    g->m[j][i] = w;
}

int graph_get_edge(graph *g,int i,int j)
{
    return g->m[i][j];
}

int SearchShortestPath(graph* g,int src,int dst,int* path)
{
    int* arr = calloc(g->nvertices,sizeof(int));
    int* prev = calloc(g->nvertices,sizeof(int));

    dijkstra(g,src,arr,prev);

    int i = dst;
    int pathlen = 0;

    while(i != src && i < g->nvertices){
        pathlen++;
        i = prev[i];
    }

    int j = 0;
    i = dst;

    while(i != src){
        path[pathlen - j] = i;
        j++;
        i = prev[i];
    }

    printf("\nshort length -> %d\n",arr[dst]);

    return pathlen;
}