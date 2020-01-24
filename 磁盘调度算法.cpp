#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<cmath>
#include<cstring>
#define max 50
using namespace std;

int arr[max], copyarr[max], finished[max];   //arr数组用来存请求服务队列，copyarr为辅助数组，值和arr相同
int num;   //队列元素个数                    //finished数组用来存已排好序的队列（SSTF和电梯法需要用到）
int n1 = 0;    //递归计数
int start;  //磁头起始位置

/*赋随机值*/void SetValue()
{
	int i;
	srand(int(time(0)));
	for (i = 0; i < num; i++)
	{
		arr[i] = rand() % 200;
		copyarr[i] = arr[i];
	}
}
/*输入*/void input()
{
	int i;
	cout << "请输入请求磁盘服务的队列元素个数:" << endl;
	cin >> num;
	SetValue();   //调用赋值函数
	cout << "请求磁盘服务序列为:";
	for (i = 0; i < num; i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << "请输入磁头起始位置:";
	cin >> start;
	cout << endl;
}
/*升序排序法*/void sort(int a[], int m)
{
	//对a数组的前m个元素进行升序排序，即小的在前，大的在后
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
/*计算总磁道数*/void sum(int a[])
{
	//计算从磁头起始位置遍历完a数组所走的磁道数
	int i;
	int total = 0;
	total = total + abs(start - a[0]);  //起始位置与第一个元素a[0]的位置差值的绝对值
	for (i = 0; i < num - 1; i++)
	{
		total = total + abs(a[i] - a[i + 1]);  //绝对值进行累加
	}
	cout << "磁头总移动的磁道数为:" << total << endl;
	cout << "磁头移动顺序为:";
	cout << start;
	for (i = 0; i < num; i++)
		cout << "->" << a[i];    //输出从磁头起始位置遍历完a数组的磁头轨迹
	cout << endl;
	cout << endl;
}
/*先来先服务法*/void FCFS()
{
	cout << "先来先服务法:" << endl;
	sum(arr);     //先来先服务法不需要进行排序，直接调用sum函数，参数是arr数组。
}
/*最短寻道时间优先法*/void SSTF(int x, int y)
{
	//x为元素个数，y为磁头起始位置

	if (x == 0)   //退出递归的条件
	{
		cout << "最短寻道时间优先法:" << endl;
		sum(finished);   //最后调用sum函数，参数为finished数组
		return;
	}
	int i, t, temp[max];
	int flag=0;   //标记
	int newstart;  //新的起始位置
	
	for (i = 0; i < x; i++)
		temp[i] = abs(y - copyarr[i]);   //计算起始位置y与copyarr数组前x个元素的差值的绝对值，放进temp数组
	
	sort(temp, x);   //对temp数字进行升序排序，排序完成后temp[0]为最小值
	
	for (i = 0; i < x; i++)
	{
		//判断起始位置y与temp[0]所对应的元素大小
		if (y + temp[0] == copyarr[i])
		{
			flag = 1;   //copyarr[i]比y大
			break;
		}
		if (y - temp[0] == copyarr[i])
		{
			flag = 2;   //copyarr[i]比y小
			break;
		}
	}
	switch (flag)
	{
	case 1:newstart = y + temp[0]; break;  //copyarr[i]比y大，新的起始位置为y+temp[0]
	case 2:newstart = y - temp[0]; break;  //copyarr[i]比y小，新的起始位置为y-temp[0]
	}

	for (i = 0; i < x; i++)
	{
		if (copyarr[i] == newstart)   //在辅助数组copyarr里找到newstart的位置
			break;
	}

	t = copyarr[i];
	copyarr[i] = copyarr[x - 1];
	copyarr[x - 1] = t;             //把最后一个元素和newstart调换位置

	finished[n1++] = newstart;       //把newstart存进finished数组
	SSTF(x - 1, newstart);          //递归调用，元素个数减1，新的起始位置
}
/*电梯法*/void dianti()
{
	int i, j, k;
	int temp[max];
	memcpy(temp, arr, sizeof(temp));    //把arr数组复制给temp
	temp[num] = start;    //把磁头起始位置start放进temp数组，不留空位
	sort(temp, num + 1);   //对temp数组进行排序
	for (i = 0; i < num + 1; i++)
	{
		if (temp[i] == start)    //找到start的位置
			break;
	}
	cout << "电梯法:" << endl;
	cout << "先往左再往右:" << endl;
	k = 0;
	for (j = i - 1; j >= 0; j--)
		finished[k++] = temp[j];   //比start小的元素降序放进finished数组
	for (j = i + 1; j <= num; j++)
		finished[k++] = temp[j];   //比start大的元素升序放进finished数组
	sum(finished);    //最后调用sum函数，参数为finished数组

	cout << "电梯法:" << endl;
	cout << "先往右再往左:" << endl;
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
