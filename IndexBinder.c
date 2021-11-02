#include "BinaryTree.h"
#include "Index.h"
#include "IndexBinder.h"
#include "WordCardBinder.h"

//IndexBinder_Create
void IndexBinder_Create(IndexBinder* indexBinder)
{
	//1. ����ö�� �����.
	BinaryTree_Create(&indexBinder->indexes);
	//2. ��뷮�� ���Ѵ�.
	indexBinder->length = 0;
	//3. ������.
}

//IndexBinder_TakeIn
Index* IndexBinder_TakeIn(IndexBinder* indexBinder, WordCard* wordCard)
{
	BinaryNode* node;
	Index index;
	Index* indexLink;
	Long arrayIndex;

	//1. �ܾ�ī���� ��ġ�� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	index.alphabet = wordCard->word.spellings[0];
	//3. �ҹ����� ��� �빮�ڷ� �ٲ��ش�.
	if (index.alphabet >= 'a' && index.alphabet <= 'z')
	{
		index.alphabet -= 32;
	}
	//4. ����ö�� ���� �߿� ���� ���ĺ��� �ִ��� Ȯ���Ѵ�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//5. ���� ���ĺ��� ���� ��쿡
	if (node == NULL)
	{
		//5.1 ������ ���� �����.
		Index_Create(&index, 3);
		//5.2 ������ ����ö�� �����.
		node = BinaryTree_Insert(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//5.3 ����ö�� ��뷮�� ������Ų��.
		indexBinder->length++;
	}
	//6. ������ �ּҸ� ���Ѵ�.
	indexLink = (Index*)(node + 1);
	//7. ���ο� ������ �����.
	arrayIndex = Index_TakeIn(indexLink, wordCard);
	//8. ������ �ּҸ� ����Ѵ�.
	return indexLink;
	//9. ������.
}

//IndexBinder_Find
Index* IndexBinder_Find(IndexBinder* indexBinder, char alphabet)
{
	Index index;
	Index* indexLink = NULL;
	BinaryNode* node;

	//1. �ܾ�ī���� ���ĺ��� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	if (alphabet >= 'a' && alphabet <= 'z')
	{
		alphabet -= 32;
	}
	index.alphabet = alphabet;
	//3. ����ö�� �����߿� ���� ���ĺ��� �ִ��� ã�´�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. ����ö�� ���� ���ĺ��� ������
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
Index* IndexBinder_TakeOut(IndexBinder* indexBinder, char alphabet, WordCard* wordCard)
{
	BinaryNode* node;
	Index index;
	Index* indexLink;
	Long arrayIndex;

	//1. ���ĺ��� �ܾ�ī���� ��ġ�� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	if (alphabet >= 'a' && alphabet <= 'z')
	{
		alphabet -= 32;
	}
	index.alphabet = alphabet;
	//3. ����ö���� ���� ���ĺ��� ã�´�.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. ������ �ּҸ� ���Ѵ�.
	indexLink = (Index*)(node + 1);
	//5. ���ο��� ������ ã�´�.
	arrayIndex = Index_Find(indexLink, wordCard);
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
	//1. ����ö���� ���ε��� �����Ѵ�.
	BinaryTree_MakeBalance(&indexBinder->indexes, sizeof(Index));
	//2. ������ ���ε��� �ܾ�ī�带 �����Ѵ�.
	Node_IndexArrange(indexBinder->indexes.root);
	//3. ������.

}


//IndexBinder_Destroy
void IndexBinder_Destroy(IndexBinder* indexBinder)
{
	//1. ������ ���ε��� �ܾ�ī����� ���ش�.
	Node_IndexDestroy(indexBinder->indexes.root);
	//2. ����ö�� ���ε��� ���ش�.
	BinaryTree_Destroy(&indexBinder->indexes);
	//3. ������.
}

//�Լ�������
//CompareIndexes
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;
	int ret;

	if (one_->alphabet > other_->alphabet)
	{
		ret = 1;
	}
	else if (one_->alphabet == other_->alphabet)
	{
		ret = 0;
	}
	else if( one_->alphabet < other_->alphabet)
	{
		ret = -1;
	}
	return ret;
}

//����Լ�
//Node_IndexDestroy
void Node_IndexDestroy(BinaryNode* node)
{
	Index* index;
	//1. node�� �д´�.
	//2. node��  null�� �ƴϸ�
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

//Node_IndexArrange
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