/**
 * Implementing Square Matrix Multiply Pseudo Code (CLRS Pg 75) 
 **/
#include <stdio.h>

#define N 3 // matrix size
int A[N][N]={88,5,69,-34,-44,89,14,37,72};
int B[N][N]={-19,88,93,-43,32,-29,49,42,-3};

void printMatrix(int M[N][N]);

void main(){
    int C[N][N]={0};
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    printMatrix(A);
    printMatrix(B);
    printMatrix(C);
}

void printMatrix(int M[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d \t",M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}