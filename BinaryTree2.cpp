#include<queue>
#include<iostream>
#include<stack>
using namespace std;
typedef struct node
{
	struct node* pLeft;
	int value;
	struct node* pRight;
}Binarytree;


//����1.����������
void CreateBinarySearchTree(Binarytree** tree)
{
	cout << "������һ��������ٸ��ڵ�" << endl;
	int sum;
	cin >> sum;
	queue<Binarytree*>q1;
	Binarytree* flag=NULL;
	int num=0;
	while (sum)
	{
		//ÿ�δӸ���ʼ��
		(*tree) = flag;
		cout << "������Ҫ�����ֵ" << endl;
		cin >> num;
		Binarytree* ptree = (Binarytree*)malloc(sizeof(Binarytree));
		ptree->pLeft = NULL;
		ptree->pRight = NULL;
		ptree->value = num;
		sum--;
		q1.push(ptree);
		//���б���
		while (*tree)
		{
			//����ýڵ���ڷ���ڵ��ֵ�����������
			if ((*tree)->value > q1.front()->value)
			{
				if ((*tree)->pLeft)
				{
					(*tree) = (*tree)->pLeft;
					continue;
				}
				(*tree)->pLeft = q1.front();
				(*tree) = q1.front();
				q1.pop();
				break;

			}
			else
			{//����ýڵ�С�ڻ���ڷ���ڵ��ֵ�����������
				if ((*tree)->pRight)
				{
					(*tree) = (*tree)->pRight;
					continue;
				}
				(*tree)->pRight = q1.front();
				(*tree) = q1.front();
				q1.pop();
				break;
			}
			
		}
		if ((*tree) == NULL)
		{
			(*tree) = q1.front();
			 flag = q1.front();
			 q1.pop();
		}
		
	}
	(*tree) = flag;
}


//����2.����������
void AddNode(Binarytree** tree, int value)
{
	//��ΪҪ�ı䴫�������ֵ�������**,�����ñ��λȥ��ѯ����˲���ı����ָ��
	Binarytree* pnode=(Binarytree*)malloc(sizeof(Binarytree));
	pnode->pLeft = NULL;
	pnode->pRight = NULL;
	pnode->value = value;
	if ((*tree) == NULL)
	{
		*tree = pnode;
		return;
	}
	//���λ����Ϊ���б�������Ľڵ�
	Binarytree* pFlag = (*tree);
	while (pFlag)
	{
		//����ʱ������������
		if (pFlag->value > pnode->value)
		{
			//ֱ���ҵ��սڵ�Ϊֹ�������λ��
			if (pFlag->pLeft == NULL)
			{
				pFlag->pLeft = pnode;
				return;
			}
			//������ڣ���ڵ��滻Ϊ�����ӣ������ټ���ȥѰ�����������Ŀսڵ�
			pFlag = pFlag->pLeft;
		}
		//С��ʱ������������
		else if (pFlag->value < pnode->value)
		{
			//ֱ���ҵ��սڵ�Ϊֹ�������λ��
			if (pFlag->pRight == NULL)
			{
				pFlag->pRight = pnode;
				return;
			}
			//������ڣ���ڵ��滻Ϊ���Һ��ӣ��Һ����ټ���ȥѰ�����������Ŀսڵ�
			pFlag = pFlag->pRight;
		}
		else
		{
			cout << "��������ͬ��ֵ��������Ψһ�ԣ���ֵʧ��:"<<pnode->value<< endl;
			//�ͷŵ���ǰ���õĽڵ�
			free(pnode);
			pnode = NULL;
			return;
		}
	}
}

Binarytree* CreateBST(int arr[], int nLength)
{
	if (arr == NULL || nLength <= 0)return NULL;
	Binarytree* pTree = NULL;
	for (int i = 0; i < nLength; i++)
	{

		AddNode(&pTree, arr[i]);
	}
	return pTree;
}


//--------------------------------------------------------------//
//ɾ�������������ڵ�
void BinarySearch(int value, Binarytree** pFather, Binarytree** pChild,Binarytree* tree)
{
	if (tree == NULL)return;
	while (tree)
	{
		//����ʱ������������
		if (tree->value >value)
		{
			(*pFather) = tree;
			tree = tree->pLeft;
		}
		//С��ʱ������������
		else if (tree->value <value)
		{
			//������ڣ���ڵ��滻Ϊ���Һ��ӣ��Һ����ټ���ȥѰ�����������Ŀսڵ�
			(*pFather) = tree;
			tree = tree->pRight;
		}
		else 
		{
			(*pChild) = tree;
			return;
		}
	}
	//�������,��ʱfatherӦ��û�п��ýڵ�
	*pFather = NULL;
}

void DeleteOneLeavfBST(Binarytree** pChild, Binarytree** pFather)
{
	if ((*pChild)->pLeft)
	{
		//ͨ��ֵ�ıȽ����ж������ӻ����Һ���
		if ((*pFather)->value > (*pChild)->value)
		{
			(*pFather)->pLeft = (*pChild)->pLeft;
			free((*pChild));
			(*pChild) = NULL;
		}
		else
		{
			(*pFather)->pRight = (*pChild)->pLeft;
			free((*pChild));
			(*pChild) = NULL;
		}
	}
	else
	{
		if ((*pFather)->value > (*pChild)->value)
		{
			(*pFather)->pLeft = (*pChild)->pRight;
			free((*pChild));
			(*pChild) = NULL;
		}
		else
		{
			(*pFather)->pRight = (*pChild)->pRight;
			free((*pChild));
			(*pChild) = NULL;
		}
	}
}

void DeleteBST(Binarytree** tree)
{
	Binarytree* pFather = NULL;
	Binarytree* pChild = NULL;
	cout << "������Ҫɾ����ֵ" << endl;
	int value;
	cin >> value;
	BinarySearch(value, &pFather, &pChild, *tree);
	//Ҷ�ӽڵ��ʱ��
	if (pChild->pLeft == NULL && pChild->pRight == NULL)
	{
		//���Ϊ��ʱ
		if (pFather == NULL)
		{
			*tree = pChild->pLeft ? pChild->pLeft : pChild->pRight;
			free(pChild);
			pChild = NULL;
			return;
		}
		if (pFather->value > pChild->value)
			pFather->pLeft = NULL;
		else pFather->pRight = NULL;
		free(pChild);
		pChild = NULL;
	}
	//��һ���ڵ��ʱ��
	else if (pChild->pLeft == NULL || pChild->pRight == NULL)
	{
		//���Ϊ��ʱ
		if (pFather == NULL)
		{
			*tree = pChild->pLeft ? pChild->pLeft : pChild->pRight;
			free(pChild);
			pChild = NULL;
			return;
		}
		DeleteOneLeavfBST(&pChild, &pFather);
	}
	//�������ڵ��ʱ��
	else if (pChild->pLeft && pChild->pRight)
	{
		int num;
		//�ҵ��������������ֵ�Ľڵ�
		Binarytree* ppFather = pChild;
		Binarytree* ppChild = pChild->pLeft;
		while (ppChild->pRight)
		{
			ppFather = ppChild;
			ppChild = ppChild->pRight;
		}
		//��¼�����������ֵ
		num = ppChild->value;
		//�������������ֵ�ڵ�ɾ��
		DeleteOneLeavfBST(&ppChild, &ppFather);
		//��Ҫɾ���Ľڵ��ֵ�滻�������������ֵ
		pChild->value = num;
	}
}

//--------------------------------------------------------------//
void Search(Binarytree* pTree, int num, Binarytree** pDel,Binarytree**pFather)
{
	if (pTree == NULL)return;
	while (pTree)
	{
		//����ȵ�ʱ��
		if (pTree->value == num)
		{
			*pDel = pTree;
			return;
		}
		else if (pTree->value > num)
		{
			//������
			*pFather = pTree;
			pTree = pTree->pLeft;
		}
		else
		{
			//������
			*pFather = pTree;
			pTree = pTree->pRight;
		}
	}
	*pFather = NULL;
}

void DelNode(Binarytree** pTree, int num)
{
	//����
	Binarytree* pDel = NULL;
	Binarytree* pFather = NULL;
	Search(*pTree, num, &pDel, &pFather);
	//�����������ӵ����
	//������������ӵĻ��������޸�ֵ��Ȼ����ɾһ����0����һ�����ӵĽڵ�
	//��Ǳ�ɾ���Ľڵ�
	Binarytree* pMark = NULL;
	if (pDel->pLeft != NULL && pDel->pRight != NULL)
	{
		//���������ֵ;
		pMark = pDel;
		pFather = pDel;
		pDel = pDel->pLeft;
		while (pDel->pRight != NULL)
		{
			pFather = pDel;
			pDel = pDel->pRight;
		}
		//ֵ����
		pMark->value = pDel->value;
	}
	//һ����0�����ӣ���ʵ����Ч����������һ���ģ������ӱ�ɾ�ڵ�ĺ��Ӿ���
	//��
	if (pFather == NULL)
	{
		
		*pTree = pDel->pLeft ? pDel->pLeft : pDel->pRight;
		free(pDel);
		pDel = NULL;
		return;
	}
	//�Ǹ�
	if (pDel == pFather->pLeft)
	{
		//�����һ�����ӵ�ʱ��,���������˺��ӽڵ㣬�����û�к��ӵ�ʱ��,pDel->pLeft==NULL,������ӵ���NULL
		pFather->pLeft = pDel->pLeft ? pDel->pLeft : pDel->pRight;
	}
	else
	{
		pFather->pRight = pDel->pLeft ? pDel->pLeft : pDel->pRight;
	}
	free(pDel);
	pDel = NULL;
}

//--------------------------------------------------------------//
//ѭ��ǰ�����
stack<Binarytree*>s1;
//void PreOrderTraversal(Binarytree* tree)
//{
//	if (tree == NULL)return;
//	while (1)
//	{
//		//����ڵ�
//		while (tree)
//		{
//			printf("%d ", tree->value);
//			s1.push(tree);
//			//�ҵ���ڵ�������,Ϊ�������Ҫȥ�����ҽڵ�
//			tree = tree->pLeft;
//		}
//		//���Ϊջ��,������ѭ��
//		if (s1.empty())break;
//		//����
//		tree = s1.top();
//		s1.pop();
//		tree = tree->pRight;
//	}
//	cout << endl;
//}

//ǰ����� ������
void PreOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	while (1)
	{
		//����ڵ�
		//�����Ϊ��,��������
		if (tree)
		{
			printf("%d ", tree->value);
			s1.push(tree);
			//�ҵ���ڵ�������,Ϊ�������Ҫȥ�����ҽڵ�
			tree = tree->pLeft;
			continue;
		}
		//���Ϊ��
		else
		{
			//���Ϊջ��,������ѭ��
			if (s1.empty())break;
			//����
			tree = s1.top();
			s1.pop();
			tree = tree->pRight;
		}
	}
	cout << endl;
}

//������� �����
void InOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	while (1)
	{
		//����ڵ�
		//�����Ϊ��,��������
		if (tree)
		{
			s1.push(tree);
			tree = tree->pLeft;
			continue;
		}
		//���Ϊ��
		else
		{
			//���Ϊջ��,������ѭ��
			if (s1.empty())break;
			//�Ҹ�
			tree = s1.top();
			s1.pop();
			//�ҵ������ӡ��
			printf("%d ", tree->value);
			//����
			tree = tree->pRight;
		}
	}
	cout << endl;
}

//������� ���Ҹ�

//void LastOrderTraversal(Binarytree* tree)
//{
//	Binarytree* ptree = NULL;
//	if (tree == NULL)return;
//	while (1)
//	{
//		//����ڵ�
//		//�����Ϊ��,���������ڵ���ջ,ʹ��ȫ����������ջ
//		while (tree)
//		{
//			s1.push(tree);
//			tree = tree->pLeft;
//		}
//		//���Ϊ�գ����õ�ǰ���ڵ�
//		tree = s1.top();
//
//		//�ṹ��,��������������жϵ�ʱ���ǲ���Ҫ������ջ�ظ��ڵ�ģ����������ȥ�ҵ��µ���ջԪ�أ���ѭ������  �������һ��ջ��Ԫ��֮�󣬻�Ҫ�жϸ�Ԫ���Ƿ�Ҫ��ջ��
//		//�жϸýڵ���������Ƿ�Ϊ�գ����߸ýڵ���������Ƿ��Ѿ�������������Ѿ���������˵���ýڵ���Գ�ջ�ˣ�
//		while(tree->pRight == NULL ||ptree == tree->pRight)
//		{
//			//��ӡ�Ľڵ���Ǹýڵ㣬��¼�ýڵ�
//			ptree = tree;
//			//��ӡֵ
//			printf("%d ", tree->value);
//			//��ջ��׼��������һ��ջ��Ԫ��
//			s1.pop();
//			//��ջǰһ������Ԫ�صģ�������ջ��û��Ԫ�ص�ʱ�򣬼���ӡ��֮��ͽ���ʱ����ʱ�ж�ջ�Ƿ�Ϊ�գ�����Ϊ��������
//			if (s1.empty())break;
//			//�ڵ�Ϊ��һ��ջ��Ԫ�أ���ջ��Ԫ����ȥ�ж�һ���Ƿ���Ҫ��ջ
//			tree = s1.top();
//		}
//		if (s1.empty())break;
//		//���ջ��Ԫ�ش��ڣ����Ҹ�ջ��Ԫ�ص���������Ϊ��ӡ������ýڵ����½ڵ㣬Ҫ��ջ
//		if(tree->pRight&&tree->pRight!=ptree)
//		{
//			tree = tree->pRight;
//		}
//
//	}
//	cout << endl;
//}
void LastOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	Binarytree* pMark = NULL;
	while (1)
	{
		//tree����Ϊ�½ڵ��ʱ����ջ����
		while (tree)
		{
			s1.push(tree);
			tree = tree->pLeft;
		}
		//������ջ֮��û�нڵ��ˣ�˵��û���ˣ������˳���
		if (s1.empty())break;
		//�м䲻��tree��Ϊ����,��ΪҪʹ��tree�����½ڵ��ʱ���ȥ��ջ,Ҳ����˵�����tree���ӵ�ʱ�򣬸ոպþ͵��ڵ�ǰ�ṹ��ѭ�����������tree���ӵ�ʱ��ÿ��Ҳ����������д�ѭ��
		if (s1.top()->pRight == NULL || s1.top()->pRight == pMark)
		{
			pMark = s1.top();
			s1.pop();
			cout << pMark->value << " ";

		}
		else
		{
			//ʹ��tree����Ϊ�½ڵ��ʱ����ջ����
			tree = s1.top()->pRight;
		}
	}
	cout << endl;
}

//�������
void PushFirst(Binarytree* tree)
{
	queue<Binarytree*>q1;
	if (tree == NULL)return;
	//��ǰ�ڵ������
	q1.push(tree);
	while (1)
	{
		//���û�нڵ���ӣ���ô��ʾ�����ټ���������
		if (q1.empty())break;
		//��õ�ǰ���еĶ�ͷ�ڵ�
		tree = q1.front();
		//�����Ϊ�������
		if (tree->pLeft != NULL)q1.push(tree->pLeft);
		if (tree->pRight != NULL)q1.push(tree->pRight);
		//��ӡ�ýڵ��ֵ
		cout << tree->value << " ";
		//�ͷŵ�ǰ��ͷ�ڵ㣨�Ѿ���������ˣ�
		q1.pop();
		//if (q1.empty())break;
		
	}
	cout << endl;
}

//--------------------------------------------------------------//


//BST������ת��˫������
void BSTtoList(Binarytree* tree, Binarytree** pHead, Binarytree** pEnd)
{
	if (tree == NULL)return;
	//����������
	BSTtoList(tree->pLeft, pHead, pEnd);
	if ((*pHead) == NULL)
	{
		//����ͷ�ڵ�Ϊ�գ���ô�ýڵ����ͷ���
		*pHead = tree;
	}
	else
	{
		tree->pLeft = (*pEnd);
		(*pEnd)->pRight = tree;
	}
	*pEnd = tree;
	//����������
	BSTtoList(tree->pRight, pHead, pEnd);
}

//--------------------------------------------------------------//
Binarytree* CreateTree()
{
	Binarytree* pTree = NULL;
	pTree = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->value = 1;
	//����
	pTree->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->value = 2;
	//���ӵ���
	pTree->pLeft->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->value = 4;
	pTree->pLeft->pLeft->pLeft = NULL;
	pTree->pLeft->pLeft->pRight = NULL;

	//�Һ���
	pTree->pRight = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pRight->value = 3;
	pTree->pRight->pLeft = NULL;
	pTree->pRight->pRight = NULL;

	pTree->pLeft->pRight = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pRight->value = 5;
	pTree->pLeft->pRight->pLeft = NULL;
	pTree->pLeft->pRight->pRight = NULL;

	return pTree;
}

int main()
{
	Binarytree* tree = NULL;
	/*CreateBinarySearchTree(&tree);*/
	int arr[] = { 10,3,12,1,9,11,15,8};
	tree = CreateBST(arr, sizeof(arr) / sizeof(arr[0]));
	PreOrderTraversal(tree);
	InOrderTraversal(tree);
	LastOrderTraversal(tree);
	PushFirst(tree);
	//DelNode(&tree, 10);
	//DeleteBST(&tree);
	//PreOrderTraversal(tree);
	//InOrderTraversal(tree);
	//LastOrderTraversal(tree);
	//PushFirst(tree);
	Binarytree* pHead = NULL;
	Binarytree* pEnd = NULL;
	BSTtoList(tree, &pHead, &pEnd);
	while (pHead)
	{
		cout << pHead->value << " ";
		pHead = pHead->pRight;
	}
	return 0;
}