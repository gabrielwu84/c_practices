/*
 * Queue Data Structure (CLRS pg 235)
 */
#include <stdio.h>
#include <stdlib.h> // for malloc

int head;
int tail;
int* Q;
int qSize=0;
int isEmpty=1;

void enqueue(int x);
int dequeue();

void main(){
    // initialize
    Q=(int *)malloc(2*sizeof(int));
    head=1;tail=0;
    qSize=2;
    // test
    printf("enqueue(1) \n");
    enqueue(1);
    printf("enqueue(2) \n");
    enqueue(2);
    printf("enqueue(3) \n");
    enqueue(3);
    printf("enqueue(4) \n");
    enqueue(4);
    printf("enqueue(5) \n");
    enqueue(5);
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("enqueue(6) \n");
    enqueue(6);
    printf("enqueue(7) \n");
    enqueue(7);
    printf("enqueue(8) \n");
    enqueue(8);
    printf("enqueue(9) \n");
    enqueue(9);
    printf("enqueue(10) \n");
    enqueue(10);
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
    printf("dequeue: %d \n",dequeue());
}

void enqueue(int x){
    isEmpty=0;
    Q[tail]=x;
    if(tail==qSize-1){
        tail=0;
    }else{
        tail++;
    }
    // check overflow
    if(tail==head){
        int qSize1=2*qSize;
        int* Q1=(int *)malloc(qSize1*sizeof(int));
        int j=0;
        for(int i=head;i<qSize-1;i++){
            Q1[j]=Q[i];
            j++;
        }
        for(int i=0;i<head;i++){
            Q1[j]=Q[i];
            j++;
        }
        head=qSize1-1;tail=qSize-1;
        free(Q);
        Q=Q1;
        qSize=qSize1;
    }
}
int dequeue(){
    if(isEmpty==1){
        printf("underflow ");
        return 0;
    }else{
        if(head==qSize-1){
            head=0;
        }else{
            head++;
        }
        int x=Q[head];
        if(head+1==tail){
            isEmpty=1;
        }
        return x;
    }
}