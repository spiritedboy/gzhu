#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<cmath>
#include<cstring>
#define max 50
using namespace std;

int arr[max], copyarr[max], finished[max];   //arr�������������������У�copyarrΪ�������飬ֵ��arr��ͬ
int num;   //����Ԫ�ظ���                    //finished�������������ź���Ķ��У�SSTF�͵��ݷ���Ҫ�õ���
int n1 = 0;    //�ݹ����
int start;  //��ͷ��ʼλ��

/*�����ֵ*/void SetValue()
{
	int i;
	srand(int(time(0)));
	for (i = 0; i < num; i++)
	{
		arr[i] = rand() % 200;
		copyarr[i] = arr[i];
	}
}
/*����*/void input()
{
	int i;
	cout << "������������̷���Ķ���Ԫ�ظ���:" << endl;
	cin >> num;
	SetValue();   //���ø�ֵ����
	cout << "������̷�������Ϊ:";
	for (i = 0; i < num; i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << "�������ͷ��ʼλ��:";
	cin >> start;
	cout << endl;
}
/*��������*/void sort(int a[], int m)
{
	//��a�����ǰm��Ԫ�ؽ����������򣬼�С����ǰ������ں�
	int i, j, k, temp;
	for (i = 0; i < m - 1; i++)
	{
		k = i;
		for (j = i + 1; j < m; j++)
		{
			if (a[j] < a[k])
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
/*�����ܴŵ���*/void sum(int a[])
{
	//����Ӵ�ͷ��ʼλ�ñ�����a�������ߵĴŵ���
	int i;
	int total = 0;
	total = total + abs(start - a[0]);  //��ʼλ�����һ��Ԫ��a[0]��λ�ò�ֵ�ľ���ֵ
	for (i = 0; i < num - 1; i++)
	{
		total = total + abs(a[i] - a[i + 1]);  //����ֵ�����ۼ�
	}
	cout << "��ͷ���ƶ��Ĵŵ���Ϊ:" << total << endl;
	cout << "��ͷ�ƶ�˳��Ϊ:";
	cout << start;
	for (i = 0; i < num; i++)
		cout << "->" << a[i];    //����Ӵ�ͷ��ʼλ�ñ�����a����Ĵ�ͷ�켣
	cout << endl;
	cout << endl;
}
/*�����ȷ���*/void FCFS()
{
	cout << "�����ȷ���:" << endl;
	sum(arr);     //�����ȷ��񷨲���Ҫ��������ֱ�ӵ���sum������������arr���顣
}
/*���Ѱ��ʱ�����ȷ�*/void SSTF(int x, int y)
{
	//xΪԪ�ظ�����yΪ��ͷ��ʼλ��

	if (x == 0)   //�˳��ݹ������
	{
		cout << "���Ѱ��ʱ�����ȷ�:" << endl;
		sum(finished);   //������sum����������Ϊfinished����
		return;
	}
	int i, t, temp[max];
	int flag=0;   //���
	int newstart;  //�µ���ʼλ��
	
	for (i = 0; i < x; i++)
		temp[i] = abs(y - copyarr[i]);   //������ʼλ��y��copyarr����ǰx��Ԫ�صĲ�ֵ�ľ���ֵ���Ž�temp����
	
	sort(temp, x);   //��temp���ֽ�����������������ɺ�temp[0]Ϊ��Сֵ
	
	for (i = 0; i < x; i++)
	{
		//�ж���ʼλ��y��temp[0]����Ӧ��Ԫ�ش�С
		if (y + temp[0] == copyarr[i])
		{
			flag = 1;   //copyarr[i]��y��
			break;
		}
		if (y - temp[0] == copyarr[i])
		{
			flag = 2;   //copyarr[i]��yС
			break;
		}
	}
	switch (flag)
	{
	case 1:newstart = y + temp[0]; break;  //copyarr[i]��y���µ���ʼλ��Ϊy+temp[0]
	case 2:newstart = y - temp[0]; break;  //copyarr[i]��yС���µ���ʼλ��Ϊy-temp[0]
	}

	for (i = 0; i < x; i++)
	{
		if (copyarr[i] == newstart)   //�ڸ�������copyarr���ҵ�newstart��λ��
			break;
	}

	t = copyarr[i];
	copyarr[i] = copyarr[x - 1];
	copyarr[x - 1] = t;             //�����һ��Ԫ�غ�newstart����λ��

	finished[n1++] = newstart;       //��newstart���finished����
	SSTF(x - 1, newstart);          //�ݹ���ã�Ԫ�ظ�����1���µ���ʼλ��
}
/*���ݷ�*/void dianti()
{
	int i, j, k;
	int temp[max];
	memcpy(temp, arr, sizeof(temp));    //��arr���鸴�Ƹ�temp
	temp[num] = start;    //�Ѵ�ͷ��ʼλ��start�Ž�temp���飬������λ
	sort(temp, num + 1);   //��temp�����������
	for (i = 0; i < num + 1; i++)
	{
		if (temp[i] == start)    //�ҵ�start��λ��
			break;
	}
	cout << "���ݷ�:" << endl;
	cout << "������������:" << endl;
	k = 0;
	for (j = i - 1; j >= 0; j--)
		finished[k++] = temp[j];   //��startС��Ԫ�ؽ���Ž�finished����
	for (j = i + 1; j <= num; j++)
		finished[k++] = temp[j];   //��start���Ԫ������Ž�finished����
	sum(finished);    //������sum����������Ϊfinished����

	cout << "���ݷ�:" << endl;
	cout << "������������:" << endl;
	k = 0;
	for (j = i + 1; j <= num; j++)
		finished[k++] = temp[j];
	for (j = i - 1; j >= 0; j--)
		finished[k++] = temp[j];
	sum(finished);
}
int main()
{
	input();
	FCFS();
	SSTF(num, start);
	dianti();
}
