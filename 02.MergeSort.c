/**
 * Implementing Merge Sort Pseudo Code (CLRS Pg 31-34) 
 **/
#include <stdio.h>
#include <stdlib.h> // for malloc
// work out value to use as sentinel for int type, INT_MAX.
#define INT_MAX  ((1 << (sizeof(int)*8 - 2)) - 1 + (1 << (sizeof(int)*8 - 2))) 

#define N 20 // array length
int x[N]={67,92,7,52,45,78,61,36,8,27,74,14,34,79,41,55,88,64,85,14};
int inf=INT_MAX; // set infinity to sentinel value 

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
    int* L = (int*) malloc((n1+1) * sizeof(int)); // + 1 for the sentinel
    int* R = (int*) malloc((n2+1) * sizeof(int)); // + 1 for the sentinel
    for(int i=0;i<n1;i++){
        L[i]=A[p+i];
    }
    L[n1]=inf;
    for(int j=0;j<n2;j++){
        R[j]=A[q+1+j];
    }
    R[n2]=inf;
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
    // sort array A from index p to index r. 
    if(p<r){
        int q=(p+r)/2; 
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        merge(A,p,q,r);
    }
}