typedef struct{
  int nvertices;
  int **m;
  int *visited;
}graph;

graph *graph_create(int nvertices);

void graph_clear(graph *g);

void graph_free(graph *g);

void graph_set_edge(graph *g,int i,int j,int w);

int graph_get_edge(graph *g,int i,int j);

void dijkstra(graph *g,int src,int *d,int *prev);

int SearchShortestPath(graph* g,int src,int dst,int* path);

void print_adjacency(graph *g,int size);

void generate_graph_adjacency(graph *g,int size);

void generate_graph_gird(graph *g,int size);