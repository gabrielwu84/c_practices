/*
 * Binary Search Trees (CLRS pg 286-292)
 */

#include <stdio.h>
#include <stdlib.h> // for malloc

struct bTreeItem{
    int key;
    struct bTreeItem* p;
    struct bTreeItem* left;
    struct bTreeItem* right;
};
struct bTreeItem* root=0;

void insert(int key);
void delete(int key);
void treeInsert(struct bTreeItem* z);
void treeDelete(struct bTreeItem* z);
struct bTreeItem* treeMinimum(struct bTreeItem* x);
struct bTreeItem* iterativeTreeSearch(struct bTreeItem* x, int k);
void printBTree();
void iterativePrintBTree(struct bTreeItem* x);

void main(){ 
    insert(1);
    insert(2);
    insert(2);
    insert(2);
    insert(5);
    insert(3);
    delete(7);
    printBTree();
}

void insert(int key){
    struct bTreeItem* z = malloc(sizeof(struct bTreeItem));
    (*z).key=key;
    treeInsert(z);
}
void treeInsert(struct bTreeItem* z){
    (*z).p=0; (*z).left=0; (*z).right=0;
    struct bTreeItem* y = 0;
    struct bTreeItem* x = root;
    while(x!=0){
        y=x;
        if((*z).key<(*x).key){
            x=(*x).left;
        }else{
            x=(*x).right;
        }
    }
    (*z).p=y;
    if(y==0){
        root=z; // tree was empty
    }else if((*z).key<(*y).key){
        (*y).left=z;
    }else{
        (*y).right=z;
    }
    return;
}

void transplant(struct bTreeItem* u, struct bTreeItem* v){
    if((*u).p==0){
        root=v;
    }else if(u==(*(*u).p).left){
        (*(*u).p).left=v;
    }else{
        (*(*u).p).right=v;
    }
    if(v!=0){
        (*v).p=(*u).p;
    }
}

void delete(int key){
    struct bTreeItem* x=iterativeTreeSearch(root,key);
    if(x!=0){
        treeDelete(x);
    }
    free(x);
}
void treeDelete(struct bTreeItem* z){
    if((*z).left==0){
        transplant(z,(*z).right);
    }else if((*z).right==0){
        transplant(z,(*z).left);
    }else{
        struct bTreeItem* y=treeMinimum((*z).right);
        if((*y).p!=z){
            transplant(y,(*y).right);
            (*y).right=(*z).right;
            (*(*y).right).p=y;
        }
        transplant(z,y);
        (*y).left=(*z).left;
        (*(*y).left).p=y;
    }
    return;
}

struct bTreeItem* treeMinimum(struct bTreeItem* x){
    while((*x).left!=0){
        x=(*x).left;
        return x;
    }
}
struct bTreeItem* iterativeTreeSearch(struct bTreeItem* x, int k){
    while(x!=0 && k!=(*x).key){
        if(k<(*x).key){
            x=(*x).left;
        }else{
            x=(*x).right;
        }
    }
    return x;
}

void printBTree(){
    iterativePrintBTree(root);
}
void iterativePrintBTree(struct bTreeItem* x){
    if((*x).left!=0){
        iterativePrintBTree((*x).left);
    }
    printf("%d | ",(*x).key);
    if((*x).right!=0){
        iterativePrintBTree((*x).right);
    }
    return;
}