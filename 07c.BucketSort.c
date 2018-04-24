/*
 * Bucket Sort (CLRS pg 201)
 */
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <math.h> // for floor

#define N 20 // array length
float A[N]={0.08,0.05,0.06,0.04,0.045,0.89,0.14,0.37,0.72,0.19,0.88,0.93,0.43,0.32,0.29,0.49,0.42,0.3,0.88,0.90};

typedef struct bucketItem {
    float value;
    struct bucketItem *next;
} bucketItem;

void insertInto(bucketItem **B,float Ai,int k);
void bucketSort(float *A,int n);

void main(){
    bucketSort(A,N);
    for(int i=0;i<N;i++){
        printf("%0.4f ",A[i]);
    }
}
void bucketSort(float *A,int n){
    bucketItem **B=malloc(n*sizeof(bucketItem*));
    for(int i=0;i<n;i++){
        B[i]=NULL; 
    }
    for(int i=0;i<n;i++){
        insertInto(B,A[i],(int)floor(n*A[i]));
    }
    int j=0;
    for(int i=0;i<n;i++){
        bucketItem* x=B[i];
        while(x!=NULL){
            A[j]=(*x).value;
            j++;
            x=(*x).next;
        }
    }
    return;
}
void insertInto(bucketItem **B,float Ai,int k){
    bucketItem *item_ptr=(bucketItem*) malloc(sizeof(bucketItem));
    (*item_ptr).value=Ai;
    (*item_ptr).next=NULL;
    bucketItem **b_tt=&(B[k]); // address of pointer to next item in bucket
    int foundPos=0;
    while((*b_tt)!=NULL && !foundPos){
        bucketItem *b_t=(*b_tt);
        if((*b_t).value>Ai){
            foundPos=1;
        } else {
            b_tt=&((*b_t).next);
        }
    }
    if(foundPos){
        (*item_ptr).next=(*b_tt);
    }
    *b_tt=item_ptr;
    return;
}