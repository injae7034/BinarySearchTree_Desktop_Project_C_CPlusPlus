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
	//1. 할당량을 입력받는다.
	//2. 색인을 만든다.
	Array_Create(&index->visitingCards, capacity, sizeof(VisitingCard*));
	//3. 할당량을 정한다.
	index->capacity = capacity;
	//4. 사용량을 정한다.
	index->length = 0;
	//5. 끝내다.
}

//Index_TakeIn
Long Index_TakeIn(Index* index, VisitingCard* visitingCardLink)
{
	Long arrayIndex;

	//1. 회사이름을 색인에 쓴다.
	strcpy(index->companyName, visitingCardLink->company.name);
	//2. 사용량이 할당량보다 작으면
	if (index->length < index->capacity)
	{
		//2.1 빈 줄에 명함의 위치를 적는다.
		arrayIndex = Array_Store(&index->visitingCards, index->length, &visitingCardLink,
			sizeof(VisitingCard*));
	}
	//3. 그렇지 않으면
	else
	{
		//3.1 새 줄에 명함의 위치를 적는다.
		arrayIndex = Array_AppendFromRear(&index->visitingCards, &visitingCardLink, sizeof(VisitingCard*));
		//3.2 할당량을 증가시킨다.
		index->capacity++;
	}
	//4. 사용량을 증가시킨다.
	index->length++;
	//5. 위치를 출력한다.
	return arrayIndex;
	//6. 끝내다.
}

//Index_Find
Long Index_Find(Index* index, VisitingCard* visitingCardLink)
{
	Long arrayIndex;
	
	//1. 명함주소를 입력받는다.
	//2. 명함을 찾는다.
	arrayIndex = Array_LinearSearchUnique(&index->visitingCards, visitingCardLink, sizeof(VisitingCard*),
		CompareArray_VisitingCards);
	//3. 위치를 출력한다.
	return arrayIndex;
	//4. 끝내다.
}

//Long Index_TakeOut
Long Index_TakeOut(Index* index, Long arrayIndex)
{
	//1. 위치를 입력받는다.
	//2. 해당 위치의 명함을 지운다.
	arrayIndex = Array_Delete(&index->visitingCards, arrayIndex, sizeof(VisitingCard*));
	//3. 할당량을 감소시킨다.
	index->capacity--;
	//4. 사용량을 감소시킨다.
	index->length--;
	//5. 위치를 출력한다.
	return arrayIndex;
	//6. 끝내다.
}

//Index_Arrange
void Index_Arrange(Index* index)
{
	//1. 오름차순으로 정렬한다.
	Array_InsertionSort(&index->visitingCards, sizeof(VisitingCard*), CompareArray_PersonalNames);
	//2. 끝내다.
}

//Index_GetAt
VisitingCard* Index_GetAt(Index* index, Long arrayIndex)
{
	VisitingCard* visitingCardLink;

	//1. 배열첨자를 입력받는다.
	//2. 색인배열에 저장된 명함의 주소를 불러온다.
	Array_GetAt(&index->visitingCards, arrayIndex, &visitingCardLink, sizeof(VisitingCard*));
	//3. 명함의 주소를 출력한다.
	return visitingCardLink;
	//4. 끝내다.
}

//Index_Destroy
void Index_Destroy(Index* index)
{
	//1. 색인의 명함주소배열을 할당해제한다.
	Array_Destroy(&index->visitingCards);
	//2. 끝내다.
}

//함수포인터
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