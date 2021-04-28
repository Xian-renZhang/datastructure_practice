#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WEIGHT 100;

typedef struct
{
    int weight;                // 用来存放各个结点的权值
    int parent, LChild, RChild; // 指向双亲、孩子结点的指针
}HTNode, * HuffmanTree;      // 动态分配数组，存储哈夫曼树

typedef char** HuffmanCode; // 动态分配数组，存储哈夫曼编码

void select(HuffmanTree ht, int n, int* s1, int* s2)
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

void CrtHuffmanTree(HuffmanTree ht, int* w, int n)
{   // 构造哈夫曼树ht[m+1], w[]存放已知的n个权值
    int i, m, s1, s2;

    for (i = 1; i <= n; i++)   // 1~n号单元存放叶子结点，初始化
    {
        ht[i].weight = w[i];
        ht[i].parent = ht[i].LChild = ht[i].RChild = 0;
    }
    m = 2 * n - 1;
    for (i = n + 1; i <= m; i++) // n+1~m号单元存放非叶子结点，初始化
        ht[i].weight = ht[i].parent = ht[i].LChild = ht[i].RChild = 0;

    // 初始化完毕，以下创建非叶子结点，建哈夫曼树
    for (i = n + 1; i <= m; i++)
    {
        select(ht, i - 1, &s1, &s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = ht[s2].parent = i;
        ht[i].LChild = s1;  
        ht[i].RChild = s2;
    }
}

void PreOrderHuffman(HuffmanTree HT, int m)
{   // 先序遍历哈夫曼树
    if (m == 0)
        return;
    printf("%d  ", HT[m].weight);
    PreOrderHuffman(HT, HT[m].LChild);
    PreOrderHuffman(HT, HT[m].RChild);
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n)
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

int main()
{
    HuffmanTree HT;  HuffmanCode HC;
    int i, n, m;  
    int* w;

    // 输入叶子结点数及权重
    printf("Input the number of total leaves of Huffman Tree:");
    scanf("%d", &n);  
    m = 2 * n - 1;

    // 0号单元均未使用
    HT = (HTNode*)malloc((m + 1) * sizeof(HTNode));
    HC = (char**)malloc((n+1) * sizeof(char*));
    w = (int*)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++)
    {
        printf("Input the %d element's weight:", i);
        scanf("%d", &w[i]);  // 依次输入5 7 3 2 8
    }

    // 生成哈夫曼树并输出
    CrtHuffmanTree(HT, w, n);
    for (i = 1; i <= m; i++)
    {
        printf("\n%5d%5d%5d%5d", HT[i].weight, HT[i].parent, HT[i].LChild, HT[i].RChild);
    }
    printf("\n\n");

    // 先序遍历哈夫曼树
    PreOrderHuffman(HT, m);  
    printf("\n\n");

    // 生成哈夫曼编码并输出
    CrtHuffmanCode(HT, HC, n);
    for (i = 1; i <= n; i++)
    {
        printf("%d编码为%s\n", HT[i].weight, HC[i]);
    }

    getchar();  getchar();
    return 0;
}