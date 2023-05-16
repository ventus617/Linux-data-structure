#include<iostream>
using namespace std;

//void Next(int *arr, int len,char*s2)
//{
//	//next[0]是0
//	arr[0] = 0;
//	char flag;
//	int position;
//	for (int i = 1; i < len-1; i++)
//	{
//		arr[i] = -1;
//	}
//	for (int i = 1; i < len-1; i++)
//	{
//		flag = s2[arr[i - 1]];
//		position = i - 1;
//		while (arr[i] == -1)
//		{
//			if (s2[i] == flag)
//			{
//				arr[i] = arr[position] + 1;
//			}
//			else if (s2[i] != flag)
//			{
//				if (arr[position]== 0)
//				{
//					arr[i] = 0;
//				}
//				else
//				{
//					flag = s2[arr[arr[position] - 1]];
//					position = arr[arr[position] - 1];
//				}
//			}
//
//		}
//	}
//
//
//
//}
//int KMP(const int*arr,const char*s1,int len1,const char*s2,int len2 )
//{
//	if (s1 == NULL || s2 == NULL)return -1;
//	int flag1 = 0;
//	int flag2 = 0;
//	while(flag1<len1)
//	{
//		if (s1[flag1] == s2[flag2])
//		{
//			flag1++;
//			flag2++;
//		}
//		else if (flag2 < (len2-1))
//		{
//			if (flag2 == 0)
//			{
//				flag1++;
//				continue;
//			}
//			//如果不相同，找next数组
//			flag2 = arr[flag2 - 1];
//		}
//		else if (s2[flag2] =='\0')return flag1 - len2+1;
//	}
//	return -1;
//
//}
//int main()
//{
//	char s1[] = "abcabceabcabcabcabcdabcabcfabcabc";
//	char s2[] = "abcabcdabcabcf";
//	const int len2 = sizeof(s2);
//	int arr[len2-1];
//	const int len1 = sizeof(s1);
//	Next(arr, len2, s2);
//	int flag;
//	flag=KMP(arr, s1, len1, s2, len2);
//	cout << flag << endl;
//	return 0;
//}



int* GetNext(const char* match)
{
	//申请空间
	int* Next = NULL;
	int i = 1;
	int len = strlen(match);
	Next = (int*)malloc(sizeof(int) * len);
	Next[0] = 0;
	//获取在Next中进行比较的位置
	int position=i-1;
	//要对实际的match进行比较的位置
	int arrposition;
	while (i < len)
	{
		arrposition = Next[position];
		//匹配
		if (match[i] == match[arrposition])
		{
			Next[i] = arrposition + 1;
			i++;
			position = i - 1;
		}
		else if (arrposition == 0)
		{
			Next[i] = 0;
			i++;
			position = i - 1;
		}
		else
		{
			//确定新的匹配位置
			position = arrposition - 1;
		}
	}
	return Next;
}

int KMP(const char* src, const char* match)
{
	if (src == NULL || match == NULL)return -1;
	//获得next数组
	int* Next = NULL;
	Next = GetNext(match);
	int flag1 = 0;
	int flag2 = 0;
	while (flag1 < strlen(src) && flag2 < strlen(match))
	{
		//相等
		if (src[flag1] == match[flag2])
		{
			flag1++;
			flag2++;
		}
		else
		{
			//如果匹配串到头，就直接++
			if (flag2 == 0)
			{
				flag1++;
			}
			else
			{
				flag2 = Next[flag2 - 1];
			}
		}
	}
	//检测
	if (flag2 == strlen(match))
	{
		return flag1 - flag2;
	}
	else
	{
		return -1;
	}
}


int main()
{
	int result = KMP("abcabceabcabcabcabcdabcabcfabcabc", "abcabcdabcabcf");
	cout << result << endl;
	return 0;
}