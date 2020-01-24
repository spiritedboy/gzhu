#include<iostream>
#include<ctime>
using namespace std;
typedef struct
{
	int *a;     //数组头指针
	int size;   //数组长度
}SqList;
/*初始化*/void InitSqList(SqList &S, int m)
{
	//初始化顺序表，并置它的长度为m
	S.size = m;
	S.a = new int[S.size];
}
/*赋随机值*/void SetValue(SqList &S)
{
	//每次排序前都应先置随机数
	int i;
	srand(int(time(0))); 
	for (i = 1; i < S.size; i++)
	{
		S.a[i] = rand() % (S.size * 12);    //根据表长确定随机数的范围
	}
}
/*输出*/void OutPut(SqList &S)
{
	int i, n;
	n = 0;
	for (i = 1; i < S.size; i++)
	{
		cout << S.a[i] << " ";
		n++;
		if (n % 20 == 0)    //每20个数据就换行
			cout << endl;
	}
}
/*冒泡排序*/void maopao(SqList &S)
{
	int x, j, m, flag;
	int aa = 1;  //趟数
	m = S.size - 2;     //n个元素比较n-1次，S表里只有size-1个元素
	int n = 0;   //移动次数
	int t = 0;   //比较次数
	flag = 1;
	while ((m > 0) && (flag == 1))
	{
		flag = 0;
		for (j = 1; j <= m; j++)
		{
			if (S.a[j] > S.a[j + 1])
			{
				flag = 1;
				n++;        //每比较一次，n自增
				x = S.a[j];
				S.a[j] = S.a[j + 1];
				S.a[j + 1] = x;
			}
		}
		t = t + m;   //j从1到m共有m，所以比较了m次
		m--;
		if (S.size == 21)  //20个数据的时候才输出每一趟的结果
		{
			cout << "第" << aa << "趟的结果是" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "冒泡排序后的结果为:" << endl;
	OutPut(S);
	cout << "比较次数:" << t << endl;
	cout << "移动次数:" << n << endl;
}
/*选择排序*/void xuanze(SqList &S)
{
	int i, j, k, t;
	int m = 0;   //比较次数
	int n = 0;   //移动次数
	int aa = 1;  //趟数
	for (i = 1; i <S.size - 1; i++)
	{
		k = i;
		for (j = i + 1; j < S.size; j++)
		{
			m++;     //每比较一次，m自增
			if (S.a[j] < S.a[k])
				k = j;
		}
		if (k != i)
		{
			n++;      //每交换一次，n自增
			t = S.a[i];
			S.a[i] = S.a[k];
			S.a[k] = t;
		}
		if (S.size == 21)  //20个数据的时候才输出每一趟的结果
		{
			cout << "第" << aa << "趟的结果是" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "选择排序后的结果为:" << endl;
	OutPut(S);
	cout << "比较次数:" << m << endl;
	cout << "移动次数:" << n << endl;
}
/*折半插入排序*/void zheban(SqList &S)
{
	int low, high, i, j, mid;
	int a = 0;    //比较次数
	int b = 0;    //移动次数
	int aa = 1;  //趟数
	for (i = 2; i < S.size; i++)
	{
		S.a[0] = S.a[i];
		b++;      //a[i]移动到a[0]
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			a++;       //每比较一次，a自增
			if (S.a[0] < S.a[mid])
				high = mid - 1;   //a[0]比中点小，插入点在中点左边
			else
				low = mid + 1;    //a[0]比中点大，插入点在中点右边
		}

		for (j = i - 1; j >= high + 1; j--)
		{
			S.a[j + 1] = S.a[j];   //后移腾出位置
			b++;      //每移动一次，b自增   
		}
		S.a[high + 1] = S.a[0];
		b++;

		if (S.size == 21)  //20个数据的时候才输出每一趟的结果
		{
			cout << "第" << aa << "趟的结果是" << endl;
			OutPut(S);  
			aa++;
		}
	}
	cout << "折半插入排序后的结果为:" << endl;
	OutPut(S);
	cout << "比较次数:" << a << endl;
	cout << "移动次数:" << b << endl;
}


//因为快速排序用到递归，所以要用全局变量
int num1 = 0;    //快速排序的比较次数
int num2 = 0;    //快速排序的移动次数
int num3 = 1;    //快速排序的趟数
/*快速排序*/void kuaisu(SqList &S, int low, int high)
{
	if (high <= low)   //递归结束条件
		return;
	int i = low;
	int j = high + 1;
	int temp;
	int key = S.a[low];
	while (true)
	{
		while (S.a[--j] > key)  //从右向左找比key小的值的下标
		{
			num1++;          //比较次数自增1
			if (j == low)    //如果递减到low，那就退出循环
			{
				break;
			}
		}

		while (S.a[++i] < key)  //从左向右找比key大的值的下标
		{
			num1++;         //比较次数自增1
			if (i == high)  //如果递增到high，那就退出循环
			{
				break;
			}
		}

		if (i >= j)   //i>=j,说明high到i的对应值全比key大，low+1到j的值全比key小，后面就不需要调换i，j的对应值
			break;

		//i对应值比key大，j对应值比key小   i，j对应值交换位置
		num2++;  //交换次数自增1
		temp = S.a[i];
		S.a[i] = S.a[j];
		S.a[j] = temp;
	}

	//low+1到j的值都比key小，low和j对应值互换位置
	num2++;    //交换次数自增1
	temp = S.a[low];
	S.a[low] = S.a[j];
	S.a[j] = temp;

	if (S.size == 21)  //20个数据的时候才输出每一趟的结果
	{
		cout << "第" << num3 << "趟的结果是" << endl;
		OutPut(S);
		num3++;
	}
	kuaisu(S, low, j - 1);    //key的左边递归排序
	kuaisu(S, j + 1, high);   //key的右边递归排序
}
void main()
{
	SqList S1,S2;

	InitSqList(S1, 21);   //初始化顺序表  n个数据这里就填n+1  如20个数据填21
	InitSqList(S2, 501);    

	SetValue(S1);
	cout <<S1.size-1<< "个原始的数据为:" << endl;
	OutPut(S1);
	cout << endl;
	
	cout << "============冒泡排序============" << endl;
	SetValue(S1);
	maopao(S1);
	cout << endl;

	cout << "============选择排序============" << endl;
	SetValue(S1);
	xuanze(S1);
	cout << endl;

	cout << "============折半插入排序============" << endl;
	SetValue(S1);
	zheban(S1);
	cout << endl;

	cout << "============快速排序============" << endl;
	SetValue(S1);
	kuaisu(S1, 1, 20);     //n个数据就填1和n  如20个数据就填1 20
	cout << "快速排序后的结果为:" << endl;
	OutPut(S1);
	cout << "比较次数:" << num1 << endl;
	cout << "移动次数:" << num2 << endl;

	//置全局变量num1,num2,num3都为0
	num1 = 0;
	num2 = 0;
	num3 = 0;
	//

	cout << endl << endl;

	SetValue(S2);
	cout << S2.size - 1 << "个原始的数据为:" << endl;
	OutPut(S2);
	cout << endl;

	cout << "============冒泡排序============" << endl;
	SetValue(S2);
	maopao(S2);
	cout << endl;

	cout << "============选择排序============" << endl;
	SetValue(S2);
	xuanze(S2);
	cout << endl;

	cout << "============折半插入排序============" << endl;
	SetValue(S2);
	zheban(S2);
	cout << endl;

	cout << "============快速排序============" << endl;
	SetValue(S2);
	kuaisu(S2, 1, 500);     
	cout << "快速排序后的结果为:" << endl;
	OutPut(S2);
	cout << "比较次数:" << num1 << endl;
	cout << "移动次数:" << num2 << endl;
}