#include<stdio.h>
#include<stdlib.h>
#include<iostream>

typedef struct node
{
	int nValue;
	struct node* pNext;
}List;

List* CreateList()
{
	int len;
	printf("请输入链表长度:\n");
	scanf("%d", &len);

	List* pHead = NULL;
	List* pTail = NULL;

	List* pTemp = NULL;

	int num;
	while (len != 0)
	{
		printf("请输入链表数值:\n");
		scanf("%d", &num);

		pTemp = (List*)malloc(sizeof(List));
		pTemp->nValue = num;
		pTemp->pNext = NULL;

		//尾添加
		if (pHead == NULL)
		{
			pHead = pTemp;
		}
		else
		{
			pTail->pNext = pTemp;
		}
		pTail = pTemp;
		len--;
	}

	return pHead;
}

void Print(List* pHead)
{
	while (pHead)
	{
		printf("%d ", pHead->nValue);
		pHead = pHead->pNext;
	}
	printf("\n");
}

void ReverePrint(List* pHead)
{
	if (pHead == NULL)return;

	//处理下一个节点
	ReverePrint(pHead->pNext);

	//打印当前节点
	printf("%d ", pHead->nValue);
}
//三指针法，在不重新创建新链表的基础上的头插法
List* ReveseList(List* pHead)
{

	if (pHead == NULL||pHead->pNext==NULL)
		return NULL;
	List* New = NULL;
	List* Node = pHead;
	List* Original = pHead->pNext;
	while (Original->pNext != NULL) {
		//老链表头指向新链表头
		Node->pNext = New;
		//更新 新链表头的标记
		New = Node;
		//更新 旧链表头的标记
		Node = Original;
		//更新 旧的旧链表头的标记
		Original = Original->pNext;
	}
	Node->pNext = New;
	return Node;
}
List* ReveseList1(List*pHead)
{

	if (pHead== NULL||pHead->pNext == NULL)
		return NULL;
	List* New = (List*)malloc(sizeof(List));
	List* Node = (List*)malloc(sizeof(List));
	List* Original = (List*)malloc(sizeof(List));
	New->pNext = NULL;
	Node->pNext = pHead;
	Original->pNext = pHead->pNext;
	while (Original->pNext != NULL) {
		Node->pNext->pNext = New->pNext;
		New->pNext = Node->pNext;
		Node->pNext = Original->pNext;
		Original->pNext = Original->pNext->pNext;
	}
	Node->pNext->pNext= New->pNext;
	//这个的返回无法free
	List* NNode = Node->pNext;
	free(New);
	free(Node);
	free(Original);
	return NNode;
}




//将两个顺序链表按照顺序重新链接
List* AddOtherList(List* pHead1,List*pHead2)
{
	//判断链表是否为空
	if (pHead1 == NULL || pHead2 == NULL)return NULL;
	if (pHead1->pNext == NULL && pHead2 != NULL)return pHead2;
	if (pHead2->pNext == NULL && pHead1 != NULL)return pHead1;

	List* Head = NULL;
	List* Tail = NULL;
	List* flag1 = pHead1;
	List* flag2 = pHead2;
	//第一次非循环的操作 需要把两个链表的最小值找到
	if (flag1->nValue <= flag2->nValue) {
		//找到后赋值给头节点和尾节点
		Head = flag1;
		Tail = flag2;
		//在把头指针指向给尾结点之前，两个节点都向后找到对应的flag，不然由于头结点是老的头结点，会导致老的头结点指向尾结点，然后再赋值flag的话会导致链表断联
		flag1 = pHead1->pNext;
		flag2 = pHead2->pNext;
		Head->pNext = Tail;
	}
	else{
		Head = flag2;
		Tail = flag1;
		flag1 = pHead1->pNext;
		flag2 = pHead2->pNext;
		Head->pNext = Tail;
	}

	
	//当有一个标记位为NULL则代表该链表遍历完成，结束查询
	while (flag1 != NULL && flag2 != NULL)
	{
		if (flag1->nValue <= flag2->nValue) {
			//比较后将较小值给链接到尾结点
			Tail->pNext = flag1;
			//尾结点转变为新的尾结点
			Tail = flag1;
			//标记位此时继续指向下一个
			flag1 = flag1->pNext;
		}
		else if (flag1->nValue > flag2->nValue)
		{
			Tail->pNext = flag2;
			Tail = flag2;
			flag2 = flag2->pNext;
		}
	}
	//由于此刻仅仅是推出了遍历空间，尾结点还没链接到剩下的另一个链表处，需要将其链接到下一个非空标记位节点
	if (flag1== NULL) {
		Tail->pNext = flag2;
	}
	else if (flag2== NULL)
	{
		Tail->pNext = flag1;
	}
	return Head;
}
//将两个顺序链表按照顺序重新链接（优化处理掉标记位）
List* AddOtherList1(List* pHead1, List* pHead2)
{
	//判断链表是否为空
	if (pHead1 == NULL || pHead2 == NULL)return NULL;
	if (pHead1->pNext == NULL && pHead2 != NULL)return pHead2;
	if (pHead2->pNext == NULL && pHead1 != NULL)return pHead1;

	List* pBegin = NULL;
	List* pEnd = NULL;
	//第一次非循环的操作 需要把两个链表的最小值找到,将其赋予头节点，标记继续指向下一个
	if (pHead1->nValue <= pHead2->nValue) {
		pBegin = pHead1;
		pHead1 = pHead1->pNext;
	}
	else {
		pBegin = pHead2;
		pHead2 = pHead2->pNext;
	}
	//新链表内只有一个节点，头尾都是其本身
	pEnd = pBegin;
	//合并
	while (pHead1 != NULL &&pHead2 != NULL) {
		if (pHead1->nValue < pHead2->nValue) {
			pEnd->pNext = pHead1;
			pEnd = pHead1;
			pHead1 = pHead1->pNext;
		}
		else {
			pEnd->pNext = pHead2;
			pEnd = pHead2;
			pHead2 = pHead2->pNext;
		}
	}
	//将剩余的连接过去
	if (pHead1 != NULL) {
		pEnd->pNext = pHead1;
	}
	else {
		pEnd->pNext = pHead2;
	}

	return pBegin;
}

//折叠链表
//在中间截断 然后倒置，然后间隔插入即可

int main()
{
	List* pHead = CreateList();
	Print(pHead);
	printf("\n");
	List* pHead2 = CreateList();
	Print(pHead2);
	printf("\n");
	//将两个顺序链表按照顺序重新链接
	Print(AddOtherList1(pHead,pHead2));
	printf("\n");
	return 0;
}


