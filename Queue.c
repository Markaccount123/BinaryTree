#include"Queue.h"
//������ʲôʱ�����õ��أ�����˵���������ȳ��ĳ��������е��Ŷ�ȡƱ������Ŀ����Ҫ��֤��ȡ��Ʊ�����ȱ�����
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
		printf("�ڴ治��\n");
		exit(-1);
	}
	newNode->_date = x;
	newNode->_next = NULL;
	//�������һ��ʼ���ǿյ����
	if (pq->_head == NULL) // ��Ϊ���ʼ����ʱ��ͷ��β����NULL�������ͷβNULL��ʱ��Ҳ˵�������βҲ��NULL
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
	//����ǰ����ж���ɾ���ˣ���ʱ��Ҫ�ǲ������β�����ͻ��ΪҰָ��
	if (pq->_head == NULL)
	{
		pq->_tail == NULL;
	}
}

QDateType QueueFront(Queue* pq)
{
	assert(pq);
	assert(pq->_head);//ȷ����ͷ����Ч�ģ���Ϊ��
	return pq->_head->_date;
}

QDateType QueueBack(Queue* pq)
{
	assert(pq);
	assert(pq->_tail); //ȷ����β����Ч�ģ���Ϊ��
	return pq->_tail->_date;
}

//����1�ǿգ�����0�Ƿǿ�
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