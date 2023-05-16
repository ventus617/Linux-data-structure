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




//����׼ֵ�����ҷֿ��ţ���ˣ�Ϊ˫ָ�뷨����Ϊ����Ƿ�
//head��ͷ��    tail��β�������鳤�ȣ�Ϊlen-1
int GetPivot(int* arr, int head, int tail) {
	int temp = 0;
	int flag = head+((tail-head)>>1);//����ҵ�һ����Ϊ��׼ֵ
	while (head < tail)//����Ϊ���ڣ���Ϊ�������ظ�ʱ����ѭ��
	{
		//������ұ�����ֵ�����û�У�ֱ��ĩβ������ĩβ
		while (head < tail && arr[head] < arr[flag]) {
			head++;
		}
		//�������ϻ�׼ֵ��ȣ�������Ҳ��Ļ�����ʱhead�ͱ�flag����������Ҫ�����ǣ������flag���ʱ��ͣ��
		temp = arr[flag];
		arr[flag] = arr[head];
		arr[head] = temp;
		flag = head;
		//���Ҳ��ұ���С��ֵ�����û�У��ͷ�����β����ʱ��Ҫ�ж������ȵ�����������������ʹ��jͣ��flag֮ǰ�����Դ��head>flag������
		while (head < tail && arr[flag] <= arr[tail]) {
			tail--;
		}
		//�Ƚ�����ֵ���ٸ�ֵ�±�
		temp = arr[flag];
		arr[flag] = arr[tail];
		arr[tail] = temp;
		flag = tail;
	}
	return flag;
}


void QuickSort(int*arr,int head,int tail){
	//���ѡ���׼ֵ,ʹ��Ϊƽ�����(����ջ�����ΪO(logn)*ÿ���ʱ��O(n))��������������(����ջ�����ΪO(n)*ÿ���ʱ��O(n))
	//��׼ֵ,���ڻ�׼ֵ�ķ�һ��,С�ڻ�׼ֵ�ķ�һ��
	//����Ի�׼ֵ��ߺ��ұ߷ֱ���п�������
	if (head < tail) {
		int pivot = GetPivot(arr, head, tail);
		QuickSort(arr, head, pivot-1);//���������
		QuickSort(arr, pivot+1, tail);//���ұ�����
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