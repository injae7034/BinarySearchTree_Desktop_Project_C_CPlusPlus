#include "BinaryTree.h"
#include<string.h>
#include"IndexBinder.h"
#include"Index.h"
#include "VisitingCardBinder.h"
#pragma warning(disable:4996)

//IndexBinder_Create
void IndexBinder_Create(IndexBinder* indexBinder)
{
	//1. 색인철을 만든다.
	BinaryTree_Create(&indexBinder->indexes);
	//2. 사용량을 정한다.
	indexBinder->length = 0;
	//3. 끝내다
}

//IndexBinder_TakeIn
Index* IndexBinder_TakeIn(IndexBinder* indexBinder, VisitingCard* visitingCardLink)
{
	BinaryNode* node;
	Index index;
	Long arrayIndex;
	Index* indexLink;

	//1. 명함의 위치를 입력받는다.
	//2. 색인에 회사이름을 기재한다.
	strcpy(index.companyName, visitingCardLink->company.name);
	//3. 색인철의 색인 중에 같은 회사이름이 있는지 찾는다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. 같은 회사이름이 없는 경우에
	if (node == NULL)
	{
		//4.1 색인을 새로 만든다.
		Index_Create(&index, 3);
		//4.2 색인을 색인철에 끼운다.
		node = BinaryTree_Insert(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//4.3 색인철의 사용량을 증가시킨다.
		indexBinder->length++;
	}
	//5. 색인의 주소를 구한다.
	indexLink = (Index*)(node + 1);
	//6. 색인에 명함을 끼운다.
	arrayIndex = Index_TakeIn(indexLink, visitingCardLink);
	//7. 색인의 위치를 출력한다.
	return indexLink;
	//8. 끝내다.
}

//IndexBinder_Find
Index* IndexBinder_Find(IndexBinder* indexBinder, char(*companyName))
{
	Index* indexLink = NULL;
	BinaryNode* node;
	Index index;

	//1. 명함의 회사이름을 입력받는다.
	//2. 색인에 회사이름을 기재한다.
	strcpy(index.companyName, companyName);
	//3. 색인철의 색인중에서 같은 회사의 이름이 있는지 찾는다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. 색인철에 같은 회사가 있으면
	if (node != NULL)
	{
		//4.1 색인의 주소를 구한다.
		indexLink = (Index*)(node + 1);
	}
	//5. 색인의 위치를 출력한다.
	return indexLink;
	//6. 끝내다.
}

//IndexBinder_TakeOut
Index* IndexBinder_TakeOut(IndexBinder* indexBinder, char(*companyName), VisitingCard* visitingCardLink)
{
	BinaryNode* node;
	Index* indexLink;
	Index index;
	Long arrayIndex;

	//1. 회사 이름과 명함의 위치를 입력받는다.
	//2. 색인에 회사 이름을 기재한다.
	strcpy(index.companyName, companyName);
	//3. 색인철에서 같은 회사 이름을 찾는다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. 색인의 주소를 구한다.
	indexLink = (Index*)(node + 1);
	//5. 색인에서 명함을 찾는다.
	arrayIndex = Index_Find(indexLink, visitingCardLink);
	//6. 색인에서 명함을 지운다.
	arrayIndex = Index_TakeOut(indexLink, arrayIndex);
	//7. 색인의 명함개수가 0이면
	if (indexLink->length == 0)
	{
		//7.1 색인을 지운다.
		node = BinaryTree_Delete(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//7.2 색인의 사용량을 감소시킨다.
		indexBinder->length--;
		indexLink = NULL;
	}
	//8. 색인의 주소를 출력한다.
	return indexLink;
	//9. 끝내다.
}

//IndexBinder_MakeList
void IndexBinder_MakeList(IndexBinder* indexBinder, Index* (*indexes), Long* count)
{
	//1. 색인배열을 만든다.
	BinaryTree_MakeKeys(&indexBinder->indexes, indexes, count, sizeof(Index));
	//2. 끝내다.
}

//IndexBinder_Arrange
void IndexBinder_Arrange(IndexBinder* indexBinder)
{
	//1. 색인철의 색인들을 정리한다.
	BinaryTree_MakeBalance(&indexBinder->indexes, sizeof(Index));
	//2. 각각의 색인들의 명함들을 정리한다.
	Node_IndexArrange(indexBinder->indexes.root);
	//3. 끝내다.
}

//IndexBinder_Destroy
void IndexBinder_Destroy(IndexBinder* indexBinder)
{
	//1. 각각의 색인들으 명함을 없앤다.
	Node_IndexDestroy(indexBinder->indexes.root);
	//2. 색인철의 색인들을 없앤다.
	BinaryTree_Destroy(&indexBinder->indexes);
	//3. 끝내다.
}

//재귀함수

void Node_IndexArrange(BinaryNode* node)
{
	Index* index;
	//1. node를 읽는다.
	//2. node가 null이 아니면
	if (node != NULL)
	{
		//2.1 색인의 명함들을 정리한다.
		Node_IndexArrange(node->left);
		index = (Index*)(node + 1);
		Index_Arrange(index);
		Node_IndexArrange(node->right);
	}
	//3. 끝내다.
}

//Node_IndexDestroy
void Node_IndexDestroy(BinaryNode* node)
{
	Index* index;
	//1. node를 읽는다.
	//2. node가 null이 아니면 
	if (node != NULL)
	{
		//2.1 색인의 명함들을 없앤다.
		Node_IndexDestroy(node->left);
		Node_IndexDestroy(node->right);
		index = (Index*)(node + 1);
		Index_Destroy(index);
	}
	//3. 끝내다.
}

//함수포인터
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;

	return strcmp(one_->companyName, other_->companyName);
}