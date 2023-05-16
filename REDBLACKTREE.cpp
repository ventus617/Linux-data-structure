#include<iostream>
#include<queue>
using namespace std;

typedef struct node
{
	struct node* left;
	struct node* right;
	struct node* father;
	int val;
	int color;//0��1��
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
			cout << q1.front()->val<<"��ɫ"<<" ";
		}
		else
		{
			cout << q1.front()->val << "��ɫ" << " ";
		}
		q1.pop();

	}
}

//����
void RedBlackTreeRightRotate(RedBlackTree** node)
{
	if ((*node) == NULL || (*node)->left == NULL)return;
	//�õ��ڶ���ĺ���
	RedBlackTree* Flag = (*node)->left;

	//��������
	(*node)->left = Flag->right;
	Flag->right = (*node);
	//��
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
	//��������
	if ((*node)->left!= NULL)
	{
		(*node)->left->father = (*node);
	}
	Flag->father = (*node)->father;
	(*node)->father = Flag;
	//���ص��ǵ�ǰ�޸ĵ����
	//(*node) = Flag;
}

//����
void RedBlackTreeLeftRotate(RedBlackTree** tree)
{
	if ((*tree) == NULL || (*tree)->right == NULL)return;
	RedBlackTree* Flag = (*tree)->right;
	//��������
	(*tree)->right = Flag->left;
	Flag->left = (*tree);
	//��
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
	//��������
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


//�����ף�������
RedBlackTree* GetUncle(RedBlackTree* node)
{
	if (node == node->father->left)
		return node->father->right;
	else
		return node->father->left;
}

//�Ż���ɫ�ı�
void ChangeRBTColor(RedBlackTree** tree)
{
	//������ɫ�Ǻ�ɫ
	if ((*tree)->father == NULL || (*tree)->father->color == 1)return;
	//����
	RedBlackTree* Uncle = NULL;
	//үү
	RedBlackTree* Grandfather = NULL;
	//����
	RedBlackTree* Father = (*tree)->father;
	while ((*tree)->father != NULL && (*tree)->father->color == 0)
	{
		Uncle = GetUncle(Father);
		Grandfather = Father->father;
		//������
		if (Uncle != NULL && Uncle->color == 0)
		{
			Uncle->color = 1;
			Father->color = 1;
			Grandfather->color = 0;
			(*tree) = Grandfather;
			Father = (*tree)->father;
			//�����ʱ�����ڵ��Ǹ�
			if (Father == NULL)
			{
				(*tree)->color = 1;
				break;
			}
			continue;
		}
		//�����ɫ
		if (Uncle == NULL || Uncle->color == 1)
		{
			//������үү����
			if (Father == Grandfather->left)
			{
				//��ǰ�ڵ��Ǹ��׵��Ҳ�
				if ((*tree) == Father->right)
				{
					(*tree) = Father;
					RedBlackTreeLeftRotate(tree);
					//��ʱ��ת�����Ҳ����
					Father = (*tree)->father;
				}
				//��ǰ�ڵ��Ǹ��׵���
				if ((*tree) == Father->left)
				{
					Father->color =1;
					Grandfather->color = 0;
					RedBlackTreeRightRotate(&Grandfather);
					break;
				}
			}
			//������үү���Ҳ�
			else
			{
				//��ǰ�ڵ��Ǹ��׵���
				if ((*tree) == Father->left)
				{
					(*tree) = Father;
					RedBlackTreeRightRotate(tree);
					Father = (*tree)->father;
				}
				//��ǰ�ڵ��Ǹ��׵��Ҳ�
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

//RBT���Ĳ�������ɫƽ��
void ChangeColor(RedBlackTree** tree)
{
	//������ɫ�Ǻ�ɫ
	if ((*tree)->father == NULL||(*tree)->father->color == 1)return;
	//���������ɫ�Ǻ�ɫ
	while ((*tree)->father != NULL&&(*tree)->father->color == 0)
	{
		//�鿴������ɫ
		if ((*tree)->father == (*tree)->father->father->left)
		{
			//����Ǻ�ɫ
			if ((*tree)->father->father->right != NULL&&(*tree)->father->father->right->color == 0)
			{
				//���׺�������,үү���
				(*tree)->father->color = 1;
				(*tree)->father->father->right->color = 1;
				(*tree)->father->father->color =0;
				(*tree) = (*tree)->father->father;
				continue;
			}
			//����Ǻ�ɫ
			else if((*tree)->father->father->right == NULL||(*tree)->father->father->right->color == 1)
			{
				//���������үү���Һ���
				if ((*tree)->father == (*tree)->father->father->right)
				{
					//�����ǵ��Ǹ��׵���ڵ�
					if ((*tree) == (*tree)->father->left)
					{
						//��ǵ�Z�ĸ���Ϊ�µı�ǵ�
						(*tree) = (*tree)->father;
						//����
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
				//������үү������
				else
				{
					//�����ǵ��Ǹ��׵��ҽڵ�
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
			//����Ǻ�ɫ
			if ((*tree)->father->father->left != NULL&&(*tree)->father->father->left->color == 0 )
			{
				//���׺�������,үү���
				(*tree)->father->color = 1;
				(*tree)->father->father->left->color = 1;
				(*tree)->father->father->color = 0;
				(*tree) = (*tree)->father->father;
				continue;
			}
			else if((*tree)->father->father->left == NULL||(*tree)->father->father->left->color == 1 )
			{
				//���������үү���Һ���
				if ((*tree)->father == (*tree)->father->father->right)
				{
					//�����ǵ��Ǹ��׵���ڵ�
					if ((*tree) == (*tree)->father->left)
					{
						//��ǵ�Z�ĸ���Ϊ�µı�ǵ�
						(*tree) = (*tree)->father;
						//����
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
				//������үү������
				else
				{
					//�����ǵ��Ǹ��׵��ҽڵ�
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
	//����Ĭ�Ͻڵ�
	RedBlackTree* node = (RedBlackTree*)malloc(sizeof(RedBlackTree));
	node->color = 0;
	node->val = value;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	//���Ҳ����
	//���Ϊ��
	if ((*tree) == NULL)
	{
		node->color = 1;
		(*tree) = node;
		return;
	}
	//��Ϊ��
	RedBlackTree* flag = (*tree);
	while (flag)
	{
		//����ʱ,����������
		if (flag->val > node->val)
		{
			if (flag->left == NULL)
			{
				flag->left = node;
				node->father = flag;
				//��Ҫ���б��
				ChangeRBTColor(&node);
				//������ɺ��õ�ǰ�ĸ��ڵ�
				while ((*tree)->father != NULL)
				{
					(*tree) = (*tree)->father;
				}
				//������ɺ������ǰ���ڵ��Ǻ�ɫ���ĳɺ�ɫ
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
				//������ɺ��õ�ǰ�ĸ��ڵ�
				while ((*tree)->father != NULL)
				{
					(*tree) = (*tree)->father;
				}
				//������ɺ������ǰ���ڵ��Ǻ�ɫ���ĳɺ�ɫ
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
			cout<<"��������ͬ��ֵ,��Ч"<<endl;
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
		printf("��ɫ ");
	}
	else
	{
		printf("��ɫ ");
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
	//�ҵ�Ҫɾ���Ľڵ�
	RBTSearch((*tree), &pDel, &pFather, value);
	if (pDel == NULL)return;
	pMark = pDel;
	//1.�ж��ǲ����������ĺ���
	if (pDel->left && pDel->right)
	{
		//�����������ֵ�ĺ���Ϊɾ���ڵ����ɾ��
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
	
	//��ʱֻ�е����ڵ���
	//2.�ж��ǲ��Ǹ��ڵ�
	if (pFather == NULL)
	{
		//�鿴��û�к���

		//�����һ������
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
		//���û�к���
		else if (pDel->left == NULL && pDel->right == NULL)
		{
			free((*tree));
			(*tree) = NULL;
			return;
		}

	}
	//���Ǹ��ڵ�
	//3.�鿴��ɾ������ɫ,��ɫֱ��ɾ
	if (pDel->color == 0)
	{
		DelRedNode(&pFather, &pDel);
		return;
	}
	//4.����Ǻ�ɫ��鿴��û�к���
	if (pDel->color == 1)
	{
		//����һ������,�ض��Ǻ캢��
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
		//5.û�к���
		else
		{
			//����ֵܽڵ�
			if (pFather)
			{
				if (pDel == pFather->left)pBrother = pFather->right;
				else pBrother = pFather->left;
			}
			//��ɾ���ٽ�����ɫ�ı�
			DelRedNode(&pFather, &pDel);
			while (1)
			{
				//�鿴�ֵܵ���ɫ
				if (pBrother && pBrother->color == 0)
				{
					pFather->color = 0;
					pBrother->color = 1;
					if (pBrother == pFather->left)
					{
						RedBlackTreeRightRotate(&pFather);
						//��ת֮���ֵܵ�λ�û�ı�
						pBrother = pFather->left;
					}
					else
					{
						RedBlackTreeLeftRotate(&pFather);
						pBrother = pFather->right;
					}
				}
				//�ֵ��Ǻ�ɫ
				else
				{

					//��ֶ�Ӻ�,��ֶ�Ӻ�(��)
					if (pBrother->left && pBrother->left->color == 0 && (pBrother->right == NULL || pBrother->right->color == 1))
					{
						//���ֵܷ���
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
					//��������Ū����Գ�������������ͬ����������Ū����Գ�����������(ֻ������һ��ѭ����)
					//��ֶ�Ӻ�
					else if (pBrother->right && pBrother->right->color == 0)
					{
						//���ֵܷ���
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
					//ȫ�����
					else if ((pBrother->left == NULL && pBrother->right == NULL) || (pBrother->left&&pBrother->left->color == 1 &&pBrother->right&&pBrother->right->color == 1))
					{
						//����Ϊ��
						if (pFather->color == 0)
						{
							pFather->color = 1;
							pBrother->color = 0;
							break;
						}
						//����Ϊ��
						if (pFather->color == 1)
						{
							pBrother->color = 0;
							pDel = pFather;
							pFather = pDel->father;
							//����Ǹ���,�ͽ�����
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
	//�ҵ����ڵ�
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