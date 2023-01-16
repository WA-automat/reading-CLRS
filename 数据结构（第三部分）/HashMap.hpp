#pragma once

#include<iostream>
#include<vector>

using namespace std;

// ������ʵ�ֹ�ϣ��
// ���������ʹ�õ���STL�е�vector�䳤����
// ��˫������ʽʵ��
template<typename K, typename V, unsigned N = 1000>
class HashMap {

	// ���г�Ա
public:

	// ��ֵ������ 
	typedef pair<K, V> Pair;

	// ���캯��
	HashMap() {
		// ���ɶ�����
		base.resize(N);
	}

	// ��������
	~HashMap() = default;

	// ���ɶ�Ӧ��hashcode
	static size_t hashcode(K key) {
		return hash<K>()(key);
	}

	// ����һ��Ԫ��
	void insert(K key, V val) {
		size_t hashkey = hashcode(key);
		vector<Pair>& items = base[hashkey % N];
		
		// ��֮ǰ���ֹ����������Ḳ�ǵ�ԭ�ȵ�ֵ
		for (Pair& item : items) {
			if (item.first == key) {
				item.second = val;
				return;
			}
		}
		// ֮ǰû���ֹ�����������½�һ����ֵ��
		base[hashkey % N].push_back({ key, val });
	}

	// ���ݼ����ֵ
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

	// ˽�г�Ա
private:

	// �ײ�ʵ��
	vector<vector<Pair>> base;

};

