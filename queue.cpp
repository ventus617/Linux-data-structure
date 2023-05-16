#include<iostream>
using namespace std;

typedef struct node
{
	struct node* next;
	int val;
}List;

typedef struct myqueue
{
	List* front;
	List* back;
	int count;
}Queue;

void Init(Queue**queue)
{
	(*queue) = (Queue*)malloc(sizeof(Queue));//获取一片可以指向的空间
	(*queue)->count = 0;
	(*queue)->front = NULL;
	(*queue)->back = NULL;
}

void pushQueue(Queue* queue,int val)
{
	if (queue== NULL)return;
	List* node = (List*)malloc(sizeof(List));
	node->next = NULL;
	node->val = val;
	if (queue->front == NULL)
	{
		queue->front = node;
		queue->back = queue->front;
	}
	else
	{
		queue->back->next = node;
		queue->back = node;
	}
	queue->count++;
}

void popQueue(Queue* queue)
{
	if (queue == NULL)return;
	if (queue->front==NULL||queue->count== 0)
	{
		cout << "pop失败，队头元素为空" << endl;
		return;
	}
	int val;
	val = queue->front->val;
	cout << "pop" << val << "成功" << endl;
	List* count = queue->front;
	queue->front = queue->front->next;
	free(count);
	count=NULL;
	queue->count--;
	//队尾并不知道是不是空了，因此要赋值为空
	if (queue->count == 0)
	{
		queue->back = NULL;
	}
}

void DestroyQueue(Queue** queue)
{
	while((*queue)->count > 0)
	{
		popQueue(*queue);
	}
	free((*queue));
	(*queue) = NULL;
	printf("释放成功\n");
	
}


int main()
{
	Queue* queue;
	Init(&queue);
	pushQueue(queue, 1);
	pushQueue(queue, 2);
	pushQueue(queue, 3);
	pushQueue(queue, 4);
	pushQueue(queue, 5);
	popQueue(queue);
	popQueue(queue);
	popQueue(queue);
	popQueue(queue);
	popQueue(queue);
	popQueue(queue);
	DestroyQueue(&queue);
	return 0;
}