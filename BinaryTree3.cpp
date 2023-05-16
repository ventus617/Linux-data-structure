#include<iostream>
using namespace std;

typedef struct node
{
	struct node* pLeft;
	int value;
	struct node* pRight;
	struct node* pFather;
}Binarytree;

Binarytree* CreateTree()
{
	Binarytree* pTree = NULL;
	pTree = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->value = 1;
	pTree->pFather = NULL;
	//����
	pTree->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->value = 2;
	pTree->pLeft->pFather = pTree;
	//���ӵ���
	pTree->pLeft->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->value = 4;
	pTree->pLeft->pLeft->pRight = NULL;
	pTree->pLeft->pLeft->pFather = pTree->pLeft;
	//���ӵ������
	pTree->pLeft->pLeft->pLeft=(Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->pLeft->pFather = pTree->pLeft->pLeft;
	pTree->pLeft->pLeft->pLeft->pLeft = NULL;
	pTree->pLeft->pLeft->pLeft->pRight = NULL;
	pTree->pLeft->pLeft->pLeft->value = 6;

	//�Һ���
	pTree->pRight = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pRight->value = 3;
	pTree->pRight->pLeft = NULL;
	pTree->pRight->pRight = NULL;
	pTree->pRight->pFather = pTree;

	pTree->pLeft->pRight = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pRight->value = 5;
	pTree->pLeft->pRight->pLeft = NULL;
	pTree->pLeft->pRight->pRight = NULL;
	pTree->pLeft->pRight->pFather = pTree->pLeft;

	return pTree;
}

//���Ǵ����²㿪ʼ�ģ���Ϊ���²���ϲ��Ӱ�����
void BinaryRightRotate(Binarytree** node)
{
	if ((*node) == NULL || (*node)->pLeft == NULL)return;
	//�õ��ڶ���ĺ���
	Binarytree* Flag = (*node)->pLeft;

	//��������
	(*node)->pLeft = Flag->pRight;
	Flag->pRight = (*node);
	//��
	if ((*node)->pFather != NULL)
	{
		if ((*node)->pFather->pLeft == (*node))
		{
			(*node)->pFather->pLeft = Flag;
		}
		else
		{
			(*node)->pFather->pRight = Flag;
		}
	}
	//��������
	if ((*node)->pLeft != NULL)
	{
		(*node)->pLeft->pFather = (*node);
	}
	Flag->pFather = (*node)->pFather;
	(*node)->pFather = Flag;
	//���ص��ǵ�ǰ�޸ĵ�֮������ϲ�ڵ�
	(*node) = Flag;
}

void BinaryLeftRotate(Binarytree** tree)
{
	if ((*tree)->pRight == NULL || (*tree) == NULL)return;
	Binarytree* Flag = (*tree)->pRight;
	//��������
	(*tree)->pRight = Flag->pLeft;
	Flag->pLeft = (*tree);
	//��Ϊ��
	if ((*tree)->pFather)
	{
		if ((*tree)->pFather->pLeft == (*tree))
		{
			(*tree)->pFather->pLeft = Flag;
		}
		else
		{
			(*tree)->pFather->pRight = Flag;
		}
	}
	//��������
	if ((*tree)->pRight)
	{
		(*tree)->pRight->pFather = (*tree);
	}
	Flag->pFather = (*tree)->pFather;
	(*tree)->pFather = Flag;
	(*tree) = Flag;
}

void PreOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	cout << tree->value << " ";
	PreOrderTraversal(tree->pLeft);
	PreOrderTraversal(tree->pRight);
}

int main()
{
	Binarytree* tree = CreateTree();
	PreOrderTraversal(tree);
	cout << endl;
	BinaryRightRotate(&tree);
	PreOrderTraversal(tree);
	cout << endl;
	BinaryLeftRotate(&tree);
	PreOrderTraversal(tree);
	cout << endl;
	return 0;
}