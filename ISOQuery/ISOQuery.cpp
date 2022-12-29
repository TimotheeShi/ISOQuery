// ISOQuery.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "ISOTable.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;



float str2num(std::string str);

int main()
{
    string design;
    string dev;
    string level;
    string dev_name;
    string line;
	int i = 1;
    cout << "请输入查询需求：（格式：<设计值> <公差类型> <公差测量值> <公差等级>）\n";
	cout << "\n\n[" << i << "]  Iutput:\n";
	while (getline(cin, line)) {
		cout << "\n[" << i << "]  Output:\n";
		istringstream iss(line);
		iss >> design >> dev_name >> dev >> level;
		for_each(dev_name.begin(), dev_name.end(), [](char& c) {c = tolower(c); });
		float design_val = str2num(design);
		ISOTable tzd = ISOTable(dev_name);
		if (isdigit(dev[0])) {
			float dev_val = str2num(dev);
			tzd.query_level(design_val, dev_val, dev_name);
		}
		if (isdigit(level[0])) {
			unsigned int lev = (unsigned int)str2num(level);
			tzd.query_dev(design_val, lev, dev_name);
		}
		++i;
		cout << "\n\n[" << i << "]  Iutput:\n";
	}
}

float str2num(std::string str) {
	float result = 0;
	float res1 = 0;
	float res2 = 0;
	float sign = 1;
	auto b = str.cbegin();
	if (str[0] == '-') {
		b = ++(str.cbegin());
		sign = -1;
	}
	auto itr = std::find(str.cbegin(), str.cend(), '.');
	for (auto itr1 = b; itr1 != itr; ++itr1) {
		float addend = float(*itr1) - 48.0;
		res1 = res1 * 10 + addend;
	}
	if (itr != str.cend()) {
		for (auto itr2 = --str.cend(); itr2 != itr; --itr2) {
			float addend = float(*itr2) - 48.0;
			res2 = 0.1 * res2 + addend;
		}
	}
	result = sign * (res1 + 0.1 * res2);
	return result;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
