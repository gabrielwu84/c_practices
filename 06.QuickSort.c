/*
 * Quicksort (CLRS pg 171)
 */
#include <stdio.h>

#define N 20 // array length
int A[N]={67,92,7,52,45,78,61,36,8,27,74,14,34,79,41,55,88,64,85,140};

void exchange(int *A,int i,int j);
int partition(int *A,int p,int r);
void quicksort(int *A,int p,int r);

void main(){
    for(int i=1;i<N+1;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    quicksort(A,0,N);
    for(int i=1;i<N+1;i++){
        printf("%d ",A[i]);
    }
}
void quicksort(int *A,int p,int r){
    if(p<r){
        int q=partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

int partition(int *A,int p,int r){
    int x=A[r];
    int i=p-1;
    for(int j=p;j<r;j++){
        if(A[j]<=x){
            i=i+1;
            exchange(A,i,j);
        }
    }
    exchange(A,i+1,r);
    return i+1;
}

void exchange(int *A,int i,int j){
    int A_i=A[i];
    A[i]=A[j];
    A[j]=A_i;
    return;
}