#include<iostream>
#include<queue>
using namespace std;



typedef struct node
{
	int** arr;
	int Vetical;
	int Ess;
}Matrix;

void Insert(Matrix* Tu)
{
	int MyEss;
	MyEss = Tu->Ess;
	while (MyEss)
	{
		cout << "请输入匹配的顶点:";
		int VeticalA;
		int VeticalB;
		cin >> VeticalA;
		cin >> VeticalB;
		//输入的点在范围内，输入的点不能相同，输入的点原先不能有值
		if (VeticalA >= 1 && VeticalA <= Tu->Vetical && VeticalB >= 1 && VeticalB <= Tu->Vetical && Tu->arr[VeticalA-1][VeticalB-1] == 0 && Tu->arr[VeticalB-1][VeticalA-1] == 0 && VeticalA != VeticalB)
		{
			//因为是无向图，则对称位置都要赋值
			Tu->arr[VeticalA - 1][VeticalB - 1] = 1;
			Tu->arr[VeticalB - 1][VeticalA - 1] = 1;
			MyEss--;
		}
		else
		{
			cout << "插入失败" << endl;
		}
	}
}
Matrix* CreateMatrix()
{
	cout << "请输入顶点个数和边数:";
	int nEdg = 0;
	int Vertical = 0;
	cin >> Vertical;
	cin >> nEdg;
	//创建二维数组
	Matrix* Tu = (Matrix*)malloc(sizeof(Matrix));
	memset(Tu, 0, sizeof(Matrix));
	Tu->arr = (int**)malloc(sizeof(int*) * Vertical);
	for (int i = 0; i < Vertical; i++)
	{
		Tu->arr[i] = (int*)malloc(sizeof(int) * Vertical);
		memset(Tu->arr[i], 0, sizeof(int) * Vertical);
	}
	Tu->Vetical = Vertical;
	Tu->Ess = nEdg;
	//插入边
	Insert(Tu);
	return Tu;
}



void Show(Matrix* Tu)
{
	int num = Tu->Vetical;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			cout << Tu->arr[i][j] << " ";
		}
		cout << endl;
	}
}

//深度优先搜索

void MyDFS(Matrix* Tu, int begin, int* arr)
{
	//begin是操作的第几个顶点

//操作顶点的行号是i-1
	int i = begin - 1;
	//如果没被标记，就打印并且标记,标记过了就不操作
	if (arr[i] == 0)
	{
		cout << i + 1 << " ";
		arr[i] = 1;
	}
	//找到其未被标记 的 邻居节点，标记过了就不操作

	for (int j = 0; j < Tu->Vetical; j++)
	{
		//j+1是因为传的邻居节点如果是1 它则在第0行
		if (arr[j] == 0 && Tu->arr[i][j] == 1)MyDFS(Tu, j + 1, arr);

		//该项递归没有终止条件，因为终止条件隐式的在循环中，即j=Tu->Vetical则结束
	}
}

void DFS(Matrix* Tu)
{
	int begin;
	cout << "请输入要从哪个顶点开始DFS遍历：";
	cin >> begin;
	//创建标记数组
	if (Tu == NULL || begin<1 || begin>Tu->Vetical)return;
	int* arr = (int*)malloc(sizeof(int) * Tu->Vetical);
	memset(arr, 0, sizeof(int) * Tu->Vetical);
	MyDFS(Tu, begin, arr);
	cout << endl;
	//遍历完成后释放掉该数组即可
	free(arr);
	arr = NULL;
}

void MyBFS(Matrix* Tu, int*arr, queue<int>& q1)
{
	//遍历
	//1.起始入队，开始标记
	//2.取出队首代表的顶点，该顶点对应的行全部非0的列入队，并且标记
	while (q1.size() > 0)
	{
		//每次得到队首
		int begin = q1.front();
		//进行处理
		cout << q1.front() << " ";
		q1.pop();

		for (int i = 0; i < Tu->Vetical; i++)
		{
			//标记的是顶点
			
			//如果顶点没被标记并且存在对应的边关系 那么入队 
			if (Tu->arr[begin - 1][i] == 1 && arr[i] == 0)
			{
				//入队后标记，顶点1 i为0 顶点2 i为1....
				q1.push(i+1);
				arr[i] = 1;

			}
		}
	}

}

void BFS(Matrix* Tu)
{
	int begin;
	cout << "请输入要从哪个顶点开始BFS遍历:";
	cin >> begin;
	if (Tu == NULL || begin<1 || begin>Tu->Vetical)return;
	//创建标记数组
	int* arr = (int*)malloc(sizeof(int) * Tu->Vetical);
	memset(arr, 0, sizeof(int) * Tu->Vetical);
	//创建遍历队列
	queue<int>q1;
	//处理
	arr[begin - 1] = 1;
	q1.push(begin);
	MyBFS(Tu, arr,q1);

	cout << endl;
	free(arr);
	arr = NULL;

}


int main()
{
	Matrix* Tu = NULL;
	Tu = CreateMatrix();
	//DFS(Tu);
	BFS(Tu);
	return 0;
}


