#pragma once

#include<iostream>

using namespace std;

// �����
template<typename T>
class linkedListNode {
public:

	linkedListNode() = default;
	linkedListNode(T data) :val(data) {};
	~linkedListNode() = default;

	T val;
	linkedListNode<T>* front;
	linkedListNode<T>* back;
};

// ���Ա����ʽ�洢�ṹ��˫����
template<typename T>
class LinkedList {

	// ���г�Ա
public:

	// ���캯��
	LinkedList() :length(0) {

		// ��ʼ״̬����ָ���ָ��
		linkedListNode<T>* base = new linkedListNode<T>();
		
		base->front = base->back = nullptr;

		_head = _tail = base;

	}

	// ��������
	~LinkedList() = default;

	// ����һ��Ԫ��
	void insert(int idx, T val) {

		if (idx == 0) {
			push_front(val);
			return;
		}
		else if (idx == length) {
			push_back(val);
			return;
		}

		++length;

		// �����µĽڵ�
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		// �����ڵ�
		linkedListNode<T>* base = _head;

		if (idx > length) {
			cout << "[warn]:The Index bigger than length;";
			return;
		}

		// �����ﵽĿ��λ��
		while (idx--) {
			base = base->back;
		}

		// ����
		tmp->back = base->back;
		tmp->front = base;
		base->back->front = tmp;
		base->back = tmp;

	}
	// ��ͷ����һ��Ԫ��
	void push_front(T val) {

		// �����µĽڵ�
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		++length;

		// ����Ϊ��ʱ
		if (this->empty()) {

			tmp->back = nullptr;
			tmp->front = _head;
			_head->back = tmp;
			_tail = tmp;
			
			return;
		}

		// ����Ϊ��ʱ
		tmp->back = _head->back;
		tmp->front = _head;
		_head->back->front = tmp;
		_head->back = tmp;

	}
	// ��β����һ��Ԫ��
	void push_back(T val) {

		// �����µĽڵ�
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		// ���Ӻ�βָ�����һλ
		_tail->back = tmp;
		tmp->front = _tail;
		_tail = tmp;

		++length;
		
	}


	// ɾ����ͷԪ��
	T pop_front(void) {

		if (this->empty()) {
			cout << "[warn]:Empty!" << endl;
			return T();
		}

		linkedListNode<T>* tmp = _head->back;
		_head->back->back->front = _head;
		_head->back = _head->back->back;

		T data = tmp->val;
		--length;

		delete tmp;

		return data;
	}
	// ɾ����βԪ��
	T pop_back(void) {

		if (this->empty()) {
			cout << "[warn]:Empty!" << endl;
			return T();
		}

		linkedListNode<T>* tmp = _tail;
		_tail = _tail->front;
		_tail->back = nullptr;

		T data = tmp->val;
		--length;

		delete tmp;

		return data;
	}

	// ���Ƿ�Ϊ��
	bool empty(void) {
		return _head == _tail;
	}

	// ��
	int size(void) {
		return length;
	}

	// ��ӡ����Ԫ��
	void print(void) {
		linkedListNode<T>* base = _head;
		while (base->back) {
			base = base->back;
			cout << base->val << ' ';
		}
	}

	
	// ˽�г�Ա
private:

	// ͷָ����βָ��
	linkedListNode<T>* _head;
	linkedListNode<T>* _tail;

	// ˫������
	int length;

};

