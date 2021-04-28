#include<stdio.h>
#define MAXSIZE 50
#define TRUE 1
#define FALSE 0

typedef int* ElemType;

typedef struct {
	ElemType elem[MAXSIZE];
	int front;
	int rear;
}seqQueue;

//初始化队列
void initQueue(seqQueue* queue) {
	queue->front = 0;
	queue->rear = 0;
}

//判断队列是否为空
int isEmpty(seqQueue* queue) {
	if (queue->front == queue->rear) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//判断队列是否已满
int isFull(seqQueue* queue) {
	if ((queue->rear + 1) % MAXSIZE == queue->front) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//在队列的队尾插入x
int enterQueue(seqQueue* queue, ElemType x) {
	if ((queue->rear + 1) % MAXSIZE == queue->front) {
		return FALSE;
	}
	queue->elem[queue->rear] = x;
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return TRUE;
}

//将队列的队头元素出队，并用x返回其值
int deleteQueue(seqQueue* queue, ElemType* x) {
	if (queue->front == queue->rear) {
		return FALSE;
	}
	*x = queue->elem[queue->front];
	queue->front = (queue->front + 1) % MAXSIZE;
	return TRUE;
}

//取队列的队头元素
int getHead(seqQueue* queue, ElemType* x) {
	if (queue->front == queue->rear) {
		return FALSE;
	}
	*x = queue->elem[queue->front];
	return TRUE;
}

//将队列置为空队列
int clearQueue(seqQueue* queue) {
	queue->front = queue->rear = 0;
	return TRUE;
}

//返回队列元素个数
int queueLength(seqQueue* queue) {
	if (queue->front == queue->rear) {
		return FALSE;
	}
	return (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

//打印队列
int printQueue(seqQueue* queue) {
	if (queue->front == queue->rear) {
		return FALSE;
	}
	for (int i = queue->front; i != queue->rear; i = (i + 1) % MAXSIZE) {
		printf("&d ", queue->elem[i]);
	}
	return TRUE;
}