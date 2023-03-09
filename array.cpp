#include<iostream>
#include<stdio.h>
#include<stdlib.h>

void PrintArr(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

}

//���鳤��Ϊn��Ԫ��Ϊn-1�����һ�������ж�������ظ������򱨴�

//���� ������һ��һ���Ƚϣ� ����
//��ԭ���������O��1���Ŀռ����ģ�O��n����ʱ�临������
//�±꽻��
int CompareArray1(int* arr,int len)
{
	if (arr == NULL || len <= 0)return 0;
	//Ԫ��ֵ���±�Ƚ�
	int i = 0;
	int Index = 0;
	int temp = 0;
	for(i;i<len;){
		if (arr[i] == i) {
			//������һ��
			i++;
		}
		else {
			//��⵱ǰԪ��ֵ��Ϊ������λ��
			Index = arr[i];//�м�ֵ���ʹ��һ���м��������
			if (arr[i] == arr[Index]) {
				printf("�����ظ�����");
				return 0;
			}
			else {
				temp = arr[i];
				arr[i] = arr[Index];
				arr[Index] = temp;
			}
		}
	}
	PrintArr(arr,len);
	return 1;
}

int CompareArray2(int* arr, int len)
{
	if (arr == NULL || len <= 0)return 0;
	//Ԫ��ֵ���±�Ƚ�
	int i = 0;
	int temp = 0;
	for (i; i < len;) {
		if (arr[i] == i) {
			//������һ��
			i++;
		}
		else {
			//��⵱ǰԪ��ֵ��Ϊ������λ��
			if (arr[i] == arr[arr[i]]) {
				printf("�����ظ�����");
				return 0;
			}
			else {
				temp = arr[arr[i]];
				arr[arr[i]]=arr[i];
				arr[i] = temp;
			}
		}
	}
	PrintArr(arr, len);
	return 1;
}
int CompareArray(int* arr, int len)
{
	if (arr == NULL || len <= 0)return 0;
	//Ԫ��ֵ���±�Ƚ�
	int i = 0;
	int temp = 0;
	while(i<len){
		if (arr[i] == i) {
			//������һ��
			i++;
		}
		else {
			//��⵱ǰԪ��ֵ��Ϊ������λ��
			if (arr[i] == arr[arr[i]]) {
				printf("�����ظ�����");
				return 0;
			}
			else {
				temp = arr[arr[i]];
				arr[arr[i]] = arr[i];
				arr[i] = temp;
			}
		}
	}
	PrintArr(arr, len);
	return 1;
}
//һ����������һ��Ԫ�ؽ�����һ�Σ�����Ԫ�ؾ�����2�Σ�������ҳ�ֻ����һ�ε�Ԫ��
//�������� Hash ����(ǰ�����һ��) �����ͬΪ0��ͬΪ1�������ͬ�� ��� �������
int FindOnlyOnce(int * arr,int len) {
	if (arr == NULL || len <= 0) return NULL;
	int temp = arr[0];
	for (int i = 1; i < len; i++)
	{
		temp=arr[i] ^ temp;
	}
	return temp;
}
//һ����������2��Ԫ�ؽ�����һ�Σ�����Ԫ�ؾ�����2�Σ�������ҳ�ֻ����һ�ε�2��Ԫ��
//���� ���� 
//ͨ������� �õ�һ��������ͬ���ֵ�����ֵ����ô��������������ϣ��������Ĳ�ͬλ��1����һ����0λ����
//��˰��ո�λ�������飬��ͬ������һ���飬�ͷֳ���������ͬ������ 
void FinddifTwoNum(int* arr, int len)
{
	int Num1 = 0;//��ȡȫ�������ֵ
	int Num2 = 1;//�����õ�λ��ֵ1
	int DifNum1=0;
	int DifNum2=0;
	//�������
	for (int i = 0; i < len; i++)
	{
		Num1 ^= arr[i];
	}
	//��λ��ֵΪ0ʱ�������Ѱ��λ��ֵ��0���Ǹ��� ������˷�0λ
	while ((Num1 & Num2) == 0)
	{
		Num2 <<= 1;
	}
	//���鲢��ÿ�����ó�ֵ
	for (int i = 0; i < len; i++) {
		//���������0����Ϊһ��
		if ((Num2 & arr[i])!=0) {
			//��ÿ������ֵ
			DifNum2 ^= arr[i];
		}
		//���벻Ϊ0����Ϊ��һ��
		else {
			DifNum1 ^= arr[i];
		}
	}
	printf("%d %d\n",Num1,Num2);
}
//n��Ԫ�� ֵ1~n��Ԫ�����ظ���Ѱ�Ҷ�ʧ��һ��Ԫ�أ�����µ�Ԫ��������һ��arr�У�
//���  �ͼ�(�ÿ��������ޣ���ֹ�ڴ�Խ�����)  ����(���±�Ž�ȥ ֵΪ0�ľ��ǿ�)
int FindLostOne(int* arr, int len) {
	if (arr == NULL || len <= 0)return;
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	for (int i = 0; i < len; i++) {
		num1 ^= i+1;
		num2 ^= arr[i];
	}
	//������ʵҲͬ��һ������
	return num2 ^ num1;
}
int main(void) {
	int arr[] = {0,1,1,2,2,3};
	PrintArr(arr, sizeof(arr) / sizeof(int));
	FinddifTwoNum(arr, sizeof(arr) / sizeof(int));
	return 0;
}