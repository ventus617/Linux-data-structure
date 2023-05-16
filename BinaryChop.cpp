#include<iostream>
using namespace std;

int BinaryChop(int *arr,int len,int num) {
	if (arr == NULL)return -1;
	//�м�ֵ
	int Mid = 0;
	int Head = 0;
 //β��ֵ�������鳤��,�������������һ��Ԫ�ص��±꣬����Ҫ��ȥ1
	int Tail = len-1;
	//����
	while (Head <= Tail) {
		Mid = (Head + Tail) >> 1;
		//������
		if (arr[Mid] == num)return Mid;
		//��벿��
		if (arr[Mid] > num) {
			Tail = Mid - 1;
		}
		//�Ұ벿��
		if (arr[Mid] < num) {
			Head = Mid + 1;
		}
	}
	return -1;
}
int BinaryChop2(int* arr, int head, int len,int num) {
	if (arr == NULL || len < head)return -1;
	//�м�ֵ
	int Mid = (len + head) >> 1;
	//������
	if (arr[Mid] == num)return Mid;
	//�Ұ벿��
	else if (arr[Mid] < num) {
		return BinaryChop2(arr, Mid+1,len, num);
	}
	//��벿��
	else if (arr[Mid > num]) {
		return BinaryChop2(arr, head, Mid-1, num);
	}
}

int main(void) {
	int arr[] = { 2,3,4,5,6,7,109,232,4454,6868,9990 };
	int len = sizeof(arr) / sizeof(int);
	int num = 0;
	cin >> num;
	//cout<<"�ҵ�����,�����±�Ϊ��"<<BinaryChop2(arr, 0,len-1,num)<<endl;
	cout << "�ҵ�����,�����±�Ϊ��" << BinaryChop(arr, len, num) << endl;
	return 0;
}
