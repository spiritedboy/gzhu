#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<map>
using namespace std;
map<string, int>m1, m2;   //��������map����
map<string, int>::iterator it;  //������
/*�и�С�ļ�*/void fenge()
{
	int n, temp1;
	char data[25], time[25];
	string str;
	string ip1;

	ofstream arr[256];   //��ip��ǰ8λ�ָ2^8=256�����Զ�����һ���ļ�������
	for (n = 0; n < 256; n++)
	{
		int x = n;
		char a[5];
		_itoa_s(x, a, 10);  //�����ͱ���nת��Ϊ�ַ���

		string address = "f:\\test\\";    //����f�̽���һ���ļ���test
		address = address + a + ".txt";   //�ļ������ǹ���n�ı���  �ļ�����0��255

		arr[n].open(address, ios::out);   //д�ķ�ʽ��256���ļ���
	}

	ifstream inf("f:\\50w.txt", ios::in);  //���ķ�ʽ��ip����Դ�ļ�
	inf.seekg(0, ios::beg);    //ָ�������ļ�ͷ

	cout << "��ʼ�и�С�ļ�:" << endl;

	while (inf >> str >> data >> time)   //���ж�����
	{
		//���ַ���a��һ���ָ�ֵ���µ��ַ���s
		// s.assign(a,start,len);start�ǽ�ȡ�ַ�������λ�ã�len�ǽ�ȡ�ַ����ĳ���
		ip1.assign(str, 0, 8);

		temp1 = stoi(ip1, nullptr, 2);  //��2���Ƶ�ip1ת��ʮ��������

		arr[temp1] << str << '\n';  //�ҵ���Ӧ���ļ�����������strд���ļ�
	}

	inf.close();   //�ر�ip����Դ�ļ�

	for (n = 0; n < 256; n++)   //�ر�256���ļ���
	{
		arr[n].close();
	}

	cout << "�и����,�ļ������� f:\\test" << endl;
	cout << endl;
}
/*С�ļ�����*/void paixu()
{
	int n;
	int max;
	string str;
	ifstream arr[256];

	cout << "���������С�ļ�����ip������������:" << endl;

	for (n = 0; n < 256; n++)   //ѭ��256��
	{
		int x = n;
		max = 1;   //��ǰ���ֵΪ1
		char a[5];
		_itoa_s(x, a, 10);
		string address = "f:\\test\\";
		address = address + a + ".txt";
		arr[n].open(address, ios::in);   //���ķ�ʽ������Ϊ "n.txt" ���ļ���
		arr[n].seekg(0, ios::beg);

		/*map<string, int>  ��ߵ�string������32λip���ұߵ�intĬ��Ϊ0�������Դ�ip���ֵĴ���*/

		while (arr[n] >> str)  //��ȡ�����ݷŽ�str
		{
			m1[str]++;   //str��Ӧ��intֵ����һ��  ��ip����+1
		}

		//����map���ҳ�int�����ֵ
		for (it = m1.begin(); it != m1.end(); it++)
		{
			//it->first  ��Ӧ����map��string  �������Ϊ�����±�
			//it->second ��Ӧ����map��int     �������Ϊ�����±��Ӧ��ֵ��

			if (it->second > max)  //���intֵ����max  max�͵���int,��֤max���
			{
				max = it->second;
			}
		}//����map�����ֵΪmax


		//�ҵ����ֵ֮���ٱ���һ��map
		for (it = m1.begin(); it != m1.end(); it++)
		{
			if (it->second == max)  //���intֵ����max��˵���������ֵ
			{
				m2[it->first] = max;  //����д����һ��map2�stringΪit->first��intֵΪmap1��max
			}
		}

		m1.erase(m1.begin(), m1.end());  //��һ���ļ�������ˣ���ΪҪѭ��ʹ��map1������Ҫ�Ƚ�map1���

		arr[n].close();     //�رյ�һ���ļ���
	}

	cout << "�������" << endl;
	cout << endl;
}
/*������*/void shuchu()
{
	//ͨ����һ�����������ǰ�256���ļ���ÿһ���ļ������ip��д����map2����

	int max = 1;

	//�ҵ�map2��ip�������ֵmax
	for (it = m2.begin(); it != m2.end(); it++)   
	{
		if (it->second > max)
		{
			max = it->second;
		}
	}

	cout << "��������ip�������Ϊ" << endl;
	for (it = m2.begin(); it != m2.end(); it++)   //�ٱ���һ��
	{
		if (it->second == max)   //����maxʱ�������string��it->first����int��it->second��  
		{
			cout << "ip:"<<it->first << "  ����:" << it->second << endl;
		}
	}

	m2.erase(m2.begin(), m2.end());   //������map2
}
void main()
{
	fenge();
	paixu();
	shuchu();
}