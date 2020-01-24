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
	cout << "请输入你要进行计算校验和的文件名及其路径:" << endl;
	cin >> fileName;
	ifstream inf(fileName, ios::in);  //读的方式打开文件
	inf.seekg(0, ios::beg);
	cout << '\n' << "文件内容为:" << endl;
	while (getline(inf, str1))
	{
		cout << str1 << endl;
		str += str1;   //把全部行都加在一起变成一个超长字符串，因为文件可能不止一行
	}
	inf.close();   //关闭文件

	cout << '\n' << "校验和为:" << endl;
	for (n = 0; n < str.size(); n = n + 2)
	{
		a = str[n];
		H = a << 8;    //char类型的字符a对应的十进制ascii码左移8位，仍是十进制
		b = str[n + 1];
		L = b;         //字符b对应的十进制ascii码

		fdata = H + L;  //两个十进制相加
		cout << hex << fdata << "+";  //结果转成十六进制
		sum = sum + fdata;   //累加
	}
	while (sum > 0x10000)  //进位处理
	{
		carry++;
		sum = sum - 0x10000;
	}
	sum = sum + carry;
	cout << "carry" << "=" << hex << sum << endl;
}