#include<iostream>
#include<string>
#include<ctime>
using namespace std;
typedef struct Array
{
	string name;
	int size;
	int start;
	int end;
	bool state;  //false为空闲，true为占用
};  //内存区块
typedef struct LNode
{
	Array arr;
	struct LNode* next;
}*Linklist;  //链表

Array r1, r2, r3, r4, r5, temp;
int order[10];  //存放每个空闲区块的大小
int n;   //空闲区块的数量
Linklist L;

/*设置区块值*/void setArray(Array& r, int a, int b, int c, bool d)
{
	r.size = a;
	r.start = b;
	r.end = c;
	r.state = d;
}
/*插入*/void Insert(Array e)
{
	LNode* q = L;
	while (q->next != NULL)
		q = q->next;    //找到队尾
	LNode* p = new LNode;
	p->arr = e;
	p->next = NULL;
	q->next = p;
}
/*删除*/void Delete(Array e)
{
	//在链表中找到e结点并删除
	LNode* q = L;
	LNode* p = L->next;
	while (p->next != NULL)
	{
		if (p->arr.size == e.size && p->arr.start == e.start)
			break;          //这里条件可以换成p->arr==e  但是要重载==  我懒得写重载函数
		q = q->next;
		p = p->next;
	}
	q->next = p->next;
	p->next = NULL;
	delete p;
}
/*赋值*/void SetValue()
{
	srand(int(time(NULL)));
	int a1, a2, a3, a4;
	a1 = rand() % 256;
	a2 = rand() % 256 + a1;
	a3 = rand() % 256 + a2;
	a4 = rand() % 256 + a3;

	setArray(r1, a1, 0, a1, false);
	setArray(r2, a2 - a1, a1, a2, true);
	setArray(r3, a3 - a2, a2, a3, false);
	setArray(r4, a4 - a3, a3, a4, true);
	setArray(r5, 1024 - a4, a4, 1024, false);

	//刚开始默认有两个区块被占用，名字分别是a和b
	r2.name = "a";
	r4.name = "b";

	//初始化空链表
	L = new LNode;
	L->next = NULL;

	//把初始化的结点全部插入链表
	Insert(r1);
	Insert(r2);
	Insert(r3);
	Insert(r4);
	Insert(r5);   
}
/*输入*/void Input(Array& e)
{
	//e的赋值
	cout << "请输入你要创建的进程名字:";
	cin >> e.name;
	cout << "请输入你要创建的进程大小:";
	cin >> e.size;
	e.state = true;
}
/*输出*/void Output()
{
	//输出链表的全部值
	LNode* q = L->next;
	cout << "当前分区情况为:" << endl;
	while (q != NULL)
	{
		if (q->arr.state == false)
		{
			cout << "空闲区:  进程名字:无  起始位置:" << q->arr.start << "  结束位置:" << q->arr.end << "  大小:" << q->arr.size << endl;
		}
		else
			cout << "占用区:  进程名字:" << q->arr.name << "   起始位置:" << q->arr.start << "  结束位置:" << q->arr.end << "  大小:" << q->arr.size << endl;
		q = q->next;
	}
}
/*合并*/void Combine()
{
	LNode* q = L->next;
	LNode* p = q->next;
	while (p != NULL)
	{
		if (q->arr.state == false && p->arr.state == false)
		{
			//相邻两个空闲区合并在一起
			p->arr.start = q->arr.start;
			p->arr.size = q->arr.size + p->arr.size;
			Delete(q->arr);  //调用删除函数，删掉前一个结点
		}
		q = p;
		p = p->next;
	}
}
/*回收*/void Recycle(string s)
{
	//找到进程名字为s并且状态为已占用（true）的结点，把它的状态修改为空闲（false）
	LNode* p = L->next;
	while (p != NULL)
	{
		if (p->arr.name == s && p->arr.state == true)
		{
			p->arr.state = false;
			break;
		}
		p = p->next;
	}
	Combine();   //调用合并函数就可以回收该结点
}
/*分割*/void Cut(Array reply, Array apply)
{
	//把一个空闲结点分成两个结点  已占用结点后面跟着空闲结点
	//reply为空闲分区，apply为申请分区

	if (reply.size < apply.size)
		return;  //申请分区的大小大于空闲分区，直接返回
	LNode* q = L;
	LNode* p = L->next;
	LNode* temp = new LNode;
	temp->arr = apply;  //把apply赋值给temp
	while (p->next != NULL)
	{
		//找到reply在链表中所对应的结点指针p和它的前一个结点指针q
		if (p->arr.size == reply.size && p->arr.start == reply.start)
			break;
		q = q->next;
		p = p->next;
	}
	q->next = temp;   //前一个结点q接temp
	temp->next = p;   //temp接p

	//修改结点的数据
	temp->arr.start = p->arr.start;
	if (p->arr.start == 0)
		temp->arr.end = temp->arr.size;
	else
		temp->arr.end = p->arr.end - (p->arr.size - temp->arr.size);
	p->arr.start = temp->arr.end;
	p->arr.size = p->arr.size - temp->arr.size;

	//分割完之后可能出现大小为0的空闲分区，遍历链表，找到并删除大小为0的结点即可
	q = L->next;
	while (q != NULL)
	{
		if (q->arr.size == 0)
		{
			Delete(q->arr);
			break;
		}
		q = q->next;
	}
}
/*数组处理*/void Manage()
{
	//把空闲分区的大小依次赋值给order数组
	LNode* p = L->next;
	n = 0;
	while (p != NULL)
	{
		if (p->arr.state == false)
			order[n++] = p->arr.size;
		p = p->next;
	}
}
/*排序*/void Sort(int choice)
{
	//choice=0是升序，choice=1是降序

	Manage();  //每次排序前都重新处理order数组
	int i, j, k;
	int temp;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (choice == 0)
			{
				if (order[j] < order[k])
					k = j;
			}
			else
			{
				if (order[j] > order[k])
					k = j;
			}
		}
		if (k != i)
		{
			temp = order[i];
			order[i] = order[k];
			order[k] = temp;
		}
	}
}
/*首先适配算法*/void FF()
{
	Input(temp);
	LNode* p = L->next;

	Sort(1);  //降序排序
	if (order[0] < temp.size)
	{
		cout << "空闲分区都不满足分配需求，分配失败！" << endl;
		return;
	}

	while (p->next != NULL)
	{
		//按顺序查找，碰到第一个满足分配条件的空闲分区就停止查找
		if (p->arr.size >= temp.size && p->arr.state == false)
		{
			Cut(p->arr, temp);  //对该结点调用分割函数
			break;
		}
		p = p->next;
	}

	Output();
}
/*循环首先适配算法*/void NF()
{
	Input(temp);

	Sort(1);  //降序排序
	if (order[0] < temp.size)  //order[0]是最大的空闲分区
	{
		cout << "空闲分区都不满足分配需求，分配失败！" << endl;
		return;
	}
	
	static LNode* p = L->next;
	LNode* q;

	while (1)  //因为有满足分配条件的空闲分区，所以这不是死循环
	{
		if (p == NULL)
			p = L->next;  //从头开始

		//按顺序查找，碰到第一个满足分配条件的空闲分区就停止查找
		if (p->arr.size >= temp.size && p->arr.state == false)
		{
			q = p->next;   //q指向p的下一个结点
			Cut(p->arr, temp);  //分割p
			p = q; 
			break;
		}
		p = p->next;
	}
	Output();
}
/*最佳适配算法*/void BF()
{
	int x;
	LNode* p = L->next;
	Input(temp);

	Sort(1);  //降序排序
	if (order[0] < temp.size)
	{
		cout << "空闲分区都不满足分配需求，分配失败！" << endl;
		return;
	}

	Sort(0);  //升序排序
	for (x = 0; x < n; x++)
	{
		//从小往大找，找到满足分配条件的最小空闲分区数组下标
		if (order[x] >= temp.size)
			break;
	}
	while (p != NULL)
	{
		//遍历链表，根据该下标对应的数组大小值查找目标分区在链表中的位置
		if (p->arr.size == order[x] && p->arr.state == false)
		{
			Cut(p->arr, temp);  //对该结点调用分割函数
			break;
		}
		p = p->next;
	}
	Output();
}
/*最坏适配算法*/void WF()
{
	LNode* p = L->next;
	Input(temp);

	Sort(1);  //降序排序
	if (order[0] < temp.size)
	{
		cout << "空闲分区都不满足分配需求，分配失败！" << endl;
		return;
	}

	while (p != NULL)
	{
		//遍历链表，找到order[0]所对应的分区位置  降序排序后order[0]最大
		if (p->arr.size == order[0] && p->arr.state == false)
		{
			Cut(p->arr, temp);  //对该结点调用分割函数
			break;
		}
		p = p->next;
	}
	Output();
}
int main()
{
	int choice;
	string name;
	SetValue();
loop:
	Output();
	cout << endl;
	cout << "请输入你要进行的操作:" << endl;
	cout << "1、首先适配算法  2、循环首先适配算法  3、最佳适配算法  4、最坏适配算法  5、重新生成内存分区  6、回收进程  7、退出" << endl;
	cout << "你的操作为:";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		cout << "开始执行FF算法" << endl;
		while (1)
		{
			cout << "请输入你要进行的操作:" << endl;
			cout << "1、新建进程  2、回收进程  3、返回上一级菜单  4、退出程序" << endl;
			cout << "你的操作为:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				FF();
			}; break;
			case 2:
			{
				cout << "请输入你要回收的进程名字:";
				cin >> name;
				Recycle(name);
				Output();
			}; break;
			case 3:
			{
				system("cls");
				goto loop;
			}; break;
			case 4:return 0; break;
			default:return 1;
			}
		}
	}; break;
	case 2:
	{
		{
			cout << "开始执行NF算法" << endl;
			while (1)
			{
				cout << "请输入你要进行的操作:" << endl;
				cout << "1、新建进程  2、回收进程  3、返回上一级菜单  4、退出程序" << endl;
				cout << "你的操作为:";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					NF();
				}; break;
				case 2:
				{
					cout << "请输入你要回收的进程名字:";
					cin >> name;
					Recycle(name);
					Output();
				}; break;
				case 3:
				{
					system("cls");
					goto loop;
				}; break;
				case 4:return 0; break;
				default:return 1;
				}
			}
		}; break;
	}; break;
	case 3:
	{
		cout << "开始执行BF算法" << endl;
		while (1)
		{
			cout << "请输入你要进行的操作:" << endl;
			cout << "1、新建进程  2、回收进程  3、返回上一级菜单  4、退出程序" << endl;
			cout << "你的操作为:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				BF();
			}; break;
			case 2:
			{
				cout << "请输入你要回收的进程名字:";
				cin >> name;
				Recycle(name);
				Output();
			}; break;
			case 3:
			{
				system("cls");
				goto loop;
			}; break;
			case 4:return 0; break;
			default:return 1;
			}
		}
	}; break;
	case 4:
	{
		cout << "开始执行WF算法" << endl;
		while (1)
		{
			cout << "请输入你要进行的操作:" << endl;
			cout << "1、新建进程  2、回收进程  3、返回上一级菜单  4、退出程序" << endl;
			cout << "你的操作为:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				WF();
			}; break;
			case 2:
			{
				cout << "请输入你要回收的进程名字:";
				cin >> name;
				Recycle(name);
				Output();
			}; break;
			case 3:
			{
				system("cls");
				goto loop;
			}; break;
			case 4:return 0; break;
			default:return 1;
			}
		}
	}; break;
	case 5:
	{
		SetValue();
		system("cls");
		goto loop;
	}; break;
	case 6:
	{
		cout << "请输入你要回收的进程名字:";
		cin >> name;
		Recycle(name);
		system("cls");
		goto loop;
	}; break;
	case 7:return 0; break;
	default:return 1;
	}
}
