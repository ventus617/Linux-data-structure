#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;


//青蛙每次跳1或者2个台阶，一共有n个台阶，问有多少种跳法
//跳了1级或者2级后，就剩下n-1或者n-2 所以n阶台阶就是(n-1)+(n-2)阶台阶的跳法
//n-1阶台阶又分成（n-1）-1 和（n-1）-2种跳法...
//f(n)=f(n-1)+f(n-2);

//终止时，就是剩1阶和剩2阶，那么此时就f(1)=1,f(2)=2，剩2阶就有一次性跳两阶，或者一次性1阶1阶跳的方式，就有2种方式

unsigned int JumpFrog(unsigned int num) {
	//接取每一次新的值f(n)
	int Numi = 0;
	//接取第一次的值和f(n-1)
	int Num1 = 2;
	//接取第二次的值和f(n-2)
	int Num2 = 1;
	if (num == 0)return 0;
	if (num <= 2)return num;
	//num-2 因为第一次和第二次的值是标志值，所以剩下仅需要计算num-2次
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
	cout << "请输入青蛙所跳的台阶数"<<endl;
	cin >> num;
	cout << "青蛙一共有" << JumpFrog(num) << "种跳法" << endl;
	return 0;
}
