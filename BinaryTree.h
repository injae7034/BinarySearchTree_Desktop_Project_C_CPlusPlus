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
		friend class BinaryTree;//BinaryTree에서 BinaryNode의 private멤버에 접근할 수 있게 해줌.
	public:
		//디폴트생성자
		Node()
		{
			this->left = 0;
			this->right = 0;
		}
		//매개변수를 가지는 생성자
		Node(T key)
		{
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		//복사생성자
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
		//치환연산자
		Node& operator=(const Node& source)
		{
			//1. 기존의 this를 지운다.
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
			//2. 새로운 내용을 저장한다.
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
			//3. 출력한다.
			return *this;
			//4. 끝내다
		}
		//GetLeft
		Node* GetLeft() const//Node&는 주소가 아니라 내용임!!
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
		//소멸자
		~Node()
		{
			//1. BinaryNode를 지운다.
			if (this->left != 0)
			{
				delete this->left;
			}
			if (this->right != 0)
			{
				delete this->right;
			}
			//2. 끝내다.
		}
		//MakeKeys
		void MakeKeys(T(*keys), Long* count, Long* i)
		{
			//1. 왼쪽이 있으면
			if (this->left != 0)
			{
				this->left->MakeKeys(keys, count, i);
			}
			//2. key를 배열에 저장한다.(중위)
			keys[*i] = this->key;
			(*i)++;
			(*count)++;
			//3. 오른쪽이 있으면
			if (this->right != 0)
			{
				this->right->MakeKeys(keys, count, i);
			}
			//3. keys배열과 개수, 첨자를 출력한다.
			//4. 끝내다.
		}
		//DeleteAllItems
		void DeleteAllItems()
		{
			//1. BinaryNode를 지운다.
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
			//2. 끝내다.
		}
		//MakeTree
		static Node* MakeTree(T(*keys), Long first, Long last)
		{
			Node* node = 0;
			//1. keys배열과 처음, 마지막 첨자를 입력받는다.
			//2. 처음이 마지막보다 작거나 같으면
			if (first <= last)
			{
				//2.1 중간을 구한다.
				Long middle = (first + last) / 2;
				//2.2 새로운 BinaryNode를 만든다.
				node = new Node(keys[middle]);
				//2.3 관계설정을 한다.
				node->left = node->MakeTree(keys, first, middle - 1);
				node->right = node->MakeTree(keys, middle + 1, last);
			}
			//3. binaryNode를 출력한다.
			return node;
			//4. 끝내다.
		}
	private:
		Node* left;
		T key;
		Node* right;
	};
	public:
		//기본생성자
		BinaryTree();
		//복사생성자
		BinaryTree(const BinaryTree& source);
		//치환연산자
		BinaryTree& operator=(const BinaryTree& source);
		//소멸자
		~BinaryTree();
		//연산함수
		Node* Insert(T key, int(*compare)(void*, void*));
		Node* Search(T key, int(*compare)(void*, void*));
		Node* Delete(T key, int(*compare)(void*, void*));
		void MakeBalance();
		void MakeKeys(T* (*keys), Long* count);
		void DeleteAllItems();
		void MakeTree(T(*keys), Long count);
		//인라인함수
		Long GetLength() const;
		Node* GetRoot() const;
	private:
		Node* root;
		Long length;
		Long balance;
};

//인라인함수 정의
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

//기본생성자
template<typename T>
BinaryTree<T>::BinaryTree()
{
	//1. 이분검색트리를 만든다.
	this->root = 0;
	this->length = 0;
	this->balance = 0;
	//2. 끝내다.
}

//복사생성자
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source)
{
	//1. BinaryNode를 복사한다.
	this->root = new Node(*source.root);
	//2. length를 복사한다.
	this->length = source.length;
	//3. balance를 복사한다.
	this->balance = source.balance;
	//4. 끝내다.
}

//치환연산자
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& source)
{
	//1. BinaryNode를 치환한다.
	*this->root = *source.root;
	//2. length를 치환한다.
	this->length = source.length;
	//3. balance를 치환한다.
	this->balance = source.balance;
	//4. this를 출력한다.
	return *this;
	//5. 끝내다.
}

//Insert
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*))
{
	//1. 데이터를 입력받는다.
	//2. 끼울 위치를 찾는다.
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
	//3. BinaryNode를 생성한다.
	Node* index = new Node(key);
	//4. BinaryNode를 끼운다.
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
	//5. 개수를 센다.
	this->length++;
	//6. 위치를 출력한다.
	return index;
	//7. 끝내다.
}

//Search
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Search(T key, int(*compare)(void*, void*))
{
	//1. 데이터를 입력받는다.
	//2. BinaryNode의 끝이 아닌동안 그리고 입력받은 데이터와 같지 않을 동안 반복한다.
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
	//3. 위치를 출력한다.
	return it;
	//4. 끝내다.
}

//Delete
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*))
{
	//1. 지울 데이터를 입력받는다.
	//2. BinaryTree에서 지울 데이터를 찾는다.
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
	//3. 지울 데이터의 BinaryNode를 대체할 BinaryNode를 찾는다.(관계재설정)
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
	//4. 관계를 재설정한다.
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
	//5. 데이터의 BinaryNode를 지운다.
	if (index != 0)
	{
		index->left = 0;
		index->right = 0;
		delete index;
		index = 0;
	}
	//6. 개수를 감소시킨다.
	this->length--;
	//7. balance를 구한다.
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
	//7. 위치를 출력한다.
	return index;
	//8. 끝내다.
}

//MakeBalance
template<typename T>
void BinaryTree<T>::MakeBalance()
{
	T(*keys);
	Long count;
	//1. keys 배열을 만든다.
	this->MakeKeys(&keys, &count);
	//2. 기존의 BinaryNode를 모두 지운다.
	this->DeleteAllItems();
	//3. 새로운 BinaryTree를 만든다.
	this->MakeTree(keys, count);
	//4. keys 배열을 할당해제한다.
	if (keys != 0)
	{
		delete[] keys;
	}
	//5. 끝내다.
}

//MakeKeys
template<typename T>
void BinaryTree<T>::MakeKeys(T* (*keys), Long* count)
{
	*count = 0;
	//1. keys배열을 만든다.
	*keys = new T[this->length];
	//2. keys를 저장한다.
	Long i = 0;
	this->root->MakeKeys(*keys, count, &i);
	//3. keys 배열과 개수를 출력한다.
	//4. 끝내다.
}

//DeleteAllItems
template<typename T>
void BinaryTree<T>::DeleteAllItems()
{
	//1. 기존의 BinaryNode를 모두 지운다.
	this->root->DeleteAllItems();
	//2. root를 초기화한다.
	this->root = 0;
	//3. length를 초기화한다.
	this->length = 0;
	//4. balance를 초기화한다.
	this->balance = 0;
	//5. 끝내다.
}

//MakeTree
template<typename T>
void BinaryTree<T>::MakeTree(T(*keys), Long count)
{
	//1. keys배열과 개수를 입력받는다.
	//2. 새로운 BinaryTree를 만든다.
	this->root = Node::MakeTree(keys, 0, count - 1);
	//3. 개수를 구한다.
	this->length = count;
	//4. 균형을 구한다.
	Long remainder = count % 2;
	if (remainder == 0)
	{
		this->balance = 1;
	}
	else
	{
		this->balance = 0;
	}
	//5. 끝내다.
}

//소멸자
template<typename T>
BinaryTree<T>::~BinaryTree()
{
	if (this->root != 0)
	{
		//1. BinaryNode를 지운다.
		delete this->root;
	}
	//2. 끝내다.
}

#endif // !_BINARYTREE_H
