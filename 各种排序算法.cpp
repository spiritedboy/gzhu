#include<iostream>
#include<ctime>
using namespace std;
typedef struct
{
	int *a;     //����ͷָ��
	int size;   //���鳤��
}SqList;
/*��ʼ��*/void InitSqList(SqList &S, int m)
{
	//��ʼ��˳����������ĳ���Ϊm
	S.size = m;
	S.a = new int[S.size];
}
/*�����ֵ*/void SetValue(SqList &S)
{
	//ÿ������ǰ��Ӧ���������
	int i;
	srand(int(time(0))); 
	for (i = 1; i < S.size; i++)
	{
		S.a[i] = rand() % (S.size * 12);    //���ݱ�ȷ��������ķ�Χ
	}
}
/*���*/void OutPut(SqList &S)
{
	int i, n;
	n = 0;
	for (i = 1; i < S.size; i++)
	{
		cout << S.a[i] << " ";
		n++;
		if (n % 20 == 0)    //ÿ20�����ݾͻ���
			cout << endl;
	}
}
/*ð������*/void maopao(SqList &S)
{
	int x, j, m, flag;
	int aa = 1;  //����
	m = S.size - 2;     //n��Ԫ�رȽ�n-1�Σ�S����ֻ��size-1��Ԫ��
	int n = 0;   //�ƶ�����
	int t = 0;   //�Ƚϴ���
	flag = 1;
	while ((m > 0) && (flag == 1))
	{
		flag = 0;
		for (j = 1; j <= m; j++)
		{
			if (S.a[j] > S.a[j + 1])
			{
				flag = 1;
				n++;        //ÿ�Ƚ�һ�Σ�n����
				x = S.a[j];
				S.a[j] = S.a[j + 1];
				S.a[j + 1] = x;
			}
		}
		t = t + m;   //j��1��m����m�����ԱȽ���m��
		m--;
		if (S.size == 21)  //20�����ݵ�ʱ������ÿһ�˵Ľ��
		{
			cout << "��" << aa << "�˵Ľ����" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "ð�������Ľ��Ϊ:" << endl;
	OutPut(S);
	cout << "�Ƚϴ���:" << t << endl;
	cout << "�ƶ�����:" << n << endl;
}
/*ѡ������*/void xuanze(SqList &S)
{
	int i, j, k, t;
	int m = 0;   //�Ƚϴ���
	int n = 0;   //�ƶ�����
	int aa = 1;  //����
	for (i = 1; i <S.size - 1; i++)
	{
		k = i;
		for (j = i + 1; j < S.size; j++)
		{
			m++;     //ÿ�Ƚ�һ�Σ�m����
			if (S.a[j] < S.a[k])
				k = j;
		}
		if (k != i)
		{
			n++;      //ÿ����һ�Σ�n����
			t = S.a[i];
			S.a[i] = S.a[k];
			S.a[k] = t;
		}
		if (S.size == 21)  //20�����ݵ�ʱ������ÿһ�˵Ľ��
		{
			cout << "��" << aa << "�˵Ľ����" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "ѡ�������Ľ��Ϊ:" << endl;
	OutPut(S);
	cout << "�Ƚϴ���:" << m << endl;
	cout << "�ƶ�����:" << n << endl;
}
/*�۰��������*/void zheban(SqList &S)
{
	int low, high, i, j, mid;
	int a = 0;    //�Ƚϴ���
	int b = 0;    //�ƶ�����
	int aa = 1;  //����
	for (i = 2; i < S.size; i++)
	{
		S.a[0] = S.a[i];
		b++;      //a[i]�ƶ���a[0]
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			a++;       //ÿ�Ƚ�һ�Σ�a����
			if (S.a[0] < S.a[mid])
				high = mid - 1;   //a[0]���е�С����������е����
			else
				low = mid + 1;    //a[0]���е�󣬲�������е��ұ�
		}

		for (j = i - 1; j >= high + 1; j--)
		{
			S.a[j + 1] = S.a[j];   //�����ڳ�λ��
			b++;      //ÿ�ƶ�һ�Σ�b����   
		}
		S.a[high + 1] = S.a[0];
		b++;

		if (S.size == 21)  //20�����ݵ�ʱ������ÿһ�˵Ľ��
		{
			cout << "��" << aa << "�˵Ľ����" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "�۰���������Ľ��Ϊ:" << endl;
	OutPut(S);
	cout << "�Ƚϴ���:" << a << endl;
	cout << "�ƶ�����:" << b << endl;
}


//��Ϊ���������õ��ݹ飬����Ҫ��ȫ�ֱ���
int num1 = 0;    //��������ıȽϴ���
int num2 = 0;    //����������ƶ�����
int num3 = 1;    //�������������
/*��������*/void kuaisu(SqList &S, int low, int high)
{
	if (high <= low)   //�ݹ��������
		return;
	int i = low;
	int j = high + 1;
	int temp;
	int key = S.a[low];
	while (true)
	{
		while (S.a[--j] > key)  //���������ұ�keyС��ֵ���±�
		{
			num1++;          //�Ƚϴ�������1
			if (j == low)    //����ݼ���low���Ǿ��˳�ѭ��
			{
				break;
			}
		}

		while (S.a[++i] < key)  //���������ұ�key���ֵ���±�
		{
			num1++;         //�Ƚϴ�������1
			if (i == high)  //���������high���Ǿ��˳�ѭ��
			{
				break;
			}
		}

		if (i >= j)   //i>=j,˵��high��i�Ķ�Ӧֵȫ��key��low+1��j��ֵȫ��keyС������Ͳ���Ҫ����i��j�Ķ�Ӧֵ
			break;

		//i��Ӧֵ��key��j��Ӧֵ��keyС   i��j��Ӧֵ����λ��
		num2++;  //������������1
		temp = S.a[i];
		S.a[i] = S.a[j];
		S.a[j] = temp;
	}

	//low+1��j��ֵ����keyС��low��j��Ӧֵ����λ��
	num2++;    //������������1
	temp = S.a[low];
	S.a[low] = S.a[j];
	S.a[j] = temp;

	if (S.size == 21)  //20�����ݵ�ʱ������ÿһ�˵Ľ��
	{
		cout << "��" << num3 << "�˵Ľ����" << endl;
		OutPut(S);
		num3++;
	}
	kuaisu(S, low, j - 1);    //key����ߵݹ�����
	kuaisu(S, j + 1, high);   //key���ұߵݹ�����
}
void main()
{
	SqList S1,S2;

	InitSqList(S1, 21);   //��ʼ��˳���  n�������������n+1  ��20��������21
	InitSqList(S2, 501);    

	SetValue(S1);
	cout <<S1.size-1<< "��ԭʼ������Ϊ:" << endl;
	OutPut(S1);
	cout << endl;
	
	cout << "============ð������============" << endl;
	SetValue(S1);
	maopao(S1);
	cout << endl;

	cout << "============ѡ������============" << endl;
	SetValue(S1);
	xuanze(S1);
	cout << endl;

	cout << "============�۰��������============" << endl;
	SetValue(S1);
	zheban(S1);
	cout << endl;

	cout << "============��������============" << endl;
	SetValue(S1);
	kuaisu(S1, 1, 20);     //n�����ݾ���1��n  ��20�����ݾ���1 20
	cout << "���������Ľ��Ϊ:" << endl;
	OutPut(S1);
	cout << "�Ƚϴ���:" << num1 << endl;
	cout << "�ƶ�����:" << num2 << endl;

	//��ȫ�ֱ���num1,num2,num3��Ϊ0
	num1 = 0;
	num2 = 0;
	num3 = 0;
	//

	cout << endl << endl;

	SetValue(S2);
	cout << S2.size - 1 << "��ԭʼ������Ϊ:" << endl;
	OutPut(S2);
	cout << endl;

	cout << "============ð������============" << endl;
	SetValue(S2);
	maopao(S2);
	cout << endl;

	cout << "============ѡ������============" << endl;
	SetValue(S2);
	xuanze(S2);
	cout << endl;

	cout << "============�۰��������============" << endl;
	SetValue(S2);
	zheban(S2);
	cout << endl;

	cout << "============��������============" << endl;
	SetValue(S2);
	kuaisu(S2, 1, 500);     
	cout << "���������Ľ��Ϊ:" << endl;
	OutPut(S2);
	cout << "�Ƚϴ���:" << num1 << endl;
	cout << "�ƶ�����:" << num2 << endl;
}