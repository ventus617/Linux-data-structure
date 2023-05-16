#include<iostream>
#include<stack>
using namespace std;

void MyPush(stack<int>& s1, stack<int>& s2, int num)
{
	int temp;
	//ջ1����ȡ���֣����ջ2�ǿգ��Ƚ�ջ2�����ݵ���ջ1����������������
	while (!s2.empty())
	{
		temp = s2.top();
		s2.pop();
		s1.push(temp);
	}
 //����ջ1
	s1.push(num);
}

void MyPop(stack<int>& s1, stack<int>& s2)
{
	int temp;
	//�����ûԪ�أ���ֱ�ӽ���
	if (s1.empty() && s2.empty())
	{
		cout << "û��Ԫ�أ��޷���ջ" << endl;
		return;
	}
	//���ջ1��Ԫ��,���Ƚ�ջ1��Ԫ��ȫ������ջ2�У�����ջ2��Ԫ�أ����Ƕ��е���Ԫ��
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