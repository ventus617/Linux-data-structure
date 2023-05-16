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
		cout << "������ƥ��Ķ���:";
		int VeticalA;
		int VeticalB;
		cin >> VeticalA;
		cin >> VeticalB;
		//����ĵ��ڷ�Χ�ڣ�����ĵ㲻����ͬ������ĵ�ԭ�Ȳ�����ֵ
		if (VeticalA >= 1 && VeticalA <= Tu->Vetical && VeticalB >= 1 && VeticalB <= Tu->Vetical && Tu->arr[VeticalA-1][VeticalB-1] == 0 && Tu->arr[VeticalB-1][VeticalA-1] == 0 && VeticalA != VeticalB)
		{
			//��Ϊ������ͼ����Գ�λ�ö�Ҫ��ֵ
			Tu->arr[VeticalA - 1][VeticalB - 1] = 1;
			Tu->arr[VeticalB - 1][VeticalA - 1] = 1;
			MyEss--;
		}
		else
		{
			cout << "����ʧ��" << endl;
		}
	}
}
Matrix* CreateMatrix()
{
	cout << "�����붥������ͱ���:";
	int nEdg = 0;
	int Vertical = 0;
	cin >> Vertical;
	cin >> nEdg;
	//������ά����
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
	//�����
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

//�����������

void MyDFS(Matrix* Tu, int begin, int* arr)
{
	//begin�ǲ����ĵڼ�������

//����������к���i-1
	int i = begin - 1;
	//���û����ǣ��ʹ�ӡ���ұ��,��ǹ��˾Ͳ�����
	if (arr[i] == 0)
	{
		cout << i + 1 << " ";
		arr[i] = 1;
	}
	//�ҵ���δ����� �� �ھӽڵ㣬��ǹ��˾Ͳ�����

	for (int j = 0; j < Tu->Vetical; j++)
	{
		//j+1����Ϊ�����ھӽڵ������1 �����ڵ�0��
		if (arr[j] == 0 && Tu->arr[i][j] == 1)MyDFS(Tu, j + 1, arr);

		//����ݹ�û����ֹ��������Ϊ��ֹ������ʽ����ѭ���У���j=Tu->Vetical�����
	}
}

void DFS(Matrix* Tu)
{
	int begin;
	cout << "������Ҫ���ĸ����㿪ʼDFS������";
	cin >> begin;
	//�����������
	if (Tu == NULL || begin<1 || begin>Tu->Vetical)return;
	int* arr = (int*)malloc(sizeof(int) * Tu->Vetical);
	memset(arr, 0, sizeof(int) * Tu->Vetical);
	MyDFS(Tu, begin, arr);
	cout << endl;
	//������ɺ��ͷŵ������鼴��
	free(arr);
	arr = NULL;
}

void MyBFS(Matrix* Tu, int*arr, queue<int>& q1)
{
	//����
	//1.��ʼ��ӣ���ʼ���
	//2.ȡ�����״���Ķ��㣬�ö����Ӧ����ȫ����0������ӣ����ұ��
	while (q1.size() > 0)
	{
		//ÿ�εõ�����
		int begin = q1.front();
		//���д���
		cout << q1.front() << " ";
		q1.pop();

		for (int i = 0; i < Tu->Vetical; i++)
		{
			//��ǵ��Ƕ���
			
			//�������û����ǲ��Ҵ��ڶ�Ӧ�ı߹�ϵ ��ô��� 
			if (Tu->arr[begin - 1][i] == 1 && arr[i] == 0)
			{
				//��Ӻ��ǣ�����1 iΪ0 ����2 iΪ1....
				q1.push(i+1);
				arr[i] = 1;

			}
		}
	}

}

void BFS(Matrix* Tu)
{
	int begin;
	cout << "������Ҫ���ĸ����㿪ʼBFS����:";
	cin >> begin;
	if (Tu == NULL || begin<1 || begin>Tu->Vetical)return;
	//�����������
	int* arr = (int*)malloc(sizeof(int) * Tu->Vetical);
	memset(arr, 0, sizeof(int) * Tu->Vetical);
	//������������
	queue<int>q1;
	//����
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


