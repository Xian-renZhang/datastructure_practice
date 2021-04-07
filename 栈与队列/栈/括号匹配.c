#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include "顺序栈.c"

int BracketMatch(char* str);

int main()
{
    char str[100];

    printf("Please input a string:");  
    gets_s(str);
    switch (BracketMatch(str))
    {
    case 0:
        printf("\n括号匹配！");
        break;
    case 1:
        printf("\n左括号多余！");
        break;
    case 2:
        printf("\n右括号多余！");
        break;
    case 3:
        printf("\n左右括号不匹配！");
        break;
    }
    getchar();  getchar();
    return 0;
}

// 判断左括号ch1和右ch2是否匹配，匹配返回TRUE，否则返回FALSE
int Match(char ch1, char ch2)
{   
    switch (ch1) 
    {
    case '(':
        if (ch2 == ')')
            return 1;
        break;
    case '[':
        if (ch2 == ']')
            return 1;
        break;
    case '{':
        if (ch2 == '}')
            return 1;
    }
    return 0;
}

int BracketMatch(char* str)
{   // str[]中为输入的字符串，利用堆栈技术来检查该字符串中的括号是否匹配
    SeqStack S;  int i;  char ch;

    InitStack(&S);
    for (i = 0; str[i] != '\0'; i++)   // 对字符串中的字符逐一扫描
    {
        switch (str[i])
        {
        case '(':
        case '[':
        case '{': 
            Push(&S, str[i]);  
            break;
        case ')':
        case ']':
        case '}': 
            if (IsEmpty(&S)) {
                return 2;
            }
            else {
                GetTop(&S, &ch);
                if (Match(ch, str[i]))    // 用Match判断两个括号是否匹配
                    Pop(&S, &ch);         // 已匹配的左括号出栈
                else  
                    return 3;
            }
        }
    }
    return (IsEmpty(&S) ? 0 : 1);
}