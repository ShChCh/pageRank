#ifndef PAGERANK_H
#define PAGERANK_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef struct GNode * G_Node;


G_Node PROrder(G_Node);
float sumOfConnectedBy(Graph,G_Node,G_Node);
G_Node calculatePageRank(Graph, float , float, float);
void writePRtoFile(G_Node,char **);
#endif
