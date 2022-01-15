#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;

template<typename T>
class BinaryTree
{
public:
	//Nested Class
	class Node
	{
		friend class BinaryTree;//BinaryTree���� BinaryNode�� private����� ������ �� �ְ� ����.
	public:
		//����Ʈ������
		Node()
		{
			this->left = 0;
			this->right = 0;
		}
		//�Ű������� ������ ������
		Node(T key)
		{
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		//���������
		Node(const Node& source)
		{
			this->left = 0;
			this->key = source.key;
			this->right = 0;
			if (source.left != 0)
			{
				this->left = new Node(*source.left);
			}
			if (source.right != 0)
			{
				this->right = new Node(*source.right);
			}
		}
		//ġȯ������
		Node& operator=(const Node& source)
		{
			//1. ������ this�� �����.
			if (this->left != 0)
			{
				delete this->left;
				this->left = 0;
			}
			if (this->right != 0)
			{
				delete this->right;
				this->right = 0;
			}
			//2. ���ο� ������ �����Ѵ�.
			this->key = source.key;
			if (source.left != 0)
			{
				this->left = new Node;
				*this->left = *source.left;
			}
			if (source.right != 0)
			{
				this->right = new Node;
				*this->right = *source.right;
			}
			//3. ����Ѵ�.
			return *this;
			//4. ������
		}
		//GetLeft
		Node* GetLeft() const//Node&�� �ּҰ� �ƴ϶� ������!!
		{
			return const_cast<Node*>(this->left);
		}
		//GetKey
		T& GetKey() const
		{
			return const_cast<T&>(this->key);
		}
		//GetRight
		Node* GetRight() const
		{
			return const_cast<Node*>(this->right);
		}
		//�Ҹ���
		~Node()
		{
			//1. BinaryNode�� �����.
			if (this->left != 0)
			{
				delete this->left;
			}
			if (this->right != 0)
			{
				delete this->right;
			}
			//2. ������.
		}
		//MakeKeys
		void MakeKeys(T(*keys), Long* count, Long* i)
		{
			//1. ������ ������
			if (this->left != 0)
			{
				this->left->MakeKeys(keys, count, i);
			}
			//2. key�� �迭�� �����Ѵ�.(����)
			keys[*i] = this->key;
			(*i)++;
			(*count)++;
			//3. �������� ������
			if (this->right != 0)
			{
				this->right->MakeKeys(keys, count, i);
			}
			//3. keys�迭�� ����, ÷�ڸ� ����Ѵ�.
			//4. ������.
		}
		//DeleteAllItems
		void DeleteAllItems()
		{
			//1. BinaryNode�� �����.
			if (this->left != 0)
			{
				this->left->DeleteAllItems();
			}
			if (this->right != 0)
			{
				this->right->DeleteAllItems();
			}
			this->left = 0;
			this->right = 0;
			delete this;
			//2. ������.
		}
		//MakeTree
		static Node* MakeTree(T(*keys), Long first, Long last)
		{
			Node* node = 0;
			//1. keys�迭�� ó��, ������ ÷�ڸ� �Է¹޴´�.
			//2. ó���� ���������� �۰ų� ������
			if (first <= last)
			{
				//2.1 �߰��� ���Ѵ�.
				Long middle = (first + last) / 2;
				//2.2 ���ο� BinaryNode�� �����.
				node = new Node(keys[middle]);
				//2.3 ���輳���� �Ѵ�.
				node->left = node->MakeTree(keys, first, middle - 1);
				node->right = node->MakeTree(keys, middle + 1, last);
			}
			//3. binaryNode�� ����Ѵ�.
			return node;
			//4. ������.
		}
	private:
		Node* left;
		T key;
		Node* right;
	};
	public:
		//�⺻������
		BinaryTree();
		//���������
		BinaryTree(const BinaryTree& source);
		//ġȯ������
		BinaryTree& operator=(const BinaryTree& source);
		//�Ҹ���
		~BinaryTree();
		//�����Լ�
		Node* Insert(T key, int(*compare)(void*, void*));
		Node* Search(T key, int(*compare)(void*, void*));
		Node* Delete(T key, int(*compare)(void*, void*));
		void MakeBalance();
		void MakeKeys(T* (*keys), Long* count);
		void DeleteAllItems();
		void MakeTree(T(*keys), Long count);
		//�ζ����Լ�
		Long GetLength() const;
		Node* GetRoot() const;
	private:
		Node* root;
		Long length;
		Long balance;
};

//�ζ����Լ� ����
template<typename T>
inline Long BinaryTree<T>::GetLength() const
{
	return this->length;
}
template<typename T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::GetRoot() const
{
	return const_cast<Node*>(this->root);
}

//�⺻������
template<typename T>
BinaryTree<T>::BinaryTree()
{
	//1. �̺а˻�Ʈ���� �����.
	this->root = 0;
	this->length = 0;
	this->balance = 0;
	//2. ������.
}

//���������
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source)
{
	//1. BinaryNode�� �����Ѵ�.
	this->root = new Node(*source.root);
	//2. length�� �����Ѵ�.
	this->length = source.length;
	//3. balance�� �����Ѵ�.
	this->balance = source.balance;
	//4. ������.
}

//ġȯ������
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& source)
{
	//1. BinaryNode�� ġȯ�Ѵ�.
	*this->root = *source.root;
	//2. length�� ġȯ�Ѵ�.
	this->length = source.length;
	//3. balance�� ġȯ�Ѵ�.
	this->balance = source.balance;
	//4. this�� ����Ѵ�.
	return *this;
	//5. ������.
}

//Insert
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*))
{
	//1. �����͸� �Է¹޴´�.
	//2. ���� ��ġ�� ã�´�.
	Node* it = this->root;
	Node* parent = 0;
	while (it != 0)
	{
		parent = it;
		if (compare(&it->key, &key) > 0)
		{
			it = it->left;
		}
		else
		{
			it = it->right;
		}
	}
	//3. BinaryNode�� �����Ѵ�.
	Node* index = new Node(key);
	//4. BinaryNode�� �����.
	if (parent != 0)
	{
		if (compare(&parent->key, &key) > 0)
		{
			parent->left = index;
		}
		else
		{
			parent->right = index;
		}
		if (compare(&this->root->key, &index->key) > 0)
		{
			this->balance--;
		}
		else
		{
			this->balance++;
		}
	}
	else
	{
		this->root = index;
	}
	//5. ������ ����.
	this->length++;
	//6. ��ġ�� ����Ѵ�.
	return index;
	//7. ������.
}

//Search
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Search(T key, int(*compare)(void*, void*))
{
	//1. �����͸� �Է¹޴´�.
	//2. BinaryNode�� ���� �ƴѵ��� �׸��� �Է¹��� �����Ϳ� ���� ���� ���� �ݺ��Ѵ�.
	Node* it = this->root;
	while (it != 0 && compare(&it->key, &key) != 0)
	{
		if (compare(&it->key, &key) > 0)
		{
			it = it->left;
		}
		else
		{
			it = it->right;
		}
	}
	//3. ��ġ�� ����Ѵ�.
	return it;
	//4. ������.
}

//Delete
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*))
{
	//1. ���� �����͸� �Է¹޴´�.
	//2. BinaryTree���� ���� �����͸� ã�´�.
	Node* parent = 0;
	Node* it = this->root;
	while (compare(&it->key, &key) != 0)
	{
		parent = it;
		if (compare(&it->key, &key) > 0)
		{
			it = it->left;
		}
		else
		{
			it = it->right;
		}
	}
	//3. ���� �������� BinaryNode�� ��ü�� BinaryNode�� ã�´�.(�����缳��)
	Node* index = it;
	T tempKey = index->key;
	Node* parentOfIndex = parent;
	Node* replacement = 0;
	Node* parentOfReplacement = 0;
	it = index->right;
	while (it != 0)
	{
		parentOfReplacement = replacement;
		replacement = it;
		it = it->left;
	}
	it = index->left;
	while (it != 0 && index->right == 0)
	{
		parentOfReplacement = replacement;
		replacement = it;
		it = it->right;
	}
	//4. ���踦 �缳���Ѵ�.
	if (replacement != 0)
	{
		if (parentOfReplacement != 0)
		{
			if (compare(&parentOfReplacement->key, &replacement->key) > 0)
			{
				parentOfReplacement->left = replacement->right;
			}
			else
			{
				parentOfReplacement->right = replacement->left;
			}
			replacement->left = index->left;
			replacement->right = index->right;
		}
		else
		{
			if (compare(&index->key, &replacement->key) < 0)
			{
				replacement->left = index->left;
			}
		}
	}
	if (parentOfIndex != 0)
	{
		if (compare(&parentOfIndex->key, &index->key) > 0)
		{
			parentOfIndex->left = replacement;
		}
		else
		{
			parentOfIndex->right = replacement;
		}
	}
	else
	{
		this->root = replacement;
	}
	//5. �������� BinaryNode�� �����.
	if (index != 0)
	{
		index->left = 0;
		index->right = 0;
		delete index;
		index = 0;
	}
	//6. ������ ���ҽ�Ų��.
	this->length--;
	//7. balance�� ���Ѵ�.
	if (parentOfIndex != 0)
	{
		if (compare(&this->root->key, &tempKey) > 0)
		{
			this->balance++;
		}
		else
		{
			this->balance--;
		}
	}
	else
	{
		if (this->root != 0)
		{
			if (compare(&replacement->key, &tempKey) > 0)
			{
				this->balance--;
			}
			else
			{
				this->balance++;
			}
		}
	}
	//7. ��ġ�� ����Ѵ�.
	return index;
	//8. ������.
}

//MakeBalance
template<typename T>
void BinaryTree<T>::MakeBalance()
{
	T(*keys);
	Long count;
	//1. keys �迭�� �����.
	this->MakeKeys(&keys, &count);
	//2. ������ BinaryNode�� ��� �����.
	this->DeleteAllItems();
	//3. ���ο� BinaryTree�� �����.
	this->MakeTree(keys, count);
	//4. keys �迭�� �Ҵ������Ѵ�.
	if (keys != 0)
	{
		delete[] keys;
	}
	//5. ������.
}

//MakeKeys
template<typename T>
void BinaryTree<T>::MakeKeys(T* (*keys), Long* count)
{
	*count = 0;
	//1. keys�迭�� �����.
	*keys = new T[this->length];
	//2. keys�� �����Ѵ�.
	Long i = 0;
	this->root->MakeKeys(*keys, count, &i);
	//3. keys �迭�� ������ ����Ѵ�.
	//4. ������.
}

//DeleteAllItems
template<typename T>
void BinaryTree<T>::DeleteAllItems()
{
	//1. ������ BinaryNode�� ��� �����.
	this->root->DeleteAllItems();
	//2. root�� �ʱ�ȭ�Ѵ�.
	this->root = 0;
	//3. length�� �ʱ�ȭ�Ѵ�.
	this->length = 0;
	//4. balance�� �ʱ�ȭ�Ѵ�.
	this->balance = 0;
	//5. ������.
}

//MakeTree
template<typename T>
void BinaryTree<T>::MakeTree(T(*keys), Long count)
{
	//1. keys�迭�� ������ �Է¹޴´�.
	//2. ���ο� BinaryTree�� �����.
	this->root = Node::MakeTree(keys, 0, count - 1);
	//3. ������ ���Ѵ�.
	this->length = count;
	//4. ������ ���Ѵ�.
	Long remainder = count % 2;
	if (remainder == 0)
	{
		this->balance = 1;
	}
	else
	{
		this->balance = 0;
	}
	//5. ������.
}

//�Ҹ���
template<typename T>
BinaryTree<T>::~BinaryTree()
{
	if (this->root != 0)
	{
		//1. BinaryNode�� �����.
		delete this->root;
	}
	//2. ������.
}

#endif // !_BINARYTREE_H
