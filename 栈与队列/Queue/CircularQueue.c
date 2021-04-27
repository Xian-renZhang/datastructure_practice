#include<stdio.h>
#define MAXSIZE 50
#define TRUE 1
#define FALSE 0

typedef int ElemType;

typedef struct {
	ElemType elem[MAXSIZE];
	int front;
	int rear;
}SeqQueue;

//初始化队列Q
int InitQueue(SeqQueue* Q) {
	Q->front = 0;
	Q->rear = 0;
	
	return  TRUE;
}

//判断队列是否为空
int IsEmpty(SeqQueue* Q) {
	if (Q->front == Q->rear) {
		return TRUE;
	}
	return FALSE;
}

//判断队列是否已满
int IsFull(SeqQueue* Q) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {
		return TRUE;
	}
	return FALSE;
}

//在队列的队尾插入x
int EnterQueue(SeqQueue* Q, ElemType x) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {
		return FALSE;
	}
	Q->elem[Q->rear] = x;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return TRUE;
}

//将队列的队头元素出队，并用x返回其值
int DeleteQueue(SeqQueue* Q, ElemType* x) {
	if (Q->front == Q->rear) {
		return FALSE;
	}
	*x = Q->elem[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return TRUE;
}

//取队列的队头元素
int GetHead(SeqQueue* Q, ElemType* x) {
	if (Q->front == Q->rear) {
		return FALSE;
	}
	*x = Q->elem[Q->front];
	return TRUE;
}

//将队列置为空队列
int Clear(SeqQueue* Q) {
	Q->front = Q->rear = 0;
	return TRUE;
}

//返回队列元素个数
int QueueLength(SeqQueue* Q) {
	if (Q->front == Q->rear) {
		return FALSE;
	}
	return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//打印队列
int PrintQueue(SeqQueue* Q) {
	if (Q->front == Q->rear) {
		return FALSE;
	}
	for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
		printf("&d ", Q->elem[i]);
	}
	return TRUE;
}