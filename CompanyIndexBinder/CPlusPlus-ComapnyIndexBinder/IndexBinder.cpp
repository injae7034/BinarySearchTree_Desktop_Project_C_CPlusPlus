#include "IndexBinder.h"
#include "VisitingCard.h"
#include "Index.h"
#include "BinaryTree.h"


//디폴트생성자
IndexBinder::IndexBinder()
{
	this->length = 0;
}

//복사생성자
IndexBinder::IndexBinder(const IndexBinder& source)
	:indexes(source.indexes)
{
	this->length = source.length;
}

//치환연산자
IndexBinder& IndexBinder::operator=(const IndexBinder& source)
{
	this->indexes = source.indexes;
	this->length = source.length;

	return *this;
}

//TakeIn
Index* IndexBinder::TakeIn(VisitingCard* visitingCardLink)
{
	//1. 명함의 주소를 입력받는다.
	//2. 색인에 회사이름을 기재한다.
	Index index(visitingCardLink->GetCompanyName());
	//3. 색인철의 색인 중에 같은 회사의 이름이 있는지 찾는다.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. 색인철에 같은 회사이름이 없는 경우에
	if (binaryNode == 0)
	{
		//4.1 색인을 색인철에 끼운다.
		binaryNode = this->indexes.Insert(index, CompareIndexes);
		//4.2 색인철의 사용량을 증가시킨다.
		this->length++;
	}
	//5. 색인철의 주소를 구한다.
	Index* indexLink = &binaryNode->GetKey();
	//6. 색인에 명함을 끼운다.
	Long arrayIndex = indexLink->TakeIn(visitingCardLink);
	//7. 색인의 위치를 출력한다.
	return indexLink;
	//8. 끝내다.
}

//Find
Index* IndexBinder::Find(string companyName)
{
	//1. 명함의 상호를 입력받는다.
	//2. 색인에 회사이름을 기재한다.
	Index index(companyName);
	//3. 색인철의 색인중에서 같은 회사의 이름이 있는지 찾는다.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. 색인철에 중복되는 회사가 있으면
	Index* indexLink = 0;
	if (binaryNode != 0)
	{
		//4.1 색인의 주소를 구한다.
		indexLink = &binaryNode->GetKey();
	}
	//5. 색인의 위치를 출력한다.
	return indexLink;
	//6. 끝내다.
}

//TakeOut
Index* IndexBinder::TakeOut(string companyName, VisitingCard* visitingCardLink)
{
	//1. 회사이름과 명함의 주소를 입력받는다.
	//2. 색인에 회사이름을 기재한다.
	Index index(companyName);
	//3. 색인철에서 회사이름이 있는지 찾는다.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. 색인의 주소를 구한다.
	Index* key = &binaryNode->GetKey();
	//5. 색인에서 명함을 찾는다.
	Long arrayIndex = key->Find(visitingCardLink);
	//6. 색인에서 명함을 지운다.
	arrayIndex = key->TakeOut(arrayIndex);
	//7. 색인의 명함개수가 0개이면
	if (key->GetLength() == 0)
	{
		//7.1 색인을 지운다.
		binaryNode = this->indexes.Delete(*key, CompareIndexes);
		//7.2 색인철의 사용량을 감소시킨다.
		this->length--;
		key = 0;
	}
	//8. 색인의 주소를 출력한다.
	return key;
	//9. 끝내다.
}

//MakeList
void IndexBinder::MakeList(Index* (*indexes), Long* count)
{
	//1. 색인배열을 만든다.
	this->indexes.MakeKeys(indexes, count);
	//2. 끝내다.
}

//Arrange
void IndexBinder::Arrange()
{
	//1. 색인철의 색인들을 정리한다.
	this->indexes.MakeBalance();
	//2. 각각의 색인들의 명함들을 정리한다.
	IndexArrange(this->indexes.GetRoot());
	//3. 끝내다.
}

//소멸자
IndexBinder::~IndexBinder()
{

}

//함수포인터
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;

	return (one_->GetCompanyName().compare(other_->GetCompanyName()));
}

//재귀함수
//IndexArrange
void IndexArrange(BinaryTree<Index>::Node* binaryNode)
{
	//1. binaryNode를 읽는다.
	//2. binaryNode가 null이 아니면
	if (binaryNode != 0)
	{
		//2.1 색인의 명함들을 정리한다.
		IndexArrange(binaryNode->GetLeft());
		Index* index = &binaryNode->GetKey();
		index->Arrange();
		IndexArrange(binaryNode->GetRight());
	}
	//3. 끝내다.
}