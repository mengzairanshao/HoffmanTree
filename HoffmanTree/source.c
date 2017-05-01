#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 6
enum MyEnum
{
	left=1,
	right=2
};
typedef int Count;
typedef int Element;

typedef struct HoffmanTreeNode
{
	Count conut;
	Element ele;
	char code[256];
	struct HoffmanTreeNode *lchild, *rchild;
} HoffmanTreeNode, *HoffmanTree;

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

void TraversalPrintLeaf(HoffmanTree *T)
{
	if((*T)->lchild==NULL&&(*T)->rchild==NULL)
	{
		printf("%d对应的编码为:%s\n", (*T)->ele,(*T)->code);
	}
	else
	{
		TraversalPrintLeaf(&(*T)->lchild);
		TraversalPrintLeaf(&(*T)->rchild);
	}
}

int main()
{
	char code[256] = "";
	HoffmanTree T[N];
	HoffmanTree hoffmanTree = NULL;
	int count[] = {40,30,10,10,6,4 };
	for (int i = 0; i < N; i++)
	{
		T[i] = malloc(sizeof(HoffmanTreeNode));
		T[i]->conut = count[i];
		T[i]->ele = i;
		strcpy_s(T[i]->code, 256, "");
		T[i]->lchild = NULL;
		T[i]->rchild = NULL;
	}
	hoffmanTree = createHoffmanTree(T, 0);
	TraversalPrintLeaf(&hoffmanTree);
	return 0;
}
