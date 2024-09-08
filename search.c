#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "txt_bin.h"

typedef struct item{
    char *name;
} Item;

Item** arr;
int items_count = 0;

void Initialize_hash_map(){
    arr = (Item**)malloc(sizeof(Item*)* MAX_NAMES);
    for (int i = 0; i < MAX_NAMES; i++)
        arr[i] = NULL;
}

int calc_hash(const char*  str){
    return (int)strlen(str)%MAX_NAMES;
}

void insert(char* name){
    if(items_count==MAX_NAMES){
        printf("hash Table is full\n");
        return;
    }
    Item* item=(Item*)malloc(sizeof(Item));
    int hash=calc_hash(name);
    // Item->key=key;
    item->name=strdup(name);
    while(arr[hash]!=NULL 
    // && arr[hash]->key != key && arr[hash]->key != -1
    ){
        hash++;
        hash%=MAX_NAMES;
    }
    arr[hash]=item;
    items_count++;
}



int* search(char **strs,int n){
    int *index_arr=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        index_arr[i] = -1;  
    }

    for(int i=0;i<n;i++){
        int hash=calc_hash(strs[i])%MAX_NAMES;
        int initialHash=hash;
        while(strcmp(arr[hash]->name,strs[i])!=0){
            hash++;
            hash%=MAX_NAMES;
            if(hash==initialHash){
                break;
            }
        }
        if(strcmp(arr[hash]->name,strs[i])==0){
            index_arr[i]=hash;
        }
    }

    return index_arr;
}

void free_hash_list(){
    for (int i = 0; i < MAX_NAMES; i++) {
        if (arr[i] != NULL) {
            if (arr[i]->name != NULL) { // Add this check
                free(arr[i]->name);  
            }
            free(arr[i]);        
        }
    }
    free(arr);
    arr = (Item**)malloc(sizeof(Item*)* MAX_NAMES);
}


void initializeSearch(){
    Initialize_hash_map();
    char** names=read_from_binary("data.bin");
    for(int i=0;i<MAX_NAMES;i++){
        insert(names[i]);
    }
    for(int i=0;i<MAX_NAMES;i++){
        free(names[i]);
    }
    free(names);
    
}

// int main(){
//     Initialize_hash_map();
//     char** names=read_from_binary("data.bin");
//     for(int i=0;i<MAX_NAMES;i++){
//         insert(names[i]);
//     }
    
//     //free names
//     for(int i=0;i<MAX_NAMES;i++){
//         free(names[i]);
//     }
//     free(names);

//     char* dummy_strs[] = {"shiva", "jp"};
//     int *result=search(dummy_strs,2);

//     for(int i=0;i<2;i++){
//             printf("name string at index: %d\n",result[i]);
        
//     }
//     char* dummy_strs2[] = {"shiva", "ashish"};
//     result=search(dummy_strs2,2);

//     for(int i=0;i<2;i++){
//             printf("name string at index: %d\n",result[i]);
        
//     }


//     return 0;
// }