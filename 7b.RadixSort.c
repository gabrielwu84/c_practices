/*
 * Radix Sort (CLRS pg 198)
 */
#include <stdio.h>
#include <stdlib.h> // for malloc

#define N 20 // array length
int A[N]={88,5,69,34,44,89,14,37,72,19,88,93,43,32,29,49,42,3,89,90};

void stableSortByBit(int *A,int n,int k);
void radixSort(int *A,int n);

void main(){
    radixSort(A,N);
    for(int i=0;i<N;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}

void radixSort(int *A,int n){
    // size of int in bytes * no of bits in a byte
    for(int i=0;i<sizeof(int)*8;i++){
        stableSortByBit(A,n,i);
    }
    return;
}

void stableSortByBit(int *A,int n,int k){
    int *A0=malloc(n*sizeof(int));
    int *A1=malloc(n*sizeof(int));
    int n0=0, n1=0;
    for(int i=0;i<n;i++){
        // get the kth bit of number
        if(((A[i]>>k)&1)==1){
            A1[n1]=A[i];
            n1++;
        }else{
            A0[n0]=A[i];
            n0++;
        }
    }
    for(int i=0;i<n0;i++){
        A[i]=A0[i];
    }
    for(int i=0;i<n1;i++){
        A[i+n0]=A1[i];
    }
    return;
}