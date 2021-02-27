#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"

typedef  char BTDateType;

typedef struct BinaryTreeNode
{
	BTDateType _date;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

//ǰ�����
//���ȸ�������  �� ������ ������
void PrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->_date);//�ȴ�ӡ��
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

//�������
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->_left);
	printf("%c ", root->_date);//��ӡ��
	InOrder(root->_right);
}


//��������
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%c ", root->_date);//��ӡ��
}

//��������size��ν������������Ҫ�úô���˼�������⣡
//int size = 0;  ���������ȫ�ֱ���Ҳ���ã���Ϊ�������ν��������TreeSizeֵ��ʱ������ֵ���ۼӵģ�
//int TreeSize(BTNode* root)
//{
//	if (root == NULL)
//		return 0;
//
//	//int size = 0;  ���size��һ���ֲ���������ÿ�ε���һ���ҾͶ�����һ��size�����ӵ�size����ͬһ��ֵ������Ҫ�����size���ȫ�ֱ���
//	size++;
//	TreeSize(root->_left);
//	TreeSize(root->_right);
//	return size;
//}

//������ﴫ����int size �൱�ڴ�ֵ����ô�ҵ�һ�ν�ȥ��++�ˣ����ǵڶ��ν�ȥ�����Ϊ�գ�++��size�ֲ�����ԭ������
//��������Ҫ��ַ����֤��һֱ����ͨһ��size��������ۼ�
//void TreeSize(BTNode* root,int* psize)
//{
//	if (root == NULL)
//		return 0;
//	else
//		(*psize)++;
//
//	TreeSize(root->_left, psize);
//	TreeSize(root->_right,psize);
//}

//�ݹ�ķ�ʽ��
int TreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + TreeSize(root->_left) + TreeSize(root->_right); //���������ıܿ������sizeֵ�ۼӵ�ֵ
}


//��Ҷ�ӽ��ĸ���
int TreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}

//���
int TreeDepth(BTNode* root)
{
	//�յĻ�����Ⱦ���0
	if (root == NULL)
		return 0;
	//��ʱ�Ȳ��ǿ�Ҳ����Ҷ�ӵ�ʱ������������ȣ�������ҵ���ȣ�ȡ��������нϴ����һ����Ȼ����+1
	int LeftTreeDepth = root->_left;
	int RightTreeDepth = root->_right;
	//��������������������
	return  LeftTreeDepth > RightTreeDepth ? LeftTreeDepth + 1 : RightTreeDepth + 1;
}
//��������K�������
//��ǰ���ĵ�K�����ת�������������ĵ�K-1��
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

//����������ֵΪx�Ľ��
BTNode* BinaryTreeFind(BTNode* root, BTDateType x)
{
	if (root == NULL)
		return NULL;
	if (root->_date == x)
		return root;
	//��������ֱ���ҵ��ˣ��Ͳ�����ȥ�ұ�����
	BTNode* node = BinaryTreeFind(root->_left, x);
	if (node)
		return node;
	//û��������ҵ�������ȥ�ұ���
	node = BinaryTreeFind(root->_right, x);
	if (node)
		return node;
	return NULL;
}

//����
void DestoryTree(BTNode* root)
{
	//���ʹ�ú������������ʹ�����������ᷢ�֣�root����ɵ��ˣ���ô����Ҳ����������������
	if (root == NULL)
		return NULL;
	DestoryTree(root->_left);
	DestoryTree(root->_right);
	free(root);
}

//�������Ĳ������
void BinaryTreeLevelOrder(BTNode* root)
{
	//������������Ķ�������ŵĿɲ���ֻ��ֵ����ô�����������ʱ���Ҳ����������Һ����������
	Queue q;
	QueueInit(&q);
	if (root == NULL)
		return;
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		//�����Popֻ�ǰ�������ݴӶ��������ó����ˣ���û��ɾ��
		QueuePop(&q);//���������������������ó���
		printf("%c ", front->_date);
		if (front->_left)
		{
			QueuePush(&q, front->_left);
		}
		if (front->_right)
		{
			QueuePush(&q, front->_right);
		}
	}
	QueueDestory(&q);
	printf("\n");
}


//�ж϶������Ƿ���һ����ȫ������
//�������������˼�룬��ȫ�������ͷ���ȫ��������������ǣ�
//�ڲ��������   
//���������ȫ��������ô��Ľ�㶼�Ǿۼ���ǰ��ģ��������NULL�����Էָ�ģ���
//����������Ƿ���ȫ��������ᷢ�֣���Ľ���м���ܰ�����NULL
int BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root == NULL)
		return 1;  //�Ǿͷ���1�����Ƿ���0
	QueuePush(&q, root);

	//�������ȫ����������ô��Ľ�㶼������֮�󣬶��о���NULL��
	//����Ƿ���ȫ����������������һ��break֮����ȥ�����У���ᷢ�ֶ����ǲ�ΪNULL��
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front == NULL)
			break;


		QueuePush(&q, front->_left);
		QueuePush(&q, front->_right);
	}
	//��ʱ����һ��������һ���գ������ж϶�������ʣ�µ�
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front)
		{
			QueueDestory(&q);
			return 0;
		}
	}
	QueueDestory(&q);
	return 1;
}



BTNode* CreateNode(char x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->_date = x;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}




int main()
{
	BTNode* A = CreateNode('A');
	BTNode* B = CreateNode('B');
	BTNode* C = CreateNode('C');
	BTNode* D = CreateNode('D');
	BTNode* E = CreateNode('E');
	//������������
	A->_left = B;
	A->_right = C;
	B->_left = D;
	B->_right = E;

	PrevOrder(A);
	printf("\n");

	InOrder(A);
	printf("\n");

	PostOrder(A);
	printf("\n");


	//int sizea = 0;
	//TreeSize(A, &sizea);
	//printf("TreeSize: %d\n", sizea);
	////printf("TreeSize: %d\n", TreeSize(A)); ���ʹ��ȫ�ֱ���size����ô�ڴ�ӡһ��size��ʱ����һ�ε�ֵ�ͻ��ۼӣ�����ͻ���10

	//int sizeb = 0;
	//TreeSize(B, &sizeb);
	//printf("TreeSize: %d\n", sizeb);


	printf("TreeSize: %d\n", TreeSize(A));
	printf("TreeLeafSize: %d\n", TreeLeafSize(A));
	printf("TreeDepth: %d\n", TreeDepth(A));
	printf("BinaryTreeLevelKSize: %d\n", BinaryTreeLevelKSize(A, 3));
	BinaryTreeLevelOrder(A);


	printf("BinaryTreeComplete: %d\n", BinaryTreeComplete(A)); //���ص���1���Ƕ�����

	getchar();
	return 0;
}