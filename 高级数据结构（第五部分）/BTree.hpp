#pragma once

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/// <summary>
/// B���Ľڵ�
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class BTreeNode {

	// ���г�Ա
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	//	int n; the number of the keys in this node
	// bool isLeaf; 

	// �ؼ�������
	vector<Pair> kvs;	// kvs.size() return n

	// ���ӽڵ�
	vector<BTreeNode<K, V>*> ptrs;	// ptrs.empty() return isLeaf

	// Ĭ�Ϲ��캯������������
	BTreeNode() = default;
	~BTreeNode() = default;

};

/// <summary>
/// B������
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class BTree {

	// ���г�Ա
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	// ָ������
	using pointer = BTreeNode<K, V>*;

	// ���ӽڵ㼰���Ӧ������
	using PlaceOfChild = pair<pointer, int>;

	// ���캯��
	BTree(int deg) :root(new BTreeNode<K, V>()), t(deg >= 2 ? deg : 2) {}
	BTree() :BTree(2) {}

	// ��������
	~BTree() {

		// ʵ�ָ�������destroy��������
		destroy(root);
	
	}

	// ����Ԫ��
	void insert(const K& key, const V& val) {

		// ָ����ڵ�
		pointer base = root;

		// �����ڵ�����
		if (base->kvs.size() == 2 * t - 1) {
			
			pointer s = new BTreeNode<K, V>();
			root = s;
			s->ptrs.push_back(base);
			splitChild(s, 0);
			insert_notfull(s, key, val);

		}
		else insert_notfull(base, key, val);
	}

	//void remove(const K& key);

	// ���Һ���
	V find(const K& key) {

		// ʹ�ø���������������
		PlaceOfChild node = search(root, key);

		// ����ѯ�ɹ�
		if (node.first) {

			pointer p = node.first;
			Pair kv = p->kvs[node.second];
			return kv.second;
		
		}
		
		// ��ѯ����ʱ
		else {
			
			// �ų�����
			cout << "[warn]:Query failure!" << endl;
			return V();

		}
	}

	// ��СԪ�ض�Ӧ��ֵ
	int minimum(void) {
		pointer p = minimum(root);
		return p->kvs[0].second;
	}

	// ���Ԫ�ض�Ӧ��ֵ
	int maximum(void) {
		pointer p = maximum(root);
		return p->kvs[p->kvs.size() - 1].second;
	}

	void remove(const K& key) {
		remove(root, key);
	}

	//void print(void);

	// ˽�г�Ա
private:

	// ��Ա����
	
	// ���ڵ�
	pointer root;

	// ��С����
	int t;	//the minimum degree, more than or equal to 2


	// ����Ϊ���ָ�������

	// ������������
	void destroy(pointer& node) {
		
		// ���ڵ���ڣ��Ž������ٲ���
		if (node) {

			// ɾ���ӽڵ�
			for (auto item : node->ptrs) {
				destroy(item);
			}

			// ɾ������
			delete node;
			node = nullptr;
		}

	}

	// ������������
	PlaceOfChild search(pointer node, const K& key) {

		// �ڵ�ǰ�ڵ����key�����ֲ��ң�
		size_t idx = lower_bound(node->kvs.begin(), node->kvs.end(), make_pair(key, 0)) - node->kvs.begin();

		// ����������ж�
		// ��key�ڴ˽����
		if (idx < node->kvs.size() && node->kvs[idx].first == key) return make_pair(node, idx);
		else if (node->ptrs.empty()) return make_pair(nullptr, 0);
		else return search(node->ptrs[idx], key);
	
	}

	// �����ӽ�����ˣ������ڵ㻹û��
	void splitChild(pointer x, const int i) {

		pointer y = x->ptrs[i];
		pointer z = new BTreeNode<K, V>();

		// ��y�е�һ��Ԫ���Ƴ�
		for (int j = 0; j < t - 1; ++j) z->kvs.push_back(y->kvs[j + t]);

		if (!y->ptrs.empty()) {
			for (int j = 0; j < t; ++j) z->ptrs.push_back(y->ptrs[j + t]);
			for (int j = 0; j < t; ++j) y->ptrs.pop_back();
		}

		x->kvs.insert(x->kvs.begin() + i, y->kvs[t - 1]);
		x->ptrs.insert(x->ptrs.begin() + i, z);

		for (int j = 0; j < t; ++j) y->kvs.pop_back();
	}

	// ���븨������
	void insert_notfull(pointer node, const K& key, const V& val) {
		
		Pair item = make_pair(key, val);
		// �ڵ�ǰ�ڵ����key�����ֲ��ң�
		size_t idx = lower_bound(node->kvs.begin(), node->kvs.end(), make_pair(key, 0)) - node->kvs.begin();

		if (node->ptrs.empty()) {
			node->kvs.insert(node->kvs.begin() + idx, item);
		}
		else {

			if (node->ptrs[idx]->kvs.size() == 2 * t - 1) {
				splitChild(node, idx);
				if (key >= node->kvs[idx].first) ++idx;
			}

			insert_notfull(node->ptrs[idx], key, val);

		}

	}

	// ��СԪ��
	pointer minimum(pointer p) {

		while (!p->ptrs.empty()) p = p->ptrs[0];
		return p;

	}

	// ���Ԫ��
	pointer maximum(pointer p) {

		while (!p->ptrs.empty()) p = p->ptrs[p->ptrs.size() - 1];
		return p;

	}

	PlaceOfChild predecessor(pointer x, int i) {
		
		if (!x->ptrs.empty()) {
			x = maximum(x->ptrs[i]);
			return make_pair(x, x->kvs.size() - 1);
		}
		else if (i != 0) return make_pair(x, i - 1);
		
		int key = x->kvs[i].first;
		pointer y = root;
		vector<PlaceOfChild> stk;
		while (true) {
			if (y->kvs[0].first == key) break;
			for (i = 0; i<y->kvs.size() && key>y->kvs[i].first; ++i);
			stk.push_back(make_pair(y, i));
			y = y->ptrs[i];
		}

		PlaceOfChild p;
		while (!stk.empty()) {
			p = stk.back();
			stk.pop_back();
			if (p.second != 0) return p;
		}
		return make_pair(nullptr, 0);

	}

	PlaceOfChild successor(pointer x, int i) {

		if (!x->ptrs.empty()) {
			x = minimum(x->ptrs[i + 1]);
			return make_pair(x, 0);
		}
		else if (i != x->kvs.size() - 1) return make_pair(x, i + 1);

		int key = x->kvs[i].first;
		pointer y = root;
		vector<PlaceOfChild> stk;
		while (true) {
			if (y->kvs.back().first == key) break;
			for (i = 0; i<y->kvs.size() && key>y->kvs[i].first; ++i);
			stk.push_back(make_pair(y, i));
			y = y->ptrs[i];
		}

		PlaceOfChild p;
		while (!stk.empty()) {
			p = stk.back();
			stk.pop_back();
			if (p.second != p.first->kvs.size()) return p;
		}
		return make_pair(nullptr, 0);

	}

	// �ϲ�
	void combine(pointer x, pointer y, PlaceOfChild z) {

		x->kvs.push_back(z.first->kvs[z.second]);

		for (int i = 0; i < t - 1; ++i) {
			x->kvs.push_back(y->kvs[i]);
		}

		if (!x->ptrs.empty()) {
			for (int i = 0; i < t; ++i) {
				x->ptrs.push_back(y->ptrs[i]);
			}
		}
		delete y;
		y = nullptr;

		z.first->kvs.erase(z.first->kvs.begin() + z.second);

		// �������ֻᱨ��
		z.first->ptrs.earse(z.first->ptrs.begin() + z.second + 1);

		if (z.first->kvs.empty()) {
			root = z.first->ptrs[z.second];
			delete z.first;
		}
	}

	// ɾ��Ԫ�ظ�������
	void remove(pointer node, const K& key) {

		// �ڵ�ǰ�ڵ����key�����ֲ��ң�
		size_t idx = lower_bound(node->kvs.begin(), node->kvs.end(), make_pair(key, 0)) - node->kvs.begin();

		// ��ʼ���������
		if (idx < node->kvs.size() && node->kvs[idx].first == key) {

			// ��ΪҶ�ӽڵ�
			if (node->ptrs.empty()) node->kvs.erase(node->kvs.begin() + idx);
			// ��ΪҶ�ӽڵ�
			else {
				if (node->ptrs[idx]->kvs.size() >= t) {
					PlaceOfChild preOfk = predecessor(node, idx);
					node->kvs[idx] = preOfk.first->kvs[preOfk.second];
					remove(node->ptrs[idx], node->kvs[idx].first);
				}
				else if (node->ptrs[idx + 1]->kvs.size() >= t) {
					PlaceOfChild sucOfk = successor(node, idx);
					node->kvs[idx] = sucOfk.first->kvs[sucOfk.second];
					remove(node->ptrs[idx + 1], node->kvs[idx].first);
				}
				else {
					combine(node->ptrs[idx], node->ptrs[idx + 1], make_pair(node, idx));
					remove(node->ptrs[idx], key);
				}
			}

		}
		else {

			// �����������
			if (node->ptrs.empty()) return;
			else if (node->ptrs[idx]->kvs.size() != t - 1) remove(node->ptrs[idx], key);
			else {
				pointer y, z;
				if (idx > 0 && node->ptrs[idx - 1]->kvs.size() != t - 1) {

					y = node->ptrs[idx - 1];
					z = node->ptrs[idx];
					z->kvs.insert(z->kvs.begin(), node->kvs[idx - 1]);

					if (!y->ptrs.empty()) {

						z->ptrs.insert(z->ptrs.begin(), y->ptrs.back());
						y->ptrs.pop_back();

					}

					node->kvs[idx - 1] = y->kvs.back();
					y->kvs.pop_back();
					remove(z, key);

				}
				else if (idx < node->ptrs.size() - 1 && node->ptrs[idx + 1]->kvs.size() != t - 1) {
					
					y = node->ptrs[idx + 1];
					z = node->ptrs[idx];
					z->kvs.push_back(node->kvs[idx]);

					if (!y->ptrs.empty()) {

						z->ptrs.push_back(y->ptrs[0]);
						y->ptrs.erase(y->ptrs.begin());

					}

					node->kvs[idx] = y->kvs[0];
					y->kvs.erase(y->kvs.begin());
					remove(z, key);

				}
				else if (idx > 0) {
					
					y = node->ptrs[idx - 1];
					z = node->ptrs[idx];
					combine(y, z, make_pair(node, idx - 1));
					remove(y, key);

				}
				else if (idx < node->ptrs.size() - 1) {

					y = node->ptrs[idx];
					z = node->ptrs[idx + 1];
					combine(y, z, make_pair(node, idx));
					remove(y, key);

				}
			}

		}

	}

};

