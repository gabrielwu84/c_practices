/*
 * CLRS pg 254
 */

#include <stdio.h>
#include <stdlib.h> // for malloc

struct daTableItem{
    int key;
    int data;
};

int keySize=20;
struct daTableItem** daTable; // Direct Access Table

void set(int key,int value);
void del(int key);
struct daTableItem* get(int key);
void printTable();
void printEntry(struct daTableItem* x);

void main(){
    // initialization
    daTable = calloc(keySize,sizeof(struct daTableItem*));
    // test
    struct daTableItem* x;
    printf("set(2,100)\n");
    printf("set(5,12311)\n");
    set(2,100);
    set(5,12311);
    printf("get(2)\n");
    x=get(2);
    printEntry(x);
    printf("get(3)\n");
    x=get(3);
    printEntry(x);
    printf("get(5)\n");
    x=get(5);
    printEntry(x);
    printf("del(2)\n");
    printf("get(2)\n");
    del(2);
    x=get(2);
    printEntry(x);
    printf("del(2)\n");
    printf("printTable\n");
    del(2);
    printTable();
}

void set(int key,int value){
    struct daTableItem* item=malloc(sizeof(struct daTableItem));
    (*item).key=key;
    (*item).data=value;
    *(daTable+key)=item;
    return;
}
void del(int key){
    if(*(daTable+key)!=0){
        free(*(daTable+key));
        *(daTable+key)=0;
    }
    return;
}
struct daTableItem* get(int key){
    // either returns 0 (entry is empty) or pointer to daTableItem (holding its value). 
    return *(daTable+key);
}

void printTable(){
    for (int i=0;i<keySize;i++){
        if(*(daTable+i)!=0){
            printf("%d %d\n",(*(*(daTable+i))).key,(*(*(daTable+i))).data);
        }
    }
}

void printEntry(struct daTableItem* x){
    if(x!=0){
        printf("%d\n",(*x).data);
    }else{
        printf("null\n");
    }
}