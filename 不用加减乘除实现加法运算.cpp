#include<iostream>
using namespace std;

//�õ�a+b��Ҫ��λ��λ����a&b,��ô�⼸λ�������ƣ����������ӷ�
//�õ�a+b�Ľ���в���Ҫ��λ��λ����a^b����ô�⼸λ�����Ҫ��λ��λ������������(���μӷ�)
//Ҳ����˵��������㵽û����Ҫ��λ��λ��ʱ����ʱa+b��ֵ����a^b
 int Addnum( int num1,  int num2) {
	 int temp = 0;//���м�ֵ����һ��^ǰ�Ľ��
	 int And = num1;//����ȡ&�Ľ��
	 int Xor = num2;//����ȡ^�Ľ��
	 while (And ^ 0) {
		 temp = Xor;
		 Xor = And ^ Xor;
		 And = And & temp;
		 And <<= 1;
	 }
	 return Xor;
}

 //�����м�ֵ����ȡ
 int Addnum2(int num1, int num2) {
	 int And = num1;//����ȡ&�Ľ��
	 int Xor = num2;//����ȡ^�Ľ��
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