#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define OK 1;
#define ERROR 0;

//使用前请设置ElemType及相应的输入输出函数
typedef int ElemType;

typedef struct SeqList {
	ElemType* elem;
	int last;
}SeqList;

//初始化顺序表
void InitList(SeqList* L) {
	L->elem = (ElemType*)malloc(sizeof(ElemType));
	if (!L->elem) {
		printf("内存分配不成功！\n");
		exit(-1);
	}
	L->last = -1;
}

//创建顺序表
int CreateList(SeqList* L) {
	int length, i;
	printf("请输入顺序表的长度：\n");
	scanf("%d", &length);
	L->elem = (ElemType*)malloc(length * sizeof(ElemType));
	if (NULL == L->elem) {
		printf("内存分配不成功！\n");
		exit(-1);
	}
	L->last = length-1;
	printf("请输入顺序表的初始元素：\n");
	for (i = 0; i < length; i++) {
		scanf("%d", &L->elem[i]);
	}
	printf("创建成功!\n");
	return OK;
}

//输出顺序表
void PrintList(SeqList *L) {
	int i;
	printf("输出顺序表：\n");
	for (i = 0; i <= L->last; i++) {
			printf("%d ", L->elem[i]);
	}
		printf("\n");
}

//顺序表的插入运算，将新元素插入到i位置
int InsList(SeqList* L, int i, ElemType e) {
	ElemType* newpointer=NULL;
	if ((i < 1) || (i > L->last + 2)) {
		printf("插入位置不合法");
		return ERROR;
	} 
	newpointer = (ElemType*)realloc(L->elem, (L->last + 2) * sizeof(ElemType));
	if (newpointer==NULL) {
		printf("继续分配内存空间失败！");
		return ERROR;
	}
	else {
		L->elem = newpointer;
	}
	int j;
	for (j = L->last; j >= i - 1; j--) {
		L->elem[j+1] = L->elem[j];
	}
	L->elem[i] = e;
	L->last++;
	return OK;
}

//删除顺序表中第i个数据元素，并用e返回其值
int DelList(SeqList* L, int i, ElemType* e) {
	if (i<1 || i>L->last + 1) {
		printf("删除位置不合理！\n");
		return ERROR;
	}

	*e = L->elem[i - 1];
	for (int k = i; k <= L->last; k++) {
		L->elem[k - 1] = L->elem[k];
	}
	//可以通过realloc释放末尾的内存空间
	L->last--;
	return OK;
}

//顺序表的按内容查找，返回该元素在表中的序号
int Locate(SeqList* L, ElemType e) {
	int i = 0;
	while (i <= L->last && (L->elem[i] != e)) {
		i++;
	}
	if (i <= L->last) {
		return (i + 1);
	}
	else {
		return ERROR;
	}
}

//判断顺序表是否为空
int ListEmpty(SeqList *L) {
	if (L->last == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

//置空顺序表
void ClearList(SeqList* L) {
	L->last = -1;
}

//销毁顺序表
void DestroyList(SeqList* L) {
	free(L->elem);
	L->elem = NULL;
	L->last = -1;
}

//顺序表的合并,将所有在线性表Lb中但不在La中的数据元素插入到La中
int UnionList(SeqList* La, SeqList* Lb) {
	int i;
	for (i = 0; i <= Lb->last; i++) {
		ElemType e = Lb->elem[i];

		int k = 0;
		int flag = 0;
		while (k <= La->last && (La->elem[k] != e)) {
			k++;
		}
		if (k <= La->last) {
			flag = 1;
		}

		if (!flag) {
			ElemType* newpointer = NULL;
			newpointer = (ElemType*)realloc(La->elem, (La->last + 2) * sizeof(ElemType));
			if (newpointer == NULL) {
				printf("继续分配内存空间失败！");
				exit(-1);
			}
			else {
				La->elem = newpointer;
			}
			int j = (La->last + 1);
			La->elem[j] = e;
			La->last++;
		}
	}
	return OK;
}

//删除非递减有序顺序表中的重复元素
int DelSameX(SeqList* L) {
	int i, j;
	if (L->last <= 1) {
		return OK;
	}
	for (i = 1, j = 1; i <= L->last; i++) {
		if (L->elem[i] != L->elem[i - 1]) {
			L->elem[j++] = L->elem[i];
		}
	}
	L->last = j - 1;
	return OK;
}