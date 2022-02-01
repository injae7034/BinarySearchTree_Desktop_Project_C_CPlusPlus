#ifndef _INDEX_H
#define _INDEX_H
#include "Array.h"
typedef signed long int Long;
typedef struct _wordCard WordCard;
typedef struct _index
{
	char alphabet;
	Array wordCards;
	Long capacity;
	Long length;
}Index;

void Index_Create(Index* index, Long capacity);
Long Index_TakeIn(Index* index, WordCard* wordCard);
Long Index_Find(Index* index, WordCard* wordCard);
// Index_FindBySpellings에서 arrayIndexes의 자료형주의
void Index_FindBySpellings(Index* index, char(*spellings), Long*(*arrayIndexes), Long* count);
Long Index_TakeOut(Index* index, Long arrayIndex);
WordCard* Index_GetAt(Index* index, Long arrayIndex);
void Index_Arrange(Index* index);
void Index_Destroy(Index* index);

//함수포인터
int CompareArray_WordCards(void* one, void* other);
int CompareArray_Spellings(void* one, void* other);

#endif // !_INDEX_H
