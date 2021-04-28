#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "../../栈与队列/Queue/CircularQueue.c"

typedef int DataType;

typedef struct Node {
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}binaryTreeNode,*binaryTree;

//创建二叉树
void createTree(binaryTree* root) {
	DataType data = 0;
	printf("请输入节点数值（当输入100时当前结点创建完毕）：");
	scanf("%d", &data);

	if (data == 100) {
		*root = NULL;
	}
	else {
		*root = (binaryTreeNode*)malloc(sizeof(binaryTreeNode));
		if (*root == NULL) {
			return;
		}
		(*root)->data = data;
		printf("\n创建%d的左孩子：", data);
		createTree(&(*root)->lChild);
		printf("\n创建%d的右孩子：", data);
		createTree(&(*root)->rChild);
	}
}

//销毁二叉树
void destoryTree(binaryTree root) {
	if (root == NULL) {
		return;
	}
	destoryTree(root->lChild);
	destoryTree(root->rChild);
	free(root);
}

//先序遍历
void preOrder(binaryTree root) {
	if (root == NULL) {
		return;
	}
	printf("%d ", root->data);
	preOrder(root->lChild);
	preOrder(root->rChild);
}

//中序遍历
void inOrder(binaryTree root) {
	if (root == NULL) {
		return;
	}
	inOrder(root->lChild);
	printf("%d ", root->data);
	inOrder(root->rChild);
}

//后序遍历
void postOrder(binaryTree root) {
	if (root == NULL) {
		return;
	}
	postOrder(root->lChild);
	postOrder(root->rChild);
	printf("%d ", root->data);
}

//层次遍历
void levelOrder(binaryTree root) {
	seqQueue queue;
	binaryTreeNode* node = NULL;	//队中存放节点指针

	initQueue(&queue);	
	if (root == NULL) {
		return;
	}

	enterQueue(&queue, root);	//根节点入队
	while (!isEmpty(&queue)) {
		deleteQueue(&queue, &node);
		printf("%d ", node->data);

		if (node->lChild != NULL) {
			enterQueue(&queue, node->lChild);
		}
		if (node->rChild != NULL) {
			enterQueue(&queue, node->rChild);
		}
	}
}

//打印叶子节点
void printLeaf(binaryTree root) {
	if (root == NULL) {
		return;
	}
	if ((root->lChild == NULL) && (root->rChild == NULL)) {
		printf("%d ", root->data);
	}
	else {
		printLeaf(root->lChild);
		printLeaf(root->rChild);
	}
}

//打印叶子个数
int getLeafNum(binaryTree root) {
	if (root == NULL) {
		return 0;
	}
	if ((root->lChild == NULL) && (root->rChild == NULL)) {
		return 1;
	}
	return getLeafNum(root->lChild) + getLeafNum(root->rChild);
}
//打印树的高度
int getHeight(binaryTree root) {
	int lHeight=0,rHeight = 0;	//左右子树的高度

	if (root == NULL) {
		return 0;
	}
	if ((root->lChild == NULL) && (root->rChild == NULL)) {	//叶子节点高度为0
		return 0;
	}

	lHeight = getHeight(root->lChild);
	rHeight = getHeight(root->rChild);

	return((lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1));
}

int main() {
	binaryTree root = NULL;
	
	printf("创建二叉树：\n");
	createTree(&root);
	printf("\n先序遍历二叉树：");
	preOrder(root);
	printf("\n中序遍历二叉树：");
	inOrder(root);
	printf("\n后序遍历二叉树：");
	postOrder(root);
	printf("\n层次遍历二叉树：");
	levelOrder(root);
	printf("\n打印二叉树叶子节点：");
	printLeaf(root);
	printf("\n打印二叉树叶子节点个数：%d", getLeafNum(root));
	printf("\n打印二叉树高度：%d", getHeight(root));

	destoryTree(root);

	return 0;
}