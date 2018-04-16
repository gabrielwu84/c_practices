/*
 * CLRS pg 256-258
 */

#include <stdio.h>
#include <stdlib.h> // for malloc

struct hashTableItem{
    int key;
    int data;
    struct hashTableItem* prev;
    struct hashTableItem* next;
};

int hashTableSize=5;
struct hashTableItem** hashTable; // Hash Table

void set(int key,int value);
void del(int key);
struct hashTableItem* get(int key);
int hashFn(int key);
struct hashTableItem* findKeyInBucket(int key, struct hashTableItem* listPtr);
void printTable();
void printEntry(struct hashTableItem* x);

void main(){
    // initialization
    hashTable = calloc(hashTableSize,sizeof(struct hashTableItem*));
    // test
    struct hashTableItem* x;
    printf("set(2,100)\n");
    set(2,100);
    printTable();
    printf("get(2)\n");
    x=get(2);
    printEntry(x);
    printf("get(3)\n");
    x=get(3);
    printEntry(x);
    printTable();
    printf("set(7,12311)\n");
    set(7,12311);
    printTable();
    printf("set(2,12311)\n");
    set(2,12311);
    printTable();
    printf("set(8,192)\n");
    set(8,192);
    printTable();
    printf("del(2)\n");
    del(2);
    printTable();
    printf("del(2)\n");
    del(2);
    printTable();
    printf("get(2)\n");
    x=get(2);
    printEntry(x);
}

void set(int key,int value){
    // insert into Linked List of hashFn(key) 
    // check if key exists in linked list. 
    struct hashTableItem** bucketPtrPtr=hashTable+hashFn(key);
    struct hashTableItem* bucketPtr=*bucketPtrPtr;
    struct hashTableItem* itemPosition=findKeyInBucket(key, bucketPtr);
    if(itemPosition==0){
        // key does not exist, make a new hashTableItem and insert at the beginning of linked list
        struct hashTableItem* item=malloc(sizeof(struct hashTableItem));
        (*item).key=key;
        (*item).data=value;
        (*item).next=bucketPtr;
        (*item).prev=0;
        if(bucketPtr!=0){
            (*bucketPtr).prev=item;
        }
        *bucketPtrPtr=item;
    }else{
        // key exists, update its value
        (*itemPosition).data=value;
    }
}
void del(int key){
    struct hashTableItem* bucketPtr=*(hashTable+hashFn(key));
    struct hashTableItem* itemPosition = findKeyInBucket(key, bucketPtr);
    if(itemPosition!=0){
        if((*itemPosition).next!=0){
            (*(*itemPosition).next).prev=(*itemPosition).prev;
        }
        (*(*itemPosition).prev).next=(*itemPosition).next;
        free(itemPosition);
    }
}
int hashFn(int key){
    return key%hashTableSize;
}
struct hashTableItem* get(int key){
    struct hashTableItem* bucketPtr=*(hashTable+hashFn(key));
    return  findKeyInBucket(key, bucketPtr);
}

struct hashTableItem* findKeyInBucket(int key, struct hashTableItem* listPtr){
    while(listPtr!=0 && (*listPtr).key!=key){
        listPtr=(*listPtr).next;
    }
    return listPtr;
}

void printTable(){
    for (int i=0;i<hashTableSize;i++){
        struct hashTableItem* listPtr=*(hashTable+i);
        while(listPtr!=0){
            printf("%d %d\n",(*listPtr).key,(*listPtr).data);
            listPtr=((*listPtr).next);
        }
    }
}

void printEntry(struct hashTableItem* x){
    if(x!=0){
        printf("%d\n",(*x).data);
    }else{
        printf("null\n");
    }
}