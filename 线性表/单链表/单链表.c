#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define TRUE          1
#define FALSE         0
#define OK            1
#define ERROR         0
//使用前请设置ElemType及相应的输入输出函数
typedef char ElemType;

typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, * LinkList;

//初始化带头结点单链表
void InitList(LinkList* L) {
	*L = (LinkList)malloc(sizeof(Node));
	if (NULL == *L) {
		printf("内存分配不成功！\n");
		exit(ERROR);
	}
	//将头结点的next指针设为空指针
	(*L)->next = NULL;
}

//尾插法建立单链表,当输入$时，建表结束
void CreateFromTail(LinkList L) {
	Node* r, * s;
	char c;
	r = L;
	while ((c = getchar())!='$') {
		s = (Node*)malloc(sizeof(Node));
		if (NULL == s) {
				printf("内存分配不成功！\n");
				exit(-1);
		}
		else {
			s->data = c;
			r ->next = s;
			r = s;
		}
	}
	r->next = NULL;
}

//单链表的输出
void PrintList(LinkList L) {
	Node* p;
	p = L->next;
	while (p != NULL) {
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}

//求单链表的长度
int ListLength(LinkList L) {
	Node* p;
	int j = 0;
	p = L->next;
	while (p != NULL) {
		j++;
		p = p->next;
	}
	return j;
}

//在单链表中查找第i个结点
Node* Get(LinkList L, int i) {
	Node* p;
	int j = 0;
	if (i < 1) {
		return NULL;
	}
	p = L->next;
	//p->next==null:p指向最后一个结点
	//p==null:p指向最后一个结点的next部分所放的空指针
	while (p != NULL) {
		j++;
		if (i == j) {
			break;
		}
		p = p->next;
	}
	//查找超过链表范围后返回空值
	return p;
}

// 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
int GetData(LinkList L, int i, ElemType* e) {   
	Node* p;
	if (!(p = Get(L, i))) {
		return ERROR;
	}
	*e = p->data;
	return OK;
}

//在带头结点的单链表中第i个位置插入值为e的新值
int InsList(LinkList L, ElemType e, int i) {
	Node* pre, * s;
	if (i < 1) {
		return ERROR;
	}
	pre = ((i == 1) ? L : Get(L, i - 1));
	if (pre == NULL) {
		printf("插入位置不合理！");
		return ERROR;
	}
	s = (Node*)malloc(sizeof(Node));
	if (NULL == s) {
		printf("内存分配不成功！\n");
		exit(ERROR);
	}
	else {
		s->data = e;
	}
	s->next = pre->next;
	pre->next = s;
	return OK;
}

//在带头结点的单链表中删除第i个元素，并将删除的元素保存到变量*e中
int DelList(LinkList L, int i, ElemType* e) {
	Node* pre, * r;
	if (i < 1) {
		return ERROR;
	}
	pre = ((i == 1) ? L : Get(L, i - 1));
	if (pre == NULL || pre->next == NULL) {
		printf("被删结点的位置不合理！");
		return ERROR;
	}
	r = pre->next;
	pre->next = r->next;
	*e = r->data;
	free(r);
	return OK;
}

//在单链表中查找值为key的结点
Node* Locate(LinkList L, ElemType key) {
	Node* p;
	p = L->next;
	while (p != NULL) {
		if (p->data == key) {
			break;
		}
		p = p->next;
	}
	return p;
}

//判断单链表是否为空
int ListEmpty(LinkList L) {
	if (L->next == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//清空单链表
int ClearList(LinkList L) {
	Node* p, * q;
	p = L->next;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}

//销毁单链表
int DestroyList(LinkList *L) {
	Node* p;
	while (*L != NULL) {
		p = (*L)->next;
		free(*L);
		*L = p;
	}
}