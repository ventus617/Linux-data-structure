#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<windows.h>

typedef struct node
{
	int nValue;
	struct node* pNext;
}List, * ListN;

List** CreateHashMap(int* arr, int M) {
	if (arr == NULL || M <= 0)return NULL;
	List** HashMap = (List**)malloc(sizeof(ListN) * M);
	//指针数组的创建
	memset(HashMap, 0, sizeof(ListN) * M);

	//插入数据
	for (int i = 0; i < M; i++) {
		int key = arr[i] % M;
		ListN Node = (ListN)malloc(sizeof(List));
		Node->nValue = arr[i];
		Node->pNext = HashMap[key];
		HashMap[key] = Node;
	}
	return HashMap;

}

void FindInHash(List** list, int num, int len) {
	if (list == NULL)return;
	int Index = num % len;
	ListN Node = list[Index];
	while (Node) {
		if (Node->nValue == num) {
			printf("find it %d\n", num);
			return;
		}
		else {
			Node = Node->pNext;
		}
	}
	printf("find nothing\n");

}

int main01()
{
	int arr[] = { 1,2,3,43,5,456,44,12 };
	List** HashMap = CreateHashMap(arr, sizeof(arr) / sizeof(int));
	int len = sizeof(arr) / sizeof(int);
	FindInHash(HashMap, 1, len);
	return 0;
}