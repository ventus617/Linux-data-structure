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
		cout << "请输入所想知的fibonacci数列的第n个数:" << endl;
		cin >> num;
		num = fibonacci2(num);
		cout << "得到的fibonacci数为：" << num << endl;
	}
	return 0;
}
//如果所求数据太大，计算量太大，计算超时 例如50 调用次数近似可以用2^50-1次来看
unsigned int fibonacci1(unsigned int num) {
	if (num == 0)return 0;
	if (num == 1||num==2) {
		return 1;
	}
	int a = fibonacci1(num - 1) + fibonacci1(num - 2);
	return a;
}
//或者在递归过程中，存储一下计算过的值

//优化fibonacci，线性的处理方式，即所需的最后一个值，是前两个值的结果，从小往大算，保存每一次的结果
unsigned int fibonacci2(unsigned int num) {
	if (num == 0)return 0;
	if (num == 1 || num == 2)return 1;
	unsigned int Numi = 0;//接f(i)的结果
	unsigned int Numi1 = 1;//fibonacci第一个数，以及拿来接后续f(i-2)的结果
	unsigned int Numi2 = 1;//fibonacci第二个数，以及拿来接后续f(i-1)的结果
	//由于第一个和第一个数字已经有初值了，所以从第二个数开始,因此需要num-2次
	for (unsigned int i = 2; i < num; i++) {
		Numi = Numi1 + Numi2;
		Numi1 = Numi2;
		Numi2 = Numi;
	}
	return Numi;
}
//数学解法 矩阵方法