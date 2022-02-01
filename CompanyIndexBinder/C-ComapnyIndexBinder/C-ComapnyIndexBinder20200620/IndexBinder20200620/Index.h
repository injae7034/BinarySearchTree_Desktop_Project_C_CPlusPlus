#ifndef _INDEX_H
#define _INDEX_H
#include "Array.h"
#include<stddef.h>//size

typedef signed long int Long;
typedef struct _visitingCard VisitingCard;
typedef struct _index
{
	char companyName[32];
	Array visitingCards;
	Long capacity;
	Long length;
}Index;

void Index_Create(Index* index, Long capacity);
Long Index_TakeIn(Index* index, VisitingCard* visitingCardLink);
Long Index_Find(Index* index, VisitingCard* visitingCardLink);
Long Index_TakeOut(Index* index, Long arrayIndex);
void Index_Arrange(Index* index);
VisitingCard* Index_GetAt(Index* index, Long arrayIndex);
void Index_Destroy(Index* index);

//함수포인터
int CompareArray_VisitingCards(void* one, void* other);
int CompareArray_PersonalNames(void* one, void* other);

#endif // !_INDEX_H

