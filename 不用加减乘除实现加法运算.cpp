#include<iostream>
using namespace std;

//得到a+b需要进位的位，即a&b,那么这几位都会左移，继续产生加法
//得到a+b的结果中不需要进位的位，即a^b，那么这几位会和需要进位的位产生二次运算(二次加法)
//也就是说，如果计算到没有需要进位的位的时候，这时a+b的值就是a^b
 int Addnum( int num1,  int num2) {
	 int temp = 0;//用中间值来接一下^前的结果
	 int And = num1;//来接取&的结果
	 int Xor = num2;//来接取^的结果
	 while (And ^ 0) {
		 temp = Xor;
		 Xor = And ^ Xor;
		 And = And & temp;
		 And <<= 1;
	 }
	 return Xor;
}

 //不用中间值来接取
 int Addnum2(int num1, int num2) {
	 int And = num1;//来接取&的结果
	 int Xor = num2;//来接取^的结果
	 while (And ^ 0) {
		 Xor = num1 ^ num2;
		 And = num1 & num2;
		 And <<= 1;
		 num1 = And;
		 num2 = Xor;
	 }
	 return Xor;
 }

 int main(void)
 {
	 int num1 = 0;
	 int num2 = 0;
	 cin >> num1>>num2;
	 cout << num1 << " + " << num2 << " = " << Addnum2(num1, num2);
	 return 0;
 }