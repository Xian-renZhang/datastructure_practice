#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef int DataType;

typedef struct Node {
	DataType data;
	struct Node* LChild;
	struct Node* RChild;
}BiTNode,*BiTree;

void InitTree(BiTree *bt) {
	*bt = (BiTree)malloc(sizeof(BiTNode));
	if (*bt == NULL) {
		printf("内存分配不成功！");
		return;
	}
	(*bt)->LChild == NULL;
	(*bt)->RChild == NULL;
	return;
}

void CreatTree(BiTree bt) {
	int data=0;
	printf("请输入节点数值：(当输入-1时当前结点创建完成)\n");
	scanf("%d", &data);

	if (data == -1) {
		return;
	}
	else {		
		bt->data = data;
		BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
		printf("\n输入%d的左孩子：", data);
		CreatTree(&node);
		printf("\n输入%d的右孩子：", data);
		CreatTree(&)
	}
}