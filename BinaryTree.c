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

//前序遍历
//（先根遍历）  根 左子树 右子树
void PrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->_date);//先打印根
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

//中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->_left);
	printf("%c ", root->_date);//打印根
	InOrder(root->_right);
}


//后续遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%c ", root->_date);//打印根
}

//这里的这个size如何解决才是真正需要好好处理思考的问题！
//int size = 0;  但是你遍历全局变量也不好，因为当你两次进行求这个TreeSize值的时候，他的值是累加的，
//int TreeSize(BTNode* root)
//{
//	if (root == NULL)
//		return 0;
//
//	//int size = 0;  这个size是一个局部变量，我每次调用一次我就定义了一次size，所加的size不是同一个值，所以要把这个size变成全局变量
//	size++;
//	TreeSize(root->_left);
//	TreeSize(root->_right);
//	return size;
//}

//如果这里传的是int size 相当于传值，那么我第一次进去是++了，但是第二次进去如果不为空，++的size又不在是原来的了
//所以这里要传址，保证我一直是在通一个size上面进行累加
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

//递归的方式求
int TreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + TreeSize(root->_left) + TreeSize(root->_right); //这里很巧妙的避开了这个size值累加的值
}


//求叶子结点的个数
int TreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}

//深度
int TreeDepth(BTNode* root)
{
	//空的话，深度就是0
	if (root == NULL)
		return 0;
	//此时既不是空也不是叶子的时候，我求出左的深度，再求出右的深度，取两个深度中较大的那一个，然后在+1
	int LeftTreeDepth = root->_left;
	int RightTreeDepth = root->_right;
	//避免掉代码过长导致冗余
	return  LeftTreeDepth > RightTreeDepth ? LeftTreeDepth + 1 : RightTreeDepth + 1;
}
//二叉树第K层结点个数
//当前树的第K层可以转换成左右子树的第K-1层
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

//二叉树查找值为x的结点
BTNode* BinaryTreeFind(BTNode* root, BTDateType x)
{
	if (root == NULL)
		return NULL;
	if (root->_date == x)
		return root;
	//如果在左边直接找到了，就不用再去右边找了
	BTNode* node = BinaryTreeFind(root->_left, x);
	if (node)
		return node;
	//没有在左边找到，那再去右边找
	node = BinaryTreeFind(root->_right, x);
	if (node)
		return node;
	return NULL;
}

//销毁
void DestoryTree(BTNode* root)
{
	//最好使用后续遍历，如果使用先序遍历你会发现，root被你干掉了，那么你就找不到你的左右子树了
	if (root == NULL)
		return NULL;
	DestoryTree(root->_left);
	DestoryTree(root->_right);
	free(root);
}

//二叉树的层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
	//在这里所定义的队列里面放的可不能只是值，那么你就在他出的时候找不到他的左右孩子入队列了
	Queue q;
	QueueInit(&q);
	if (root == NULL)
		return;
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		//这里的Pop只是把这个数据从队列里面拿出来了，并没有删除
		QueuePop(&q);//从这个队列里面把这个结点拿出来
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


//判断二叉树是否是一颗完全二叉树
//这个题借助上面的思想，完全二叉树和非完全二叉树的区别就是：
//在层序遍历中   
//如果你是完全二叉树那么你的结点都是聚集在前面的（结点和你的NULL是明显分割开的），
//但是如果你是非完全二叉树你会发现，你的结点中间可能包含了NULL
int BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root == NULL)
		return 1;  //是就返回1，不是返回0
	QueuePush(&q, root);

	//如果是完全二叉树，那么你的结点都出队列之后，队列就是NULL的
	//如果是非完全二叉树，当你遇见一个break之后，你去检查队列，你会发现队列是不为NULL的
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front == NULL)
			break;


		QueuePush(&q, front->_left);
		QueuePush(&q, front->_right);
	}
	//此时上面一斤遇见了一个空，再来判断队列里面剩下的
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
	//将他们链起来
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
	////printf("TreeSize: %d\n", TreeSize(A)); 如果使用全局变量size，那么在打印一次size的时候上一次的值就会累加，这里就会变成10

	//int sizeb = 0;
	//TreeSize(B, &sizeb);
	//printf("TreeSize: %d\n", sizeb);


	printf("TreeSize: %d\n", TreeSize(A));
	printf("TreeLeafSize: %d\n", TreeLeafSize(A));
	printf("TreeDepth: %d\n", TreeDepth(A));
	printf("BinaryTreeLevelKSize: %d\n", BinaryTreeLevelKSize(A, 3));
	BinaryTreeLevelOrder(A);


	printf("BinaryTreeComplete: %d\n", BinaryTreeComplete(A)); //返回的是1，是二叉树

	getchar();
	return 0;
}