#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>
#define max 100
using namespace std;
typedef struct PCB
{
	string ProcessName;   //名字
	int Arrivetime;       //到达时间
	int Runtime;          //运行时间
	string state;         //进程状态  为“C”表示已完成
	bool finish;          //入队标志，初值false表示未入队，入队后置为true
	struct PCB* next;     //指向下一个结点的指针
};
typedef struct
{
	PCB *front;
	PCB *rear;
}LinkQueue;

PCB process[max];    //进程数组
string printname[2 * max];  //输出数组    输出调度队列的具体顺序
LinkQueue Q;         //就绪队列
int systime;         //系统初始时间
int num;             //进程数量
int outputnum = 0;   //调度次数


/*队列初始化*/void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = new PCB;
	Q.front->next = NULL;
}
/*入队*/void EnQueue(LinkQueue& Q, PCB e)
{
	PCB* p;
	p = new PCB;
	p->ProcessName = e.ProcessName;
	p->Arrivetime = e.Arrivetime;
	p->Runtime = e.Runtime;
	p->state = e.state;
	p->next = Q.front;    //新建结点的指针指向头结点，构成循环链表
	Q.rear->next = p;     //最后一个结点的指针指向新建结点
	Q.rear = p;           //队尾指针指向新建结点
}
/*出队*/void DeQueue(PCB &temp)
{
	if (Q.front == Q.rear)
	{
		return;           //队列为空,直接返回
	}
	PCB* p;
	p = Q.front->next;   //p指向第一个元素
	temp= *p;            //取p的值传给temp，引用传递
	Q.front->next = p->next;   //头指针移到第二个元素上

	if (Q.rear == p)   //如果是最后一个元素出队
		Q.rear = Q.front;  //尾指针指向头指针

	delete p;    //释放第一个结点所占用的空间     
}
/*输出就绪队列*/void output()
{
	PCB* p = Q.front;    
	p = p->next;       //p指向队列的第一个结点
	cout <<"当前就绪队列:" << endl;
	cout << "进程名字" << '\t' << "进程到达时间" << '\t' << "进程剩余运行时间" << endl;
	while (p != Q.front)
	{
		//循环队列的遍历
		cout << p->ProcessName << '\t' << '\t' << p->Arrivetime << '\t' << '\t' << p->Runtime << endl;
		p = p->next;
	}
	cout << endl;
}
/*升序排序*/void sort(PCB a[], int n)
{
	//对a[]数组的前n个元素按照到达时间进行升序排序,先到达的排在前面
	int i, j, k;
	PCB temp;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].Arrivetime < a[k].Arrivetime)
				k = j;
		}
		if (k != i)
		{
			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
}
/*运行进程*/void Run()
{
	int i;
	systime++;   //每调度一次  系统时间+1
	outputnum++;  //调度次数+1
	cout << "当前的系统时刻为" <<systime<<",这是第" << outputnum << "次调度。"<< endl;
	if (Q.front != Q.rear)
	{
		//就绪队列不为空的情况

		PCB head;
		DeQueue(head);  //队首元素出队，赋值给head
		cout << "当前运行的进程名为:" << head.ProcessName << endl;
		printname[outputnum] = head.ProcessName;    //把进程名放进输出数组
		head.Runtime--;       //此进程运行时间减1

		for (i = 0; i < num; i++)
		{
			//判断有无新进程到达，有的话新进程先入队
			if ((systime >= process[i].Arrivetime) && (process[i].finish == false))
			{
				EnQueue(Q, process[i]);
				process[i].finish = true;   //入队标志置为true
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  //黑底红字
				cout << "进程"<<process[i].ProcessName << "在此时刻"<<systime<<"到达了，先入队!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //恢复成黑底白字
			}
		}
		if (head.Runtime > 0)
		{
			//判断队首的剩余运行时间是否大于0，
			EnQueue(Q, head);  
			cout <<head.ProcessName << "的剩余运行时间还大于0，重新入队!" << endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  //黑底绿字
			cout <<head.ProcessName << "的剩余运行时间为0，已完成调度，不再入队!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //恢复成黑底白字
			for (i = 0; i < num; i++)
			{
				//在process数组找到对应的进程，把它的状态置为“C”
				if (process[i].Arrivetime == head.Arrivetime && process[i].ProcessName == head.ProcessName)
					process[i].state = "C";   //根据名字和到达时间可以确定唯一进程，把该进程的状态置为“C”
			}
		}
		output();
	}
	else
	{
		//就绪队列为空的情况
		
		for (i = 0; i < num; i++)
		{
			//判断有无新进程到达，有的话新进程入队
			if ((systime >= process[i].Arrivetime) && (process[i].finish == false))
			{
				EnQueue(Q, process[i]);  //有新元素入队
				process[i].finish = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  //黑底红字
				cout << "进程" << process[i].ProcessName << "在此时刻" << systime << "到达了，先入队!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //恢复成黑底白字
				output();
			}
		}
	}
}
/*输入并处理数据*/void input()
{
	int i;
	char choice;
	InitQueue(Q);
	cout << "=========时间片轮转调度========" << endl;
	cout << "用户输入模式请输1，随机模式请输2:" << endl;
	loop:cin >> choice;
	switch (choice)
	{
	case '1':
	{
		cout << "请输入你要输入的进程数量:" << endl;
		cin >> num;
		for (i = 0; i < num; i++)
		{
			cout << "请输入第" << i + 1 << "个进程的名字:";
			cin >> process[i].ProcessName;
			cout << "请输入第" << i + 1 << "个进程的到达时间(整数):";
			cin >> process[i].Arrivetime;
			cout << "请输入第" << i + 1 << "个进程的运行时间(大于0的整数):";
			cin >> process[i].Runtime;
			process[i].finish = false;  //入队标志置初值false
		}
	}; break;
	case '2':
	{
		cout << "请输入你要随机生成的进程数量:" << endl;
		cin >> num;
		srand(int(time(NULL)));
		for (i = 0; i < num; i++)
		{
			process[i].ProcessName = rand() % 26 + 65;   //26个大写英文字母随机生成名字
			process[i].Arrivetime = rand() % 12+rand()%3;   //到达时间取0~13
			process[i].Runtime = rand() % 10+1;          //运行时间取1~10
			process[i].finish = false;                   //入队标志置初值false
		}
	}; break;
	default: 
	{
		cout << "输入错误，请重新输入！" << endl;
		goto loop;    //跳转回去，重新输入
	}
	}

	sort(process, num);   //对上述进程进行升序排序
	system("cls");    //清屏
	cout << "\n按进程到达时间进行排序处理后，全部进程的信息如下:\n" << endl;
	cout << "进程名字" << '\t' << "进程到达时间" << '\t' << "进程总运行时间" << endl;
	for (i = 0; i < num; i++)
	{
		cout << process[i].ProcessName << '\t' << '\t' << process[i].Arrivetime << '\t' << '\t' << process[i].Runtime << endl;
	}
	cout << endl;
	
	systime = process[0].Arrivetime-1;  //排序后process[0]是最先到达的进程，它的到达时间减一当作系统初始时间
	for (i = 0; i < num; i++)
	{
		//最先到达的进程可能不止一个，把它们都入队
		if (process[0].Arrivetime == process[i].Arrivetime)
		{
			EnQueue(Q, process[i]);      //入队
			process[i].finish = true;    //入队标志置为true
		}
	}
	output();
}
int main()
{
	int i,choice;
	input();
	cout << "现在开始执行时间片轮转调度算法！\n" << endl;
	while (Q.front != Q.rear || process[num - 1].finish == false)
	{
		//只有队列为空并且最后到达的进程已入队的时候才停止调度
		Run();
	}
	cout << "全部进程现在都已被调度执行完毕！" << endl;
	cout << "是否输出具体调度顺序？是的话请输1，否的话请按任意键退出。"<<endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "具体调度顺序为:" << endl;
		for (i = 1; i <= outputnum; i++)
			cout << printname[i] << " ";   //因为printname数组是从1开始填充数据的
		cout << endl;
	}
	else
		return 0;
}