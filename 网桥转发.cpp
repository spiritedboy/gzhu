#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
map<string, int>m;
map<string, int>::iterator it;  //迭代器

void output()
{
	cout << "当前转发表如下:" << endl;
	cout << "源地址" << '\t' << "端口" << endl;
	for (it = m.begin(); it != m.end(); it++)
	{
		if (it->second != 0)
			cout << it->first << '\t' << it->second << endl;
	}
	cout << endl;
}
int main()
{
	int port1=1, port2=2;   //文件1的端口号是1，文件2的端口号是2
	string src, dst, str;  //src源地址  dst目的地址  str数据报
	string fileName1 = "f:\\port1.txt";    //文件1都是从端口1读数据
	string fileName2 = "f:\\port2.txt";    //文件2都是从端口2读数据
	
	ifstream inf1(fileName1, ios::in);  //读的方式打开文件
	ifstream inf2(fileName2, ios::in);
	inf1.seekg(0, ios::beg);       //指针置在文件头
	inf2.seekg(0, ios::beg);
	
	while (!inf1.eof() || !inf2.eof())  //只有文件1和文件2都读取完毕才结束循环
	{
		if (!inf1.eof())   //文件1未读完时
		{
			inf1 >> dst >> src >> str;
			if (m[dst] != 0)    //如果转发表存在目的地址
			{
				if (m[dst] == port1)   //目的地址端口等于文件1的端口
				{
					cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
					cout << "不转发" << endl;
				}
				else
				{
					cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
					cout << "转发到端口" << port2 << endl;
				}
			}
			else            //如果转发表不存在目的地址
			{
				cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
				cout << "转发到除端口" << port1 << "外的所有端口" << endl;
			}
			if (m[src] == 0)   //自学习，判断转发表有无源地址，没有就把源地址和端口号添加进转发表
				m[src] = port1;
			output();
		}
		else
			inf1.close();   //文件1读完了，关掉文件流

		if (!inf2.eof())
		{
			inf2 >> dst >> src >> str;
			if (m[dst] != 0)    //如果转发表存在目的地址
			{
				if (m[dst] == port2)   //目的地址端口等于文件2的端口
				{
					cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
					cout << "不转发" << endl;
				}
				else
				{
					cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
					cout << "转发到端口" << port1 << endl;
				}
			}
			else            //如果转发表不存在目的地址
			{
				cout << "目的地址:" << dst << "  源地址:" << src << "  数据报:" << str << endl;
				cout << "转发到除端口" << port2 << "外的所有端口" << endl;
			}
			if (m[src] == 0)   //自学习，判断转发表有无源地址，没有就把源地址和端口号添加进转发表
				m[src] = port2;
			output();
		}
		else
			inf2.close();
	}
	cout << endl;
}