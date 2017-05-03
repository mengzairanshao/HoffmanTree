#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N sizeof(count)/sizeof(int)

int count[] = { 40,30,10,10,6,4,5,6,7,8};
enum MyEnum
{
	left=1,
	right=2
};
typedef int Count;
typedef int Element;
/**
 * 霍夫曼树的节点
 */
typedef struct HoffmanTreeNode
{
	Count conut;
	Element ele;
	char code[256];
	struct HoffmanTreeNode *lchild, *rchild;
} HoffmanTreeNode, *HoffmanTree;

/**
 * [sort 冒泡排序]
 * @param T      [森林数组]
 * @param length [最小的两位已经合并过的次数(有多少位为NULL)]
 */
void sort(HoffmanTree* T, int length)
{
	HoffmanTree tempT = NULL;
	for (int i = length; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (T[j]->conut < T[i]->conut)
			{
				tempT = T[j];
				T[j] = T[i];
				T[i] = tempT;
			}
		}
	}
}

/**
 * [Encoding 霍夫曼编码]
 * @param T   [霍夫曼树]
 * @param dir [区分左子树还是右子树,left为左子树,right为右子树]
 */
void Encoding(HoffmanTree* T,int dir)
{
	if (((*T)->lchild)==NULL && ((*T)->rchild)==NULL)
	{
		if (dir == left)
		{
			strcat_s((*T)->code, 256,"0");
		}
		else
		{
			strcat_s((*T)->code, 256, "1");
		}
	}
	else
	{
		Encoding(&(*T)->lchild, dir);
		Encoding(&(*T)->rchild, dir);
	}
}

/**
 * [createHoffmanTree 构建霍夫曼树]
 * @param  T      [森林数组]
 * @param  length [从哪一位开始合并]
 * @return        [霍夫曼树]
 */
HoffmanTree createHoffmanTree(HoffmanTree* T, int length)
{
	for (; length <=N-2; length++)
	{
		HoffmanTree tempT = NULL;
		tempT = malloc(sizeof(HoffmanTreeNode));
		sort(T, length);
		Encoding(&T[length], left);
		Encoding(&T[length+1], right);
		tempT->conut = T[length]->conut + T[length +1]->conut;
		strcpy_s(tempT->code, 256, "");
		tempT->ele = -1;
		tempT->lchild = T[length];
		tempT->rchild = T[length+1];
		T[length ] = NULL;
		T[length +1] = tempT;
	}
	return T[N-1];
}

/**
 * [TraversalPrintLeaf 遍历霍夫曼树并打印叶子节点的编码]
 * @param T [霍夫曼树]
 * @return [编码总长度]
 */
int TraversalPrintLeaf(HoffmanTree *T)
{
	static int length = 0;
	if((*T)&&(*T)->lchild==NULL&&(*T)->rchild==NULL)
	{
		printf("%d对应的编码为:", (*T)->ele);
		for(int i = strlen((*T)->code)-1;i>=0;i--)
			printf("%c", ((*T)->code)[i]);
		printf("\n");
		length += (*T)->conut * strlen((*T)->code);
	}
	else
	{
		TraversalPrintLeaf(&(*T)->lchild);
		TraversalPrintLeaf(&(*T)->rchild);
	}
	return length;
}

int main()
{
	int length=0;
	int length1=0;
	double scale=0.0;
	char code[256] = "";
	HoffmanTree T[N];
	HoffmanTree hoffmanTree = NULL;
	for (int i = 0; i < N; i++)
	{
		T[i] = malloc(sizeof(HoffmanTreeNode));
		T[i]->conut = count[i];
		T[i]->ele = i;
		strcpy_s(T[i]->code, 256, "");
		T[i]->lchild = NULL;
		T[i]->rchild = NULL;
		length1 += count[i];
	}
	hoffmanTree = createHoffmanTree(T, 0);
	length = TraversalPrintLeaf(&hoffmanTree);
	scale = (float)(length1 * 8)/(float)length ;
	printf("编码总长度为: %d\n压缩比为: %f\n",length,scale);
	return 0;
}
