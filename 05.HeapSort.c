/*
 * Heapsort (CLRS pg 151-161)
 */
#include <stdio.h>

#define N 20 // array length
// first value is placeholder so that array index can start at 1  
// needed for nice index arithmatic. 
int A[N+1]={0,67,92,7,52,45,78,61,36,8,27,74,14,34,79,41,55,88,64,85,140};

int parent(int i); int left(int i); int right(int i);
void exchange(int *A, int i, int j);
void maxHeapify(int *A, int heapsize, int i);
void buildMaxHeap(int *A,int heapsize);
void heapsort(int *A, int heapsize);

void main(){
    for(int i=1;i<N+1;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    heapsort(A,N);
    for(int i=1;i<N+1;i++){
        printf("%d ",A[i]);
    }
}

// CLRS Pg 160
void heapsort(int *A, int heapsize){
    int A_length=heapsize;
    buildMaxHeap(A, heapsize);
    for(int i=A_length; i>1; i--){
        exchange(A,1,i);
        heapsize--;
        maxHeapify(A,heapsize,1);
    } 
    return;
}

// CLRS Pg 157
void buildMaxHeap(int *A,int heapsize){
    for(int i=parent(heapsize);i>0;i--){
        maxHeapify(A,heapsize,i);
    }
    return;
}

// CLRS Pg 154
void maxHeapify(int *A, int heapsize, int i){
    int largest=i;
    int l=left(i); 
    int r=right(i);
    if(l<=heapsize && A[l]>A[i]){
        largest = l;
    }
    if(r<=heapsize && A[r]>A[largest]){
        largest = r;
    }
    if(largest!=i){
        exchange(A,i,largest);
        maxHeapify(A,heapsize,largest);
    }
    return;
}

void exchange(int *A, int i, int j){
    int A_i=A[i];
    A[i]=A[j];
    A[j]=A_i;
    return;
}

// CLRS Pg 152
int parent(int i){
    return (i>>1); // floor(i/2)
}

int left(int i){
    return i<<1; // i*2
}

int right(int i){
    return (i<<1)|0x1; // i*2+1
}