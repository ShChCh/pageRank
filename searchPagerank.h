#ifndef searchPagerank_H
#define searchPagerank_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef struct URL_Node *UNode;
typedef struct URL_Node{
    float rate;
    int pages;
    char *name;
    UNode next;
}URL_Node;
UNode build_node_list();
UNode search_and_count(UNode,int,char **);
#endif
