#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
unsigned int fibonacci1(unsigned int num);
unsigned int fibonacci2(unsigned int num);
int main(void)
{
	unsigned int num = 0;
	while (1) {
		cout << "����������֪��fibonacci���еĵ�n����:" << endl;
		cin >> num;
		num = fibonacci2(num);
		cout << "�õ���fibonacci��Ϊ��" << num << endl;
	}
	return 0;
}
//�����������̫�󣬼�����̫�󣬼��㳬ʱ ����50 ���ô������ƿ�����2^50-1������
unsigned int fibonacci1(unsigned int num) {
	if (num == 0)return 0;
	if (num == 1||num==2) {
		return 1;
	}
	int a = fibonacci1(num - 1) + fibonacci1(num - 2);
	return a;
}
//�����ڵݹ�����У��洢һ�¼������ֵ

//�Ż�fibonacci�����ԵĴ���ʽ������������һ��ֵ����ǰ����ֵ�Ľ������С�����㣬����ÿһ�εĽ��
unsigned int fibonacci2(unsigned int num) {
	if (num == 0)return 0;
	if (num == 1 || num == 2)return 1;
	unsigned int Numi = 0;//��f(i)�Ľ��
	unsigned int Numi1 = 1;//fibonacci��һ�������Լ������Ӻ���f(i-2)�Ľ��
	unsigned int Numi2 = 1;//fibonacci�ڶ��������Լ������Ӻ���f(i-1)�Ľ��
	//���ڵ�һ���͵�һ�������Ѿ��г�ֵ�ˣ����Դӵڶ�������ʼ,�����Ҫnum-2��
	for (unsigned int i = 2; i < num; i++) {
		Numi = Numi1 + Numi2;
		Numi1 = Numi2;
		Numi2 = Numi;
	}
	return Numi;
}
//��ѧ�ⷨ ���󷽷�