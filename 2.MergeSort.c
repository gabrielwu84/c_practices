/**
 * Implementing Merge Sort Pseudo Code (CLRS Pg 31-34) 
 **/
#include <stdio.h>
#include <stdlib.h> // for malloc

#define N 10 // array length
int x[N]={3,2,6,2,1,3,123,5,2,75};

void merge(int* A, int p, int q, int r);
void mergeSort(int* A, int p, int r);

void main(){
    // initial array
    printf("before: ");
    for(int i=0;i<N;i++){
        printf("%d ",x[i]);
    }
    printf("\n\n");

    // call merge sort
    mergeSort(x, 0, N-1);

    // final array
    printf("after: ");
    for(int i=0;i<N;i++){
        printf("%d ",x[i]);
    }
    printf("\n\n");
}

void merge(int* A, int p, int q, int r){
    // p to q sorted, q+1 to r sorted.
    int n1=q-p+1;   // no of elements in L
    int n2=r-q;     // = r-(q+1)+1, the no of elements in R. 
    int* L = (int*) malloc((n1) * sizeof(int));
    int* R = (int*) malloc((n2) * sizeof(int));
    for(int i=0;i<n1;i++){
        L[i]=A[p+i];
    }
    for(int j=0;j<n2;j++){
        R[j]=A[q+1+j];
    }
    int i=0; int j=0;
    for(int k=p;k<=r;k++){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }else{
            A[k]=R[j];
            j++;
        }
    }
    free(L);
    free(R);
}

void mergeSort(int* A, int p, int r){
    if(p<r){
        int q=(p+r)/2; 
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        merge(A,p,q,r);
    }
}