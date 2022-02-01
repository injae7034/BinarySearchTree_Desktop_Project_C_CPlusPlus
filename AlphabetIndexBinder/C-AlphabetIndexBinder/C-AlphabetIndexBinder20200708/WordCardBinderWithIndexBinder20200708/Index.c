#include "Array.h"
#include "Index.h"
#include "WordCardBinder.h"
#include<string.h>//strcmp

//Index_Create
void Index_Create(Index* index, Long capacity)
{
	//1. 할당량을 입력받는다.
	//2. 색인을 만든다.
	Array_Create(&index->wordCards, capacity, sizeof(WordCard*));
	//3. 할당량을 정한다.
	index->capacity = capacity;
	//4. 사용량을 정한다.
	index->length = 0;
	//5. 끝내다.
}

//Index_TakeIn
Long Index_TakeIn(Index* index, WordCard* wordCard)
{
	Long arrayIndex;

	//1. 사용량이 할당량보다 작으면
	if (index->length < index->capacity)
	{
		//1.1 빈 곳에 단어카드를 저장한다.
		arrayIndex = Array_Store(&index->wordCards, index->length, &wordCard, sizeof(WordCard*));
	}
	//2. 그렇지 않으면
	else
	{
		//2.1 새로운 공간을 만들어서 명함을 저장한다.
		arrayIndex = Array_AppendFromRear(&index->wordCards, &wordCard, sizeof(WordCard*));
		//2.2 할당량을 증가시킨다.
		index->capacity++;
	}
	//3. 사용량을 증가시킨다.
	index->length++;
	//4. 단어카드의 위치를 출력한다.
	return arrayIndex;
	//5. 끝내다.
}

//Index_Find
Long Index_Find(Index* index, WordCard* wordCard)
{
	Long arrayIndex;

	//1. 단어카드 주소를 입력받는다.
	//2. 단어카드를 찾는다.
	arrayIndex = Array_LinearSearchUnique(&index->wordCards, wordCard, sizeof(WordCard*),
		CompareArray_WordCards);
	//3. 단어카드의 위치를 출력한다.
	return arrayIndex;
	//4. 끝내다.
}

//Index_TakeOut
Long Index_TakeOut(Index* index, Long arrayIndex)
{
	//1. 위치를 입력받는다.
	//2. 색인에 있는 단어카드를 없앤다.
	arrayIndex = Array_Delete(&index->wordCards, arrayIndex, sizeof(WordCard*));
	//3. 할당량을 감소시킨다.
	index->capacity--;
	//4. 사용량을 감소시킨다.
	index->length--;
	//5. 위치를 출력한다.
	return arrayIndex;
	//6. 끝내다.
}

//Index_GetAt
WordCard* Index_GetAt(Index* index, Long arrayIndex)
{
	WordCard* wordCard;

	//1. 배열첨자를 입력받는다.
	//2. 색인배열에 저장된 단어카드의 주소를 불러온다.
	Array_GetAt(&index->wordCards, arrayIndex, &wordCard, sizeof(WordCard*));
	//3. 단어카드의 주소를 출력한다.
	return wordCard;
	//4. 끝내다
}

//Index_Arrange
void Index_Arrange(Index* index)
{
	//1. 오름차순으로 정렬한다.
	Array_InsertionSort(&index->wordCards, sizeof(WordCard*), CompareArray_Spellings);
	//2. 끝내다.
}

//Index_Destroy
void Index_Destroy(Index* index)
{
	//1.  색인의 단어카드 저장공간을 없앤다.
	Array_Destroy(&index->wordCards);
	//2. 끝내다.
}

//함수포인터
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