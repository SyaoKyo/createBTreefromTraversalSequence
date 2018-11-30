/************************
 *                      *
 *  由遍历序列得二叉树  *
 *                      *
 ************************/
#include <iostream>
using namespace std;

struct BTNode
{
	char data;
	BTNode *lChild;
	BTNode *rChild;
};

BTNode *createBT1(char pre[], char in[], int L1, int R1, int L2, int R2);//由先序、中序遍历得二叉树
BTNode *createBT2(char in[], char post[], int L1, int R1, int L2, int R2);//由中序、后序遍历得二叉树
BTNode *createBT3(char level[], char in[], int n, int L, int R);//由中序、层次遍历得二叉树
int search(char a[], char key, int L, int R);
void getSubLevel(char subLevel[], char level[], char in[], int n, int L, int R);
void visit(BTNode *p);
void BTlevel(BTNode *bt);

const int maxSize = 1000;

int main()
{
	char pre[] = "ABDHIEJCFKGLM";//先序遍历序列
	char in[] = "HDIBEJAKFCLGM";//中序遍历序列
	char post[] = "HIDJEBKFLMGCA";//后序遍历序列
	char level[] = "ABCDEFGHIJKLM";//层次遍历序列

	BTNode *root1 = createBT1(pre, in, 0, 12, 0, 12);
	BTNode *root2 = createBT2(post, in, 0, 12, 0, 12);
	BTNode *root3 = createBT3(level, in, 13, 0, 12);
	cout << "root1:" << endl;
	BTlevel(root1);
	cout << endl;
	cout << "root2:" << endl;
	BTlevel(root2);
	cout << endl;
	cout << "root3:" << endl;
	BTlevel(root3);
	cout << endl;
	return 0;
}

BTNode *createBT1(char pre[], char in[], int L1, int R1, int L2, int R2)
{
	if (L1 > R1)
		return NULL;
	BTNode *s = new BTNode();
	s->lChild = s->rChild = NULL;
	s->data = pre[L1];

	int i;
	for (i = L2;i <= R2;i++)
		if (in[i] == pre[L1])
			break;

	s->lChild = createBT1(pre, in, L1 + 1, L1 + i - L2, L2, i - 1);
	s->rChild = createBT1(pre, in, L1 + i - L2 + 1, R1, i + 1, R2);
	return s;
}

BTNode *createBT2(char post[], char in[], int L1, int R1, int L2, int R2)
{
	if (L1 > R1)
		return NULL;
	BTNode *s = new BTNode();
	s->lChild = s->rChild = NULL;
	s->data = post[R1];

	int i;
	for (i = L2;i <= R2;i++)
		if (in[i] == post[R1])
			break;

	s->lChild = createBT2(post, in, L1, L1 + i - L2 - 1, L2, i - 1);
	s->rChild = createBT2(post, in, L1 + i - L2, R1 - 1, i + 1, R2);
	return s;
}

BTNode *createBT3(char level[], char in[], int n, int L, int R)
{
	if (L > R)
		return NULL;
	BTNode *s = new BTNode();
	s->lChild = s->rChild = NULL;
	s->data = level[0];

	int i = search(in, level[0], L, R);
	int LN = i - L;char *LLevel = new char[LN];
	int RN = R - i;char *RLevel = new char[RN];

	getSubLevel(LLevel, level, in, n, L, i - 1);
	getSubLevel(RLevel, level, in, n, i + 1, R);

	s->lChild = createBT3(LLevel, in, LN, L, i - 1);
	s->rChild = createBT3(RLevel, in, RN, i + 1, R);
	return s;
}

int search(char a[], char key, int L, int R)
{
	for (int i = L;i <= R;i++)
		if (a[i] == key)
			return i;
	return -1;
}

void getSubLevel(char subLevel[], char level[], char in[], int n, int L, int R)
{
	int k = 0;
	for (int i = 0;i < n;i++)
		if (search(in, level[i], L, R) != -1)
			subLevel[k++] = level[i];
}

void visit(BTNode *p)
{
	//可打印
	cout << p->data << " -> ";
	//可存入数组
	//arr[arri++] = p->data;
}

void BTlevel(BTNode *bt)
{
	if (bt != NULL)
	{
		int front, rear;
		BTNode *queue[maxSize];
		front = rear = 0;
		BTNode *p;
		rear = (rear + 1) % maxSize;
		queue[rear] = bt;
		while (front != rear)
		{
			front = (front + 1) % maxSize;
			p = queue[front];
			visit(p);
			if (p->lChild != NULL)
			{
				rear = (rear + 1) % maxSize;
				queue[rear] = p->lChild;
			}
			if (p->rChild != NULL)
			{
				rear = (rear + 1) % maxSize;
				queue[rear] = p->rChild;
			}
		}
	}
}