#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#pragma once
class ISOTable
{
	struct ISONode {
		ISONode* prev;
		ISONode* next;
		float max_val;
		std::vector<float> dev;

		ISONode(ISONode* p, ISONode* n, float max) : prev{ p }, next{ n }, max_val{ max }, dev{} {}
	};

public:
	ISOTable(std::string dev_type) : d_type{ dev_type } {
		init();
	}

	void query_level(float design, float dev, std::string dev_name) const {
		ISONode* curr = tab;
		while (design > curr->max_val) {
			curr = curr->next;
		}
		auto curr_level = curr->dev.cbegin();
		while (dev > *curr_level)
			++curr_level;
		auto level1 = curr_level - curr->dev.cbegin();
		 if (dev_name != "yd" && dev_name != "yzd")
			level1 += 1;
		auto level0 = level1 - 1;
		std::cout << "公差等级为：";
		if (dev == *curr_level)
			std::cout << level1 << std::endl;
		else
			std::cout << level0 << "~" << level1 << std::endl;
	}

	void query_dev(float design, unsigned int level, std::string dev_name) const {
		ISONode* curr = tab;
		while (design > curr->max_val) {
			curr = curr->next;
		}
		unsigned int lev = level;
		if (dev_name != "yd" && dev_name != "yzd")
			lev -= 1;
		std::cout << "公差值为: " << curr->dev[lev] << std::endl;
	}

private:
	ISONode* tab;
	std::string d_type;

	void init() {
		delete tab;
		tab == nullptr;
		if (d_type == "tzd" || d_type == "dcd" || d_type == "td") {
			std::ifstream table("E:\\tzd.txt");
			if (table) {
				tab = new ISONode(nullptr, nullptr, 0);
				ISONode* curr = tab;
				std::string line;
				while (getline(table, line)) {
					std::istringstream iss(line);
					std::string max_v;
					std::string dev_v;
					iss >> max_v;
					ISONode* temp = new ISONode(curr, nullptr, str2num(max_v));
					while (iss >> dev_v) {
						temp->dev.push_back(str2num(dev_v) * 0.001);
					}
					curr->next = temp;
					curr = curr->next;
				}
			}
		}

		if (d_type == "yd" || d_type == "yzd") {
			std::ifstream table("E:\\yd.txt");
			if (table) {
				tab = new ISONode(nullptr, nullptr, 0);
				ISONode* curr = tab;
				std::string line;
				while (getline(table, line)) {
					std::istringstream iss(line);
					std::string max_v;
					std::string dev_v;
					iss >> max_v;
					ISONode* temp = new ISONode(curr, nullptr, str2num(max_v));
					while (iss >> dev_v) {
						temp->dev.push_back(str2num(dev_v) * 0.001);
					}
					curr->next = temp;
					curr = curr->next;
				}
			}
		}

		if (d_type == "zxd" || d_type == "pmd") {
			std::ifstream table("E:\\zxd.txt");
			if (table) {
				tab = new ISONode(nullptr, nullptr, 0);
				ISONode* curr = tab;
				std::string line;
				while (getline(table, line)) {
					std::istringstream iss(line);
					std::string max_v;
					std::string dev_v;
					iss >> max_v;
					ISONode* temp = new ISONode(curr, nullptr, str2num(max_v));
					while (iss >> dev_v) {
						temp->dev.push_back(str2num(dev_v) * 0.001);
					}
					curr->next = temp;
					curr = curr->next;
				}
			}
		}

		if (d_type == "pxd" || d_type == "czd") {
			std::ifstream table("E:\\pxd.txt");
			if (table) {
				tab = new ISONode(nullptr, nullptr, 0);
				ISONode* curr = tab;
				std::string line;
				while (getline(table, line)) {
					std::istringstream iss(line);
					std::string max_v;
					std::string dev_v;
					iss >> max_v;
					ISONode* temp = new ISONode(curr, nullptr, str2num(max_v));
					while (iss >> dev_v) {
						temp->dev.push_back(str2num(dev_v) * 0.001);
					}
					curr->next = temp;
					curr = curr->next;
				}
			}
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

};

