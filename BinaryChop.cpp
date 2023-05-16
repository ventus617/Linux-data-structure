#include<iostream>
using namespace std;

int BinaryChop(int *arr,int len,int num) {
	if (arr == NULL)return -1;
	//中间值
	int Mid = 0;
	int Head = 0;
 //尾巴值不是数组长度,而是数组中最后一个元素的下标，所以要减去1
	int Tail = len-1;
	//查找
	while (Head <= Tail) {
		Mid = (Head + Tail) >> 1;
		//相等情况
		if (arr[Mid] == num)return Mid;
		//左半部分
		if (arr[Mid] > num) {
			Tail = Mid - 1;
		}
		//右半部分
		if (arr[Mid] < num) {
			Head = Mid + 1;
		}
	}
	return -1;
}
int BinaryChop2(int* arr, int head, int len,int num) {
	if (arr == NULL || len < head)return -1;
	//中间值
	int Mid = (len + head) >> 1;
	//相等情况
	if (arr[Mid] == num)return Mid;
	//右半部分
	else if (arr[Mid] < num) {
		return BinaryChop2(arr, Mid+1,len, num);
	}
	//左半部分
	else if (arr[Mid > num]) {
		return BinaryChop2(arr, head, Mid-1, num);
	}
}

int main(void) {
	int arr[] = { 2,3,4,5,6,7,109,232,4454,6868,9990 };
	int len = sizeof(arr) / sizeof(int);
	int num = 0;
	cin >> num;
	//cout<<"找到该数,该数下标为："<<BinaryChop2(arr, 0,len-1,num)<<endl;
	cout << "找到该数,该数下标为：" << BinaryChop(arr, len, num) << endl;
	return 0;
}
