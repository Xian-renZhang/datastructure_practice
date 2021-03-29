#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define Stack_Size 50
#define FALSE 0
#define TRUE 1

typedef char StackElemType;

typedef struct {
    StackElemType elem[Stack_Size];
    int top;
}SeqStack;

// 将S初始化为一个空栈
void InitStack(SeqStack* S)
{   
    S->top = -1;
}

// 判断栈S是否为空栈，是返回TRUE，否则返回FALSE
int IsEmpty(SeqStack* S)
{    
    if (S->top == -1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// 判断栈S是否已满，是返回TRUE，否则返回FALSE
int IsFull(SeqStack* S)
{    
    if (S->top == Stack_Size - 1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// 将数据元素x进栈S，若栈S已满，返回FALSE，否则返回TRUE
int Push(SeqStack* S, StackElemType x)
{   
    if (S->top == Stack_Size-1) {
        return FALSE;
    }
    else {
        S->top++;
        S->elem[S->top] = x;
        return TRUE;
    }
}

// 将栈S的栈顶元素出栈，通过x返回;若栈S为空，返回FALSE，否则返回TRUE
int Pop(SeqStack* S, StackElemType* x)
{   
    if (S->top == -1) {
        return FALSE;
    }
    else {
        *x = S->elem[S->top];
        S->top--;
        return TRUE;
    }
}

// 取栈S的栈顶元素，通过x返回;若栈S为空，返回FALSE，否则返回TRUE
int GetTop(SeqStack* S, StackElemType* x)
{   
    if (S->top == -1) {
        return FALSE;
    }
    else {
        *x = S->elem[S->top];
        return TRUE;
    }
}