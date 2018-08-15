#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "searchPagerank.h"
#define MAXSTRING 1500

UNode NewNode(){
    UNode n = malloc(sizeof(UNode));
    n->name=NULL;
    n->pages=0;
    n->rate=0;
    n->next=NULL;
    return n;
}
int main(int argc, char* argv[]){
    UNode l = build_node_list();
    l = search_and_count(l,argc,argv);
    int n=0;
    while(l!=NULL && n<30){
        if(l->pages == (argc-1)){
            printf("%s\n",l->name);
            n++;
        }
        l=l->next;
    }
    return 0;
}
UNode build_node_list(){
    char line[MAXSTRING];
    FILE *f;
    UNode head = NULL;
    UNode curr = head;
    if ((f = fopen("pagerankList.txt","r")) == NULL) {
        printf("Error!\n");
        return head;
   }
   while(fgets(line,MAXSTRING,f)!=NULL){
        char *token;
        token = strtok(line,", \n");
        int n=0;
        UNode temp = NewNode();
        temp->name = strdup(token);
        while(token != NULL && n<3){
            if(n==2){
                temp->rate = atof(token);
            }
            token = strtok(NULL,", \n");
            n++;
        }
        if(head==NULL){
            head = temp;
            curr = temp;
        }
        else{
            curr->next = temp;
            curr = temp;
        }
   }
   fclose(f);
   return head;
}
UNode search_and_count(UNode l, int argc, char **argv){
    char line[MAXSTRING];
    FILE *f;
    int n;
    for(n = 1; n < argc; n++){
        if ((f = fopen("invertedIndex.txt","r")) == NULL) {
            printf("Error!\n");
            return l;
        }
        while(fgets(line, MAXSTRING,f)!=NULL){
            char *token;
            char *temp = calloc(MAXSTRING,sizeof(char));
            temp = strcpy(temp,line);
            token = strtok(temp," ");
            if(strcmp(argv[n],token)==0){
                break;
            }
            else if(strcmp(argv[n],token)<0){
                return l;
            }
        }
        char * token;
        token = strtok(line," ");
        while(token!=NULL){
            token = strtok(NULL," ");
            UNode temp = l;
            if(token==NULL) break;
            while(temp != NULL){
                if(strcmp(temp->name,token) == 0){
                    temp->pages++;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    return l;
}
