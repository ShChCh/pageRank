#ifndef READDATA_H
#define READDATA_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "queue.h"

queue GetCollection();
int convert_url_to_index(char *,char **,int );
Graph GetGraph();

#endif
