#include "BinaryTree.h"
#include<stddef.h>//size_t
#include<stdlib.h>//free, malloc, calloc
#include<memory.h>//memcpy
#pragma warning(disable:4996)

//Create
void Create(BinaryTree* binaryTree)
{
	//1. 이분검색트리를 만든다.
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
	//2. 끝내다.
}

//Insert
BinaryNode* Insert(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*))
{
	BinaryNode* index;
	BinaryNode* it;
	BinaryNode* parent = NULL;

	//1. 데이터를 입력받는다.
	//2. 끼울 위치를 찾는다.
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
	//3. 노드를 만든다.
	index = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	index->left = NULL;
	index->right = NULL;
	memcpy(index + 1, key, size);
	//4. 노드를 끼운다.
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
	//5. 개수를 센다.
	binaryTree->length++;
	//6. 위치를 출력한다.
	return index;
	//7. 끝내다.
}

//Search
BinaryNode* Search(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*))
{
	BinaryNode* it = NULL;

	//1. 데이터를 입력받는다.
	//2. 노드의 끝이 아닌동안 그리고 입력받은 데이터와 같지 않을 동안 반복한다.
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
	//3. 위치를 출력한다.
	return it;
	//4. 끝내다.
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
	//1. 데이터를 입력받는다.
	//2. 데이터를 찾는다.
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
	//3. 해당데이터의 노드를 대체할 노드를 찾는다.
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
	//4. 관계를 다시 설정한다.
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
	//5. 해당데이터의 노드를 지운다.
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	//6. 개수를 감소시킨다.
	binaryTree->length--;
	//7. 균형을 구한다.
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
	//7. 위치를 출력한다.
	return index;
	//8. 끝내다.
}

//MakeBalance
void MakeBalance(BinaryTree* binaryTree, size_t size)
{
	void(*keys);
	Long count;

	//1. keys배열을 만든다.
	MakeKeys(binaryTree, &keys, &count, size);
	//2. 기존의 이분검색노드를 모두 지운다.
	DeleteAllItems(binaryTree);
	//3. 새로운 이분검색트리를 만든다.
	MakeTree(binaryTree, keys, count, size);
	//4. keys배열을 할당해제한다.
	if (keys != NULL)
	{
		free(keys);
	}
	//5. 끝내다.
}

//MakeKeys
void MakeKeys(BinaryTree* binaryTree, void* (*keys), Long* count, size_t size)
{
	Long i = 0;

	*count = 0;
	//1. keys배열을 만든다.
	*keys = calloc(binaryTree->length, size);
	//2. keys를 저장한다.
	Node_Makekeys(binaryTree->root, *keys, count, &i, size);
	//3. keys배열과 개수를 출력한다.
	//4. 끝내다.
}

//Node_MakeKeys
void Node_Makekeys(BinaryNode* node, void(*keys), Long* count, Long* i, size_t size)
{
	//1. node를 읽는다.
	//2. node가 null이 아니면
	if (node != NULL)
	{
		//2.1 key를 저장한다.
		Node_Makekeys(node->left, keys, count, i, size);
		memcpy(((char*)keys) + ((*i)*size), node + 1, size);
		(*i)++;
		(*count)++;
		Node_Makekeys(node->right, keys, count, i, size);
	}
	//3. keys와 개수, 첨자를 출력한다.
	//4. 끝내다.
}

//DeleteAllItems
void DeleteAllItems(BinaryTree* binaryTree)
{
	//1. 노드를 지운다.
	Node_DeleteAllItems(binaryTree->root);
	//2. root를 초기화한다.
	binaryTree->root = NULL;
	//3. length를 초기화한다.
	binaryTree->length = 0;
	//4. balance를 초기화한다.
	binaryTree->balance = 0;
	//5. 끝내다.
}

//Node_DeleteAllItems
void Node_DeleteAllItems(BinaryNode* node)
{
	//1. 노드를 읽는다.
	//2. 노드가 null이 아니면
	if (node != NULL)
	{
		//2.1 노드를 지운다.
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		if (node != NULL)
		{
			free(node);
		}
	}
	//3. 끝내다.
}

//MakeTree
void MakeTree(BinaryTree* binaryTree, void(*keys), Long count, size_t size)
{
	Long remainder;
	
	//1. keys배열과 개수를 입력한다.
	//2. 노드들의 관계를 균형에 맞춰 새로 설정한다.
	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	//3. 개수를 구한다.
	binaryTree->length = count;
	//4. 균형을 구한다.
	remainder = count % 2;
	if (remainder == 0)
	{
		binaryTree->balance = 1;
	}
	else
	{
		binaryTree->balance = 0;
	}
	//5. 끝내다.
}

//Node_MakeTree
BinaryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size)
{
	Long middle;
	BinaryNode* node = NULL;

	//1. keys배열과 first, last를 입력받는다.
	//2. first가 last보다 작거나 같으면
	if (first <= last)
	{
		//2.1 중간을 구한다.
		middle = (first + last) / 2;
		//2.2 새로운 노드를 만든다.
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		//2.3 노드값을 넣는다.
		memcpy(node + 1, ((char*)keys) + (middle * size), size);
		//2.4 관계설정을 한다.
		node->left = Node_MakeTree(keys, first, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, last, size);
	}
	//3. 노드를 출력한다.
	return node;
	//4. 끝내다.
}

//GetAt
void GetAt(BinaryTree* binaryTree, BinaryNode* node, void* key, size_t size)
{
	//1. 위치를 입력받는다.
	//2. key에 데이터를 저장한다.
	memcpy(key, node + 1, size);
	//3. key를 출력한다.
	//4. 끝내다.
}

//Destroy
void Destroy(BinaryTree* binaryTree)
{
	//1. 노드를 지운다.
	Node_Destroy(binaryTree->root);
	//2. 끝내다.
}

//Node_Destroy
void Node_Destroy(BinaryNode* node)
{
	//1. 노드를 입력받는다.
	//2. 노드가 null이 아니면
	if (node != NULL)
	{
		//2.1 노드를 지운다.
		Node_Destroy(node->left);
		Node_Destroy(node->right);
		if (node != NULL)
		{
			free(node);
		}
	}
	//3. 끝내다.
}