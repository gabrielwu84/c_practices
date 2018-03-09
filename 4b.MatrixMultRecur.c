#include <stdio.h>
#include <stdlib.h> // for malloc

#define N_0 5 // matrix size
// int A_0[1][1]={9};
// int B_0[1][1]={9};
// int A_0[3][3]={88,5,69,-34,-44,89,14,37,72};
// int B_0[3][3]={-19,88,93,-43,32,-29,49,42,-3};
int A_0[5][5]={80, 43, 49, 67, 12, 86, 52, 56, 14, 81, 31, 96, 17, 36, 33, 58, 2, 54, 29, 89, 41, 19, 77, 21, 92};
int B_0[5][5]={1, 21, 12, 85, 36, 31, 8, 7, 80, 95, 20, 76, 43, 71, 55, 53, 72, 93, 87, 24, 79, 27, 90, 97, 92};

int smallestPowerOf2(unsigned int n);
int** sumMatrices(int** M1,int** M2, int N);
int** squareMatMultRecur(int Ai,int Aj,int Bi,int Bj,int n);

void main(){
    int** C=squareMatMultRecur(0,0,0,0,smallestPowerOf2(N_0));
    // print result
    for(int i=0;i<N_0;i++){
        for(int j=0;j<N_0;j++){
            printf("%d \t",C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** squareMatMultRecur(int Ai,int Aj,int Bi,int Bj,int N){
    // assumes N is a power of 2. 
    int** C=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        C[i]=malloc(N*sizeof(int));
    }
    if(N==1){
        if(Ai<N_0 && Aj<N_0 && Bi<N_0 && Bj<N_0){
            C[0][0]=A_0[Ai][Aj]*B_0[Bi][Bj];
        } else { // occurs when N_0 is not a power of 2. 
            C[0][0]=0; 
        }
    }else{
        int N2=N/2;
        int **C11,**C12,**C21,**C22;
        int **C11a,**C11b,**C12a,**C12b,**C21a,**C21b,**C22a,**C22b;

        C11a=squareMatMultRecur(Ai,Aj,Bi,Bj,N2);
        C11b=squareMatMultRecur(Ai,Aj+N2,Bi+N2,Bj,N2);
        C12a=squareMatMultRecur(Ai,Aj,Bi,Bj+N2,N2);
        C12b=squareMatMultRecur(Ai,Aj+N2,Bi+N2,Bj+N2,N2);
        C21a=squareMatMultRecur(Ai+N2,Aj,Bi,Bj,N2);
        C21b=squareMatMultRecur(Ai+N2,Aj+N2,Bi+N2,Bj,N2);
        C22a=squareMatMultRecur(Ai+N2,Aj,Bi,Bj+N2,N2);
        C22b=squareMatMultRecur(Ai+N2,Aj+N2,Bi+N2,Bj+N2,N2);

        C11=sumMatrices(C11a,C11b,N2);
        C12=sumMatrices(C12a,C12b,N2);
        C21=sumMatrices(C21a,C21b,N2);
        C22=sumMatrices(C22a,C22b,N2);

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

int** sumMatrices(int** M1,int** M2, int N){
    int** M=malloc(N*sizeof(int*));
    for(int i=0;i<N;i++){
        M[i]=malloc(N*sizeof(int));
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            M[i][j]=M1[i][j]+M2[i][j];
        }
    }
    return M;
}