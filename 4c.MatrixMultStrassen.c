/**
 * Added Strassen's Algorithm to Square Matrix Multiply Recurrsive (CLRS Pg 80-12) 
 **/
#include <stdio.h>
#include <stdlib.h>

#define N_0 5
// int A_0[2][2]={80, 43, 49, 67};
// int B_0[2][2]={1, 21, 12, 85};
int A_0[5][5]={80, 43, 49, 67, 12, 86, 52, 56, 14, 81, 31, 96, 17, 36, 33, 58, 2, 54, 29, 89, 41, 19, 77, 21, 92};
int B_0[5][5]={1, 21, 12, 85, 36, 31, 8, 7, 80, 95, 20, 76, 43, 71, 55, 53, 72, 93, 87, 24, 79, 27, 90, 97, 92};

int smallestPowerOf2(unsigned int n);
int** arrayToPointer(int A[N_0][N_0],int N);
int** splitMatrix(int **A,int startI,int startJ,int N);
int** sumMatrices(int **A,int **B, int N);
int** subMatrices(int **A,int **B,int N);
int** squareMatrixMult(int **A,int **B, int N);

void main(){
    int N = smallestPowerOf2(N_0);
    int** A=arrayToPointer(A_0,N);
    int** B=arrayToPointer(B_0,N);
    int** C=squareMatrixMult(A,B,N);
    // print result
    for(int i=0;i<N_0;i++){
        for(int j=0;j<N_0;j++){
            printf("%d \t",C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** squareMatrixMult(int **A,int **B, int N){
    // assume A and B are square matrices of sides N,
    // and N is a power of 2. 
    int **C=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        C[i]=malloc(N*sizeof(int));
    }
    if(N==1){
        C[0][0]=A[0][0]*B[0][0];
    }else{
        int N2=N/2;
        int **A11,**A12,**A21,**A22;
        int **B11,**B12,**B21,**B22;
        int **C11,**C12,**C21,**C22;
        int **S1,**S2,**S3,**S4,**S5,**S6,**S7,**S8,**S9,**S10;
        int **P1,**P2,**P3,**P4,**P5,**P6,**P7;
        
        A11=splitMatrix(A,0,0,N2);
        A12=splitMatrix(A,0,N2,N2);
        A21=splitMatrix(A,N2,0,N2);
        A22=splitMatrix(A,N2,N2,N2);
        B11=splitMatrix(B,0,0,N2);
        B12=splitMatrix(B,0,N2,N2);
        B21=splitMatrix(B,N2,0,N2);
        B22=splitMatrix(B,N2,N2,N2);

        S1=subMatrices(B12,B22,N2);
        S2=sumMatrices(A11,A12,N2);
        S3=sumMatrices(A21,A22,N2);
        S4=subMatrices(B21,B11,N2);
        S5=sumMatrices(A11,A22,N2);
        S6=sumMatrices(B11,B22,N2);
        S7=subMatrices(A12,A22,N2);
        S8=sumMatrices(B21,B22,N2);
        S9=subMatrices(A11,A21,N2);
        S10=sumMatrices(B11,B12,N2);
        
        P1=squareMatrixMult(A11,S1,N2);
        P2=squareMatrixMult(S2,B22,N2);
        P3=squareMatrixMult(S3,B11,N2);
        P4=squareMatrixMult(A22,S4,N2);
        P5=squareMatrixMult(S5,S6,N2);
        P6=squareMatrixMult(S7,S8,N2);
        P7=squareMatrixMult(S9,S10,N2);
        
        C11=sumMatrices(P4,P5,N2);
        C11=sumMatrices(C11,P6,N2);
        C11=subMatrices(C11,P2,N2);
        C12=sumMatrices(P1,P2,N2);
        C21=sumMatrices(P3,P4,N2);
        C22=sumMatrices(P1,P5,N2);
        C22=subMatrices(C22,P3,N2);
        C22=subMatrices(C22,P7,N2);

        for(int i=0;i<N2;i++){
            for(int j=0;j<N2;j++){
                C[i][j]=C11[i][j];
            }
        }
        for(int i=0;i<N2;i++){
            for(int j=N2;j<N;j++){
                C[i][j]=C12[i][j-N2];
            }
        }
        for(int i=N2;i<N;i++){
            for(int j=0;j<N2;j++){
                C[i][j]=C21[i-N2][j];
            }
        }
        for(int i=N2;i<N;i++){
            for(int j=N2;j<N;j++){
                C[i][j]=C22[i-N2][j-N2];
            }
        }
    }
    return C;
}


int smallestPowerOf2(unsigned int n){
    int p=1;
    while(p<n){
        p<<=1;
    }
    return p;
}

int** arrayToPointer(int A[N_0][N_0],int N){
    int **M = malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        M[i]=malloc(N*sizeof(int));
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i<N_0 && j<N_0){
                M[i][j]=A[i][j];
            }else{
                M[i][j]=0;
            }
        }
    }
    return M;
}

int** splitMatrix(int **A,int startI,int startJ,int N){
    int **newA=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        newA[i]=malloc(N*sizeof(int));
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            newA[i][j]=A[i+startI][j+startJ];
        }
    }
    return newA;
}

int** sumMatrices(int **A,int **B,int N){
    int **C=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        C[i]=malloc(N*sizeof(int));
    }
     for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
int** subMatrices(int **A,int **B,int N){
    int **C=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        C[i]=malloc(N*sizeof(int));
    }
     for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}