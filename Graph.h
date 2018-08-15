// Graph ADT interface ... COMP9024 17s2
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

typedef struct ABC {
    Edge a;
    int current;
}
typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
   char **node_list;
} GraphRep;
Graph newGraph(int,char **);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);
char **get_node_list(Graph);
int outDegree(Graph,Vertex);
int get_nV(Graph );