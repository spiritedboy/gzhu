#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
map<string, int>m;
map<string, int>::iterator it;  //������

void output()
{
	cout << "��ǰת��������:" << endl;
	cout << "Դ��ַ" << '\t' << "�˿�" << endl;
	for (it = m.begin(); it != m.end(); it++)
	{
		if (it->second != 0)
			cout << it->first << '\t' << it->second << endl;
	}
	cout << endl;
}
int main()
{
	int port1=1, port2=2;   //�ļ�1�Ķ˿ں���1���ļ�2�Ķ˿ں���2
	string src, dst, str;  //srcԴ��ַ  dstĿ�ĵ�ַ  str���ݱ�
	string fileName1 = "f:\\port1.txt";    //�ļ�1���ǴӶ˿�1������
	string fileName2 = "f:\\port2.txt";    //�ļ�2���ǴӶ˿�2������
	
	ifstream inf1(fileName1, ios::in);  //���ķ�ʽ���ļ�
	ifstream inf2(fileName2, ios::in);
	inf1.seekg(0, ios::beg);       //ָ�������ļ�ͷ
	inf2.seekg(0, ios::beg);
	
	while (!inf1.eof() || !inf2.eof())  //ֻ���ļ�1���ļ�2����ȡ��ϲŽ���ѭ��
	{
		if (!inf1.eof())   //�ļ�1δ����ʱ
		{
			inf1 >> dst >> src >> str;
			if (m[dst] != 0)    //���ת�������Ŀ�ĵ�ַ
			{
				if (m[dst] == port1)   //Ŀ�ĵ�ַ�˿ڵ����ļ�1�Ķ˿�
				{
					cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
					cout << "��ת��" << endl;
				}
				else
				{
					cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
					cout << "ת�����˿�" << port2 << endl;
				}
			}
			else            //���ת��������Ŀ�ĵ�ַ
			{
				cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
				cout << "ת�������˿�" << port1 << "������ж˿�" << endl;
			}
			if (m[src] == 0)   //��ѧϰ���ж�ת��������Դ��ַ��û�оͰ�Դ��ַ�Ͷ˿ں���ӽ�ת����
				m[src] = port1;
			output();
		}
		else
			inf1.close();   //�ļ�1�����ˣ��ص��ļ���

		if (!inf2.eof())
		{
			inf2 >> dst >> src >> str;
			if (m[dst] != 0)    //���ת�������Ŀ�ĵ�ַ
			{
				if (m[dst] == port2)   //Ŀ�ĵ�ַ�˿ڵ����ļ�2�Ķ˿�
				{
					cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
					cout << "��ת��" << endl;
				}
				else
				{
					cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
					cout << "ת�����˿�" << port1 << endl;
				}
			}
			else            //���ת��������Ŀ�ĵ�ַ
			{
				cout << "Ŀ�ĵ�ַ:" << dst << "  Դ��ַ:" << src << "  ���ݱ�:" << str << endl;
				cout << "ת�������˿�" << port2 << "������ж˿�" << endl;
			}
			if (m[src] == 0)   //��ѧϰ���ж�ת��������Դ��ַ��û�оͰ�Դ��ַ�Ͷ˿ں���ӽ�ת����
				m[src] = port2;
			output();
		}
		else
			inf2.close();
	}
	cout << endl;
}