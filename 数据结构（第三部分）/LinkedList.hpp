#pragma once

#include<iostream>

using namespace std;

// 结点类
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

// 线性表的链式存储结构（双链表）
template<typename T>
class LinkedList {

	// 公有成员
public:

	// 构造函数
	LinkedList() :length(0) {

		// 初始状态，都指向空指针
		linkedListNode<T>* base = new linkedListNode<T>();
		
		base->front = base->back = nullptr;

		_head = _tail = base;

	}

	// 析构函数
	~LinkedList() = default;

	// 增加一个元素
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

		// 构造新的节点
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		// 基础节点
		linkedListNode<T>* base = _head;

		if (idx > length) {
			cout << "[warn]:The Index bigger than length;";
			return;
		}

		// 遍历达到目标位置
		while (idx--) {
			base = base->back;
		}

		// 连接
		tmp->back = base->back;
		tmp->front = base;
		base->back->front = tmp;
		base->back = tmp;

	}
	// 表头增加一个元素
	void push_front(T val) {

		// 构造新的节点
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		++length;

		// 当表为空时
		if (this->empty()) {

			tmp->back = nullptr;
			tmp->front = _head;
			_head->back = tmp;
			_tail = tmp;
			
			return;
		}

		// 当表不为空时
		tmp->back = _head->back;
		tmp->front = _head;
		_head->back->front = tmp;
		_head->back = tmp;

	}
	// 表尾增加一个元素
	void push_back(T val) {

		// 构造新的节点
		linkedListNode<T>* tmp = new linkedListNode<T>(val);
		tmp->front = tmp->back = nullptr;

		// 连接后，尾指针后移一位
		_tail->back = tmp;
		tmp->front = _tail;
		_tail = tmp;

		++length;
		
	}


	// 删除表头元素
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
	// 删除表尾元素
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

	// 表是否为空
	bool empty(void) {
		return _head == _tail;
	}

	// 表长
	int size(void) {
		return length;
	}

	// 打印所有元素
	void print(void) {
		linkedListNode<T>* base = _head;
		while (base->back) {
			base = base->back;
			cout << base->val << ' ';
		}
	}

	
	// 私有成员
private:

	// 头指针与尾指针
	linkedListNode<T>* _head;
	linkedListNode<T>* _tail;

	// 双链表长度
	int length;

};

