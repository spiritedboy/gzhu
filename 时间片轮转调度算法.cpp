#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>
#define max 100
using namespace std;
typedef struct PCB
{
	string ProcessName;   //����
	int Arrivetime;       //����ʱ��
	int Runtime;          //����ʱ��
	string state;         //����״̬  Ϊ��C����ʾ�����
	bool finish;          //��ӱ�־����ֵfalse��ʾδ��ӣ���Ӻ���Ϊtrue
	struct PCB* next;     //ָ����һ������ָ��
};
typedef struct
{
	PCB *front;
	PCB *rear;
}LinkQueue;

PCB process[max];    //��������
string printname[2 * max];  //�������    ������ȶ��еľ���˳��
LinkQueue Q;         //��������
int systime;         //ϵͳ��ʼʱ��
int num;             //��������
int outputnum = 0;   //���ȴ���


/*���г�ʼ��*/void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = new PCB;
	Q.front->next = NULL;
}
/*���*/void EnQueue(LinkQueue& Q, PCB e)
{
	PCB* p;
	p = new PCB;
	p->ProcessName = e.ProcessName;
	p->Arrivetime = e.Arrivetime;
	p->Runtime = e.Runtime;
	p->state = e.state;
	p->next = Q.front;    //�½�����ָ��ָ��ͷ��㣬����ѭ������
	Q.rear->next = p;     //���һ������ָ��ָ���½����
	Q.rear = p;           //��βָ��ָ���½����
}
/*����*/void DeQueue(PCB &temp)
{
	if (Q.front == Q.rear)
	{
		return;           //����Ϊ��,ֱ�ӷ���
	}
	PCB* p;
	p = Q.front->next;   //pָ���һ��Ԫ��
	temp= *p;            //ȡp��ֵ����temp�����ô���
	Q.front->next = p->next;   //ͷָ���Ƶ��ڶ���Ԫ����

	if (Q.rear == p)   //��������һ��Ԫ�س���
		Q.rear = Q.front;  //βָ��ָ��ͷָ��

	delete p;    //�ͷŵ�һ�������ռ�õĿռ�     
}
/*�����������*/void output()
{
	PCB* p = Q.front;    
	p = p->next;       //pָ����еĵ�һ�����
	cout <<"��ǰ��������:" << endl;
	cout << "��������" << '\t' << "���̵���ʱ��" << '\t' << "����ʣ������ʱ��" << endl;
	while (p != Q.front)
	{
		//ѭ�����еı���
		cout << p->ProcessName << '\t' << '\t' << p->Arrivetime << '\t' << '\t' << p->Runtime << endl;
		p = p->next;
	}
	cout << endl;
}
/*��������*/void sort(PCB a[], int n)
{
	//��a[]�����ǰn��Ԫ�ذ��յ���ʱ�������������,�ȵ��������ǰ��
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
/*���н���*/void Run()
{
	int i;
	systime++;   //ÿ����һ��  ϵͳʱ��+1
	outputnum++;  //���ȴ���+1
	cout << "��ǰ��ϵͳʱ��Ϊ" <<systime<<",���ǵ�" << outputnum << "�ε��ȡ�"<< endl;
	if (Q.front != Q.rear)
	{
		//�������в�Ϊ�յ����

		PCB head;
		DeQueue(head);  //����Ԫ�س��ӣ���ֵ��head
		cout << "��ǰ���еĽ�����Ϊ:" << head.ProcessName << endl;
		printname[outputnum] = head.ProcessName;    //�ѽ������Ž��������
		head.Runtime--;       //�˽�������ʱ���1

		for (i = 0; i < num; i++)
		{
			//�ж������½��̵���еĻ��½��������
			if ((systime >= process[i].Arrivetime) && (process[i].finish == false))
			{
				EnQueue(Q, process[i]);
				process[i].finish = true;   //��ӱ�־��Ϊtrue
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  //�ڵ׺���
				cout << "����"<<process[i].ProcessName << "�ڴ�ʱ��"<<systime<<"�����ˣ������!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //�ָ��ɺڵװ���
			}
		}
		if (head.Runtime > 0)
		{
			//�ж϶��׵�ʣ������ʱ���Ƿ����0��
			EnQueue(Q, head);  
			cout <<head.ProcessName << "��ʣ������ʱ�仹����0���������!" << endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  //�ڵ�����
			cout <<head.ProcessName << "��ʣ������ʱ��Ϊ0������ɵ��ȣ��������!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //�ָ��ɺڵװ���
			for (i = 0; i < num; i++)
			{
				//��process�����ҵ���Ӧ�Ľ��̣�������״̬��Ϊ��C��
				if (process[i].Arrivetime == head.Arrivetime && process[i].ProcessName == head.ProcessName)
					process[i].state = "C";   //�������ֺ͵���ʱ�����ȷ��Ψһ���̣��Ѹý��̵�״̬��Ϊ��C��
			}
		}
		output();
	}
	else
	{
		//��������Ϊ�յ����
		
		for (i = 0; i < num; i++)
		{
			//�ж������½��̵���еĻ��½������
			if ((systime >= process[i].Arrivetime) && (process[i].finish == false))
			{
				EnQueue(Q, process[i]);  //����Ԫ�����
				process[i].finish = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  //�ڵ׺���
				cout << "����" << process[i].ProcessName << "�ڴ�ʱ��" << systime << "�����ˣ������!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //�ָ��ɺڵװ���
				output();
			}
		}
	}
}
/*���벢��������*/void input()
{
	int i;
	char choice;
	InitQueue(Q);
	cout << "=========ʱ��Ƭ��ת����========" << endl;
	cout << "�û�����ģʽ����1�����ģʽ����2:" << endl;
	loop:cin >> choice;
	switch (choice)
	{
	case '1':
	{
		cout << "��������Ҫ����Ľ�������:" << endl;
		cin >> num;
		for (i = 0; i < num; i++)
		{
			cout << "�������" << i + 1 << "�����̵�����:";
			cin >> process[i].ProcessName;
			cout << "�������" << i + 1 << "�����̵ĵ���ʱ��(����):";
			cin >> process[i].Arrivetime;
			cout << "�������" << i + 1 << "�����̵�����ʱ��(����0������):";
			cin >> process[i].Runtime;
			process[i].finish = false;  //��ӱ�־�ó�ֵfalse
		}
	}; break;
	case '2':
	{
		cout << "��������Ҫ������ɵĽ�������:" << endl;
		cin >> num;
		srand(int(time(NULL)));
		for (i = 0; i < num; i++)
		{
			process[i].ProcessName = rand() % 26 + 65;   //26����дӢ����ĸ�����������
			process[i].Arrivetime = rand() % 12+rand()%3;   //����ʱ��ȡ0~13
			process[i].Runtime = rand() % 10+1;          //����ʱ��ȡ1~10
			process[i].finish = false;                   //��ӱ�־�ó�ֵfalse
		}
	}; break;
	default: 
	{
		cout << "����������������룡" << endl;
		goto loop;    //��ת��ȥ����������
	}
	}

	sort(process, num);   //���������̽�����������
	system("cls");    //����
	cout << "\n�����̵���ʱ������������ȫ�����̵���Ϣ����:\n" << endl;
	cout << "��������" << '\t' << "���̵���ʱ��" << '\t' << "����������ʱ��" << endl;
	for (i = 0; i < num; i++)
	{
		cout << process[i].ProcessName << '\t' << '\t' << process[i].Arrivetime << '\t' << '\t' << process[i].Runtime << endl;
	}
	cout << endl;
	
	systime = process[0].Arrivetime-1;  //�����process[0]�����ȵ���Ľ��̣����ĵ���ʱ���һ����ϵͳ��ʼʱ��
	for (i = 0; i < num; i++)
	{
		//���ȵ���Ľ��̿��ܲ�ֹһ���������Ƕ����
		if (process[0].Arrivetime == process[i].Arrivetime)
		{
			EnQueue(Q, process[i]);      //���
			process[i].finish = true;    //��ӱ�־��Ϊtrue
		}
	}
	output();
}
int main()
{
	int i,choice;
	input();
	cout << "���ڿ�ʼִ��ʱ��Ƭ��ת�����㷨��\n" << endl;
	while (Q.front != Q.rear || process[num - 1].finish == false)
	{
		//ֻ�ж���Ϊ�ղ�����󵽴�Ľ�������ӵ�ʱ���ֹͣ����
		Run();
	}
	cout << "ȫ���������ڶ��ѱ�����ִ����ϣ�" << endl;
	cout << "�Ƿ�����������˳���ǵĻ�����1����Ļ��밴������˳���"<<endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "�������˳��Ϊ:" << endl;
		for (i = 1; i <= outputnum; i++)
			cout << printname[i] << " ";   //��Ϊprintname�����Ǵ�1��ʼ������ݵ�
		cout << endl;
	}
	else
		return 0;
}