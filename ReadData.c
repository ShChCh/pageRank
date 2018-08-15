#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ReadData.h"
#define BUFSIZE 1024

/*
  A possible way to read data ...

*/
queue GetCollection(){
    queue a = newQueue();
    FILE *f;
    char ch[BUFSIZE];
    f = fopen("collection.txt","r");
    assert(f!=NULL);
    while(fscanf(f,"%s",ch) != EOF){
        QueueEnqueue(a,strdup(ch));
    }
    fclose(f);
    return a;
}
int convert_url_to_index(char *url_name,char **node,int length){
    int i;
    for(i=0;i<length;i++){
        if(strcmp(node[i],url_name)==0){
//            printf("%s%s\n",node[i],url_name);
            break;
        }
    }
    return i;
}
Graph GetGraph(){
    queue a = GetCollection();
    int length = a->length;
    char *node[length];
    char *u,*v ;
    int i=0;
    while(!QueueIsEmpty(a)){
        u = QueueDequeue(a);
        node[i]=strdup(u);
        i++;
    }
    Graph g = newGraph(length,node);
    int j;
    for(j=0;j<length;j++){
        v = node[j];
        char *temp = strdup(v);
        strcat(temp,".txt");
        FILE *f;
        char buff[BUFSIZE];
        f = fopen(temp,"r");
        assert(f!=NULL);
        while(fscanf(f,"%s",buff)!=EOF && strcmp(buff,"Section-1"));
        while(fscanf(f,"%s",buff)!=EOF && strcmp(buff,"#end")){
            int index = convert_url_to_index(strdup(buff),node,length);
//            printf("%d%d\n",j,index);
            struct Edge e = {j,index};
            insertEdge(g,e);
        }
    }
//    showGraph(g);
    return g;
}
//int main(){
//    Graph g = GetGraph();
//    showGraph(g);
//    printf("%d",adjacent(g,0,1));
////    char **temp = get_node_list(g);
////    printf("%s\n",temp[0]);
////    printf("%d\n",outDegree(g,0));
//    return 0;
//}
//void readSection1(char *urlname, Graph g){

/*
   let's say urlname is "url31"
   Open "url31.txt"
   read Section-1
	(How?, a simple approach ...
	 skip lines until first two tokens are "#start" and  "Section-1"
	 read lines (tokens) and add the required links in graph g
	 stop reading when first two tokens are "#end" and  "Section-1"
	)
*/


//}


//void readSection2(char *filename, InvertedIdx idx){

/*
   let's say filename is "url31.txt"
   Open "url31.txt"
   read Section-2
	(How?, a simple approach ...
	 skip lines until first two tokens are "#start" and  "Section-2"
	 read lines (tokens) and add  words (normalised) in inverted index ADT idx
	 stop reading when first two tokens are "#end" and  "Section-2"
	)
*/

//}



