#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;


typedef struct Lnode {
	struct Lnode* next;
	int val;
}*List,ListNode;

List CreateList() {
	int num = 0;
	cout << "please enter one number" << endl;
	cin >> num;
	int value = 0;
	List Tail = nullptr;
	List Head = nullptr;
	while (num) {
		cout << "please enter one number..." << endl;
		cin >> value;
		List Lnode = (List)malloc(sizeof(ListNode));
		Lnode->val = value;
		if (Head == nullptr) {
			Head = Lnode;
			Tail = Head;
		}
		else {
			Tail->next = Lnode;
			Tail = Lnode;
		}
		num--;
	}
	Tail->next = NULL;
	return Head;
}

int MyCount(List list) {
	if (list == NULL) return 0;
	return 1 + MyCount(list->next);
}

int MySum(int* arr,int len,int flag) {
	if (arr == NULL)return NULL;
	if (len == 1)return arr[flag];
	int val = arr[flag];
	++flag;
	--len;
	return val + MySum(arr, len, flag);
}

int BinaryChop(int* arr, int flag1, int flag2, int num) {
	int Head = flag1;
	int Tail = flag2;
	if (Head > Tail)return -1;
	int Mid = Head + ((Tail - Head) >> 1);
	if (arr[Mid] == num)return Mid;
	else if (arr[Mid] > num)return BinaryChop(arr, Head,Mid-1, num);
	else if (arr[Mid] < num)return BinaryChop(arr, Mid+1,Tail, num);
};




//将基准值的左右分开排，因此，为双指针法，可为三标记法
//head是头，    tail是尾，是数组长度，为len-1
int GetPivot(int* arr, int head, int tail) {
	int temp = 0;
	int flag = head+((tail-head)>>1);//随机找的一个作为基准值
	while (head < tail)//不能为等于，因为数组内重复时，死循环
	{
		//在左侧找比其大的值，如果没有，直到末尾，放在末尾
		while (head < tail && arr[head] < arr[flag]) {
			head++;
		}
		//在左侧加上基准值相等，如果相等也算的话，此时head就比flag更大，我们需要做的是，当其和flag相等时就停下
		temp = arr[flag];
		arr[flag] = arr[head];
		arr[head] = temp;
		flag = head;
		//在右侧找比他小的值，如果没有，就放在首尾，此时需要判断如果相等的情况，即完善情况，使得j停在flag之前，可以达成head>flag的条件
		while (head < tail && arr[flag] <= arr[tail]) {
			tail--;
		}
		//先交换数值，再赋值下标
		temp = arr[flag];
		arr[flag] = arr[tail];
		arr[tail] = temp;
		flag = tail;
	}
	return flag;
}


void QuickSort(int*arr,int head,int tail){
	//随机选择基准值,使其为平均情况(调用栈的深度为O(logn)*每层的时间O(n))，尽量避免最坏情况(调用栈的深度为O(n)*每层的时间O(n))
	//基准值,大于基准值的放一起,小于基准值的放一起
	//再针对基准值左边和右边分别进行快速排序
	if (head < tail) {
		int pivot = GetPivot(arr, head, tail);
		QuickSort(arr, head, pivot-1);//对左边排序
		QuickSort(arr, pivot+1, tail);//对右边排序
	}


}




int main() {
	/*int* arr = NULL;
	int len = sizeof(arr) / sizeof(int);*/
	//printf("%d ", MySum(arr, len, 0));

	//List list = CreateList();
	//printf("%d ",MyCount(list));

	//int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	//int len = sizeof(arr) / sizeof(int);
	//printf("%d ", BinaryChop(arr, 0, len - 1, 3));

	//int arr[] = { 1,1 };
	// int arr[] = { 1,2,3,24,35,234,5,2352,61,1,3,23,5,2,3,4231,546233,1424124};
	int arr[] = { 1,4,7,18,3,9 };
	for (int i = 0; i < ((sizeof(arr) / sizeof(int))); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	QuickSort(arr, 0, sizeof(arr) / sizeof(int)-1);
	for (int i = 0; i < ((sizeof(arr) / sizeof(int))); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}