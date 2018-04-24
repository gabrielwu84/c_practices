/**
 * Implementing Insertion Sort Pseudo Code (CLRS Pg 18) 
 **/

#include <stdio.h>
#define N 10 // array length
int x[N]={3,2,6,2,1,3,123,5,2,75};

void main(){
    // initial array
    printf("before: ");
    for(int i=0;i<N;i++){
        printf("%d ",x[i]);
    }
    printf("\n\n");

    // insertion sort
    for(int j=1;j<N;j++){
        int x_j=x[j];
        int i=j-1;
        while(i>=0 && x[i]>x_j){
            x[i+1]=x[i];
            i=i-1;
            x[i+1]=x_j;
        }
    }
    // final array
    printf("after: ");
    for(int i=0;i<N;i++){
        printf("%d ",x[i]);
    }
    printf("\n\n");
}