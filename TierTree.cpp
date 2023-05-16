#include<iostream>
using namespace std;

typedef struct TireNode
{
	//��û���ַ��ģ���ʹ��Ҳ����ʽ��ʾ��ָ��������±������(��Ϊkeyֵ���в��ҵ�)
	struct TireNode* node[26];//ָ����һ���ڵ��ָ�����飬�±�����ַ���ɢ�к���
	int count;//����λ
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
	//�����ַ����ĳ��������룬��ȡ���ַ�����ÿһλ���ַ�����
	while (i<len)
	{
		//�����Ӧ�Ľڵ����ҵ����ַ���λ�ú�û�нڵ��򴴽�
		if (Tree->node[arr[i] - 97] == NULL)
		{
			Tree->node[arr[i] - 97] = GetNode();
		}
		//�ҵ��ڵ��������һ���ַ�
		Tree = Tree->node[arr[i] - 97];
		i++;
	}
	//���ռǵ�����ĩβ���λ
	Tree->count++;
	Tree->str = (char*)arr;

}

TireTree* CreateTireTree(int nLength,const char**str)
{
	if (str == NULL || nLength <= 0)return NULL;
	//���ڵ�
	TireTree *pTree= GetNode();
	//��������
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
	//�������ĺ���
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
		//���û�ҵ���Ӧ�Ľڵ�ͷ���
		if (Tree->node[str[i] - 97] == NULL)
		{
			printf("404 not found\n");
			return;
		}
		else
		{
			//�ҵ��ͼ�������һ���ַ���
			Tree = Tree->node[str[i] - 97];
			i++;
		}
	}
	//���ȫ���ҵ�֮�󣬲鿴�ǲ��Ǵ���ĩβ��ǣ������������ַ�������
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