#pragma once

#include<iostream>
#include<vector>

using namespace std;

// 拉链法实现哈希表
// 这里的链表使用的是STL中的vector变长数组
// 以双链表形式实现
template<typename K, typename V, unsigned N = 1000>
class HashMap {

	// 公有成员
public:

	// 键值对类型 
	typedef pair<K, V> Pair;

	// 构造函数
	HashMap() {
		// 生成多链表
		base.resize(N);
	}

	// 析构函数
	~HashMap() = default;

	// 生成对应的hashcode
	static size_t hashcode(K key) {
		return hash<K>()(key);
	}

	// 插入一个元素
	void insert(K key, V val) {
		size_t hashkey = hashcode(key);
		vector<Pair>& items = base[hashkey % N];
		
		// 若之前出现过这个键，则会覆盖掉原先的值
		for (Pair& item : items) {
			if (item.first == key) {
				item.second = val;
				return;
			}
		}
		// 之前没出现过这个键，则新建一个键值对
		base[hashkey % N].push_back({ key, val });
	}

	// 根据键获得值
	V get(K key) {
		size_t hashkey = hashcode(key);
		vector<Pair>& items = base[hashkey % N];
		for (Pair& item : items) {
			if (item.first == key) {
				return item.second;
			}
		}
		cout << "[warn]:The corresponding element is not found!" << endl;
		return V();
	}

	// 私有成员
private:

	// 底层实现
	vector<vector<Pair>> base;

};

