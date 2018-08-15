/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/
#ifndef InvertedIdx_H
#define InvertedIdx_H

#include <stdbool.h>
#include "DLListStr.h"
typedef char *Item;      // item is just a key

typedef struct Node *Tree;

Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)

Tree TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item);   // insert a new item into a Tree
DLListStr get_list(Tree);
void output_to_file(Tree,FILE *);
void output_line(Tree,FILE *);
#endif // InvertedIdx_H
