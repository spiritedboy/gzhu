#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	int fdata = 0, H = 0, L = 0;
	int sum = 0, carry = 0;
	int n;
	char a, b;
	string fileName, str, str1;
	cout << "��������Ҫ���м���У��͵��ļ�������·��:" << endl;
	cin >> fileName;
	ifstream inf(fileName, ios::in);  //���ķ�ʽ���ļ�
	inf.seekg(0, ios::beg);
	cout << '\n' << "�ļ�����Ϊ:" << endl;
	while (getline(inf, str1))
	{
		cout << str1 << endl;
		str += str1;   //��ȫ���ж�����һ����һ�������ַ�������Ϊ�ļ����ܲ�ֹһ��
	}
	inf.close();   //�ر��ļ�

	cout << '\n' << "У���Ϊ:" << endl;
	for (n = 0; n < str.size(); n = n + 2)
	{
		a = str[n];
		H = a << 8;    //char���͵��ַ�a��Ӧ��ʮ����ascii������8λ������ʮ����
		b = str[n + 1];
		L = b;         //�ַ�b��Ӧ��ʮ����ascii��

		fdata = H + L;  //����ʮ�������
		cout << hex << fdata << "+";  //���ת��ʮ������
		sum = sum + fdata;   //�ۼ�
	}
	while (sum > 0x10000)  //��λ����
	{
		carry++;
		sum = sum - 0x10000;
	}
	sum = sum + carry;
	cout << "carry" << "=" << hex << sum << endl;
}