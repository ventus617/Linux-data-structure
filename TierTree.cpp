#include<iostream>
using namespace std;

typedef struct TireNode
{
	//是没有字符的，即使有也是隐式显示在指针数组的下标里面的(作为key值进行查找的)
	struct TireNode* node[26];//指向下一个节点的指针数组，下标就是字符的散列函数
	int count;//计数位
	char *str;
}TireTree;

TireTree* GetNode()
{
	TireTree* MyTireTree = (TireTree*)malloc(sizeof(TireTree));
	memset(MyTireTree, 0, sizeof(TireTree));
	return MyTireTree;
}

void InsertTireTree(TireTree* Tree, const char* arr)
{
	if (Tree == NULL || arr == NULL)return;
	int len = strlen(arr);
	int i = 0;
	//根据字符串的长度来插入，即取出字符串中每一位的字符来插
	while (i<len)
	{
		//如果对应的节点中找到该字符的位置后没有节点则创建
		if (Tree->node[arr[i] - 97] == NULL)
		{
			Tree->node[arr[i] - 97] = GetNode();
		}
		//找到节点则继续下一个字符
		Tree = Tree->node[arr[i] - 97];
		i++;
	}
	//最终记得设置末尾标记位
	Tree->count++;
	Tree->str = (char*)arr;

}

TireTree* CreateTireTree(int nLength,const char**str)
{
	if (str == NULL || nLength <= 0)return NULL;
	//根节点
	TireTree *pTree= GetNode();
	//放入树中
	for (int i = 0; i < nLength; i++)
	{
		InsertTireTree(pTree, str[i]);
	}
	return pTree;
}


void PreOrder(TireTree* Tree)
{
	if (Tree == NULL)return;
	if (Tree->count != 0)
	{
		printf("%s\n", Tree->str);
	}
	//遍历它的孩子
	for (int i = 0; i < 26; i++)
	{
		PreOrder(Tree->node[i]);
	}

}

void FindOne(TireTree* Tree,const char* str)
{
	if (Tree == NULL)return;
	int i = 0;
	int len = strlen(str);
	while (i < len)
	{
		//如果没找到对应的节点就返回
		if (Tree->node[str[i] - 97] == NULL)
		{
			printf("404 not found\n");
			return;
		}
		else
		{
			//找到就继续找下一个字符的
			Tree = Tree->node[str[i] - 97];
			i++;
		}
	}
	//如果全都找到之后，查看是不是存在末尾标记，存在则代表该字符串存在
	if (Tree->count != 0)
	{
		printf("find it %s !\n", Tree->str);
	}
	else
	{
		printf("not found 404!\n");
	}
}

int main()
{
	const char* str[] = { "beautiful","accept","socket","connect","listen","bind","boy","girl","child"};
	TireTree* tree = CreateTireTree(9, str);
	PreOrder(tree);
	FindOne(tree, "accept");
	return 0;
}