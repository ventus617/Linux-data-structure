#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;


//����ÿ����1����2��̨�ף�һ����n��̨�ף����ж���������
//����1������2���󣬾�ʣ��n-1����n-2 ����n��̨�׾���(n-1)+(n-2)��̨�׵�����
//n-1��̨���ֳַɣ�n-1��-1 �ͣ�n-1��-2������...
//f(n)=f(n-1)+f(n-2);

//��ֹʱ������ʣ1�׺�ʣ2�ף���ô��ʱ��f(1)=1,f(2)=2��ʣ2�׾���һ���������ף�����һ����1��1�����ķ�ʽ������2�ַ�ʽ

unsigned int JumpFrog(unsigned int num) {
	//��ȡÿһ���µ�ֵf(n)
	int Numi = 0;
	//��ȡ��һ�ε�ֵ��f(n-1)
	int Num1 = 2;
	//��ȡ�ڶ��ε�ֵ��f(n-2)
	int Num2 = 1;
	if (num == 0)return 0;
	if (num <= 2)return num;
	//num-2 ��Ϊ��һ�κ͵ڶ��ε�ֵ�Ǳ�־ֵ������ʣ�½���Ҫ����num-2��
	for (int i = 0; i < (num - 2); i += 1) {
		Numi = Num1 + Num2;
		Num2 = Num1;
		Num1 = Numi;
	}
	return Numi;
}


int main()
{
	unsigned int num = 0;
	cout << "����������������̨����"<<endl;
	cin >> num;
	cout << "����һ����" << JumpFrog(num) << "������" << endl;
	return 0;
}
