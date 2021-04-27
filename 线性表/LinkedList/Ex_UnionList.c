#include<stdio.h>
#include "LinkedList.c"

// 将所有在线性表Lb中但不在La中的数据元素插入到La中
int Union(LinkList La, LinkList Lb) {   
    int La_Len, Lb_Len, i;  ElemType e;

    La_Len = ListLength(La);
    Lb_Len = ListLength(Lb);
    for (i = 1; i <= Lb_Len; i++) {
        GetData(Lb, i, &e);       // 取Lb中第i个数据元素赋给e
        if (!Locate(La, e))       // La中不存在和e相同的数据元素
            if (!InsList(La, e, ++La_Len))    // 插入
                return ERROR;
    }
    return OK;
}

int main() {
    LinkList A, B;

    printf("Union\nInput elements of SET A ( END with $) :\n");
    InitList(&A);  CreateFromTail(A);
    printf("Input elements of SET B ( END with $) :\n");
    InitList(&B);  CreateFromTail(B);
    printf("SET A : ");  PrintList(A);
    printf("SET B : ");  PrintList(B);
    Union(A, B);
    printf("After A = A U B , SET A : ");  PrintList(A);
    getchar();  getchar();
    return 0;
}