//#include<stdio.h>
//#include<iostream>
//using namespace std;
//
//typedef struct LNode {
//	struct LNode* Next;
//	int value;
//}List,*ListN;
//
//ListN CreateList() {
//	cout << "请输入要创建的链表长度:" << endl;
//	int ListLen = 0;
//	cin >> ListLen;
//	if (ListLen == 0)return NULL;
//	int Value = 0;
//	//将链表的创建看做一个新创建的节点，插入一个头尾都指向NULL的链表
//	ListN Head = NULL;
//	ListN Tail = NULL;//辅助添加，不然每次添加都得遍历到head链表的表尾
//	ListN Node = NULL;
//	for (int i = 0; i < ListLen; i += 1) {
//		//先创建并初始化需要插入的新节点
//		cout << "请输入该节点的值value:" << endl;
//		cin >> Value;
//		Node = (ListN)malloc(sizeof(List));//申请空间，获得地址
//		Node->Next = NULL;
//		Node->value = Value;
//
//		//尾添加
//
//		//如果头是NULL，那么该点就是第一个节点，将其赋值给头节点
//		if (Head == NULL) {
//			Head = Node;
//		}
//		else {
//			//保持头节点不动，当插入一个新节点，是尾结点的下一个指向来接（最开始头尾节点都是一个节点，只不过保持头不变，尾结点作为标记值一直跟着走就行）
//			Tail->Next = Node;
//		}
//		//新来的节点都成为新的尾巴
//		Tail = Node;
//	}
//
//	return Head;
//}
//
//void PrintList(ListN list) {
//	if (list == NULL)return;
//	while (list != NULL) {
//		printf("%d ",list->value);
//		list = list->Next;
//	}
//	printf("\n");
//	return;
//}
//
//
//int main() {
//	ListN list=CreateList();
//	PrintList(list);
//}