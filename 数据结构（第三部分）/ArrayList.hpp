#pragma once

#include<iostream>

using namespace std;

// ģ����
// ʵ��һ��˳��ʵ�ֵ����Ա�
// ��Ҫʵ����ɾ�Ĳ�Ĺ���
template<typename T, unsigned MAXSIZE = 1000>
class ArrayList {

	// ���г�Ա
public:

	// ���캯��
	ArrayList() :length(0) {};

	// ��������
	~ArrayList() = default;


	// ���һ��Ԫ��
	// ��base[idx]���һ����Ԫ��val
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
	// ��β���Ԫ��
	void push_back(T val) {
		this->insert(length, val);
	}
	// ��ͷ���Ԫ��
	void push_front(T val) {
		this->insert(0, val);
	}

	// ɾ��һ��Ԫ��
	// ɾ��base[idx]
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
	// ��βɾ��Ԫ��
	void pop_back(void) {
		this->remove(length - 1);
	}
	// ��ͷɾ��Ԫ��
	void pop_front(void) {
		this->remove(0);
	}

	// �ı��i��Ԫ�ص�ֵ
	void change(int idx, T val) {
		_base[idx] = val;
	}

	// ���ص�i��Ԫ�ص�ֵ
	T find(int idx) {
		return _base[idx];
	}

	// ��ӡ����Ԫ��
	void print(void) {
		for (int i = 0; i < length; ++i) {
			cout << _base[i] << ' ';
		}
	}


	// ˽�г�Ա
private:

	// �ײ�˳��ʵ��
	T _base[MAXSIZE];

	// ���Ա���
	size_t length;

};

