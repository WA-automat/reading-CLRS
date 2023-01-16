#pragma once

#include<iostream>

using namespace std;

template<typename T>
class BinarySearchTreeNode {
public:

	// ���캯������������
	BinarySearchTreeNode(T data) :val(data), left(nullptr), right(nullptr) {};
	~BinarySearchTreeNode() = default;

	// ��Ա����
	T val;
	BinarySearchTreeNode<T>* left;
	BinarySearchTreeNode<T>* right;
};

// ����������
template<typename T>
class BinarySearchTree {

	// ���г�Ա
public:

	// ���캯������������
	BinarySearchTree() :root(nullptr) {}
	~BinarySearchTree() {
		destory(root);
	};

	// ������
	void insert(T val) {
	
		// �����µĽ��
		BinarySearchTreeNode<T>* tmp = new BinarySearchTreeNode<T>(val);

		if (!root) root = tmp;
		else {
			BinarySearchTreeNode<T>* base = root;
			while (true) {
				if (base->val > val && base->left) base = base->left;
				else if (base->val <= val && base->right) base = base->right;
				else break;
			}
			if (base->val > val) base->left = tmp;
			else base->right = tmp;
		}
	}
	
	// �������ֵ
	T maximum(void) {
		BinarySearchTreeNode<T>* base = root;
		if (!base) {
			throw runtime_error("empty!");
		}
		while (base->right) {
			base = base->right;
		}
		return base->val;
	}

	// ������Сֵ
	T minimum(void) {
		BinarySearchTreeNode<T>* base = root;
		if (!base) {
			throw runtime_error("empty!");
		}
		while (base->left) {
			base = base->left;
		}
		return base->val;
	}

	void show(void) {
		print(root);
	}

	// ˽�г�Ա
private:

	// ���ڵ�
	BinarySearchTreeNode<T>* root;


	// ����������������
	static void destory(BinarySearchTreeNode<T>* pointer) {
		if (pointer->left) destory(pointer->left);
		if (pointer->right) destory(pointer->right);
		delete pointer;
	}

	// ��ӡ������������
	static void print(BinarySearchTreeNode<T>* pointer) {
		if (pointer) {
			if (pointer->left) print(pointer->left);
			cout << pointer->val << ' ';
			if (pointer->right) print(pointer->right);
		}
	}

};

