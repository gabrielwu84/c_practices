/*
 * CLRS pg 269-273
 */

#include <stdio.h>
#include <stdlib.h> // for malloc

struct oaTableItem{
    short state; // 0:empty, 1:deleted, 2:filled
    int key;
    int data;
};

int keySize=23; // must be prime number
struct oaTableItem* oaTable; // Open Access Table

void hashInsert(int key,int value);
struct oaTableItem* hashReturn(int key);
struct oaTableItem* hashSearch(int key);
void hashDelete(int key);
void printTable();
void printEntry(struct oaTableItem* x);

void main(){
    // initialization
    oaTable = calloc(keySize,sizeof(struct oaTableItem));
    // test
    struct oaTableItem* x;
    printf("hashInsert(20,100)\n");
    hashInsert(20,100);
    printTable();
    printf("hashReturn(20)\n");
    x=hashReturn(20);
    printEntry(x);
    printf("hashInsert(50,12311)\n");
    printf("hashDelete(2)\n");
    printf("hashDelete(2)\n");
    hashInsert(50,12311);
    hashDelete(2);
    hashDelete(2);
    printTable();
}

void hashInsert(int key,int value){
    int i=1;
    while((*(oaTable+(key*i)%keySize)).state>0 && i<keySize){
        i++;
    }
    if(i<keySize){
        struct oaTableItem* item=(oaTable+key*i%keySize);
        (*item).state=2;
        (*item).key=key;
        (*item).data=value;
    }else{
        // overflow
    }
}

struct oaTableItem* hashReturn(int key){ 
    return hashSearch(key);
}
struct oaTableItem* hashSearch(int key){ 
    int i=1;
    struct oaTableItem* itemPtr=(oaTable+(key*i)%keySize);
    struct oaTableItem item =*itemPtr;
    while(item.state<2 && item.key!=key && i<keySize){
        i++;
        item =(*(oaTable+(key*i)%keySize));
    }
    if(i==keySize){
        return 0;
    }else{
        return itemPtr;
    }
}
void hashDelete(int key){
    struct oaTableItem* itemPtr=hashSearch(key);
    if(itemPtr!=0){
        if((*itemPtr).state==2){
            (*itemPtr).state=1;
        }
    }
}

void printTable(){
    for (int i=0;i<keySize;i++){
        if((*(oaTable+i)).state==2){
            printf("key:%d, data:%d;\n",(*(oaTable+i)).key,(*(oaTable+i)).data);
        }
    }
}

void printEntry(struct oaTableItem* x){
    if(x!=0){
        printf("%d\n",(*x).data);
    }else{
        printf("null");
    }
}