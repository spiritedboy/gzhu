#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<map>
using namespace std;
map<string, int>m1, m2;   //定义两个map容器
map<string, int>::iterator it;  //迭代器
/*切割小文件*/void fenge()
{
	int n, temp1;
	char data[25], time[25];
	string str;
	string ip1;

	ofstream arr[256];   //按ip的前8位分割，2^8=256，所以定义了一个文件流数组
	for (n = 0; n < 256; n++)
	{
		int x = n;
		char a[5];
		_itoa_s(x, a, 10);  //将整型变量n转化为字符串

		string address = "f:\\test\\";    //先在f盘建立一个文件夹test
		address = address + a + ".txt";   //文件名就是关于n的变量  文件名从0到255

		arr[n].open(address, ios::out);   //写的方式打开256个文件流
	}

	ifstream inf("f:\\50w.txt", ios::in);  //读的方式打开ip数据源文件
	inf.seekg(0, ios::beg);    //指针置在文件头

	cout << "开始切割小文件:" << endl;

	while (inf >> str >> data >> time)   //逐行读数据
	{
		//将字符串a的一部分赋值给新的字符串s
		// s.assign(a,start,len);start是截取字符串的首位置，len是截取字符串的长度
		ip1.assign(str, 0, 8);

		temp1 = stoi(ip1, nullptr, 2);  //将2进制的ip1转成十进制整形

		arr[temp1] << str << '\n';  //找到对应的文件流，将整个str写入文件
	}

	inf.close();   //关闭ip数据源文件

	for (n = 0; n < 256; n++)   //关闭256个文件流
	{
		arr[n].close();
	}

	cout << "切割完成,文件保存在 f:\\test" << endl;
	cout << endl;
}
/*小文件排序*/void paixu()
{
	int n;
	int max;
	string str;
	ifstream arr[256];

	cout << "正在逐个对小文件按照ip次数进行排序:" << endl;

	for (n = 0; n < 256; n++)   //循环256次
	{
		int x = n;
		max = 1;   //当前最大值为1
		char a[5];
		_itoa_s(x, a, 10);
		string address = "f:\\test\\";
		address = address + a + ".txt";
		arr[n].open(address, ios::in);   //读的方式打开名字为 "n.txt" 的文件流
		arr[n].seekg(0, ios::beg);

		/*map<string, int>  左边的string用来存32位ip，右边的int默认为0，它可以存ip出现的次数*/

		while (arr[n] >> str)  //读取的数据放进str
		{
			m1[str]++;   //str对应的int值自增一次  即ip次数+1
		}

		//遍历map，找出int的最大值
		for (it = m1.begin(); it != m1.end(); it++)
		{
			//it->first  对应的是map的string  可以理解为数组下标
			//it->second 对应的是map的int     可以理解为数组下标对应的值。

			if (it->second > max)  //如果int值大于max  max就等于int,保证max最大
			{
				max = it->second;
			}
		}//现在map的最大值为max


		//找到最大值之后再遍历一遍map
		for (it = m1.begin(); it != m1.end(); it++)
		{
			if (it->second == max)  //如果int值等于max，说明它是最大值
			{
				m2[it->first] = max;  //把它写入另一个map2里，string为it->first，int值为map1的max
			}
		}

		m1.erase(m1.begin(), m1.end());  //第一个文件就完成了，因为要循环使用map1，所以要先将map1清空

		arr[n].close();     //关闭第一个文件流
	}

	cout << "排序完成" << endl;
	cout << endl;
}
/*输出结果*/void shuchu()
{
	//通过上一个函数，我们把256个文件中每一个文件的最多ip都写进了map2里面

	int max = 1;

	//找到map2的ip次数最大值max
	for (it = m2.begin(); it != m2.end(); it++)   
	{
		if (it->second > max)
		{
			max = it->second;
		}
	}

	cout << "最多次数的ip及其次数为" << endl;
	for (it = m2.begin(); it != m2.end(); it++)   //再遍历一遍
	{
		if (it->second == max)   //碰到max时，就输出string（it->first）和int（it->second）  
		{
			cout << "ip:"<<it->first << "  次数:" << it->second << endl;
		}
	}

	m2.erase(m2.begin(), m2.end());   //最后清空map2
}
void main()
{
	fenge();
	paixu();
	shuchu();
}