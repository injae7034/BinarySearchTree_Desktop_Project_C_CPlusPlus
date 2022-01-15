#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
#include "BinaryTree.h"

typedef signed long int Long;
typedef struct _visitingCard VisitingCard;
typedef struct _index Index;
typedef struct _indexBinder
{
	BinaryTree indexes;
	Long length;
}IndexBinder;

void IndexBinder_Create(IndexBinder* indexBinder);
Index* IndexBinder_TakeIn(IndexBinder* indexBinder, VisitingCard* visitingCardLink);
Index* IndexBinder_Find(IndexBinder* indexBinder, char(*companyName));
Index* IndexBinder_TakeOut(IndexBinder* indexBinder, char(*companyName), VisitingCard* visitingCardLink);
void IndexBinder_Arrange(IndexBinder* indexBinder);
void IndexBinder_MakeList(IndexBinder* indexBinder, Index* (*indexes), Long* count);
void IndexBinder_Destroy(IndexBinder* indexBinder);

//함수포인터
int CompareIndexes(void* one, void* other);

//재귀함수
void Node_IndexArrange(BinaryNode* node);
void Node_IndexDestroy(BinaryNode* node);

#endif // !_INDEXBINDER_H

