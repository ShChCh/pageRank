/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"
//#include "DLListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   Tree left, right;
   char  data[100];
   DLListStr  list;
} Node;

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   strcpy(new->data, it);  // replace,   data(new) = it;
   left(new) = right(new) = NULL;
   new->list = newDLListStr();
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%s\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// check whether a key is in a Tree
Tree TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return NULL;

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      return TreeSearch(left(t), it);

   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      return TreeSearch(right(t), it);

   else                                 // it == data(t)
      return t;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL)
      t = newNode(it);

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      left(t) = TreeInsert(left(t), it);

   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      right(t) = TreeInsert(right(t), it);

   return t;
}
DLListStr get_list(Tree t){
    if(t==NULL){
        return NULL;
    }
    else{
        return t->list;
    }
}
void output_line(Tree n, FILE *f){
    if(n==NULL) return;
    fprintf(f,"%s ", n->data);
	DLListStr url_list = n->list;
    showDLListStr(url_list,f);
	fprintf(f,"\n");
}
void output_to_file(Tree n, FILE *f){
    if(n==NULL) return;
    output_to_file(n->left,f);
    output_line(n,f);
    output_to_file(n->right,f);
}

