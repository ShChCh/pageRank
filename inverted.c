#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "inverted.h"
#define BUFSIZE 1024

int main(int argc, char* argv[]){
	if(argc == 1){
		Tree t = GetInvertedList();
		writeILtoFile(t);
		return 1;
	}else{
		printf("There shouldn't be any argument\n");
		return 0;
	}

}
void writeILtoFile(Tree n){
	FILE *a = fopen("invertedIndex.txt","w");
	fclose(a);
	FILE *f = fopen("invertedIndex.txt","a");
	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
    }
    output_to_file(n,f);
	fclose(f);
}

Tree GetInvertedList(){
    queue a = GetCollection();
    Tree t = newTree();
    char *u;
    while(!QueueIsEmpty(a)){
        u = QueueDequeue(a);
        char *temp = strdup(u);
        strcat(temp,".txt");
        FILE *f;
        char buff[BUFSIZE];
        f = fopen(temp,"r");
        assert(f!=NULL);
        while(fscanf(f,"%s",buff)!=EOF && strcmp(buff,"Section-2"));
        while(fscanf(f,"%s",buff)!=EOF && strcmp(buff,"#end")){
                char *p = normalise(buff);
                t = TreeInsert(t,p);
                Tree n = TreeSearch(t,p);
                DLListStr url_list = get_list(n);
                insertSetOrd(url_list,u);
        }

    }
    return t;
}
char *normalise(char *p){
    int i=0;
    int length = strlen(p);
    char temp[length];
    int j=0;
    while(p[i]!='\0'){
        if(isalnum(p[i])){
            temp[j] = tolower(p[i]);
            j++;
        }
        i++;
    }
    temp[j]='\0';
    char *res =strdup(temp);
    return res;
}
