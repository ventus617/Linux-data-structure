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


//建立1.二叉搜索树
void CreateBinarySearchTree(Binarytree** tree)
{
	cout << "请输入一共插入多少个节点" << endl;
	int sum;
	cin >> sum;
	queue<Binarytree*>q1;
	Binarytree* flag=NULL;
	int num=0;
	while (sum)
	{
		//每次从根开始找
		(*tree) = flag;
		cout << "请输入要插入的值" << endl;
		cin >> num;
		Binarytree* ptree = (Binarytree*)malloc(sizeof(Binarytree));
		ptree->pLeft = NULL;
		ptree->pRight = NULL;
		ptree->value = num;
		sum--;
		q1.push(ptree);
		//进行遍历
		while (*tree)
		{
			//如果该节点大于放入节点的值则放在左子树
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
			{//如果该节点小于或等于放入节点的值则放在右子树
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


//建立2.二叉搜索树
void AddNode(Binarytree** tree, int value)
{
	//因为要改变传入的树的值，因此是**,但利用标记位去查询，因此不会改变根的指向
	Binarytree* pnode=(Binarytree*)malloc(sizeof(Binarytree));
	pnode->pLeft = NULL;
	pnode->pRight = NULL;
	pnode->value = value;
	if ((*tree) == NULL)
	{
		*tree = pnode;
		return;
	}
	//标记位，作为进行遍历插入的节点
	Binarytree* pFlag = (*tree);
	while (pFlag)
	{
		//大于时，插入左子树
		if (pFlag->value > pnode->value)
		{
			//直到找到空节点为止，插入该位置
			if (pFlag->pLeft == NULL)
			{
				pFlag->pLeft = pnode;
				return;
			}
			//如果存在，则节点替换为该左孩子，左孩子再继续去寻找满足条件的空节点
			pFlag = pFlag->pLeft;
		}
		//小于时，插入右子树
		else if (pFlag->value < pnode->value)
		{
			//直到找到空节点为止，插入该位置
			if (pFlag->pRight == NULL)
			{
				pFlag->pRight = pnode;
				return;
			}
			//如果存在，则节点替换为该右孩子，右孩子再继续去寻找满足条件的空节点
			pFlag = pFlag->pRight;
		}
		else
		{
			cout << "插入了相同的值，不满足唯一性，该值失败:"<<pnode->value<< endl;
			//释放掉当前无用的节点
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
//删除二叉搜索树节点
void BinarySearch(int value, Binarytree** pFather, Binarytree** pChild,Binarytree* tree)
{
	if (tree == NULL)return;
	while (tree)
	{
		//大于时，插入左子树
		if (tree->value >value)
		{
			(*pFather) = tree;
			tree = tree->pLeft;
		}
		//小于时，插入右子树
		else if (tree->value <value)
		{
			//如果存在，则节点替换为该右孩子，右孩子再继续去寻找满足条件的空节点
			(*pFather) = tree;
			tree = tree->pRight;
		}
		else 
		{
			(*pChild) = tree;
			return;
		}
	}
	//如果跳出,此时father应该没有可用节点
	*pFather = NULL;
}

void DeleteOneLeavfBST(Binarytree** pChild, Binarytree** pFather)
{
	if ((*pChild)->pLeft)
	{
		//通过值的比较来判断是左孩子还是右孩子
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
	cout << "请输入要删除的值" << endl;
	int value;
	cin >> value;
	BinarySearch(value, &pFather, &pChild, *tree);
	//叶子节点的时候
	if (pChild->pLeft == NULL && pChild->pRight == NULL)
	{
		//如果为根时
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
	//有一个节点的时候
	else if (pChild->pLeft == NULL || pChild->pRight == NULL)
	{
		//如果为根时
		if (pFather == NULL)
		{
			*tree = pChild->pLeft ? pChild->pLeft : pChild->pRight;
			free(pChild);
			pChild = NULL;
			return;
		}
		DeleteOneLeavfBST(&pChild, &pFather);
	}
	//有两个节点的时候
	else if (pChild->pLeft && pChild->pRight)
	{
		int num;
		//找到其左子树的最大值的节点
		Binarytree* ppFather = pChild;
		Binarytree* ppChild = pChild->pLeft;
		while (ppChild->pRight)
		{
			ppFather = ppChild;
			ppChild = ppChild->pRight;
		}
		//记录左子树的最大值
		num = ppChild->value;
		//将左子树的最大值节点删除
		DeleteOneLeavfBST(&ppChild, &ppFather);
		//将要删除的节点的值替换成左子树的最大值
		pChild->value = num;
	}
}

//--------------------------------------------------------------//
void Search(Binarytree* pTree, int num, Binarytree** pDel,Binarytree**pFather)
{
	if (pTree == NULL)return;
	while (pTree)
	{
		//当相等的时候
		if (pTree->value == num)
		{
			*pDel = pTree;
			return;
		}
		else if (pTree->value > num)
		{
			//左子树
			*pFather = pTree;
			pTree = pTree->pLeft;
		}
		else
		{
			//右子树
			*pFather = pTree;
			pTree = pTree->pRight;
		}
	}
	*pFather = NULL;
}

void DelNode(Binarytree** pTree, int num)
{
	//查找
	Binarytree* pDel = NULL;
	Binarytree* pFather = NULL;
	Search(*pTree, num, &pDel, &pFather);
	//分析两个孩子的情况
	//如果是两个孩子的话，就先修改值，然后变成删一个有0或者一个孩子的节点
	//标记被删除的节点
	Binarytree* pMark = NULL;
	if (pDel->pLeft != NULL && pDel->pRight != NULL)
	{
		//左子树最大值;
		pMark = pDel;
		pFather = pDel;
		pDel = pDel->pLeft;
		while (pDel->pRight != NULL)
		{
			pFather = pDel;
			pDel = pDel->pRight;
		}
		//值覆盖
		pMark->value = pDel->value;
	}
	//一个或0个孩子，其实处理效果都可以是一样的，即连接被删节点的孩子就行
	//根
	if (pFather == NULL)
	{
		
		*pTree = pDel->pLeft ? pDel->pLeft : pDel->pRight;
		free(pDel);
		pDel = NULL;
		return;
	}
	//非根
	if (pDel == pFather->pLeft)
	{
		//如果是一个孩子的时候,就连接上了孩子节点，如果是没有孩子的时候,pDel->pLeft==NULL,因此连接的是NULL
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
//循环前序遍历
stack<Binarytree*>s1;
//void PreOrderTraversal(Binarytree* tree)
//{
//	if (tree == NULL)return;
//	while (1)
//	{
//		//处理节点
//		while (tree)
//		{
//			printf("%d ", tree->value);
//			s1.push(tree);
//			//找到左节点来处理,为空则代表要去处理右节点
//			tree = tree->pLeft;
//		}
//		//如果为栈空,则跳出循环
//		if (s1.empty())break;
//		//找右
//		tree = s1.top();
//		s1.pop();
//		tree = tree->pRight;
//	}
//	cout << endl;
//}

//前序遍历 根左右
void PreOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	while (1)
	{
		//处理节点
		//如果不为空,正常处理
		if (tree)
		{
			printf("%d ", tree->value);
			s1.push(tree);
			//找到左节点来处理,为空则代表要去处理右节点
			tree = tree->pLeft;
			continue;
		}
		//如果为空
		else
		{
			//如果为栈空,则跳出循环
			if (s1.empty())break;
			//找右
			tree = s1.top();
			s1.pop();
			tree = tree->pRight;
		}
	}
	cout << endl;
}

//中序遍历 左根右
void InOrderTraversal(Binarytree* tree)
{
	if (tree == NULL)return;
	while (1)
	{
		//处理节点
		//如果不为空,正常处理
		if (tree)
		{
			s1.push(tree);
			tree = tree->pLeft;
			continue;
		}
		//如果为空
		else
		{
			//如果为栈空,则跳出循环
			if (s1.empty())break;
			//找根
			tree = s1.top();
			s1.pop();
			//找到根后打印根
			printf("%d ", tree->value);
			//找右
			tree = tree->pRight;
		}
	}
	cout << endl;
}

//后序遍历 左右根

//void LastOrderTraversal(Binarytree* tree)
//{
//	Binarytree* ptree = NULL;
//	if (tree == NULL)return;
//	while (1)
//	{
//		//处理节点
//		//如果不为空,正常遍历节点入栈,使得全部左子树入栈
//		while (tree)
//		{
//			s1.push(tree);
//			tree = tree->pLeft;
//		}
//		//如果为空，则获得当前根节点
//		tree = s1.top();
//
//		//结构上,在针对右子树的判断的时候是不需要重新入栈重复节点的，因此这里是去找到新的入栈元素，是循环过程  即获得下一个栈顶元素之后，还要判断该元素是否要出栈了
//		//判断该节点的右子树是否为空，或者该节点的右子树是否已经遍历过（如果已经遍历过，说明该节点可以出栈了）
//		while(tree->pRight == NULL ||ptree == tree->pRight)
//		{
//			//打印的节点就是该节点，记录该节点
//			ptree = tree;
//			//打印值
//			printf("%d ", tree->value);
//			//出栈，准备遍历下一个栈内元素
//			s1.pop();
//			//出栈前一定是有元素的，因此如果栈内没有元素的时候，即打印完之后就结束时，此时判断栈是否为空，空则为遍历结束
//			if (s1.empty())break;
//			//节点为下一个栈顶元素，该栈顶元素再去判断一次是否需要出栈
//			tree = s1.top();
//		}
//		if (s1.empty())break;
//		//如果栈顶元素存在，并且该栈顶元素的右子树并为打印过，则该节点是新节点，要入栈
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
		//tree仅在为新节点的时候入栈遍历
		while (tree)
		{
			s1.push(tree);
			tree = tree->pLeft;
		}
		//当入完栈之后没有节点了，说明没有了，可以退出了
		if (s1.empty())break;
		//中间不用tree作为遍历,因为要使得tree仅在新节点的时候才去入栈,也就是说如果用tree来接的时候，刚刚好就得在当前结构中循环，如果不用tree来接的时候，每次也是在这里进行大循环
		if (s1.top()->pRight == NULL || s1.top()->pRight == pMark)
		{
			pMark = s1.top();
			s1.pop();
			cout << pMark->value << " ";

		}
		else
		{
			//使得tree仅在为新节点的时候入栈遍历
			tree = s1.top()->pRight;
		}
	}
	cout << endl;
}

//层序遍历
void PushFirst(Binarytree* tree)
{
	queue<Binarytree*>q1;
	if (tree == NULL)return;
	//当前节点先入队
	q1.push(tree);
	while (1)
	{
		//如果没有节点入队，那么表示不用再继续遍历了
		if (q1.empty())break;
		//获得当前队列的队头节点
		tree = q1.front();
		//如果不为空则入队
		if (tree->pLeft != NULL)q1.push(tree->pLeft);
		if (tree->pRight != NULL)q1.push(tree->pRight);
		//打印该节点的值
		cout << tree->value << " ";
		//释放当前队头节点（已经完成任务了）
		q1.pop();
		//if (q1.empty())break;
		
	}
	cout << endl;
}

//--------------------------------------------------------------//


//BST二叉树转成双向链表
void BSTtoList(Binarytree* tree, Binarytree** pHead, Binarytree** pEnd)
{
	if (tree == NULL)return;
	//处理左子树
	BSTtoList(tree->pLeft, pHead, pEnd);
	if ((*pHead) == NULL)
	{
		//链表头节点为空，那么该节点就是头结点
		*pHead = tree;
	}
	else
	{
		tree->pLeft = (*pEnd);
		(*pEnd)->pRight = tree;
	}
	*pEnd = tree;
	//处理右子树
	BSTtoList(tree->pRight, pHead, pEnd);
}

//--------------------------------------------------------------//
Binarytree* CreateTree()
{
	Binarytree* pTree = NULL;
	pTree = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->value = 1;
	//左孩子
	pTree->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->value = 2;
	//左孩子的左
	pTree->pLeft->pLeft = (Binarytree*)malloc(sizeof(Binarytree));
	pTree->pLeft->pLeft->value = 4;
	pTree->pLeft->pLeft->pLeft = NULL;
	pTree->pLeft->pLeft->pRight = NULL;

	//右孩子
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