/*
 * Stack Data Structure (CLRS pg 233)
 */
#include <stdio.h>
#include <stdlib.h> // for malloc

int top=-1;
int *S;
int sSize=0;

int stackEmpty();
int push(int x);
int pop();

void main(){
    S=(int *)malloc(sizeof(int));
    sSize=1;
    push(1);
    push(2);
    push(3);
    push(4);
    printf("%d\n",pop());
    printf("%d\n",pop());
    printf("%d\n",pop());
    printf("%d\n",pop());
    printf("%d\n",pop());
}

int stackEmpty(){
    if (top==-1)
        return 1;
    else 
        return 0;
}
int push(int x){
    S[++top]=x;
    // check overflow. if so allocate larger memory and copy data to new array. 
    if (top==sSize-1){
        int sSize1=2*sSize;
        int *S1=(int *)malloc(sSize1*sizeof(int));
        for (int i=0;i<sSize;i++){
            S1[i]=S[i];
        }
        sSize=sSize1;
        free(S);
        S=S1;
    }
}
int pop(){
    if(stackEmpty()==1){
        printf("underflow");
        return 0;
    }else{
        return S[top--];
    }
}