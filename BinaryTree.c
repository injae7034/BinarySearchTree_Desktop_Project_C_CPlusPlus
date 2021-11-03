#include "BinaryTree.h"
#include<stddef.h>//size_t
#include<stdlib.h>//free, malloc, calloc
#include<memory.h>//memcpy
#pragma warning(disable:4996)

//Create
void Create(BinaryTree* binaryTree)
{
	//1. �̺а˻�Ʈ���� �����.
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
	//2. ������.
}

//Insert
BinaryNode* Insert(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*))
{
	BinaryNode* index;
	BinaryNode* it;
	BinaryNode* parent = NULL;

	//1. �����͸� �Է¹޴´�.
	//2. ���� ��ġ�� ã�´�.
	it = binaryTree->root;
	while (it != NULL)
	{
		parent = it;
		if (compare(it + 1, key) > 0)
		{
			it = it->left;
		}
		else
		{
			it = it->right;
		}
	}
	//3. ��带 �����.
	index = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	index->left = NULL;
	index->right = NULL;
	memcpy(index + 1, key, size);
	//4. ��带 �����.
	if (parent != NULL)
	{
		if (compare(parent + 1, key) > 0)
		{
			parent->left = index;
		}
		else
		{
			parent->right = index;
		}
		if (compare(binaryTree->root + 1, index + 1) > 0)
		{
			binaryTree->balance--;
		}
		else
		{
			binaryTree->balance++;
		}
	}
	else
	{
		binaryTree->root = index;
	}
	//5. ������ ����.
	binaryTree->length++;
	//6. ��ġ�� ����Ѵ�.
	return index;
	//7. ������.
}

//Search
BinaryNode* Search(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*))
{
	BinaryNode* it = NULL;

	//1. �����͸� �Է¹޴´�.
	//2. ����� ���� �ƴѵ��� �׸��� �Է¹��� �����Ϳ� ���� ���� ���� �ݺ��Ѵ�.
	it = binaryTree->root;
	while (it != NULL && compare(it + 1, key) != 0)
	{
		if (compare(it + 1, key) > 0)
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
BinaryNode* Delete(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*))
{
	BinaryNode* index;
	BinaryNode* parentOfIndex;
	BinaryNode* replacement = NULL;
	BinaryNode* parentOfReplacement = NULL;
	BinaryNode* it;
	BinaryNode* parent = NULL;
	void* tempKey;

	tempKey = malloc(size);
	//1. �����͸� �Է¹޴´�.
	//2. �����͸� ã�´�.
	it = binaryTree->root;
	while (compare(it + 1, key) != 0)
	{
		parent = it;
		if (compare(it + 1, key) > 0)
		{
			it = it->left;
		}
		else
		{
			it = it->right;
		}
	}
	//3. �ش絥������ ��带 ��ü�� ��带 ã�´�.
	index = it;
	memcpy(tempKey, index + 1, size);
	parentOfIndex = parent;
	it = index->right;
	while (it != NULL)
	{
		parentOfReplacement = replacement;
		replacement = it;
		it = it->left;
	}
	it = index->left;
	while (it != NULL && index->right == NULL)
	{
		parentOfReplacement = replacement;
		replacement = it;
		it = it->right;
	}
	//4. ���踦 �ٽ� �����Ѵ�.
	if (replacement != NULL)
	{
		if (parentOfReplacement != NULL)
		{
			if (compare(parentOfReplacement + 1, replacement + 1) > 0)
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
			if (compare(index + 1, replacement + 1) < 0)
			{
				replacement->left = index->left;
			}
		}
	}
	if (parentOfIndex != NULL)
	{
		if (compare(parentOfIndex + 1, index + 1) > 0)
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
		binaryTree->root = replacement;
	}
	//5. �ش絥������ ��带 �����.
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	//6. ������ ���ҽ�Ų��.
	binaryTree->length--;
	//7. ������ ���Ѵ�.
	if (parentOfIndex != NULL)
	{
		if (compare(binaryTree->root + 1, tempKey) > 0)
		{
			binaryTree->balance++;
		}
		else
		{
			binaryTree->balance--;
		}
	}
	else
	{
		if (binaryTree->root != NULL)
		{
			if (compare(replacement + 1, tempKey) > 0)
			{
				binaryTree->balance--;
			}
			else
			{
				binaryTree->balance++;
			}
		}
	}
	if (tempKey != NULL)
	{
		free(tempKey);
	}
	//7. ��ġ�� ����Ѵ�.
	return index;
	//8. ������.
}

//MakeBalance
void MakeBalance(BinaryTree* binaryTree, size_t size)
{
	void(*keys);
	Long count;

	//1. keys�迭�� �����.
	MakeKeys(binaryTree, &keys, &count, size);
	//2. ������ �̺а˻���带 ��� �����.
	DeleteAllItems(binaryTree);
	//3. ���ο� �̺а˻�Ʈ���� �����.
	MakeTree(binaryTree, keys, count, size);
	//4. keys�迭�� �Ҵ������Ѵ�.
	if (keys != NULL)
	{
		free(keys);
	}
	//5. ������.
}

//MakeKeys
void MakeKeys(BinaryTree* binaryTree, void* (*keys), Long* count, size_t size)
{
	Long i = 0;

	*count = 0;
	//1. keys�迭�� �����.
	*keys = calloc(binaryTree->length, size);
	//2. keys�� �����Ѵ�.
	Node_Makekeys(binaryTree->root, *keys, count, &i, size);
	//3. keys�迭�� ������ ����Ѵ�.
	//4. ������.
}

//Node_MakeKeys
void Node_Makekeys(BinaryNode* node, void(*keys), Long* count, Long* i, size_t size)
{
	//1. node�� �д´�.
	//2. node�� null�� �ƴϸ�
	if (node != NULL)
	{
		//2.1 key�� �����Ѵ�.
		Node_Makekeys(node->left, keys, count, i, size);
		memcpy(((char*)keys) + ((*i)*size), node + 1, size);
		(*i)++;
		(*count)++;
		Node_Makekeys(node->right, keys, count, i, size);
	}
	//3. keys�� ����, ÷�ڸ� ����Ѵ�.
	//4. ������.
}

//DeleteAllItems
void DeleteAllItems(BinaryTree* binaryTree)
{
	//1. ��带 �����.
	Node_DeleteAllItems(binaryTree->root);
	//2. root�� �ʱ�ȭ�Ѵ�.
	binaryTree->root = NULL;
	//3. length�� �ʱ�ȭ�Ѵ�.
	binaryTree->length = 0;
	//4. balance�� �ʱ�ȭ�Ѵ�.
	binaryTree->balance = 0;
	//5. ������.
}

//Node_DeleteAllItems
void Node_DeleteAllItems(BinaryNode* node)
{
	//1. ��带 �д´�.
	//2. ��尡 null�� �ƴϸ�
	if (node != NULL)
	{
		//2.1 ��带 �����.
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		if (node != NULL)
		{
			free(node);
		}
	}
	//3. ������.
}

//MakeTree
void MakeTree(BinaryTree* binaryTree, void(*keys), Long count, size_t size)
{
	Long remainder;
	
	//1. keys�迭�� ������ �Է��Ѵ�.
	//2. ������ ���踦 ������ ���� ���� �����Ѵ�.
	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	//3. ������ ���Ѵ�.
	binaryTree->length = count;
	//4. ������ ���Ѵ�.
	remainder = count % 2;
	if (remainder == 0)
	{
		binaryTree->balance = 1;
	}
	else
	{
		binaryTree->balance = 0;
	}
	//5. ������.
}

//Node_MakeTree
BinaryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size)
{
	Long middle;
	BinaryNode* node = NULL;

	//1. keys�迭�� first, last�� �Է¹޴´�.
	//2. first�� last���� �۰ų� ������
	if (first <= last)
	{
		//2.1 �߰��� ���Ѵ�.
		middle = (first + last) / 2;
		//2.2 ���ο� ��带 �����.
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		//2.3 ��尪�� �ִ´�.
		memcpy(node + 1, ((char*)keys) + (middle * size), size);
		//2.4 ���輳���� �Ѵ�.
		node->left = Node_MakeTree(keys, first, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, last, size);
	}
	//3. ��带 ����Ѵ�.
	return node;
	//4. ������.
}

//GetAt
void GetAt(BinaryTree* binaryTree, BinaryNode* node, void* key, size_t size)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. key�� �����͸� �����Ѵ�.
	memcpy(key, node + 1, size);
	//3. key�� ����Ѵ�.
	//4. ������.
}

//Destroy
void Destroy(BinaryTree* binaryTree)
{
	//1. ��带 �����.
	Node_Destroy(binaryTree->root);
	//2. ������.
}

//Node_Destroy
void Node_Destroy(BinaryNode* node)
{
	//1. ��带 �Է¹޴´�.
	//2. ��尡 null�� �ƴϸ�
	if (node != NULL)
	{
		//2.1 ��带 �����.
		Node_Destroy(node->left);
		Node_Destroy(node->right);
		if (node != NULL)
		{
			free(node);
		}
	}
	//3. ������.
}