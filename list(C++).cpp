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
//	cout << "������Ҫ������������:" << endl;
//	int ListLen = 0;
//	cin >> ListLen;
//	if (ListLen == 0)return NULL;
//	int Value = 0;
//	//������Ĵ�������һ���´����Ľڵ㣬����һ��ͷβ��ָ��NULL������
//	ListN Head = NULL;
//	ListN Tail = NULL;//������ӣ���Ȼÿ����Ӷ��ñ�����head����ı�β
//	ListN Node = NULL;
//	for (int i = 0; i < ListLen; i += 1) {
//		//�ȴ�������ʼ����Ҫ������½ڵ�
//		cout << "������ýڵ��ֵvalue:" << endl;
//		cin >> Value;
//		Node = (ListN)malloc(sizeof(List));//����ռ䣬��õ�ַ
//		Node->Next = NULL;
//		Node->value = Value;
//
//		//β���
//
//		//���ͷ��NULL����ô�õ���ǵ�һ���ڵ㣬���丳ֵ��ͷ�ڵ�
//		if (Head == NULL) {
//			Head = Node;
//		}
//		else {
//			//����ͷ�ڵ㲻����������һ���½ڵ㣬��β������һ��ָ�����ӣ��ʼͷβ�ڵ㶼��һ���ڵ㣬ֻ��������ͷ���䣬β�����Ϊ���ֵһֱ�����߾��У�
//			Tail->Next = Node;
//		}
//		//�����Ľڵ㶼��Ϊ�µ�β��
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