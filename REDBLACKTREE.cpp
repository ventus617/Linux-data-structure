#include<iostream>
#include<queue>
using namespace std;

typedef struct node
{
	struct node* left;
	struct node* right;
	struct node* father;
	int val;
	int color;//0红1黑
}RedBlackTree;


void PushFirst(RedBlackTree* tree)
{
	queue<RedBlackTree*>q1;
	if (tree == NULL)
	{
		return;
	}
	q1.push(tree);
	while (q1.size() != 0)
	{
		tree = q1.front();
		if (tree->left != NULL) q1.push(tree->left);
		if (tree->right != NULL)q1.push(tree->right);
		if (q1.front()->color == 0)
		{
			cout << q1.front()->val<<"红色"<<" ";
		}
		else
		{
			cout << q1.front()->val << "黑色" << " ";
		}
		q1.pop();

	}
}

//右旋
void RedBlackTreeRightRotate(RedBlackTree** node)
{
	if ((*node) == NULL || (*node)->left == NULL)return;
	//得到第二层的孩子
	RedBlackTree* Flag = (*node)->left;

	//三个孩子
	(*node)->left = Flag->right;
	Flag->right = (*node);
	//根
	if ((*node)->father != NULL)
	{
		if ((*node)->father->left == (*node))
		{
			(*node)->father->left = Flag;
		}
		else
		{
			(*node)->father->right = Flag;
		}
	}
	//三个父亲
	if ((*node)->left!= NULL)
	{
		(*node)->left->father = (*node);
	}
	Flag->father = (*node)->father;
	(*node)->father = Flag;
	//返回的是当前修改的情况
	//(*node) = Flag;
}

//左旋
void RedBlackTreeLeftRotate(RedBlackTree** tree)
{
	if ((*tree) == NULL || (*tree)->right == NULL)return;
	RedBlackTree* Flag = (*tree)->right;
	//三个孩子
	(*tree)->right = Flag->left;
	Flag->left = (*tree);
	//根
	if ((*tree)->father)
	{
		if ((*tree)->father->left == (*tree))
		{
			(*tree)->father->left = Flag;
		}
		else
		{
			(*tree)->father->right = Flag;
		}
	}
	//三个父亲
	if ((*tree)->right)
	{
		(*tree)->right->father = (*tree);
	}
	Flag->father = (*tree)->father;
	(*tree)->father = Flag;
	//(*tree) = Flag;
}

void RBTSearch(RedBlackTree* tree, RedBlackTree** Del, RedBlackTree** Father,int val)
{
	if (tree == NULL)return;
	while (tree)
	{
		if (tree->val > val)
		{
			
			tree = tree->left;
			
		}
		else if (tree->val < val)
		{
			
			tree = tree->right;
			
		}
		else if(tree->val==val)
		{
			(*Del) = tree;
			(*Father) = tree->father;
			return;
		}
	}
	(*Father) = NULL;
}


//传父亲，得叔叔
RedBlackTree* GetUncle(RedBlackTree* node)
{
	if (node == node->father->left)
		return node->father->right;
	else
		return node->father->left;
}

//优化颜色改变
void ChangeRBTColor(RedBlackTree** tree)
{
	//父亲颜色是黑色
	if ((*tree)->father == NULL || (*tree)->father->color == 1)return;
	//叔叔
	RedBlackTree* Uncle = NULL;
	//爷爷
	RedBlackTree* Grandfather = NULL;
	//父亲
	RedBlackTree* Father = (*tree)->father;
	while ((*tree)->father != NULL && (*tree)->father->color == 0)
	{
		Uncle = GetUncle(Father);
		Grandfather = Father->father;
		//叔叔红的
		if (Uncle != NULL && Uncle->color == 0)
		{
			Uncle->color = 1;
			Father->color = 1;
			Grandfather->color = 0;
			(*tree) = Grandfather;
			Father = (*tree)->father;
			//如果此时操作节点是根
			if (Father == NULL)
			{
				(*tree)->color = 1;
				break;
			}
			continue;
		}
		//叔叔黑色
		if (Uncle == NULL || Uncle->color == 1)
		{
			//父亲是爷爷的左
			if (Father == Grandfather->left)
			{
				//当前节点是父亲的右侧
				if ((*tree) == Father->right)
				{
					(*tree) = Father;
					RedBlackTreeLeftRotate(tree);
					//此时旋转完后父亲也换了
					Father = (*tree)->father;
				}
				//当前节点是父亲的左
				if ((*tree) == Father->left)
				{
					Father->color =1;
					Grandfather->color = 0;
					RedBlackTreeRightRotate(&Grandfather);
					break;
				}
			}
			//父亲是爷爷的右侧
			else
			{
				//当前节点是父亲的左
				if ((*tree) == Father->left)
				{
					(*tree) = Father;
					RedBlackTreeRightRotate(tree);
					Father = (*tree)->father;
				}
				//当前节点是父亲的右侧
				if ((*tree) == Father->right)
				{
					Father->color = 1;
					Grandfather->color = 0;
					RedBlackTreeLeftRotate(&Grandfather);
					break;
				}
			}
		}
	}
}

//RBT树的插入后的颜色平衡
void ChangeColor(RedBlackTree** tree)
{
	//父亲颜色是黑色
	if ((*tree)->father == NULL||(*tree)->father->color == 1)return;
	//如果父亲颜色是红色
	while ((*tree)->father != NULL&&(*tree)->father->color == 0)
	{
		//查看叔叔颜色
		if ((*tree)->father == (*tree)->father->father->left)
		{
			//如果是红色
			if ((*tree)->father->father->right != NULL&&(*tree)->father->father->right->color == 0)
			{
				//父亲和叔叔变黑,爷爷变红
				(*tree)->father->color = 1;
				(*tree)->father->father->right->color = 1;
				(*tree)->father->father->color =0;
				(*tree) = (*tree)->father->father;
				continue;
			}
			//如果是黑色
			else if((*tree)->father->father->right == NULL||(*tree)->father->father->right->color == 1)
			{
				//如果父亲是爷爷的右孩子
				if ((*tree)->father == (*tree)->father->father->right)
				{
					//如果标记点是父亲的左节点
					if ((*tree) == (*tree)->father->left)
					{
						//标记点Z的父亲为新的标记点
						(*tree) = (*tree)->father;
						//右旋
						RedBlackTreeRightRotate(tree);
					}
					if ((*tree) == (*tree)->father->right)
					{
						(*tree)->father->color = 1;
						(*tree)->father->father->color = 0;
						(*tree) = (*tree)->father->father;
						RedBlackTreeLeftRotate(tree);
					}
				}
				//父亲是爷爷的左孩子
				else
				{
					//如果标记点是父亲的右节点
					if ((*tree) == (*tree)->father->right)
					{
						(*tree) = (*tree)->father;
						RedBlackTreeLeftRotate(tree);
					}
					if ((*tree) == (*tree)->father->left)
					{
						(*tree)->father->color = 1;
						(*tree)->father->father->color = 0;
						(*tree) = (*tree)->father->father;
						RedBlackTreeRightRotate(tree);
					}
				}
			}
		}
		else
		{
			//如果是红色
			if ((*tree)->father->father->left != NULL&&(*tree)->father->father->left->color == 0 )
			{
				//父亲和叔叔变黑,爷爷变红
				(*tree)->father->color = 1;
				(*tree)->father->father->left->color = 1;
				(*tree)->father->father->color = 0;
				(*tree) = (*tree)->father->father;
				continue;
			}
			else if((*tree)->father->father->left == NULL||(*tree)->father->father->left->color == 1 )
			{
				//如果父亲是爷爷的右孩子
				if ((*tree)->father == (*tree)->father->father->right)
				{
					//如果标记点是父亲的左节点
					if ((*tree) == (*tree)->father->left)
					{
						//标记点Z的父亲为新的标记点
						(*tree) = (*tree)->father;
						//右旋
						RedBlackTreeRightRotate(tree);
					}
					if ((*tree) == (*tree)->father->right)
					{
						(*tree)->father->color = 1;
						(*tree)->father->father->color = 0;
						(*tree) = (*tree)->father->father;
						RedBlackTreeLeftRotate(tree);
					}
				}
				//父亲是爷爷的左孩子
				else
				{
					//如果标记点是父亲的右节点
					if ((*tree) == (*tree)->father->right)
					{
						(*tree) = (*tree)->father;
						RedBlackTreeLeftRotate(tree);
					}
					if ((*tree) == (*tree)->father->left)
					{
						(*tree)->father->color = 1;
						(*tree)->father->father->color = 0;
						(*tree) = (*tree)->father->father;
						RedBlackTreeRightRotate(tree);
					}
				}
			}
		}
	}
}




void AddNode(RedBlackTree** tree, int value)
{
	//创建默认节点
	RedBlackTree* node = (RedBlackTree*)malloc(sizeof(RedBlackTree));
	node->color = 0;
	node->val = value;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	//查找插入点
	//如果为根
	if ((*tree) == NULL)
	{
		node->color = 1;
		(*tree) = node;
		return;
	}
	//不为根
	RedBlackTree* flag = (*tree);
	while (flag)
	{
		//大于时,插入左子树
		if (flag->val > node->val)
		{
			if (flag->left == NULL)
			{
				flag->left = node;
				node->father = flag;
				//还要进行辨别
				ChangeRBTColor(&node);
				//插入完成后获得当前的根节点
				while ((*tree)->father != NULL)
				{
					(*tree) = (*tree)->father;
				}
				//插入完成后如果当前根节点是红色，改成黑色
				if ((*tree)->color == 0)
				{
					(*tree)->color = 1;
				}
				return;
			}
			flag = flag->left;
		}
		else if (flag->val < node->val)
		{
			if (flag->right == NULL)
			{
				flag->right = node;
				node->father = flag;
				ChangeRBTColor(&node);
				//插入完成后获得当前的根节点
				while ((*tree)->father != NULL)
				{
					(*tree) = (*tree)->father;
				}
				//插入完成后如果当前根节点是红色，改成黑色
				if ((*tree)->color == 0)
				{
					(*tree)->color = 1;
				}
				return;
			}
			flag = flag->right;
		}
		else
		{
			cout<<"插入了相同的值,无效"<<endl;
			free(node);
			node = NULL;
			return;
		}
	}

}

RedBlackTree* CreateRBT(int* arr, int nlength)
{
	if (arr == NULL || nlength <= 0)return NULL;
	RedBlackTree* tree = NULL;
	for (int i = 0; i < nlength; i++)
	{
		AddNode(&tree, arr[i]);
	}
	return tree;
}

void InorderTraversal(RedBlackTree* tree)
{
	if (tree == NULL) return;
	InorderTraversal(tree->left);
	printf("%d", tree->val);
	if (tree->color == 0)
	{
		printf("红色 ");
	}
	else
	{
		printf("黑色 ");
	}
	InorderTraversal(tree->right);
}


void DelRedNode(RedBlackTree** pFather, RedBlackTree** pDel)
{
	if ((*pDel) == (*pFather)->left)
	{
		(*pFather)->left = NULL;
		(*pDel)->father = NULL;
		free((*pDel));
		(*pDel) = NULL;
	}
	else
	{
		(*pFather)->right = NULL;
		(*pDel)->father = NULL;
		free((*pDel));
		(*pDel) = NULL;
	}
}


void DelBlackNode(RedBlackTree** pFather, RedBlackTree** pDel,RedBlackTree** pChild)
{
	if ((*pDel) == (*pFather)->left)
	{
		(*pFather)->left = (*pChild);
		(*pDel)->father = NULL;
		(*pChild)->father = (*pFather);
		free((*pDel));
		(*pDel) = NULL;
	}
	else
	{
		(*pFather)->right = (*pChild);
		(*pDel)->father = NULL;
		(*pChild)->father = (*pFather);
		free((*pDel));
		(*pDel) = NULL;
	}
}

void RBTDelete(RedBlackTree** tree, int value)
{
	RedBlackTree* pDel = NULL;
	RedBlackTree* pFather = NULL;
	RedBlackTree* pBrother = NULL;
	RedBlackTree* pMark = NULL;
	//找到要删除的节点
	RBTSearch((*tree), &pDel, &pFather, value);
	if (pDel == NULL)return;
	pMark = pDel;
	//1.判断是不是有两个的孩子
	if (pDel->left && pDel->right)
	{
		//以左子树最大值的孩子为删除节点进行删除
		pFather = pDel;
		pDel = pDel->left;
		while (pDel->right)
		{
			pFather = pDel;
			pDel = pDel->right;
			//pDel->father = pFather;

		}
		pMark->val = pDel->val;

	}
	
	//此时只有单个节点了
	//2.判断是不是根节点
	if (pFather == NULL)
	{
		//查看有没有孩子

		//如果有一个孩子
		if (pDel->left || pDel->right)
		{
			if (pDel->left)
			{
				pDel->left->color = 1;
				pDel->left->father = NULL;
				(*tree) = pDel->left;
				free(pDel);
				pDel = NULL;
				return;
			}
			else
			{
				pDel->right->color = 1;
				pDel->right->father = NULL;
				(*tree) = pDel->right;
				free(pDel);
				pDel = NULL;
				return;
			}
		}
		//如果没有孩子
		else if (pDel->left == NULL && pDel->right == NULL)
		{
			free((*tree));
			(*tree) = NULL;
			return;
		}

	}
	//不是根节点
	//3.查看被删除的颜色,红色直接删
	if (pDel->color == 0)
	{
		DelRedNode(&pFather, &pDel);
		return;
	}
	//4.如果是黑色则查看有没有孩子
	if (pDel->color == 1)
	{
		//仅有一个孩子,必定是红孩子
		if (pDel->left || pDel->right)
		{
			if (pDel->left)
			{
				pDel->left->color = 1;
				DelBlackNode(&pFather, &pDel, &(pDel->left));
				return;
			}
			else
			{
				pDel->right->color = 1;
				DelBlackNode(&pFather, &pDel, &(pDel->right));
				return;
			}
		}
		//5.没有孩子
		else
		{
			//获得兄弟节点
			if (pFather)
			{
				if (pDel == pFather->left)pBrother = pFather->right;
				else pBrother = pFather->left;
			}
			//先删除再进行颜色改变
			DelRedNode(&pFather, &pDel);
			while (1)
			{
				//查看兄弟的颜色
				if (pBrother && pBrother->color == 0)
				{
					pFather->color = 0;
					pBrother->color = 1;
					if (pBrother == pFather->left)
					{
						RedBlackTreeRightRotate(&pFather);
						//旋转之后兄弟的位置会改变
						pBrother = pFather->left;
					}
					else
					{
						RedBlackTreeLeftRotate(&pFather);
						pBrother = pFather->right;
					}
				}
				//兄弟是黑色
				else
				{

					//左侄子红,右侄子黑(空)
					if (pBrother->left && pBrother->left->color == 0 && (pBrother->right == NULL || pBrother->right->color == 1))
					{
						//看兄弟方向
						if (pBrother == pFather->right)
						{
							pBrother->color = 0;
							pBrother->left->color = 1;
							RedBlackTreeRightRotate(&pBrother);
							pBrother = pFather->right;
						}
						else
						{
							pBrother->color = pFather->color;
							pFather->color = 1;
							pBrother->left->color = 1;
							RedBlackTreeRightRotate(&pFather);
							break;
						}
					}
					//上面的情况弄完可以出现下面的情况，同样下面的情况弄完可以出现上面的情况(只能再走一次循环了)
					//右侄子红
					else if (pBrother->right && pBrother->right->color == 0)
					{
						//看兄弟方向
						if (pBrother == pFather->left)
						{
							pBrother->color = 0;
							pBrother->right->color = 1;
							RedBlackTreeLeftRotate(&pBrother);
							pBrother = pFather->left;
						}
						else
						{
							pBrother->color = pFather->color;
							pFather->color = 1;
							pBrother->right->color = 1;
							RedBlackTreeLeftRotate(&pFather);
							break;
						}
					}
					//全黑情况
					else if ((pBrother->left == NULL && pBrother->right == NULL) || (pBrother->left&&pBrother->left->color == 1 &&pBrother->right&&pBrother->right->color == 1))
					{
						//父亲为红
						if (pFather->color == 0)
						{
							pFather->color = 1;
							pBrother->color = 0;
							break;
						}
						//父亲为黑
						if (pFather->color == 1)
						{
							pBrother->color = 0;
							pDel = pFather;
							pFather = pDel->father;
							//如果是根了,就结束了
							if (pFather == NULL)
							{
								break;
							}
							if (pFather)
							{
								if (pDel == pFather->left)pBrother = pFather->right;
								else pBrother = pFather->left;
							}
						}
					}
				}
			}
		}
	}
	//找到根节点
	while ((*tree)->father)
	{
		(*tree) = (*tree)->father;
	}
}

int main()
{
	RedBlackTree* tree = NULL;
	int arr[] = { 20,11,40,4,15,30,55,13,18,25,38,48,62,12,50};
	tree = CreateRBT(arr, sizeof(arr) / sizeof(arr[0]));
	PushFirst(tree);
	cout << endl;
	//RBTDelete(&tree,4);
	//InorderTraversal(tree);
	//cout << endl;
	//RBTDelete(&tree,62);
	//InorderTraversal(tree);
	//cout << endl;
	//RBTDelete(&tree, 40);
	//InorderTraversal(tree);
	//cout << endl;
	//RBTDelete(&tree, 13);
	//InorderTraversal(tree);
	//cout << endl;
	//RBTDelete(&tree, 20);
	//InorderTraversal(tree);
	//cout << endl;
	//RBTDelete(&tree, 13);
	//InorderTraversal(tree);
	//cout << endl;
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		RBTDelete(&tree, arr[i]);
		PushFirst(tree);
		cout << endl;
	}
	return 0;
}