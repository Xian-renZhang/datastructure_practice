#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "SequenceStack.c"
//改进：
//1.使用单类型栈还是多类型栈
//2.如何进行多位数的运算
//3.如何引入"()"括号表达式
//目前程序采用单类型char栈，数字需要经过字符转换，降低了程序的可读性，且运算数及运算结果只能是一位数

int ExprEvaluation(char* expr);

int main()
{
    char expr[80];
    printf("Input a expression(end with #): ");
    gets_s(expr,sizeof(expr));
    printf("Its value: %d\n", ExprEvaluation(expr));
    return 0;
}

#define OPSet    "+-*/#"

int In(char c, char op[]);
char Compare(char c1, char c2);
int Execute(char a, char op, char b);

int ExprEvaluation(char* expr)
{   // 不带括号的算术表达式求值的算符优先算法
    SeqStack OPTR, OPND;
    char a, b;
    char ch, op, e;

    InitStack(&OPTR);
    InitStack(&OPND);
    Push(&OPTR, '#');
    ch = *expr++;
    GetTop(&OPTR, &e);
    while (ch != '#' || e != '#')
    {
        if (!In(ch, OPSet))
        {
            Push(&OPND, ch);  ch = *expr++;
        }
        else
            switch (Compare(ch, e))
            {
            case '>': Push(&OPTR, ch);  ch = *expr++;  break;
            case '<': Pop(&OPTR, &op);  Pop(&OPND, &b);  Pop(&OPND, &a);
                      Push(&OPND, Execute(a, op, b));  break;
            }
        GetTop(&OPTR, &e);
    }
    GetTop(&OPND, &a);
    return a;
}

int In(char c, char op[])
{   // 判断字符c是否是运算符，不是返回0，是返回非0
    // 且规定'+'返回1，'-'返回2，'*'返回3，依此类推
    int i;
    for (i = 0; i < 5; i++) {
        if (c == op[i]) {
            break;
        }
    }
    if (i < 5) {
        return ++i;
    }
    return 0;
}

char Compare(char c1, char c2)
{   // 比较运算符c1与运算符c2的优先级
    // c1高于c2返回>，c1低于c2返回<，c1等于c2返回=
    char com[][5] = {
        {'>','>','<','<','>'},
        {'>','>','<','<','>'},
        {'>','>','>','>','>'},
        {'>','>','>','>','>'},
        {'<','<','<','<','<'},
    };
    return com[In(c1, OPSet)-1][In(c2, OPSet)-1];
}

int Execute(char a, char op, char b)
{   // 对数a和b进行op运算，返回运算结果
    int result=0;
    int op1 = a - '0';
    int op2 = b - '0';
    switch (op)
    {
    case '+':
        result = op1 + op2; break;
    case '-':
        result = op1 - op2; break;
    case '*':
        result = op1 * op2; break;
    case '/':
        result = op1 / op2; break;
    }
    return result;
}
