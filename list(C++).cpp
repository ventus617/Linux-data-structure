#include<stdio.h>
#include<iostream>
using namespace std;

typedef struct LNode {
	struct LNode* Next;
	struct LNode* random;
	int value;
}List,*ListN;

ListN CreateList() {
	cout << "������Ҫ������������:" << endl;
	int ListLen = 0;
	cin >> ListLen;
	if (ListLen == 0)return NULL;
	int Value = 0;
	//������Ĵ�������һ���´����Ľڵ㣬����һ��ͷβ��ָ��NULL������
	ListN Head = NULL;
	ListN Tail = NULL;//������ӣ���Ȼÿ����Ӷ��ñ�����head����ı�β
	ListN Node = NULL;
	for (int i = 0; i < ListLen; i += 1) {
		//�ȴ�������ʼ����Ҫ������½ڵ�
		cout << "������ýڵ��ֵvalue:" << endl;
		cin >> Value;
		Node = (ListN)malloc(sizeof(List));//����ռ䣬��õ�ַ
		Node->Next = NULL;
		Node->random = NULL;
		Node->value = Value;

		//β���

		//���ͷ��NULL����ô�õ���ǵ�һ���ڵ㣬���丳ֵ��ͷ�ڵ�
		if (Head == NULL) {
			Head = Node;
		}
		else {
			//����ͷ�ڵ㲻����������һ���½ڵ㣬��β������һ��ָ�����ӣ��ʼͷβ�ڵ㶼��һ���ڵ㣬ֻ��������ͷ���䣬β�����Ϊ���ֵһֱ�����߾��У�
			Tail->Next = Node;
		}
		//�����Ľڵ㶼��Ϊ�µ�β��
		Tail = Node;
	}
 //�������,Ҫ�󳤶����ٲ�����2������Ч
	Head->random = Head->Next->Next;
	return Head;
}

void PrintList(ListN list) {
	if (list == NULL)return;
	while (list != NULL) {
		printf("%d ",list->value);
		list = list->Next;
	}
	printf("\n");
	return;
}

ListN InsertList(ListN head) {
	ListN ListA = head;
	if (head == NULL)return NULL;
	while (ListA != NULL) {
		ListN ListB = (ListN)malloc(sizeof(List));
		ListB->value = ListA->value;
		ListB->Next = ListA->Next;
		ListA->Next = ListB;
		ListA = ListB->Next;
	}
	return head;

}
ListN CutList(ListN head) {
	ListN Flag1 = head;
	ListN Flag3 = Flag1->Next;
	while (Flag3->Next!= NULL) {
		Flag1->Next = Flag3->Next;
		Flag1 = Flag1->Next;
		Flag3->Next = Flag1->Next;
		Flag3 = Flag3->Next;
	}
	Flag1->Next = NULL;
	return head;
}
ListN InsertRandomList(ListN head) {
	ListN Flag1 = head;
	ListN Flag3 = Flag1->Next;
	while (Flag3->Next != NULL)
	{
		if (Flag1->random != NULL)
		{
			Flag3->random = Flag1->random->Next;
		}
		Flag1 = Flag3->Next;
		Flag3 = Flag1->Next;
	}
	return head;
}
int main() {
	ListN list=CreateList();
	PrintList(list);
	ListN listA = InsertList(list);
	PrintList(listA);
	PrintList(InsertRandomList(listA));
	PrintList(listA);
	listA = CutList(listA);
	PrintList(listA);
}