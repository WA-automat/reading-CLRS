#pragma once

#include<iostream>
#include<vector>

using namespace std;

/// <summary>
/// 쳲������ѽڵ�
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class FibNode {

	// ���г�Ա
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	// ������
	Pair kv;

	// mark == true ���ҽ���ĳ������Ϊĳ���ڵ���ӽ���ʧȥ��ĳ���ӽ��
	bool mark;
	// ���ӽ�����
	int degree;

	// ָ����
	FibNode<K, V>* left, * right;
	FibNode<K, V>* child, * parent;

	// ���캯��
	FibNode(const K& key, const V& val)
		:kv(make_pair(key, val)), mark(false), degree(0),
		left(this), right(this), 
		child(nullptr), parent(nullptr) {}
	FibNode() :FibNode(K(), V()) {}

	// ��������
	~FibNode() = default;

};

/// <summary>
/// 쳲�������
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class FibHeap {

	// ���г�Ա
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	// ָ������
	using pointer = FibNode<K, V>*;

	// ���캯��
	FibHeap() : size(0), min(nullptr) {}

	// ��������
	~FibHeap() = default;

	// ����һ��Ԫ��
	void insert(const K& key, const V& val) {

		// �½�һ���ڵ�
		pointer p = new FibNode<K, V>(key, val);

		// ����������
		listAdd(min, p);
		if (min->kv.first > key) {
			min = p;
		}
		++size;
	}

	// ɾ����������С�ڵ�
	Pair extractMin(void) {

		// Ĭ�ϵ�һ����ֵ��
		Pair ret = make_pair(K(), V());

		// ��С�ڵ�
		pointer p = min;

		// ��Сֵ����ʱ�Ž���
		// ��С�ڵ㲻����ʱ����Ĭ�ϼ�ֵ��
		if (p) {

			// ���ļ�ֵ��
			ret = p->kv;

			if (p->child) {

				pointer x = p->child, y = x->right;

				for (int i = 0; i < p->degree; ++i) {

					listAdd(min, x);

					x->parent = nullptr;
					x = y;
					y = y->right;

				}

			}

			if (p->right == p) min = nullptr;
			else {

				min = p->right;
				listDelete(p);
				consolidate();

			}

			delete p;
			--size;

		}

		return ret;
	}

	// ɾ��һ���ڵ�
	void remove(const K& key) {

		// ���ҵ���ǰ���
		pointer p = search(min, key);

		// �����Ҳ���
		if (p == nullptr) return;

		// ������ʵӦ����K������͵���Сֵ
		// �������ǲ����ģ�����������ʱ��Ĭ��ֵ����
		decreaseKey(p, K());
		extractMin();

	}

	static FibHeap heapUnion(FibHeap& a, FibHeap& b) {

		// ������һ�������ڣ��򷵻���һ��
		if (a.min == nullptr) return b;
		if (b.min == nullptr) return a;

		// ��������ϲ�
		a.listUnion(a.min, b.min);

		// �ҵ���ǰ��Сֵ
		if (a.min->kv.first > b.min->kv.first) {
			a.min = b.min;
		}

		a.size += b.size;

		return a;
	}

	// ˽�г�Ա
private:

	// ������
	int size;

	// ��СԪ��ָ��
	pointer min;

	// һЩ��������
	// ѭ���������һ���ڵ�
	void listAdd(pointer& r, pointer& p) {

		// ������Ϊ��ʱ
		if (r == nullptr) {
			r = p;
			r->left = r;
			r->right = r;
		}

		// ������Ϊ��ʱ
		else {
			pointer x = r;
			p->right = x->right;
			p->left = x;
			x->right->left = p;
			x->right = p;
		}

	}

	// ѭ������ɾ��һ���ڵ�
	void listDelete(pointer p) {
		p->left->right = p->right;
		p->right->left = p->left;
	}

	// ѭ������ϲ�
	void listUnion(pointer x, pointer y) {

		// ��xΪ������
		if (x == nullptr) x = y;
		else {

			pointer tail = x->left;
			x->left->right = y;
			y->left->right = x;
			x->left = y->left;
			y->left = tail;

		}

	}

	// ������
	int Dn(void) { 
		return log2(size) + 1; 
	}

	// ��y��Ϊx�ĺ���
	void heapLink(pointer y, pointer x) {

		listDelete(y);
		listAdd(x->child, y);
		++(x->degree);
		y->mark = false;

	}

	// ����������ӳ�һ����
	// ����a�д洢�������
	void consolidate(void) {

		vector<pointer> a(Dn(), nullptr);
		pointer x, y, z;
		int d;
		pointer sentry = new FibNode<K, V>();

		listAdd(min->left, sentry);
		for (x = min; x != sentry; x = z) {
			z = x->right;
			d = x->degree;
			while (a[d] != nullptr) {
				y = a[d];
				if (x->kv.first > y->kv.first) swap(x, y);
				heapLink(y, x);
				a[d] = nullptr;
				++d;
			}
			a[d] = x;
		}

		min = nullptr;
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] != nullptr) {
				listAdd(min, a[i]);
				if (a[i]->kv.first < min->kv.first) min = a[i];
			}
		}

		delete sentry;
	}

	// ��x��Ϊ����һ�����ڵ���
	void cut(pointer x, pointer y) {

		listDelete(x);
		--(y->degree);
		listAdd(min, x);
		x->parent = nullptr;
		x->mark = false;

	}

	// �ݹ���ж�
	void cascadingCut(pointer y) {
		
		pointer z = y->parent;
		
		// ��y��Ϊ���ڵ�ʱ
		if (z) {

			if (y->mark == false) y->mark = true;
			else {

				cut(y, z);
				cascadingCut(z);
			
			}

		}

	}

	// ���Ҹ�������
	pointer search(pointer r, const K& key) {
		
		// ���ڵ�Ϊ��
		if (r == nullptr) return r;

		pointer x = r, y;
		
		do {

			if (x->kv.first == key) {
				return x;
			}
			else if (x->kv.first < key) {
				y = search(x->child, key);
				if (y) return y;
			}
			x = x->right;

		} while (x != r);

		return nullptr;

	}

	// �ı䵱ǰ��
	void decreaseKey(pointer x, const K& key) {

		// ���¼����ڵ�ǰ��ʱ��ֱ�ӷ���
		if (key >= x->kv.first) return;

		x->kv.first = key;
		pointer y = x->parent;

		if (y && y->kv.first > x->kv.first) {
			cut(x, y);
			cascadingCut(y);
		}
		if (x->kv.first < min->kv.first) min = x;

	}

};

