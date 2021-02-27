#include"Queue.h"
//队列在什么时候能用到呢？比如说就是先入先出的场景，银行的排队取票服务项目。我要保证先取到票的人先被服务
void QueueInit(Queue* pq)
{
	assert(pq);
	pq->_head = pq->_tail = NULL;
}

void QueueDestory(Queue* pq)
{
	assert(pq);
	QueueNode* cur = pq->_head;
	while (cur)
	{
		QueueNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	pq->_head = pq->_tail = NULL;
}


void QueuePush(Queue* pq, QDateType x)
{
	assert(pq);
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL)
	{
		printf("内存不足\n");
		exit(-1);
	}
	newNode->_date = x;
	newNode->_next = NULL;
	//这个队列一开始就是空的情况
	if (pq->_head == NULL) // 因为你初始化的时候头和尾都是NULL，当你的头尾NULL的时候也说明了你的尾也是NULL
	{
		pq->_head = pq->_tail = newNode;
	}
	else
	{
		pq->_tail->_next = newNode;
		pq->_tail = newNode;
	}
}
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(pq->_head);
	QueueNode* next = pq->_head->_next;
	free(pq->_head);
	pq->_head = next;
	//这就是把所有都给删完了，此时你要是不管这个尾，他就会成为野指针
	if (pq->_head == NULL)
	{
		pq->_tail == NULL;
	}
}

QDateType QueueFront(Queue* pq)
{
	assert(pq);
	assert(pq->_head);//确保队头是有效的，不为空
	return pq->_head->_date;
}

QDateType QueueBack(Queue* pq)
{
	assert(pq);
	assert(pq->_tail); //确保队尾是有效的，不为空
	return pq->_tail->_date;
}

//返回1是空，返回0是非空
int QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->_head == NULL ? 1 : 0;
}

int QueueSize(Queue* pq)
{
	assert(pq);
	QueueNode* cur = pq->_head;
	int size = 0;
	while (cur)
	{
		size++;
		cur = cur->_next;
	}
	return size;
}