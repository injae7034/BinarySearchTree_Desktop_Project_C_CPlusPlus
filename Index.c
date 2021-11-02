#include "Array.h"
#include "Index.h"
#include "VisitingCardBinder.h"
#include<string.h>//strcpy
#include<stddef.h>//size
#include<memory.h>//memcpy
#pragma warning(disable:4996)

//Index_Create
void Index_Create(Index* index, Long capacity)
{
	//1. �Ҵ緮�� �Է¹޴´�.
	//2. ������ �����.
	Array_Create(&index->visitingCards, capacity, sizeof(VisitingCard*));
	//3. �Ҵ緮�� ���Ѵ�.
	index->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	index->length = 0;
	//5. ������.
}

//Index_TakeIn
Long Index_TakeIn(Index* index, VisitingCard* visitingCardLink)
{
	Long arrayIndex;

	//1. ȸ���̸��� ���ο� ����.
	strcpy(index->companyName, visitingCardLink->company.name);
	//2. ��뷮�� �Ҵ緮���� ������
	if (index->length < index->capacity)
	{
		//2.1 �� �ٿ� ������ ��ġ�� ���´�.
		arrayIndex = Array_Store(&index->visitingCards, index->length, &visitingCardLink,
			sizeof(VisitingCard*));
	}
	//3. �׷��� ������
	else
	{
		//3.1 �� �ٿ� ������ ��ġ�� ���´�.
		arrayIndex = Array_AppendFromRear(&index->visitingCards, &visitingCardLink, sizeof(VisitingCard*));
		//3.2 �Ҵ緮�� ������Ų��.
		index->capacity++;
	}
	//4. ��뷮�� ������Ų��.
	index->length++;
	//5. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//6. ������.
}

//Index_Find
Long Index_Find(Index* index, VisitingCard* visitingCardLink)
{
	Long arrayIndex;
	
	//1. �����ּҸ� �Է¹޴´�.
	//2. ������ ã�´�.
	arrayIndex = Array_LinearSearchUnique(&index->visitingCards, visitingCardLink, sizeof(VisitingCard*),
		CompareArray_VisitingCards);
	//3. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//4. ������.
}

//Long Index_TakeOut
Long Index_TakeOut(Index* index, Long arrayIndex)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. �ش� ��ġ�� ������ �����.
	arrayIndex = Array_Delete(&index->visitingCards, arrayIndex, sizeof(VisitingCard*));
	//3. �Ҵ緮�� ���ҽ�Ų��.
	index->capacity--;
	//4. ��뷮�� ���ҽ�Ų��.
	index->length--;
	//5. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//6. ������.
}

//Index_Arrange
void Index_Arrange(Index* index)
{
	//1. ������������ �����Ѵ�.
	Array_InsertionSort(&index->visitingCards, sizeof(VisitingCard*), CompareArray_PersonalNames);
	//2. ������.
}

//Index_GetAt
VisitingCard* Index_GetAt(Index* index, Long arrayIndex)
{
	VisitingCard* visitingCardLink;

	//1. �迭÷�ڸ� �Է¹޴´�.
	//2. ���ι迭�� ����� ������ �ּҸ� �ҷ��´�.
	Array_GetAt(&index->visitingCards, arrayIndex, &visitingCardLink, sizeof(VisitingCard*));
	//3. ������ �ּҸ� ����Ѵ�.
	return visitingCardLink;
	//4. ������.
}

//Index_Destroy
void Index_Destroy(Index* index)
{
	//1. ������ �����ּҹ迭�� �Ҵ������Ѵ�.
	Array_Destroy(&index->visitingCards);
	//2. ������.
}

//�Լ�������
//CompareArray_VisitingCards
int CompareArray_VisitingCards(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard* other_ = (VisitingCard*)other;
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

//CompareArray_PersonalNames
int CompareArray_PersonalNames(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard** other_ = (VisitingCard**)other;
	
	return strcmp((*one_)->personal.name, (*other_)->personal.name);
}