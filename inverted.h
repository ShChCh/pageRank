/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/
#ifndef INVERTED_H
#define INVERTED_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "InvertedIdx.h"
#include "ReadData.h"
Tree GetInvertedList();
char *normalise(char *);
void writeILtoFile(Tree);
#endif // INVERTED_H
