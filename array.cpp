#include<iostream>
#include<stdio.h>
#include<stdlib.h>

void PrintArr(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

}

//数组长度为n，元素为n-1内随机一个数，判断如果有重复数据则报错

//计数 暴力（一个一个比较） 排序
//在原数组基础上O（1）的空间消耗，O（n）的时间复杂消耗
//下标交换
int CompareArray1(int* arr,int len)
{
	if (arr == NULL || len <= 0)return 0;
	//元素值与下标比较
	int i = 0;
	int Index = 0;
	int temp = 0;
	for(i;i<len;){
		if (arr[i] == i) {
			//处理下一个
			i++;
		}
		else {
			//检测当前元素值作为索引的位置
			Index = arr[i];//中间值最好使用一个中间变量来接
			if (arr[i] == arr[Index]) {
				printf("数据重复出现");
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
	//元素值与下标比较
	int i = 0;
	int temp = 0;
	for (i; i < len;) {
		if (arr[i] == i) {
			//处理下一个
			i++;
		}
		else {
			//检测当前元素值作为索引的位置
			if (arr[i] == arr[arr[i]]) {
				printf("数据重复出现");
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
	//元素值与下标比较
	int i = 0;
	int temp = 0;
	while(i<len){
		if (arr[i] == i) {
			//处理下一个
			i++;
		}
		else {
			//检测当前元素值作为索引的位置
			if (arr[i] == arr[arr[i]]) {
				printf("数据重复出现");
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
//一组数据内有一个元素仅出现一次，其余元素均出现2次，请快速找出只出现一次的元素
//暴力计数 Hash 排序(前后均不一样) 异或（相同为0不同为1，因此相同数 异或 会抵消）
int FindOnlyOnce(int * arr,int len) {
	if (arr == NULL || len <= 0) return NULL;
	int temp = arr[0];
	for (int i = 1; i < len; i++)
	{
		temp=arr[i] ^ temp;
	}
	return temp;
}
//一组数据内有2个元素仅出现一次，其余元素均出现2次，请快速找出只出现一次的2个元素
//计数 排序 
//通过异或处理 得到一个两个不同数字的异或的值，那么在这个二进制数上，两个数的不同位是1，找一个非0位即可
//因此按照该位数来分组，相同的数在一个组，就分出来两个不同的数了 
void FinddifTwoNum(int* arr, int len)
{
	int Num1 = 0;//获取全部的异或值
	int Num2 = 1;//分组用的位与值1
	int DifNum1=0;
	int DifNum2=0;
	//整体异或
	for (int i = 0; i < len; i++)
	{
		Num1 ^= arr[i];
	}
	//当位与值为0时，则继续寻找位与值非0的那个数 即获得了非0位
	while ((Num1 & Num2) == 0)
	{
		Num2 <<= 1;
	}
	//分组并且每组异或得出值
	for (int i = 0; i < len; i++) {
		//如果相与是0，则为一组
		if ((Num2 & arr[i])!=0) {
			//再每组异或得值
			DifNum2 ^= arr[i];
		}
		//相与不为0，则为另一组
		else {
			DifNum1 ^= arr[i];
		}
	}
	printf("%d %d\n",Num1,Num2);
}
//n个元素 值1~n，元素无重复，寻找丢失的一个元素（如果新的元素排列在一个arr中）
//异或  和减(得考虑上下限，防止内存越界出错)  数组(按下标放进去 值为0的就是空)
int FindLostOne(int* arr, int len) {
	if (arr == NULL || len <= 0)return;
	int num1 = 0;
	int num2 = 0;
	//len是新数组的长度
	for (int i = 0; i < len; i++) {
		num1 ^= i+1;
		num2 ^= arr[i];
	}
	//增加其实也同理，一个操作
	return num2 ^ num1;
}
int main(void) {
	int arr[] = {0,1,1,2,2,3};
	PrintArr(arr, sizeof(arr) / sizeof(int));
	FinddifTwoNum(arr, sizeof(arr) / sizeof(int));
	return 0;
}
