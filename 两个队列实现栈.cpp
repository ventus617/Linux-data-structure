#include<iostream>
#include<queue>
using namespace std;

void MyPush(queue<int>& q1, queue<int>& q2, int num)
{
	//找到非空的,插入到其中，如果都空，就插入到q1
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
	//如果没有元素，就直接结束
	if (q1.empty() && q2.empty())
	{
		cout << "没有元素,出栈失败" << endl;
		return;
	}
	//找到非空的那个队列，把元素一直出到另一个队列中，直到只剩一个元素，该元素就是栈顶元素
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