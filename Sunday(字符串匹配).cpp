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
//		//�����ͬ�ͼ�����
//		if (src[flag1] == match[flag2])
//		{
//			flag1++;
//			flag2++;
//		}
//		else 
//		{
//			//�����ͬ,��ʱԴ�����±����ʣ��δ��������ƥ�䴮�ĳ��ȣ�Ҳ����˵��ƥ�䴮�����ܳ������ʼƥ���λ���𣬵��䳤�ȵ�λ��
//			flag1 += len2 -flag2;
//			//ƥ�䴮����
//			flag2 = 0;
//			//���Դ����flag1����һ��λ�õ��ַ�����ƥ�䴮�д�����������ҵ�
//			if ((position=Myfind(match, src[++flag1]))>-1)
//			{
//				//Դ����flag1��Ҫ��ȥ���ص��±�ֵ��Ҳ����˵��ʹ��Դ���Ը�ƥ���ַ���λ������ȥ������ƥ����֤��
//				flag1 = flag1 - position;
//			}
//			//����������ҵ�����flag1++����Ϊ�Ѿ���if��++�ˣ����ԾͲ�����++��
//		}
//	}
//	if (match[flag2] == '\0')return flag1 - flag2;
//	return -1;
//}
//

//��next����,��256��С������ֱ�����±�(ֱ��˳�����,���±�,�о͸��ǣ��������������������±�ֵ)
//ƥ�� 3�����ֵ,һ���濪ʼ������λ��,��������ȥ����
//1.��ͬһ��������
//���ƥ��ʧ��,����ǰƥ�䴮�ĳ��ȵ��ַ�������ƥ�䣬ʹ��position=ƫ��һ��ƥ�䴮���ȵ���һ��λ��
//����ʱ��position���ַ���next�����в�ѯ����ɶ������->������ھ�ȡ����ǰԪ�ص��±�,position���´δ�position-�±�ֵ��λ�ÿ�ʼ����(Ϊ����ȫ������,����©)
//���������->position++����������ƥ��
//k=k+ƥ�䳤��-Next[Դ��[k+ƥ�䳤��]]
//ֱ��ƥ�䴮���꣨return k������Դ�����꣨return -1��

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
//	//һ����ʼ������λ��
//	int position = 0;
//	//�������λ
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
	//��ȡnext����
	int* Next = NULL;
	Next = (int*)malloc(sizeof(int) * 256);
	memset(Next, -1, sizeof(int) * 256);

	int i = 0;
	for (i; i < strlen(match); i++)
	{
		Next[match[i]] = i;
	}
	//ƥ��
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
			//ԭ�����¶�λ,���û�ҵ�������ƶ�һλ������Ϊ���鱻��ʼ��Ϊ-1,��Ϊ�ոպ�
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
