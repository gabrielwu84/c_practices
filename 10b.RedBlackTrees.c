/*
 * Red Black Trees (CLRS pg 308-329)
 */

#include <stdio.h>
#include <stdlib.h> // for malloc
enum Color {RED=1,BLACK=0};
struct rbTreeItem{
    int key;
    enum Color color;
    struct rbTreeItem* p;
    struct rbTreeItem* left;
    struct rbTreeItem* right;
};
struct rbTreeItem* Troot=0;
struct rbTreeItem* Tnil;

void insert(int key);
void delete(int key);
void rbInsert(struct rbTreeItem* z);
void rbDelete(struct rbTreeItem* z);
void rbInsertFixup(struct rbTreeItem* z);
void rbDeleteFixup(struct rbTreeItem* x);
void leftRotate(struct rbTreeItem* x);
void rightRotate(struct rbTreeItem* x);
struct rbTreeItem* treeMinimum(struct rbTreeItem* x);
struct rbTreeItem* iterativeTreeSearch(struct rbTreeItem* x, int k);
void rbTransplant(struct rbTreeItem* u, struct rbTreeItem* v);

void printRBTree();
void iterativePrintRBTree(struct rbTreeItem* x);

void main(){ 
    Tnil=(struct rbTreeItem *) malloc(sizeof(struct rbTreeItem));
    (*Tnil).color=BLACK;
    Troot=Tnil;
    insert(1);
    insert(2);
    insert(1);
    insert(2);
    insert(1);
    insert(2);
    insert(2);
    insert(2);
    insert(5);
    insert(3);
    insert(2);
    insert(2);
    insert(5);
    insert(3);
    printRBTree();
    delete(1);
    delete(1);
    delete(5);
    delete(5);
    delete(5);
    delete(1);
    delete(1);
    delete(1);
    printRBTree();
}

void insert(int key){
    struct rbTreeItem* z = malloc(sizeof(struct rbTreeItem));
    (*z).key=key;
    rbInsert(z);
}
void rbInsert(struct rbTreeItem* z){
    struct rbTreeItem* y = Tnil;
    struct rbTreeItem* x = Troot;
    while(x!=Tnil){
        y=x;
        if((*z).key<(*x).key){
            x=(*x).left;
        }else{
            x=(*x).right;
        }
    }
    (*z).p=y;
    if(y==Tnil){
        Troot=z; // tree was empty
    }else if((*z).key<(*y).key){
        (*y).left=z;
    }else{
        (*y).right=z;
    }
    (*z).left=Tnil;
    (*z).right=Tnil;
    (*z).color=RED;
    rbInsertFixup(z);
    return;
}

void rbInsertFixup(struct rbTreeItem* z){
    struct rbTreeItem* y;
    while((*(*z).p).color==RED){
        if((*z).p==(*(*(*z).p).p).left){
            y=(*(*(*z).p).p).right;
            if((*y).color==RED){
                (*(*z).p).color=BLACK;
                (*y).color=BLACK;
                (*(*(*z).p).p).color=RED;
                z=(*(*z).p).p;
            }else{
                if(z==(*(*z).p).right){
                    z=(*z).p;
                    leftRotate(z);
                }
                (*(*z).p).color=BLACK;
                (*(*(*z).p).p).color=RED;
                rightRotate((*(*z).p).p);
            }
        }else{
            y=(*(*(*z).p).p).left;
            if((*y).color==RED){
                (*(*z).p).color=BLACK;
                (*y).color=BLACK;
                (*(*(*z).p).p).color=RED;
                z=(*(*z).p).p;
            }else{
                if(z==(*(*z).p).left){
                    z=(*z).p;
                    rightRotate(z);
                }
                (*(*z).p).color=BLACK;
                (*(*(*z).p).p).color=RED;
                leftRotate((*(*z).p).p);
            }
        }
    }
    (*Troot).color=BLACK;
    return;
}

void leftRotate(struct rbTreeItem* x){
    struct rbTreeItem* y = (*x).right;
    (*x).right=(*y).left;
    if((*y).left!=Tnil){
        (*(*y).left).p=x;
    }
    (*y).p=(*x).p;
    if((*x).p==Tnil){
        Troot=y;
    }else if(x==(*(*x).p).left){
        (*(*x).p).left=y;
    }else{
        (*(*x).p).right=y;
    }
    (*y).left=x;
    (*x).p=y;
    return;
}
void rightRotate(struct rbTreeItem* y){ 
    struct rbTreeItem* x = (*y).left;
    (*y).left=(*x).right;
    if((*x).right!=Tnil){
        (*(*x).right).p=y;
    }
    (*x).p=(*y).p;
    if((*y).p==Tnil){
        Troot=x;
    }else if(y==(*(*y).p).left){
        (*(*y).p).left=x;
    }else{
        (*(*y).p).right=x;
    }
    (*x).right=y;
    (*y).p=x;
    return;
}
void delete(int key){
    struct rbTreeItem* x=iterativeTreeSearch(Troot,key);
    if(x!=Tnil){
        rbDelete(x);
    }
    free(x);
}
void rbDelete(struct rbTreeItem* z){
    struct rbTreeItem* x;
    struct rbTreeItem* y=z;
    enum Color yOriginalColor = (*y).color;
    if((*z).left==Tnil){
        x=(*z).right;
        rbTransplant(z,(*z).right);
    }else if((*z).right==Tnil){
        x=(*z).left;
        rbTransplant(z,(*z).left);
    }else{
        y=treeMinimum((*z).right);
        yOriginalColor=(*y).color;
        x=(*y).right;
        if((*y).p==z){
            (*x).p=y;
        }else{
            rbTransplant(y,(*y).right);
            (*y).right=(*z).right;
            (*(*y).right).p=y;
        }
        rbTransplant(z,y);
        (*y).left=(*z).left;
        (*(*y).left).p=y;
        (*y).color=(*z).color;
    }
    if(yOriginalColor==BLACK){
        rbDeleteFixup(x);
    }

}

void rbTransplant(struct rbTreeItem* u, struct rbTreeItem* v){
    if((*u).p==Tnil){
        Troot = v;
    }else if(u==(*(*u).p).left){
        (*(*u).p).left = v;
    }else{
        (*(*u).p).right = v;
    }
    (*v).p=(*u).p;
    return;
}
void rbDeleteFixup(struct rbTreeItem* x){
    struct rbTreeItem* w;
    while(x!=Troot && (*x).color==BLACK){
        if(x==(*(*x).p).left){
            w = (*(*x).p).right;
            if((*w).color==RED){
                (*w).color=BLACK;
                (*(*x).p).color=RED;
                leftRotate((*x).p);
                w=(*(*x).p).right;
            }
            if((*(*w).left).color==BLACK && (*(*w).right).color==BLACK){
                (*w).color=RED;
                x=(*x).p;
            }else{
                if((*(*w).right).color==BLACK){
                    (*(*w).left).color=BLACK;
                    (*w).color=RED;
                    rightRotate(w);
                    w=(*(*x).p).right;
                }
                (*w).color=(*(*x).p).color;
                (*(*x).p).color=BLACK;
                (*(*w).right).color=BLACK;
                leftRotate((*x).p);
                x=Troot;
            }
        }else{
            w = (*(*x).p).left;
            if((*w).color==RED){
                (*w).color=BLACK;
                (*(*x).p).color=RED;
                rightRotate((*x).p);
                w=(*(*x).p).left;
            }
            if((*(*w).right).color==BLACK && (*(*w).left).color==BLACK){
                (*w).color=RED;
                x=(*x).p;
            }else{
                if((*(*w).left).color==BLACK){
                    (*(*w).right).color=BLACK;
                    (*w).color=RED;
                    leftRotate(w);
                    w=(*(*x).p).left;
                }
                (*w).color=(*(*x).p).color;
                (*(*x).p).color=BLACK;
                (*(*w).left).color=BLACK;
                rightRotate((*x).p);
                x=Troot;
            }
        }
    }
    (*x).color=BLACK;
    return;
}
struct rbTreeItem* treeMinimum(struct rbTreeItem* x){
    while((*x).left!=Tnil){
        x=(*x).left;
    }
    return x;
}
struct rbTreeItem* iterativeTreeSearch(struct rbTreeItem* x, int k){
    while(x!=Tnil && k!=(*x).key){
        if(k<(*x).key){
            x=(*x).left;
        }else{
            x=(*x).right;
        }
    }
    return x;
}

void printRBTree(){
    printf("printing rbTree\n |");
    iterativePrintRBTree(Troot);
    printf("\n");
}
void iterativePrintRBTree(struct rbTreeItem* x){
    if((*x).left!=Tnil){
        iterativePrintRBTree((*x).left);
    }
    printf(" %d |",(*x).key);
    // printf("key:%d, c:%d, address:%x, ",(*x).key,(*x).color,x);
    // printf("p:%x, l:%x, r:%x;\n",(*x).p,(*x).left,(*x).right);
    if((*x).right!=Tnil){
        iterativePrintRBTree((*x).right);
    }
    return;
}