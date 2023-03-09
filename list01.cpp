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
	printf("������������:\n");
	scanf("%d", &len);

	List* pHead = NULL;
	List* pTail = NULL;

	List* pTemp = NULL;

	int num;
	while (len != 0)
	{
		printf("������������ֵ:\n");
		scanf("%d", &num);

		pTemp = (List*)malloc(sizeof(List));
		pTemp->nValue = num;
		pTemp->pNext = NULL;

		//β���
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

	//������һ���ڵ�
	ReverePrint(pHead->pNext);

	//��ӡ��ǰ�ڵ�
	printf("%d ", pHead->nValue);
}
//��ָ�뷨���ڲ����´���������Ļ����ϵ�ͷ�巨
List* ReveseList(List* pHead)
{

	if (pHead == NULL||pHead->pNext==NULL)
		return NULL;
	List* New = NULL;
	List* Node = pHead;
	List* Original = pHead->pNext;
	while (Original->pNext != NULL) {
		//������ͷָ��������ͷ
		Node->pNext = New;
		//���� ������ͷ�ı��
		New = Node;
		//���� ������ͷ�ı��
		Node = Original;
		//���� �ɵľ�����ͷ�ı��
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
	//����ķ����޷�free
	List* NNode = Node->pNext;
	free(New);
	free(Node);
	free(Original);
	return NNode;
}




//������˳��������˳����������
List* AddOtherList(List* pHead1,List*pHead2)
{
	//�ж������Ƿ�Ϊ��
	if (pHead1 == NULL || pHead2 == NULL)return NULL;
	if (pHead1->pNext == NULL && pHead2 != NULL)return pHead2;
	if (pHead2->pNext == NULL && pHead1 != NULL)return pHead1;

	List* Head = NULL;
	List* Tail = NULL;
	List* flag1 = pHead1;
	List* flag2 = pHead2;
	//��һ�η�ѭ���Ĳ��� ��Ҫ�������������Сֵ�ҵ�
	if (flag1->nValue <= flag2->nValue) {
		//�ҵ���ֵ��ͷ�ڵ��β�ڵ�
		Head = flag1;
		Tail = flag2;
		//�ڰ�ͷָ��ָ���β���֮ǰ�������ڵ㶼����ҵ���Ӧ��flag����Ȼ����ͷ������ϵ�ͷ��㣬�ᵼ���ϵ�ͷ���ָ��β��㣬Ȼ���ٸ�ֵflag�Ļ��ᵼ���������
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

	
	//����һ�����λΪNULL���������������ɣ�������ѯ
	while (flag1 != NULL && flag2 != NULL)
	{
		if (flag1->nValue <= flag2->nValue) {
			//�ȽϺ󽫽�Сֵ�����ӵ�β���
			Tail->pNext = flag1;
			//β���ת��Ϊ�µ�β���
			Tail = flag1;
			//���λ��ʱ����ָ����һ��
			flag1 = flag1->pNext;
		}
		else if (flag1->nValue > flag2->nValue)
		{
			Tail->pNext = flag2;
			Tail = flag2;
			flag2 = flag2->pNext;
		}
	}
	//���ڴ˿̽������Ƴ��˱����ռ䣬β��㻹û���ӵ�ʣ�µ���һ����������Ҫ�������ӵ���һ���ǿձ��λ�ڵ�
	if (flag1== NULL) {
		Tail->pNext = flag2;
	}
	else if (flag2== NULL)
	{
		Tail->pNext = flag1;
	}
	return Head;
}
//������˳��������˳���������ӣ��Ż���������λ��
List* AddOtherList1(List* pHead1, List* pHead2)
{
	//�ж������Ƿ�Ϊ��
	if (pHead1 == NULL || pHead2 == NULL)return NULL;
	if (pHead1->pNext == NULL && pHead2 != NULL)return pHead2;
	if (pHead2->pNext == NULL && pHead1 != NULL)return pHead1;

	List* pBegin = NULL;
	List* pEnd = NULL;
	//��һ�η�ѭ���Ĳ��� ��Ҫ�������������Сֵ�ҵ�,���丳��ͷ�ڵ㣬��Ǽ���ָ����һ��
	if (pHead1->nValue <= pHead2->nValue) {
		pBegin = pHead1;
		pHead1 = pHead1->pNext;
	}
	else {
		pBegin = pHead2;
		pHead2 = pHead2->pNext;
	}
	//��������ֻ��һ���ڵ㣬ͷβ�����䱾��
	pEnd = pBegin;
	//�ϲ�
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
	//��ʣ������ӹ�ȥ
	if (pHead1 != NULL) {
		pEnd->pNext = pHead1;
	}
	else {
		pEnd->pNext = pHead2;
	}

	return pBegin;
}

//�۵�����
//���м�ض� Ȼ���ã�Ȼ�������뼴��

int main()
{
	List* pHead = CreateList();
	Print(pHead);
	printf("\n");
	List* pHead2 = CreateList();
	Print(pHead2);
	printf("\n");
	//������˳��������˳����������
	Print(AddOtherList1(pHead,pHead2));
	printf("\n");
	return 0;
}


