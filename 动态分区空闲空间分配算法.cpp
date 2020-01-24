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
	bool state;  //falseΪ���У�trueΪռ��
};  //�ڴ�����
typedef struct LNode
{
	Array arr;
	struct LNode* next;
}*Linklist;  //����

Array r1, r2, r3, r4, r5, temp;
int order[10];  //���ÿ����������Ĵ�С
int n;   //�������������
Linklist L;

/*��������ֵ*/void setArray(Array& r, int a, int b, int c, bool d)
{
	r.size = a;
	r.start = b;
	r.end = c;
	r.state = d;
}
/*����*/void Insert(Array e)
{
	LNode* q = L;
	while (q->next != NULL)
		q = q->next;    //�ҵ���β
	LNode* p = new LNode;
	p->arr = e;
	p->next = NULL;
	q->next = p;
}
/*ɾ��*/void Delete(Array e)
{
	//���������ҵ�e��㲢ɾ��
	LNode* q = L;
	LNode* p = L->next;
	while (p->next != NULL)
	{
		if (p->arr.size == e.size && p->arr.start == e.start)
			break;          //�����������Ի���p->arr==e  ����Ҫ����==  ������д���غ���
		q = q->next;
		p = p->next;
	}
	q->next = p->next;
	p->next = NULL;
	delete p;
}
/*��ֵ*/void SetValue()
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

	//�տ�ʼĬ�����������鱻ռ�ã����ֱַ���a��b
	r2.name = "a";
	r4.name = "b";

	//��ʼ��������
	L = new LNode;
	L->next = NULL;

	//�ѳ�ʼ���Ľ��ȫ����������
	Insert(r1);
	Insert(r2);
	Insert(r3);
	Insert(r4);
	Insert(r5);   
}
/*����*/void Input(Array& e)
{
	//e�ĸ�ֵ
	cout << "��������Ҫ�����Ľ�������:";
	cin >> e.name;
	cout << "��������Ҫ�����Ľ��̴�С:";
	cin >> e.size;
	e.state = true;
}
/*���*/void Output()
{
	//��������ȫ��ֵ
	LNode* q = L->next;
	cout << "��ǰ�������Ϊ:" << endl;
	while (q != NULL)
	{
		if (q->arr.state == false)
		{
			cout << "������:  ��������:��  ��ʼλ��:" << q->arr.start << "  ����λ��:" << q->arr.end << "  ��С:" << q->arr.size << endl;
		}
		else
			cout << "ռ����:  ��������:" << q->arr.name << "   ��ʼλ��:" << q->arr.start << "  ����λ��:" << q->arr.end << "  ��С:" << q->arr.size << endl;
		q = q->next;
	}
}
/*�ϲ�*/void Combine()
{
	LNode* q = L->next;
	LNode* p = q->next;
	while (p != NULL)
	{
		if (q->arr.state == false && p->arr.state == false)
		{
			//���������������ϲ���һ��
			p->arr.start = q->arr.start;
			p->arr.size = q->arr.size + p->arr.size;
			Delete(q->arr);  //����ɾ��������ɾ��ǰһ�����
		}
		q = p;
		p = p->next;
	}
}
/*����*/void Recycle(string s)
{
	//�ҵ���������Ϊs����״̬Ϊ��ռ�ã�true���Ľ�㣬������״̬�޸�Ϊ���У�false��
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
	Combine();   //���úϲ������Ϳ��Ի��ոý��
}
/*�ָ�*/void Cut(Array reply, Array apply)
{
	//��һ�����н��ֳ��������  ��ռ�ý�������ſ��н��
	//replyΪ���з�����applyΪ�������

	if (reply.size < apply.size)
		return;  //��������Ĵ�С���ڿ��з�����ֱ�ӷ���
	LNode* q = L;
	LNode* p = L->next;
	LNode* temp = new LNode;
	temp->arr = apply;  //��apply��ֵ��temp
	while (p->next != NULL)
	{
		//�ҵ�reply������������Ӧ�Ľ��ָ��p������ǰһ�����ָ��q
		if (p->arr.size == reply.size && p->arr.start == reply.start)
			break;
		q = q->next;
		p = p->next;
	}
	q->next = temp;   //ǰһ�����q��temp
	temp->next = p;   //temp��p

	//�޸Ľ�������
	temp->arr.start = p->arr.start;
	if (p->arr.start == 0)
		temp->arr.end = temp->arr.size;
	else
		temp->arr.end = p->arr.end - (p->arr.size - temp->arr.size);
	p->arr.start = temp->arr.end;
	p->arr.size = p->arr.size - temp->arr.size;

	//�ָ���֮����ܳ��ִ�СΪ0�Ŀ��з��������������ҵ���ɾ����СΪ0�Ľ�㼴��
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
/*���鴦��*/void Manage()
{
	//�ѿ��з����Ĵ�С���θ�ֵ��order����
	LNode* p = L->next;
	n = 0;
	while (p != NULL)
	{
		if (p->arr.state == false)
			order[n++] = p->arr.size;
		p = p->next;
	}
}
/*����*/void Sort(int choice)
{
	//choice=0������choice=1�ǽ���

	Manage();  //ÿ������ǰ�����´���order����
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
/*���������㷨*/void FF()
{
	Input(temp);
	LNode* p = L->next;
	while (p->next != NULL)
	{
		//��˳����ң�������һ��������������Ŀ��з�����ֹͣ����
		if (p->arr.size >= temp.size && p->arr.state == false)
			break;
		p = p->next;
	}
	if (p->arr.size < temp.size || p->arr.state == true)
	{
		cout << "���з�����������������󣬷���ʧ�ܣ�" << endl;
		return;
	}
	Cut(p->arr, temp);  //�Ըý����÷ָ��
	Output();
}
/*ѭ�����������㷨*/void NF()
{
	Input(temp);
	Sort(1);  //��������

	if (order[0] < temp.size)  //order[0]�����Ŀ��з���
	{
		cout << "���з�����������������󣬷���ʧ�ܣ�" << endl;
		return;
	}
	
	static LNode* p = L->next;
	LNode* q;

	while (1)  //��Ϊ��������������Ŀ��з����������ⲻ����ѭ��
	{
		if (p == NULL)
			p = L->next;  //��ͷ��ʼ

		//��˳����ң�������һ��������������Ŀ��з�����ֹͣ����
		if (p->arr.size >= temp.size && p->arr.state == false)
		{
			q = p->next;   //qָ��p����һ�����
			Cut(p->arr, temp);  //�ָ�p
			p = q; 
			break;
		}
		p = p->next;
	}
	Output();
}
/*��������㷨*/void BF()
{
	int x;
	LNode* p = L->next;
	Input(temp);
	Sort(0);  //��������

	for (x = 0; x < n; x++)
	{
		//��С�����ң��ҵ����������������С���з��������±�
		if (order[x] >= temp.size)
			break;
	}
	if (order[x] < temp.size)
	{
		cout << "���з�����������������󣬷���ʧ�ܣ�" << endl;
		return;
	}
	while (p != NULL)
	{
		//�����������ݸ��±��Ӧ�������Сֵ����Ŀ������������е�λ��
		if (p->arr.size == order[x] && p->arr.state == false)
		{
			Cut(p->arr, temp);  //�Ըý����÷ָ��
			break;
		}
		p = p->next;
	}
	Output();
}
/*������㷨*/void WF()
{
	LNode* p = L->next;
	Input(temp);
	Sort(1);  //��������

	if (order[0] < temp.size)
	{
		cout << "���з�����������������󣬷���ʧ�ܣ�" << endl;
		return;
	}
	while (p != NULL)
	{
		//���������ҵ�order[0]����Ӧ�ķ���λ��  ���������order[0]���
		if (p->arr.size == order[0] && p->arr.state == false)
		{
			Cut(p->arr, temp);  //�Ըý����÷ָ��
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
	cout << "��������Ҫ���еĲ���:" << endl;
	cout << "1�����������㷨  2��ѭ�����������㷨  3����������㷨  4��������㷨  5�����������ڴ����  6�����ս���  7���˳�" << endl;
	cout << "��Ĳ���Ϊ:";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		cout << "��ʼִ��FF�㷨" << endl;
		while (1)
		{
			cout << "��������Ҫ���еĲ���:" << endl;
			cout << "1���½�����  2�����ս���  3��������һ���˵�  4���˳�����" << endl;
			cout << "��Ĳ���Ϊ:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				FF();
			}; break;
			case 2:
			{
				cout << "��������Ҫ���յĽ�������:";
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
			cout << "��ʼִ��NF�㷨" << endl;
			while (1)
			{
				cout << "��������Ҫ���еĲ���:" << endl;
				cout << "1���½�����  2�����ս���  3��������һ���˵�  4���˳�����" << endl;
				cout << "��Ĳ���Ϊ:";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					NF();
				}; break;
				case 2:
				{
					cout << "��������Ҫ���յĽ�������:";
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
		cout << "��ʼִ��BF�㷨" << endl;
		while (1)
		{
			cout << "��������Ҫ���еĲ���:" << endl;
			cout << "1���½�����  2�����ս���  3��������һ���˵�  4���˳�����" << endl;
			cout << "��Ĳ���Ϊ:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				BF();
			}; break;
			case 2:
			{
				cout << "��������Ҫ���յĽ�������:";
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
		cout << "��ʼִ��WF�㷨" << endl;
		while (1)
		{
			cout << "��������Ҫ���еĲ���:" << endl;
			cout << "1���½�����  2�����ս���  3��������һ���˵�  4���˳�����" << endl;
			cout << "��Ĳ���Ϊ:";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				WF();
			}; break;
			case 2:
			{
				cout << "��������Ҫ���յĽ�������:";
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
		cout << "��������Ҫ���յĽ�������:";
		cin >> name;
		Recycle(name);
		system("cls");
		goto loop;
	}; break;
	case 7:return 0; break;
	default:return 1;
	}
}