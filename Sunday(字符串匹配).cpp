#include<iostream>
using namespace std;

//int Myfind(const char* match,char temp)
//{
//	for (int i = strlen(match)-1; i >=0 ; i--)
//	{
//		if (temp == match[i])
//		{
//			return i;
//		}
//	}
//	return -1;
//}
//
//int Sunday(const char* src, const char* match)
//{
//	if (src == NULL || match == NULL)return -1;
//	int flag1 = 0;
//	int flag2 = 0;
//	char temp;
//	int position = 0;
//	int len2 = strlen(match);
//	while (flag1 < strlen(src) && flag2 < strlen(match))
//	{
//		//如果相同就继续走
//		if (src[flag1] == match[flag2])
//		{
//			flag1++;
//			flag2++;
//		}
//		else 
//		{
//			//如果不同,此时源串的下标加上剩余未被遍历的匹配串的长度，也就是说该匹配串不可能出现在最开始匹配的位置起，到其长度的位置
//			flag1 += len2 -flag2;
//			//匹配串归零
//			flag2 = 0;
//			//如果源串的flag1的下一个位置的字符能在匹配串中从右向左遍历找到
//			if ((position=Myfind(match, src[++flag1]))>-1)
//			{
//				//源串的flag1就要减去返回的下标值（也就是说，使得源串以该匹配字符的位置贴上去，进行匹配验证）
//				flag1 = flag1 - position;
//			}
//			//如果并不能找到，就flag1++，因为已经在if中++了，所以就不用再++了
//		}
//	}
//	if (match[flag2] == '\0')return flag1 - flag2;
//	return -1;
//}
//

//求next数组,即256大小，方便直接拿下标(直接顺序遍历,存下标,有就覆盖，本来就是求从右向左的下标值)
//匹配 3个标记值,一个存开始遍历的位置,两个跟着去遍历
//1.相同一起往后走
//如果匹配失败,即当前匹配串的长度的字符不可能匹配，使得position=偏移一个匹配串长度的下一个位置
//将此时的position的字符在next数组中查询，完成对其操作->如果存在就取出当前元素的下标,position则下次从position-下标值的位置开始遍历(为了能全遍历完,不遗漏)
//如果不存在->position++，继续进行匹配
//k=k+匹配长度-Next[源串[k+匹配长度]]
//直到匹配串走完（return k）或者源串走完（return -1）

//int* MyNext(const char* match, int len)
//{
//	int* Next = NULL;
//	Next = (int*)malloc(sizeof(int) * 256);
//	memset(Next, -1, sizeof(int) * 256);
//	for (int i = 0; i < len; i++)
//	{
//		Next[(int)match[i]] = i;
//	}
//	return Next;
//}
//
//int FindPosition(int* Next,char temp)
//{
//	if (Next[(int)temp] == -1)return -1;
//	else return Next[(int)temp];
//}
//
//int Sunday(const char* src, const char* match)
//{
//	//一个开始遍历的位置
//	int position = 0;
//	//两个标记位
//	int flag1 = 0;
//	int flag2 = 0;
//	int temp = 0;
//	int* Next = NULL;
//	Next = MyNext(match, strlen(match));
//	while ((position+strlen(match)) < strlen(src)&&flag1<strlen(src) && flag2 < strlen(match))
//	{
//		if (src[flag1] == match[flag2])
//		{
//			flag1++;
//			flag2++;
//		}
//		else
//		{
//			position = position + strlen(match);
//			flag1 = position;
//			if ((temp=FindPosition(Next, src[flag1])) > -1)
//			{
//				position = position - temp;
//			}
//			else
//			{
//				position++;
//			}
//			flag1 = position;
//			flag2 = 0;
//		}
//	}
//	if (match[flag2] == '\0')return position;
//	return -1;
//}

int Sunday(const char* src, const char* match)
{
	if (src == NULL || match == NULL)return -1;
	//获取next数组
	int* Next = NULL;
	Next = (int*)malloc(sizeof(int) * 256);
	memset(Next, -1, sizeof(int) * 256);

	int i = 0;
	for (i; i < strlen(match); i++)
	{
		Next[match[i]] = i;
	}
	//匹配
	int flag1 = 0;
	int flag2 = 0;
	int position = 0;

	while (flag1 < strlen(src) && flag2 < strlen(match))
	{
		if (src[flag1] == match[flag2])
		{
			flag1++;
			flag2++;
		}
		else
		{
			//原串重新定位,如果没找到就向后移动一位，又因为数组被初始化为-1,因为刚刚好
			if (position + strlen(match) < strlen(src))
			{
				position = position + strlen(match) - Next[src[position + strlen(match)]];
				flag1 = position;
				flag2 = 0;
			}
			else
			{
				return -1;
			}
		}
	}
	if (match[flag2] == '\0')return position;
	return -1;
}
int main()
{
	int i = Sunday("abcabceabcabcabcabcdabcabcfabcabc", "abcabcdabcabcf");
	cout << i << endl;
	return 0;
}
