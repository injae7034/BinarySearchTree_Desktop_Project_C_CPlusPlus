#include "BinaryTree.h"
#include<string.h>
#include"IndexBinder.h"
#include"Index.h"
#include "VisitingCardBinder.h"
#pragma warning(disable:4996)

//IndexBinder_Create
void IndexBinder_Create(IndexBinder* indexBinder)
{
	//1. ����ö�� �����.
	BinaryTree_Create(&indexBinder->indexes);
	//2. ��뷮�� ���Ѵ�.
	indexBinder->length = 0;
	//3. ������
}

//IndexBinder_TakeIn
Index* IndexBinder_TakeIn(IndexBinder* indexBinder, VisitingCard* visitingCardLink)
{
	BinaryNode* node;
	Index index;
	Long arrayIndex;
	Index* indexLink;

	//1. ������ ��ġ�� �Է¹޴´�.
	//2. ���ο� ȸ���̸��� �����Ѵ�.
	strcpy(index.companyName, visitingCardLink->company.name);
	//3. ����ö�� ���� �߿� ���� ȸ���̸��� �ִ��� ã�´�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. ���� ȸ���̸��� ���� ��쿡
	if (node == NULL)
	{
		//4.1 ������ ���� �����.
		Index_Create(&index, 3);
		//4.2 ������ ����ö�� �����.
		node = BinaryTree_Insert(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//4.3 ����ö�� ��뷮�� ������Ų��.
		indexBinder->length++;
	}
	//5. ������ �ּҸ� ���Ѵ�.
	indexLink = (Index*)(node + 1);
	//6. ���ο� ������ �����.
	arrayIndex = Index_TakeIn(indexLink, visitingCardLink);
	//7. ������ ��ġ�� ����Ѵ�.
	return indexLink;
	//8. ������.
}

//IndexBinder_Find
Index* IndexBinder_Find(IndexBinder* indexBinder, char(*companyName))
{
	Index* indexLink = NULL;
	BinaryNode* node;
	Index index;

	//1. ������ ȸ���̸��� �Է¹޴´�.
	//2. ���ο� ȸ���̸��� �����Ѵ�.
	strcpy(index.companyName, companyName);
	//3. ����ö�� �����߿��� ���� ȸ���� �̸��� �ִ��� ã�´�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. ����ö�� ���� ȸ�簡 ������
	if (node != NULL)
	{
		//4.1 ������ �ּҸ� ���Ѵ�.
		indexLink = (Index*)(node + 1);
	}
	//5. ������ ��ġ�� ����Ѵ�.
	return indexLink;
	//6. ������.
}

//IndexBinder_TakeOut
Index* IndexBinder_TakeOut(IndexBinder* indexBinder, char(*companyName), VisitingCard* visitingCardLink)
{
	BinaryNode* node;
	Index* indexLink;
	Index index;
	Long arrayIndex;

	//1. ȸ�� �̸��� ������ ��ġ�� �Է¹޴´�.
	//2. ���ο� ȸ�� �̸��� �����Ѵ�.
	strcpy(index.companyName, companyName);
	//3. ����ö���� ���� ȸ�� �̸��� ã�´�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. ������ �ּҸ� ���Ѵ�.
	indexLink = (Index*)(node + 1);
	//5. ���ο��� ������ ã�´�.
	arrayIndex = Index_Find(indexLink, visitingCardLink);
	//6. ���ο��� ������ �����.
	arrayIndex = Index_TakeOut(indexLink, arrayIndex);
	//7. ������ ���԰����� 0�̸�
	if (indexLink->length == 0)
	{
		//7.1 ������ �����.
		node = BinaryTree_Delete(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//7.2 ������ ��뷮�� ���ҽ�Ų��.
		indexBinder->length--;
		indexLink = NULL;
	}
	//8. ������ �ּҸ� ����Ѵ�.
	return indexLink;
	//9. ������.
}

//IndexBinder_MakeList
void IndexBinder_MakeList(IndexBinder* indexBinder, Index* (*indexes), Long* count)
{
	//1. ���ι迭�� �����.
	BinaryTree_MakeKeys(&indexBinder->indexes, indexes, count, sizeof(Index));
	//2. ������.
}

//IndexBinder_Arrange
void IndexBinder_Arrange(IndexBinder* indexBinder)
{
	//1. ����ö�� ���ε��� �����Ѵ�.
	BinaryTree_MakeBalance(&indexBinder->indexes, sizeof(Index));
	//2. ������ ���ε��� ���Ե��� �����Ѵ�.
	Node_IndexArrange(indexBinder->indexes.root);
	//3. ������.
}

//IndexBinder_Destroy
void IndexBinder_Destroy(IndexBinder* indexBinder)
{
	//1. ������ ���ε��� ������ ���ش�.
	Node_IndexDestroy(indexBinder->indexes.root);
	//2. ����ö�� ���ε��� ���ش�.
	BinaryTree_Destroy(&indexBinder->indexes);
	//3. ������.
}

//����Լ�

void Node_IndexArrange(BinaryNode* node)
{
	Index* index;
	//1. node�� �д´�.
	//2. node�� null�� �ƴϸ�
	if (node != NULL)
	{
		//2.1 ������ ���Ե��� �����Ѵ�.
		Node_IndexArrange(node->left);
		index = (Index*)(node + 1);
		Index_Arrange(index);
		Node_IndexArrange(node->right);
	}
	//3. ������.
}

//Node_IndexDestroy
void Node_IndexDestroy(BinaryNode* node)
{
	Index* index;
	//1. node�� �д´�.
	//2. node�� null�� �ƴϸ� 
	if (node != NULL)
	{
		//2.1 ������ ���Ե��� ���ش�.
		Node_IndexDestroy(node->left);
		Node_IndexDestroy(node->right);
		index = (Index*)(node + 1);
		Index_Destroy(index);
	}
	//3. ������.
}

//�Լ�������
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;

	return strcmp(one_->companyName, other_->companyName);
}