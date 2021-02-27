#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

//相当于把你的struct BinaryTreeNode拿过来申明一下
extern struct BinaryTreeNode;
typedef struct BinaryTreeNode*  QDateType;
//这里可以把BTNode的定义放到这里，但是这是一个Queue的头文件，有点挫

typedef struct QueueNode
{
	struct QueueNode* _next;
	QDateType _date;
}QueueNode;

//队尾入数据，队头出数据
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

//返回1是空，返回0是非空
int QueueEmpty(Queue* pq);
int QueueSize(Queue* pq);




