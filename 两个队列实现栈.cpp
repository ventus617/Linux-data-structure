#include<iostream>
#include<queue>
using namespace std;

void MyPush(queue<int>& q1, queue<int>& q2, int num)
{
	//�ҵ��ǿյ�,���뵽���У�������գ��Ͳ��뵽q1
	if (q1.empty()&&q2.empty())
	{
		q1.push(num);
	}
	else if (!q2.empty())
	{
		q2.push(num);
	}
	else if (!q1.empty())
	{
		q1.push(num);
	}
}

void MyPop(queue<int>& q1, queue<int>& q2)
{
	int temp;
	//���û��Ԫ�أ���ֱ�ӽ���
	if (q1.empty() && q2.empty())
	{
		cout << "û��Ԫ��,��ջʧ��" << endl;
		return;
	}
	//�ҵ��ǿյ��Ǹ����У���Ԫ��һֱ������һ�������У�ֱ��ֻʣһ��Ԫ�أ���Ԫ�ؾ���ջ��Ԫ��
	if (!q1.empty())
	{
		while (q1.size() - 1 != 0)
		{
			temp = q1.front();
			q1.pop();
			q2.push(temp);
		}
		temp = q1.front();
		q1.pop();
		cout << temp << endl;
	}
	else if (!q2.empty())
	{
		while (q2.size() - 1 != 0)
		{
			temp = q2.front();
			q2.pop();
			q1.push(temp);
		}
		temp = q2.front();
		q2.pop();
		cout << temp << endl;
	}
}

int main()
{
	queue<int>q1;
	queue<int>q2;
	MyPush(q1, q2, 1);
	MyPush(q1, q2, 2);
	MyPush(q1, q2, 3);
	MyPush(q1, q2, 4);
	MyPop(q1, q2);
	MyPop(q1, q2);
	MyPop(q1, q2);
	MyPop(q1, q2);
	MyPop(q1, q2);
	return 0;
}