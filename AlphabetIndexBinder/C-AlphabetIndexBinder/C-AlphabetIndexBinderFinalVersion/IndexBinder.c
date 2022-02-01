#include "BinaryTree.h"
#include "Index.h"
#include "IndexBinder.h"
#include "WordCardBinder.h"

//IndexBinder_Create
void IndexBinder_Create(IndexBinder* indexBinder)
{
	//1. 색인철을 만든다.
	BinaryTree_Create(&indexBinder->indexes);
	//2. 사용량을 정한다.
	indexBinder->length = 0;
	//3. 끝내다.
}

//IndexBinder_TakeIn
Index* IndexBinder_TakeIn(IndexBinder* indexBinder, WordCard* wordCard)
{
	BinaryNode* node;
	Index index;
	Index* indexLink;
	Long arrayIndex;

	//1. 단어카드의 위치를 입력받는다.
	//2. 색인에 알파벳을 기재한다.
	index.alphabet = wordCard->word.spellings[0];
	//3. 소문자일 경우 대문자로 바꿔준다.
	if (index.alphabet >= 'a' && index.alphabet <= 'z')
	{
		index.alphabet -= 32;
	}
	//4. 색인철의 색인 중에 같은 알파벳이 있는지 확인한다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//5. 같은 알파벳이 없는 경우에
	if (node == NULL)
	{
		//5.1 색인을 새로 만든다.
		Index_Create(&index, 3);
		//5.2 색인을 색인철에 끼운다.
		node = BinaryTree_Insert(&indexBinder->indexes, &index, sizeof(Index), CompareIndexes);
		//5.3 색인철의 사용량을 증가시킨다.
		indexBinder->length++;
	}
	//6. 색인의 주소를 구한다.
	indexLink = (Index*)(node + 1);
	//7. 색인에 명함을 끼운다.
	arrayIndex = Index_TakeIn(indexLink, wordCard);
	//8. 색인의 주소를 출력한다.
	return indexLink;
	//9. 끝내다.
}

//IndexBinder_Find
Index* IndexBinder_Find(IndexBinder* indexBinder, char alphabet)
{
	Index index;
	Index* indexLink = NULL;
	BinaryNode* node;

	//1. 단어카드의 알파벳을 입력받는다.
	//2. 색인에 알파벳을 기재한다.
	if (alphabet >= 'a' && alphabet <= 'z')
	{
		alphabet -= 32;
	}
	index.alphabet = alphabet;
	//3. 색인철의 색인중에 같은 알파벳이 있는지 찾는다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. 색인철에 같은 알파벳이 있으면
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
Index* IndexBinder_TakeOut(IndexBinder* indexBinder, char alphabet, WordCard* wordCard)
{
	BinaryNode* node;
	Index index;
	Index* indexLink;
	Long arrayIndex;

	//1. 알파벳과 단어카드의 위치를 입력받는다.
	//2. 색인에 알파벳을 기재한다.
	if (alphabet >= 'a' && alphabet <= 'z')
	{
		alphabet -= 32;
	}
	index.alphabet = alphabet;
	//3. 색인철에서 같은 알파벳을 찾는다.
	node = BinaryTree_Search(&indexBinder->indexes, &index, CompareIndexes);
	//4. 색인의 주소를 구한다.
	indexLink = (Index*)(node + 1);
	//5. 색인에서 명함을 찾는다.
	arrayIndex = Index_Find(indexLink, wordCard);
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
	//1. 색인철에서 색인들을 정리한다.
	BinaryTree_MakeBalance(&indexBinder->indexes, sizeof(Index));
	//2. 각각의 색인들의 단어카드를 정리한다.
	Node_IndexArrange(indexBinder->indexes.root);
	//3. 끝내다.

}


//IndexBinder_Destroy
void IndexBinder_Destroy(IndexBinder* indexBinder)
{
	//1. 각각의 색인들의 단어카드들을 없앤다.
	Node_IndexDestroy(indexBinder->indexes.root);
	//2. 색인철의 색인들을 없앤다.
	BinaryTree_Destroy(&indexBinder->indexes);
	//3. 끝내다.
}

//함수포인터
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

//재귀함수
//Node_IndexDestroy
void Node_IndexDestroy(BinaryNode* node)
{
	Index* index;
	//1. node를 읽는다.
	//2. node가  null이 아니면
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

//Node_IndexArrange
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