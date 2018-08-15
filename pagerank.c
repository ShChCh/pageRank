#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ReadData.h"
#include "pagerank.h"

typedef struct GNode{
    int id;
    int outDegree;
    float curr_rate;
    float prev_rate;
    G_Node next;
}GNode;

int main(int argc, char* argv[]){
	if(argc == 4){
		float d = atof(argv[1]);
		float diffPR = atof(argv[2]);
		float maxit = atof(argv[3]);
		Graph g = GetGraph();
		char **node_list = get_node_list(g);
		G_Node n=calculatePageRank(g,d,diffPR, maxit);
//		printf("%s, %d, %.7f\n", node_list[n->id],n->outDegree,n->curr_rate);
		writePRtoFile(n,node_list);
		return 1;
	}else{
		printf("Wrong number of inputs\n");
		return 0;
	}

}



void writePRtoFile(G_Node n,char **node_list){
	FILE *a = fopen("pagerankList.txt","w");
	fclose(a);
	FILE *f = fopen("pagerankList.txt","a");
	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
    }
	while(n!=NULL){
		fprintf(f,"%s, %d, %.7f\n", node_list[n->id],n->outDegree,n->curr_rate);
		n = n->next;
	}
	fclose(f);
}


G_Node calculatePageRank(Graph g,float d, float diffPR, float maxit){
	G_Node head;
	int i;
	int flag = 0;
    int nV = get_nV(g);
	for (i = 0 ; i < nV; i++){

		G_Node n = malloc(sizeof(G_Node));
		n->id = i;
		n->prev_rate = n->curr_rate = 1.0 /nV;
		n->outDegree = outDegree(g , n->id );

		if(flag == 0){
			flag = 1;
			n->next = NULL;
			head = n;
		}else{
			n->next = head;
			head = n;
		}
	}



	int iteration = 0;
	float diff = diffPR;

	while(iteration < maxit && diff >= diffPR){
		iteration++;

		G_Node currentNode = head;
		while(currentNode!=NULL){
			currentNode->curr_rate = (1-d)/nV + (d * sumOfConnectedBy(g,currentNode,head));
			currentNode = currentNode->next;
		}

		G_Node currNodeDiff = head;
		while(currNodeDiff!=NULL){
			diff = diff + abs(currNodeDiff->curr_rate - currNodeDiff->prev_rate);
			currNodeDiff = currNodeDiff -> next;
		}

		G_Node advance = head;
		while(advance != NULL){
			advance->prev_rate = advance->curr_rate;
			advance = advance ->next;
		}
	}

	G_Node ret;
	ret = PROrder(head);
	return ret;
}



G_Node PROrder(G_Node head){
	G_Node ordered = NULL;
	G_Node cur = head;
	G_Node tmp = NULL;
	while(cur!= NULL){
		if(ordered == NULL){
			ordered = cur;
			cur = cur->next;
			ordered->next = NULL;
		}else if(cur->curr_rate > ordered->curr_rate){
			tmp = cur;
			cur = cur->next;
			tmp->next = ordered;
			ordered = tmp;
		}else{
			G_Node itr = ordered;
			while(itr != NULL){
				if (cur->curr_rate <= itr->curr_rate && itr->next == NULL){
					tmp = cur;
					cur = cur->next;
					itr->next = tmp;
					tmp->next = NULL;
					break;
				}else if (cur->curr_rate <= itr->curr_rate && cur->curr_rate > itr->next->curr_rate){	//normal insertion
					tmp = cur;
					cur = cur->next;
					tmp->next = itr->next;
					itr->next = tmp;
					break;
				}
				itr= itr->next;
			}
		}
	}
	return ordered;
}

float sumOfConnectedBy(Graph g,G_Node n,G_Node head){
    float sum = 0.0;
    int k;
    for(k=0;k<get_nV(g);k++){
        if(n->id !=k && adjacent(g,k,n->id)){
            G_Node temp = head;
            while(temp !=NULL){
                if(temp->id == k){
                    sum = sum + temp->prev_rate/temp->outDegree;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    return sum;
}
