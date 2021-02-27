#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

//�൱�ڰ����struct BinaryTreeNode�ù�������һ��
extern struct BinaryTreeNode;
typedef struct BinaryTreeNode*  QDateType;
//������԰�BTNode�Ķ���ŵ������������һ��Queue��ͷ�ļ����е��

typedef struct QueueNode
{
	struct QueueNode* _next;
	QDateType _date;
}QueueNode;

//��β�����ݣ���ͷ������
typedef struct Queue
{
	QueueNode* _head;
	QueueNode* _tail;
}Queue;

void QueueInit(Queue* pq);
void QueueDestory(Queue* pq);
void QueuePush(Queue* pq, QDateType x);
void QueuePop(Queue* pq);
QDateType QueueFront(Queue* pq);
QDateType QueueBack(Queue* pq);

//����1�ǿգ�����0�Ƿǿ�
int QueueEmpty(Queue* pq);
int QueueSize(Queue* pq);




