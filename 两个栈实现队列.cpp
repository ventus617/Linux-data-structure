#include<iostream>
#include<stack>
using namespace std;

void MyPush(stack<int>& s1, stack<int>& s2, int num)
{
	int temp;
	//栈1来接取数字，如果栈2非空，先将栈2的数据导入栈1，保持数据完整性
	while (!s2.empty())
	{
		temp = s2.top();
		s2.pop();
		s1.push(temp);
	}
 //再入栈1
	s1.push(num);
}

void MyPop(stack<int>& s1, stack<int>& s2)
{
	int temp;
	//如果都没元素，就直接结束
	if (s1.empty() && s2.empty())
	{
		cout << "没有元素，无法出栈" << endl;
		return;
	}
	//如果栈1有元素,就先将栈1的元素全部导入栈2中，再由栈2出元素，就是队列的首元素
	while (!s1.empty())
	{
		temp = s1.top();
		s1.pop();
		s2.push(temp);
	}
	temp = s2.top();
	s2.pop();
	cout << temp << endl;
}

int main()
{
	stack<int>s1;
	stack<int>s2;
	MyPush(s1, s2, 1);
	MyPush(s1, s2, 2);
	MyPush(s1, s2, 3);
	MyPush(s1, s2, 4);
	MyPop(s1, s2);
	MyPop(s1, s2);
	MyPop(s1, s2);
	MyPop(s1, s2);
	MyPop(s1, s2);
	return 0;
}