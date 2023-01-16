#pragma once

#include<iostream>

using namespace std;

template<typename T>
class BinarySearchTreeNode {
public:

	// 构造函数与析构函数
	BinarySearchTreeNode(T data) :val(data), left(nullptr), right(nullptr) {};
	~BinarySearchTreeNode() = default;

	// 成员变量
	T val;
	BinarySearchTreeNode<T>* left;
	BinarySearchTreeNode<T>* right;
};

// 二叉搜索树
template<typename T>
class BinarySearchTree {

	// 公有成员
public:

	// 构造函数与析构函数
	BinarySearchTree() :root(nullptr) {}
	~BinarySearchTree() {
		destory(root);
	};

	// 插入结点
	void insert(T val) {
	
		// 构造新的结点
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
	
	// 查找最大值
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

	// 查找最小值
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

	// 私有成员
private:

	// 根节点
	BinarySearchTreeNode<T>* root;


	// 析构函数辅助函数
	static void destory(BinarySearchTreeNode<T>* pointer) {
		if (pointer->left) destory(pointer->left);
		if (pointer->right) destory(pointer->right);
		delete pointer;
	}

	// 打印函数辅助函数
	static void print(BinarySearchTreeNode<T>* pointer) {
		if (pointer) {
			if (pointer->left) print(pointer->left);
			cout << pointer->val << ' ';
			if (pointer->right) print(pointer->right);
		}
	}

};

