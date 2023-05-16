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
queue<Binarytree*>q1;
typedef struct
{
	Binarytree* ptree;
	int value;
}Treearr;


Binarytree* CreateMyArrTree2(int* arr, int len)
{
	if (len == 0)return NULL;
	Binarytree* ptree = NULL;
	ptree = (Binarytree*)malloc(sizeof(Binarytree)*len);
	//��ó�ֵ
	for (int i = 0; i < len; i++)
	{
		ptree[i].value = arr[i];
		ptree[i].pLeft = NULL;
		ptree[i].pRight = NULL;
	}
	//���һ���,ֻ��len/2-1�����ڵ㣬��������ڵ����Һ��Ӷ���ֵ��,��˿��Բ���elseʹ�丳NULL
	for (int i = 0; i <=len / 2 - 1; i++)
	{
		if (2 * i + 1 <= len - 1)
		{
			ptree[i].pLeft = &ptree[2 * i + 1];
		}
		if (2 * i + 2 <= len - 1)
		{
			ptree[i].pRight = &ptree[2 * i + 2];
		}
	}
	return ptree;
}

void CreateMyArrTree(Binarytree** tree)
{
	//�õ������Ľڵ����
	int len;
	cout << "����ڵ����";
	cin >> len;
	if (len == 0)return;
	//�����洢�ṹ�������
	Treearr* arr = (Treearr*)malloc(sizeof(Treearr) * len);
	//��ֵ��Ӧ���ҵĽڵ�
	for (int i = 0; i < len; i++)
	{
		cout << "����������ڵ��ֵ" << endl;
		int flag;
		cin >> flag;
		arr[i].value = flag;
		arr[i].ptree = (Binarytree*)malloc(sizeof(Binarytree));
		arr[i].ptree->value = flag;
		//������︳�˳�ֵ,�Ͳ��ù�else��
		arr[i].ptree->pLeft = NULL;
		arr[i].ptree->pRight = NULL;
	}
	//��ʼ����
	//�к��ӵĽڵ������ֻ��len/2 -1��
	for (int i = 0; i <=len/2-1; i++)
	{
		if (2 * i + 1 <= len - 1)
		{
			arr[i].ptree->pLeft = arr[2 * i + 1].ptree;
		}
		/*else
		{
			arr[i].ptree->pLeft = NULL;
		}*/	
		if (2 * i + 2 <=len - 1)
		{
			arr[i].ptree->pRight = arr[2 * i + 2].ptree;
		}
		/*else
		{
			arr[i].ptree->pRight = NULL;
		}*/
	}
	*tree = arr[0].ptree;

}

//����ǰ��ķ�ʽ��ֵ������
void CreateMyTree(Binarytree** tree)
{
	//��ֵ
	int num;
	//���ֵ
	cin >> num;
	if (num == 0)
	{
		*tree = NULL;
		return;
	}
	//��װ�ɽڵ�,���ýڵ�����(��Ϊ�������ľ���NULL�ڵ㣬ֱ�Ӹ�ֵ����������)
	*tree = (Binarytree*)malloc(sizeof(Binarytree));
	(*tree)->value = num;
	(*tree)->pLeft = NULL;
	(*tree)->pRight = NULL;
	//�������
	CreateMyTree(&(*tree)->pLeft);
	CreateMyTree(&(*tree)->pRight);
}

//�������
//�������
void PushFirst(Binarytree* tree)
{
	if (tree == NULL)
	{
		return;
	}
	q1.push(tree);
	while (q1.size()!=0)
	{
		tree = q1.front();
		if(tree->pLeft!=NULL) q1.push(tree->pLeft);
		if(tree->pRight!=NULL)q1.push(tree->pRight);
		cout << q1.front()->value << " ";
		q1.pop();

	}

}

//�������
void PreorderTraversal(Binarytree *tree)
{
	if (tree == NULL)
	{
		return;
	}
	printf("%d ", tree->value);
	PreorderTraversal(tree->pLeft);
	PreorderTraversal(tree->pRight);
}

void InorderTraversal(Binarytree* tree)
{
	if (tree == NULL)
	{
		return;
	}
	InorderTraversal(tree->pLeft);
	printf("%d ", tree->value);
	InorderTraversal(tree->pRight);
}

void LastorderTraversal(Binarytree* tree)
{
	if (tree == NULL)
	{
		return;
	}
	LastorderTraversal(tree->pLeft);
	LastorderTraversal(tree->pRight);
	printf("%d ", tree->value);
}

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
	//CreateMyTree(&tree);
	//CreateMyArrTree(&tree);
	int arr[] = { 1,2,3,4,5 };
	tree=CreateMyArrTree2(arr, sizeof(arr) / sizeof(arr[0]));
	PreorderTraversal(tree);
	cout << endl;
	InorderTraversal(tree);
	cout << endl;
	LastorderTraversal(tree);
	cout << endl;
	PushFirst(tree);
	cout << endl;
	return 0;
}