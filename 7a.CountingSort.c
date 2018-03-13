/*
 * Counting Sort (CLRS pg 195)
 */
#include <stdio.h>
#include <stdlib.h> // for malloc

#define N 20 // array length
int A[N]={88,5,69,34,44,89,14,37,72,19,88,93,43,32,29,49,42,3,89,90};

int max(int *A,int n);
void countingSort(int *A,int *B,int n,int k);

void main(){
    int k=max(A,N);
    int *B=malloc(N*sizeof(int));

    countingSort(A,B,N,k);
    
    printf("\nA: ");
    for(int i=0;i<N;i++){
        printf("%d ",A[i]);
    }
    printf("\nB: ");
    for(int i=0;i<N;i++){
        printf("%d ",B[i]);
    }
    printf("\n");
}

void countingSort(int *A,int *B,int n,int k){
    int *C=malloc((k+1)*sizeof(int));
    for(int i=0;i<=k;i++){
        C[i]=0;
    }
    // C holds number of each entry
    for(int j=0;j<n;j++){
        C[A[j]]++;
    }
    // C holds cummulative position from 1 to N
    for(int i=1;i<=k;i++){
        C[i]=C[i]+C[i-1];
    }
    for(int j=n-1;j>=0;j--){
        // turning 1 to N into 0 to N-1
        B[C[A[j]]-1]=A[j];
        C[A[j]]--;
    }
    return;
}

int max(int *A,int n){
    int max=0;
    for(int i=0;i<n;i++){
        if(A[i]>max){
            max=A[i];
        }
    }
    return max;
}