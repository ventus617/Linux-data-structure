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
	//左孩子
	pTree->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->value = 2;
	pTree->pLeft->pFather = pTree;
	//左孩子的左
	pTree->pLeft->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->value = 4;
	pTree->pLeft->pLeft->pRight = NULL;
	pTree->pLeft->pLeft->pFather = pTree->pLeft;
	//左孩子的左的左
	pTree->pLeft->pLeft->pLeft=(Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->pLeft->pFather = pTree->pLeft->pLeft;
	pTree->pLeft->pLeft->pLeft->pLeft = NULL;
	pTree->pLeft->pLeft->pLeft->pRight = NULL;
	pTree->pLeft->pLeft->pLeft->value = 6;

	//右孩子
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

//都是从最下层开始改，因为最下层对上层的影响最低
void BinaryRightRotate(Binarytree** node)
{
	if ((*node) == NULL || (*node)->pLeft == NULL)return;
	//得到第二层的孩子
	Binarytree* Flag = (*node)->pLeft;

	//三个孩子
	(*node)->pLeft = Flag->pRight;
	Flag->pRight = (*node);
	//根
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
	//三个父亲
	if ((*node)->pLeft != NULL)
	{
		(*node)->pLeft->pFather = (*node);
	}
	Flag->pFather = (*node)->pFather;
	(*node)->pFather = Flag;
	//返回的是当前修改的之后的最上层节点
	(*node) = Flag;
}

void BinaryLeftRotate(Binarytree** tree)
{
	if ((*tree)->pRight == NULL || (*tree) == NULL)return;
	Binarytree* Flag = (*tree)->pRight;
	//三个孩子
	(*tree)->pRight = Flag->pLeft;
	Flag->pLeft = (*tree);
	//不为根
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
	//三个父亲
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