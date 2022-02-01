#include "Array.h"
#include "Index.h"
#include "WordCardBinder.h"
#include<string.h>//strcmp

//Index_Create
void Index_Create(Index* index, Long capacity)
{
	//1. �Ҵ緮�� �Է¹޴´�.
	//2. ������ �����.
	Array_Create(&index->wordCards, capacity, sizeof(WordCard*));
	//3. �Ҵ緮�� ���Ѵ�.
	index->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	index->length = 0;
	//5. ������.
}

//Index_TakeIn
Long Index_TakeIn(Index* index, WordCard* wordCard)
{
	Long arrayIndex;

	//1. ��뷮�� �Ҵ緮���� ������
	if (index->length < index->capacity)
	{
		//1.1 �� ���� �ܾ�ī�带 �����Ѵ�.
		arrayIndex = Array_Store(&index->wordCards, index->length, &wordCard, sizeof(WordCard*));
	}
	//2. �׷��� ������
	else
	{
		//2.1 ���ο� ������ ���� ������ �����Ѵ�.
		arrayIndex = Array_AppendFromRear(&index->wordCards, &wordCard, sizeof(WordCard*));
		//2.2 �Ҵ緮�� ������Ų��.
		index->capacity++;
	}
	//3. ��뷮�� ������Ų��.
	index->length++;
	//4. �ܾ�ī���� ��ġ�� ����Ѵ�.
	return arrayIndex;
	//5. ������.
}

//Index_Find
Long Index_Find(Index* index, WordCard* wordCard)
{
	Long arrayIndex;

	//1. �ܾ�ī�� �ּҸ� �Է¹޴´�.
	//2. �ܾ�ī�带 ã�´�.
	arrayIndex = Array_LinearSearchUnique(&index->wordCards, wordCard, sizeof(WordCard*),
		CompareArray_WordCards);
	//3. �ܾ�ī���� ��ġ�� ����Ѵ�.
	return arrayIndex;
	//4. ������.
}

//Index_TakeOut
Long Index_TakeOut(Index* index, Long arrayIndex)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. ���ο� �ִ� �ܾ�ī�带 ���ش�.
	arrayIndex = Array_Delete(&index->wordCards, arrayIndex, sizeof(WordCard*));
	//3. �Ҵ緮�� ���ҽ�Ų��.
	index->capacity--;
	//4. ��뷮�� ���ҽ�Ų��.
	index->length--;
	//5. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//6. ������.
}

//Index_GetAt
WordCard* Index_GetAt(Index* index, Long arrayIndex)
{
	WordCard* wordCard;

	//1. �迭÷�ڸ� �Է¹޴´�.
	//2. ���ι迭�� ����� �ܾ�ī���� �ּҸ� �ҷ��´�.
	Array_GetAt(&index->wordCards, arrayIndex, &wordCard, sizeof(WordCard*));
	//3. �ܾ�ī���� �ּҸ� ����Ѵ�.
	return wordCard;
	//4. ������
}

//Index_Arrange
void Index_Arrange(Index* index)
{
	//1. ������������ �����Ѵ�.
	Array_InsertionSort(&index->wordCards, sizeof(WordCard*), CompareArray_Spellings);
	//2. ������.
}

//Index_Destroy
void Index_Destroy(Index* index)
{
	//1.  ������ �ܾ�ī�� ��������� ���ش�.
	Array_Destroy(&index->wordCards);
	//2. ������.
}

//�Լ�������
//CompareArray_WordCards
int CompareArray_WordCards(void* one, void* other)
{
	WordCard** one_ = (WordCard**)one;
	WordCard* other_ = (WordCard*)other;
	int ret;
	if (*one_ == other_)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}

//CompareArray_Spellings
int CompareArray_Spellings(void* one, void* other)
{
	WordCard** one_ = (WordCard**)one;
	WordCard** other_ = (WordCard**)other;

	return strcmp((*one_)->word.spellings, (*other_)->word.spellings);
}