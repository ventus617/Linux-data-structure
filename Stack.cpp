#include<iostream>
using namespace std;

typedef struct Node
{
	struct Node* next;
	int val;
}List,*ListN;

typedef struct Pode
{
	List* pTop;
	int count;
}Stack;
int isEmpty(Stack* Sstack);
int GetTop(Stack* Sstack);
int GetCount(Stack* Sstack);
void Destroy(Stack** Sstack);
void Init(Stack** Sstack);
void Push(Stack* Sstack, int num);
void Pop(Stack* Sstack);
void Clear(Stack* Sstack);

int isEmpty(Stack* Sstack)
{
	if (Sstack->count == 0 || Sstack->pTop == NULL)return 1;
	return 0;
}


int GetTop(Stack* Sstack)
{
	if (Sstack==NULL||Sstack->pTop== NULL)exit(1);
	int num = Sstack->pTop->val;
	return num;
}


int GetCount(Stack* Sstack)
{
	if (Sstack==NULL||Sstack->pTop== NULL)exit(0);
	return Sstack->count;
}

void Destroy(Stack** Sstack)
{
	if ((*Sstack)->pTop == NULL)return;
	Clear(*Sstack);
	free((*Sstack));
	(*Sstack)= NULL;
}
void Init(Stack **Sstack)
{  
	(*Sstack)=(Stack*)malloc(sizeof(Stack));
	(*Sstack)->count = 0;
	(*Sstack)->pTop = (ListN)malloc(sizeof(List));
	(*Sstack)->pTop = NULL;
}

void Push(Stack *Sstack,int num)
{
	List* Node = (List*)malloc(sizeof(List));
	Node->val = num;
	Node->next = NULL;
	Node->next = Sstack->pTop;
	Sstack->pTop = Node;
	Sstack->count += 1;
}

void Pop(Stack*Sstack)
{
	if (Sstack->pTop == NULL)return;
	ListN Node = (ListN)malloc(sizeof(List));
	Node= Sstack->pTop;
	Sstack->pTop =Sstack->pTop->next;
	int num = Node->val;
	free(Node);
	Node= NULL;
	printf("%d ", num);
	Sstack->count -= 1;
}


void Clear(Stack* Sstack)
{
	if (Sstack->pTop == NULL)return;
	while (Sstack->pTop)
	{
		Pop(Sstack);
	}
}



int main()
{
	Stack *Sstack=NULL;
	Init(&Sstack);
	Push(Sstack, 5);
	Push(Sstack, 4);
	Push(Sstack, 3);
	Push(Sstack, 2);
	Push(Sstack, 1);

	Pop(Sstack);
	Pop(Sstack);
	Pop(Sstack);
	int num=isEmpty(Sstack);
	printf("%d \n", num);
	num=GetCount(Sstack);
	printf("%d \n", num);
	num=GetTop(Sstack);
	printf("%d \n", num);
	Destroy(&Sstack);
	num = GetCount(Sstack);
	printf("%d \n", num);
	num = GetTop(Sstack);
	printf("%d \n", num);

}