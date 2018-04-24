#include <stdio.h>
#include <stdlib.h> // for malloc

struct ListItem{
    int x;
    struct ListItem* prev;
    struct ListItem* next;
};

struct ListItem* headPtr=0;
void insert(int val);
void delete(int val);
void listInsert(struct ListItem* insItemPtr);
void listDelete(struct ListItem* delItemPtr);
struct ListItem* listSearch(int val);
void printList();
void printItem(struct ListItem* currItemPtr);

void main(){
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    delete(3);
    delete(3);
    delete(4);
    printList();
}

void insert(int val){
    struct ListItem* newItem=malloc(sizeof(struct ListItem));
    (*newItem).x=val;
    listInsert(newItem);
}
void delete(int val){
    struct ListItem* delItem = listSearch(val);
    if(delItem!=0){
        listDelete(delItem);
        free(delItem);
    }
}

void listInsert(struct ListItem* insItemPtr){
    (*insItemPtr).next=headPtr;
    if (headPtr!=0){
        (*headPtr).prev=insItemPtr;
    }
    headPtr=insItemPtr;
    (*insItemPtr).prev=0;
    return;
}
void listDelete(struct ListItem* delItemPtr){
    if((*delItemPtr).prev!=0){
        (*(*delItemPtr).prev).next=(*delItemPtr).next;
    }else{
        headPtr=(*delItemPtr).next;
    }
    if((*delItemPtr).next!=0){
        (*(*delItemPtr).next).prev=(*delItemPtr).prev;
    }
    return;
}

struct ListItem* listSearch(int val){
    struct ListItem* currItemPtr = headPtr;
    while(currItemPtr!=0 && ((*currItemPtr).x)!=val){
        currItemPtr=(*currItemPtr).next;
    }
    return currItemPtr;
}

void printList(){
    struct ListItem* currItemPtr = headPtr;
    while(currItemPtr!=0){
        printItem(currItemPtr);
        currItemPtr=(*currItemPtr).next;
    }
    return;
}
void printItem(struct ListItem* currItemPtr){
    printf("curr:%x, ",currItemPtr);
    printf("x:%d, ",(*currItemPtr).x);
    printf("prev:%x, ",(*currItemPtr).prev);
    printf("next:%x;\n",(*currItemPtr).next);
}