#pragma once

#include<iostream>

using namespace std;

// 模板类
// 实现一个顺序实现的线性表
// 主要实现增删改查的功能
template<typename T, unsigned MAXSIZE = 1000>
class ArrayList {

	// 公有成员
public:

	// 构造函数
	ArrayList() :length(0) {};

	// 析构函数
	~ArrayList() = default;


	// 添加一个元素
	// 在base[idx]添加一个新元素val
	void insert(int idx, T val) {
		if (length + 1 == MAXSIZE) {
			cout << "[warn]:Be already full!" << endl;
			return;
		}
		for (int i = length - 1; i >= idx; --i) {
			_base[i + 1] = _base[i];
		}
		_base[idx] = val;
		++length;
	}
	// 表尾添加元素
	void push_back(T val) {
		this->insert(length, val);
	}
	// 表头添加元素
	void push_front(T val) {
		this->insert(0, val);
	}

	// 删除一个元素
	// 删除base[idx]
	void remove(int idx) {
		if (length == 0) {
			cout << "[warn]:Empty!" << endl;
			return;
		}
		for (int i = idx + 1; i < length; ++i) {
			_base[i - 1] = _base[i];
		}
		--length;
	}
	// 表尾删除元素
	void pop_back(void) {
		this->remove(length - 1);
	}
	// 表头删除元素
	void pop_front(void) {
		this->remove(0);
	}

	// 改变第i个元素的值
	void change(int idx, T val) {
		_base[idx] = val;
	}

	// 返回第i个元素的值
	T find(int idx) {
		return _base[idx];
	}

	// 打印所有元素
	void print(void) {
		for (int i = 0; i < length; ++i) {
			cout << _base[i] << ' ';
		}
	}


	// 私有成员
private:

	// 底层顺序实现
	T _base[MAXSIZE];

	// 线性表长度
	size_t length;

};

