/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "DLListStr.h"

// data structures representing DLListStr

typedef struct DLListNode {
	char   value[100];  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *curr;  // current node in list
	DLListNode *last;  // last node in list
} DLListRep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);

        strcpy(new->value, val);  // for int, new->value = it;

	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLListStr
DLListStr newDLListStr()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}


/*
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(DLListStr L, char *val){

	/*
	   implement this function to
	   insert val in L  (in order), no duplicates (set)

	*/
    assert(L!=NULL);
    DLListNode *curr;
    if(L->nitems==0){
       DLListNode *new_node = newDLListNode(val);
       L->first = new_node;
       L->last = new_node;
       L->nitems++;
    }
    else{
        int count = 0;
        for(curr=L->first;curr != NULL; curr = curr->next){
            if(strcmp(curr->value,val)==0){
                break;
            }
            else if(strcmp(curr->value,val)>0){
                DLListNode *new_node = newDLListNode(val);
                if(count==0){
                    L->first = new_node;
                }
                else{
                    DLListNode *temp = curr->prev;
                    temp->next = new_node;
                    new_node->prev = temp;
                }
                new_node->next = curr;
                curr->prev = new_node;
                L->nitems++;
                break;
            }
            else{
                if(curr->next == NULL){
                    DLListNode *new_node = newDLListNode(val);
                    curr->next = new_node;
                    new_node->prev = curr;
                    L->last = new_node;
                    L->nitems++;
                    break;
                }
            }
            count++;
        }
    }
}



// display items from a DLListStr, comma separated
void showDLListStr(DLListStr L,FILE *f)
{
	assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next){
		fprintf(f,"%s ",curr->value);
	}
}


// free up all space associated with list
void freeDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}
//int main(){
////    DLListStr L =newDLListStr();
////    insertSetOrd(L,"b");
////    insertSetOrd(L,"a");
////    showDLListStr(L);
//    char *a = "!!asDasfasd";
//    char *p =normalise(a);
//    printf("%s",p);
//    return 0;
//}


