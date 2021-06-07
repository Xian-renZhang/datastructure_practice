#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WEIGHT 100;
#define STR 10;

typedef struct
{
    char data;
    int weight;                // 用来存放各个结点的权值
    int parent, LChild, RChild; // 指向双亲、孩子结点的指针
}treeNode, * huffmanTree;      // 动态分配数组，存储哈夫曼树

typedef char** huffmanCode; // 动态分配数组，存储哈夫曼编码

void selectMin(huffmanTree ht, int n, int* s1, int* s2)
{   // 在ht[1]~ht[n]范围内选择两个parent为0且weight最小的结点，其序号分别赋值给s1、s2
    int i,node1,node2;
    int min = MAX_WEIGHT;
    for (i = 1; i <= n; i++)
    {
        if ((ht[i].parent == 0)&&(ht[i].weight<min)) 
        {
            min = ht[i].weight;
            node1 = i;
        }
    }
    min = MAX_WEIGHT;
    for (i = 1; i <= n; i++)
    {
        if (i == node1)
        {
            continue;
        }
        if ((ht[i].parent == 0) && (ht[i].weight < min))
        {
            min = ht[i].weight;
            node2 = i;
        }
    }
    *s1 = node1;
    *s2 = node2;
}

void createHuffmanTree(huffmanTree ht, int weight[], int n)
{   int i, j, m, s1, s2;

    for (i = 0,j = 1; i < 128; i++)   // 1~n号单元存放叶子结点，初始化
    {
        if (weight[i] != 0) 
        {
            ht[j].data = i;
            ht[j].weight = weight[i];
            ht[j].parent = ht[j].LChild = ht[j].RChild = 0;
            j++;
        }
    }
    m = 2 * n - 1;
    for (i = n + 1; i <= m; i++) // n+1~m号单元存放非叶子结点，初始化
        ht[i].weight = ht[i].parent = ht[i].LChild = ht[i].RChild = 0;

    // 初始化完毕，以下创建非叶子结点，建哈夫曼树
    for (i = n + 1; i <= m; i++)
    {
        selectMin(ht, i - 1, &s1, &s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = ht[s2].parent = i;
        ht[i].LChild = s1;  
        ht[i].RChild = s2;
    }
}

void preOrder(huffmanTree HT, int m)
{   // 先序遍历哈夫曼树
    if (m == 0)
        return;
    printf("%d  ", HT[m].weight);
    preOrder(HT, HT[m].LChild);
    preOrder(HT, HT[m].RChild);
}

void createHuffmanCode(huffmanTree ht, huffmanCode hc, int n)
{   // 从叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码
    char* cd;
    int i, start, p, c;

    cd = (char*)malloc(n * sizeof(char));  // 分配求当前编码的工作空间
    if (cd == NULL)
        return;
    cd[n - 1] = '\0';         // 从右向左逐位存放编码，首先存放编码结束符
    for (i = 1; i <= n; i++)  // 求n个叶子结点对应的哈夫曼编码
    {
        start = n - 1;        // 初始化编码起始指针
        for (c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent) // 从叶子到根结点求编码
            cd[--start] = ((ht[p].LChild == c) ? '0' : '1'); // 左分支标0，右分支标1
        hc[i] = (char*)malloc((n - start) * sizeof(char));      // 为第i个编码分配空间
        strcpy(hc[i], &cd[start]);
    }
    free(cd);
}

void countFrequency(char string[], int weight[],int *n)
{
    int i;
    for ( i = 0; i < strlen(string); i++)
    {
        weight[string[i]]++;
    }
    for (i = 0; i < 128; i++)
    {
        if (weight[i] != 0)
        {
            (*n)++;
        }
    }
}

void decode(huffmanTree ht, huffmanCode hc, char string[],int n)
{
    char* c;
    int i, j, k = 0;
    c = (char*)malloc(strlen(string) * sizeof(char));
    for (i = 0; i < strlen(string); i++,k++)
    {
        c[k] = string[i];
        c[k + 1] = '\0';
        for (j = 1; j <= n; j++)
        {
            if (strcmp(c, hc[j]) == 0)
            {
                printf("%c", ht[j].data);
                k = -1;
                c[0] = '\0';
                break;
            }
        }
    }
}

int main()
{
    huffmanTree HT;  
    huffmanCode HC;
    int i, n=0, m;  
    char string[10];
    int weight[128] = {0};

    printf("请输入要编码的字符串：");
    gets(string);

    countFrequency(string, weight, &n);
    m = 2 * n - 1;

    // 0号单元均未使用
    HT = (treeNode*)malloc((m + 1) * sizeof(treeNode));
    HC = (char**)malloc((n+1) * sizeof(char*));

    // 生成哈夫曼树并输出
    createHuffmanTree(HT, weight, n);
    for (i = 1; i <= m; i++)
    {
        printf("\n%5d%5d%5d%5d", HT[i].weight, HT[i].parent, HT[i].LChild, HT[i].RChild);
    }
    printf("\n\n");

    // 先序遍历哈夫曼树
    preOrder(HT, m);  
    printf("\n\n");

    // 生成哈夫曼编码并输出
    createHuffmanCode(HT, HC, n);
    for (i = 1; i <= n; i++)
    {
        printf("%c编码为%s\n", HT[i].data, HC[i]);
    }

    printf("请输入要解码的字符串：");
    gets(string);
    decode(HT, HC, string, n);

    return 0;
}