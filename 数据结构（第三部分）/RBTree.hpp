#pragma once

#include<iostream>

using namespace std;

// �ڵ���ɫ
// C++ ö����
typedef enum class Color {
	RED, BLACK
} Color;

/// <summary>
/// ������ڵ�
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class RBTreeNode {
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	// ��Ա����
	Color color;
	Pair kv;
	RBTreeNode<K, V>* parent;
	RBTreeNode<K, V>* left;
	RBTreeNode<K, V>* right;

	// Ĭ�Ϲ��캯��
	RBTreeNode() :color(Color::RED), kv(make_pair(K(), V())), parent(nullptr), left(nullptr), right(nullptr) {};

	// ���ݼ�ֵ�ԵĹ��캯��
	RBTreeNode(K key, V val) : color(Color::RED), kv(make_pair(key, val)), parent(nullptr), left(nullptr), right(nullptr) {};

	// Ĭ���²���Ľڵ㶼�Ǻ�ɫ�ڵ�
};

/// <summary>
/// �����
/// </summary>
/// <typeparam name="K">��������</typeparam>
/// <typeparam name="V">ֵ������</typeparam>
template<typename K, typename V>
class RBTree {

	// ���г�Ա
public:

	// ��ֵ������
	using Pair = pair<K, V>;

	// �ڵ�ָ������
	using pointer = RBTreeNode<K, V>*;

	// ���캯������ʼʱ�������Ϊ��
	RBTree() {
		nil = new RBTreeNode<K, V>();
		nil->left = nil->right = nil->parent = nil;
		root = nil;
		nil->color = Color::BLACK;
	}

	// ��������
	~RBTree() {
		destroy(root);
		delete nil;
		nil = nullptr;
	}

	// �����½ڵ�
	void insert(const K& key, const V& val) {

		// ָ���ڱ�����ڵ�
		pointer p = nil;
		pointer s = root;

		// ���������ʵ�λ��
		while (s != nil) {

			// ����β���ļ��Ѿ����ڹ���ʱ�򣬺�����β���
			if (key == s->kv.first) return;

			// pʼ������Ϊs�ĸ��ڵ�
			p = s;
			if (key < s->kv.first) s = s->left;
			else if (key > s->kv.first) s = s->right;
		}

		// s��ʱΪnil
		s = new RBTreeNode<K, V>(key, val);
		s->left = s->right = s->parent = nil;

		// ��RBTreeΪ��ʱ
		if (p == nil) {
			root = s;
			root->parent = p;
		}
		// ��RBTree��Ϊ��ʱ
		else {
			if (key < p->kv.first) p->left = s;
			else if (key > p->kv.first) p->right = s;
			s->parent = p;
		}

		// �����ƽ��
		insert_fixed(s);

	}

	// �����½ڵ�
	void insert(K&& key, const V& val) {

		// ָ���ڱ�����ڵ�
		pointer p = nil;
		pointer s = root;

		// ���������ʵ�λ��
		while (s != nil) {

			// ����β���ļ��Ѿ����ڹ���ʱ�򣬺�����β���
			if (key == s->kv.first) return;

			// pʼ������Ϊs�ĸ��ڵ�
			p = s;
			if (key < s->kv.first) s = s->left;
			else if (key > s->kv.first) s = s->right;
		}

		// s��ʱΪnil
		s = new RBTreeNode<K, V>(key, val);
		s->left = s->right = s->parent = nil;

		// ��RBTreeΪ��ʱ
		if (p == nil) {
			root = s;
			root->parent = p;
		}
		// ��RBTree��Ϊ��ʱ
		else {
			if (key < p->kv.first) p->left = s;
			else if (key > p->kv.first) p->right = s;
			s->parent = p;
		}

		// �����ƽ��
		insert_fixed(s);

	}

	// �����½ڵ�
	void insert(const K& key, V&& val) {

		// ָ���ڱ�����ڵ�
		pointer p = nil;
		pointer s = root;

		// ���������ʵ�λ��
		while (s != nil) {

			// ����β���ļ��Ѿ����ڹ���ʱ�򣬺�����β���
			if (key == s->kv.first) return;

			// pʼ������Ϊs�ĸ��ڵ�
			p = s;
			if (key < s->kv.first) s = s->left;
			else if (key > s->kv.first) s = s->right;
		}

		// s��ʱΪnil
		s = new RBTreeNode<K, V>(key, val);
		s->left = s->right = s->parent = nil;

		// ��RBTreeΪ��ʱ
		if (p == nil) {
			root = s;
			root->parent = p;
		}
		// ��RBTree��Ϊ��ʱ
		else {
			if (key < p->kv.first) p->left = s;
			else if (key > p->kv.first) p->right = s;
			s->parent = p;
		}

		// �����ƽ��
		insert_fixed(s);

	}

	// �����½ڵ�
	void insert(K&& key, V&& val) {

		// ָ���ڱ�����ڵ�
		pointer p = nil;
		pointer s = root;

		// ���������ʵ�λ��
		while (s != nil) {

			// ����β���ļ��Ѿ����ڹ���ʱ�򣬺�����β���
			if (key == s->kv.first) return;

			// pʼ������Ϊs�ĸ��ڵ�
			p = s;
			if (key < s->kv.first) s = s->left;
			else if (key > s->kv.first) s = s->right;
		}

		// s��ʱΪnil
		s = new RBTreeNode<K, V>(key, val);
		s->left = s->right = s->parent = nil;

		// ��RBTreeΪ��ʱ
		if (p == nil) {
			root = s;
			root->parent = p;
		}
		// ��RBTree��Ϊ��ʱ
		else {
			if (key < p->kv.first) p->left = s;
			else if (key > p->kv.first) p->right = s;
			s->parent = p;
		}

		// �����ƽ��
		insert_fixed(s);

	}

	// ɾ�����
	void remove(const K& key) {

		pointer t;

		// ���ҵ�ָ�����
		if ((t = search(root, key)) != nil) remove(t);
		else cout << "Key is not exist." << endl;

	}

	// ɾ�����
	void remove(K&& key) {

		pointer t;

		// ���ҵ�ָ�����
		if ((t = search(root, std::move(key))) != nil) remove(t);
		else cout << "Key is not exist." << endl;

	}

	// ���Ҽ�ֵ��
	V find(const K& key) const {
		return search(root, key)->kv.second;
	}

	// ���Ҽ�ֵ��
	V find(K&& key) const {
		return search(root, std::move(key))->kv.second;
	}

	// ����operator[]
	// ���ؼ���Ӧ��ֵ
	V& operator[](const K& key) {

		pointer t = search(root, key);
		if (t != nil) return t->kv.second;
		else {
			insert(key, std::move(V()));
			return search(root, key)->kv.second;
		}

	}

	// ����operator[]
	// ���ؼ���Ӧ��ֵ
	V& operator[](K&& key) {

		pointer t = search(root, std::move(key));
		if (t != nil) return t->kv.second;
		else {
			insert(std::move(key), std::move(V()));
			return search(root, std::move(key))->kv.second;
		}

	}

	// ��ӡ���нڵ�
	void print(void) {
		show(root);
	}


	// ˽�г�Ա
private:

	// ���ڵ�
	pointer root;

	// �ڱ��ڵ�
	pointer nil;

	// ����������������
	void destroy(pointer& node) {
		if (node == nil) return;
		if (node->left != nil) destroy(node->left);
		if (node->right != nil) destroy(node->right);
		delete node;
		node = nullptr;
	}

	// ��ӡ������������
	void show(pointer& node) {
		if (node != nil) {
			show(node->left);
			cout << "key: " << node->kv.first << ", " << "value: " << node->kv.second << "; " << endl;
			show(node->right);
		}
	}

	// ����ת
	void leftRotation(pointer z) {
		
		// ��yָ��Ҫת����z���
		pointer y = z->right;

		z->right = y->left;
		if (y->left != nil) y->left->parent = z;
		y->parent = z->parent;


		// ����y��zλ��
		// ��z���Ǹ��ڵ�ʱ
		if (root == z) root = y;
		else if (z == z->parent->left) z->parent->left = y;
		else z->parent->right = y;

		y->left = z;
		z->parent = y;

	}

	// ����ת
	void rightRotation(pointer z) {

		// ��yָ��Ҫת����z���
		pointer y = z->left;

		z->left = y->right;
		if (y->right != nil) y->right->parent = z;
		y->parent = z->parent;

		// ����y��zλ��
		// ��z���Ǹ��ڵ�ʱ
		if (root == z) root = y;
		else if (z == z->parent->left) z->parent->left = y;
		else z->parent->right = y;

		y->right = z;
		z->parent = y;

	}

	// �����ĵ�������
	void insert_fixed(pointer s) {

		// ��ڵ�
		pointer uncle;

		// ���ڵ�Ϊ��ɫ
		while (s->parent->color == Color::RED) {
			
			// ���ڵ�������
			if (s->parent == s->parent->parent->left) {

				uncle = s->parent->parent->right;

				// ��ڵ�Ҳ�Ǻ�ɫ
				if (uncle->color == Color::RED) {

					// ���ڵ����ڵ㶼��Ϊ��ɫ
					s->parent->color = Color::BLACK;
					uncle->color = Color::BLACK;

					// �游����ɺ�ɫ
					s->parent->parent->color = Color::RED;

					// sָ��ָ���游��㣬��һ��ѭ���ж��游���ĸ��ڵ��Ƿ�Ϊ��ɫ
					s = s->parent->parent;

				}

				// û����ڵ����ڵ�Ϊ��ɫ
				else {

					// �����Ľڵ�Ϊ�ҽ��
					if (s == s->parent->right) {

						// ��ת���ڵ�
						s = s->parent;
						leftRotation(s);

					}

					// �������Ľڵ�����ڵ㣬�����ڵ��Ϊ��ɫ���游����ɺ�ɫ������ת�游���
					s->parent->color = Color::BLACK;
					s->parent->parent->color = Color::RED;
					rightRotation(s->parent->parent);

				}

			}
			else {

				// ���ڵ�Ϊ�ҽڵ�
				if (s->parent == s->parent->parent->right) {

					uncle = s->parent->parent->left;

					// ��ڵ�Ҳ�Ǻ�ɫ
					if (uncle->color == Color::RED) {

						// ���ڵ����ڵ㶼��Ϊ��ɫ
						s->parent->color = Color::BLACK;
						uncle->color = Color::BLACK;

						// �游����ɺ�ɫ
						s->parent->parent->color = Color::RED;

						// sָ��ָ���游��㣬��һ��ѭ���ж��游���ĸ��ڵ��Ƿ�Ϊ��ɫ
						s = s->parent->parent;

					}
					// û����ڵ�
					else {

						if (s == s->parent->left) {
							s = s->parent;
							rightRotation(s);
						}

						s->parent->color = Color::BLACK;
						s->parent->parent->color = Color::RED;
						leftRotation(s->parent->parent);

					}

				}

			}

		}

		// ���ڵ�ʼ��Ϊ��ɫ
		root->color = Color::BLACK;

	}

	// �ڲ����Һ���
	pointer search(pointer node, const K& key) const {
		
		// ���Ϊ��
		if (node == nil) return nil;
		// �Դ�С���ж�
		if (node->kv.first == key) return node;
		if (key < node->kv.first) return search(node->left, key);
		if (key > node->kv.first) return search(node->right, key);

	}

	// �ڲ����Һ���
	pointer search(pointer node, K&& key) const {

		// ���Ϊ��
		if (node == nil) return nil;
		// �Դ�С���ж�
		if (node->kv.first == key) return node;
		if (key < node->kv.first) return search(node->left, std::move(key));
		if (key > node->kv.first) return search(node->right, std::move(key));

	}

	// ���Ԫ�ص�ָ��
	pointer maximum(pointer x) {
		if (x->right == nil) return x;
		return maximum(x->right);
	}

	// ��СԪ�ص�ָ��
	pointer minimum(pointer x) {
		if (x->left == nil) return x;
		return minimum(x->left);
	}

	// ��u���ӽڵ�ָ��u��ָ��ı�ָ��v����v�ĸ��ڵ�ָ��ı�ָ��u�ĸ��ڵ�
	void transplant(pointer u, pointer v) {

		// ָ��ı�ָ��
		if (u->parent == nil) root = v;
		else if (u == u->parent->left) u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;

	}

	// �ڲ�ɾ������
	void remove(pointer z) {

		pointer x = nil;
		pointer y = z;
		Color ycolor = y->color;

		// zֻ���Һ���
		if (z->left = nil) {
			x = z->right;
			transplant(z, z->right);
		}
		// zֻ������
		else if (z->right == nil) {
			x = z->left;
			transplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			ycolor = y->color;
			x = y->right;
			if (y->parent == z) x->parent = y;
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);

			// �ı�ָ��
			y->left = z->left;
			z->left->parent = y;
			y->color = z->color;
		}

		if (ycolor == Color::BLACK) remove_fixed(x);

	}

	//�����ɾ������
	void remove_fixed(pointer x) {

		//�����x��Ϊ������������ɫ���Ǻ�ɫ
		while (x != root && x->color == Color::BLACK) {

			//x��������
			if (x == x->parent->left) {

				//w��x���ֽ��
				pointer w = x->parent->right; 

				//���1
				if (w->color == Color::RED) {
					w->color = Color::BLACK;
					x->parent->color = Color::RED;
					leftRotation(x->parent);
					w = x->parent->right;
				}

				//���2
				if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
					w->color = Color::RED;
					x = x->parent;
				}
				else {

					//���3
					if (w->right->color == Color::BLACK) {
						w->color = Color::RED;
						w->left->color = Color::BLACK;
						rightRotation(w);
						w = x->parent->right;
					}

					//���4
					w->color = w->parent->color;
					w->parent->color = Color::BLACK;
					w->right->color = Color::BLACK;
					leftRotation(x->parent);
					x = root; //����ѭ��

				}

			}
			// x��������
			else {

				pointer w = x->parent->left;

				//���1
				if (w->color == Color::RED) {
					w->parent->color = Color::RED;
					w->color = Color::BLACK;
					rightRotation(x->parent);
					w = x->parent->left;
				}

				//���2
				if (w->right->color == Color::BLACK && w->right->color == Color::BLACK) {
					w->color = Color::RED;
					x = x->parent;
				}
				else {

					//���3
					if (w->left->color == Color::BLACK) {
						w->right->color = Color::BLACK;
						w->color = Color::RED;
						leftRotation(w);
						w = x->parent->left;
					}

					//���4
					w->color = x->parent->color;
					x->parent->color = Color::BLACK;
					w->left->color = Color::BLACK;
					rightRotation(x->parent);
					x = root; //����ѭ��

				}

			}

		}

		// �ı���ɫ
		x->color = Color::BLACK;

	}

};
