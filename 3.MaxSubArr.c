/**
 * Implementing Maximum Subarray Problem Pseudo Code (CLRS Pg 71-72) 
 **/
#include <stdio.h>
#include <stdlib.h> // for malloc
// work out value to use as sentinel for int type, INT_MAX.
#define INT_MAX  ((1 << (sizeof(int)*8 - 2)) - 1 + (1 << (sizeof(int)*8 - 2))) 

#define N 20 // array length
int A[N]={88,5,69,-34,-44,89,14,37,72,-19,88,93,-43,32,-29,49,42,-3,-89,90};
int inf=INT_MAX; // set infinity to sentinel value 

void findMaxCrossSubArray(int* res, int* A, int low, int mid, int high);
void findMaxSubArray(int* res, int* A,int low, int high);

void main(){
    int* result=malloc((sizeof(int))*3);
    findMaxSubArray(result,A,0,N-1);
    printf("the Maximum Subarray in \n[");
    for(int i=0;i<N;i++){
        printf("%d ",A[i]);
    }
    printf("]\n\nis from index %d to %d and has a sum of %d :\n[", result[0],result[1],result[2]);
    for(int i=result[0];i<=result[1];i++){
        printf("%d ",A[i]);
    }
    printf("]");
    free(result);
}

void findMaxCrossSubArray(int* res, int* A, int low, int mid, int high){
    int maxLeft, maxRight, sum;
    int leftSum=-inf;
    sum=0;
    for (int i=mid;i>=low;i--){
        sum=sum+A[i];
        if(sum>leftSum){
            leftSum=sum;
            maxLeft=i;
        }
    }
    sum=0;
    int rightSum=-inf;
    for (int j=mid+1; j<=high; j++){
        sum=sum+A[j];
        if(sum>rightSum){
            rightSum=sum;
            maxRight=j;
        }
    }
    res[0]=maxLeft; res[1]=maxRight; res[2]=leftSum+rightSum;
    return;
}

void findMaxSubArray(int* res, int* A,int low, int high){
    if(high==low){
        res[0]=low; res[1]=high; res[2]=A[low];
    }else{
        int* result=malloc((sizeof(int))*3);
        int mid=(low+high)/2;
        findMaxSubArray(result,A,low,mid);
        int leftLow=result[0];
        int leftHigh=result[1];
        int leftSum=result[2];
        findMaxSubArray(result,A,mid+1,high);
        int rightLow=result[0];
        int rightHigh=result[1];
        int rightSum=result[2];
        findMaxCrossSubArray(result,A,low,mid,high);
        int crossLow=result[0];
        int crossHigh=result[1];
        int crossSum=result[2];

        if(leftSum>=rightSum && leftSum>=crossSum){
            res[0]=leftLow; res[1]=leftHigh; res[2]=leftSum;
        }else if(rightSum>=leftSum && rightSum>=crossSum){
            res[0]=rightLow; res[1]=rightHigh; res[2]=rightSum;
        }else{
            res[0]=crossLow; res[1]=crossHigh; res[2]=crossSum;
        }
        free(result);
    }
    return;
}