#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
//STL(Standard Template Class Library)-C++ Class Library
#include "BinaryTree.h"
#include "Index.h"
#include<string>
using namespace std;

//전방선언 //binaryNode는 전방선언 해 줄 필요없음. binaryNode는 BinaryTree.h에 들어가 있기 때문에!!!!!!
class VisitingCard;
typedef signed long int Long;

class IndexBinder
{
public:
	IndexBinder();//디폴트생성자
	IndexBinder(const IndexBinder& source);//복사생성자
	IndexBinder& operator=(const IndexBinder& source);//치환연산자
	~IndexBinder();//소멸자
	Index* TakeIn(VisitingCard* visitingCardLink);
	Index* Find(string companyName);
	Index* TakeOut(string companyName, VisitingCard* visitingCardLink);
	void Arrange();
	void MakeList(Index* (*indexes), Long* count);
	//인라인함수
	BinaryTree<Index>::Node* GetRoot() const;
	Long GetLength() const;
private:
	BinaryTree<Index> indexes;
	Long length;
};

//인라인 함수 정의
inline typename BinaryTree<Index>::Node* IndexBinder::GetRoot() const
{
	return const_cast<BinaryTree<Index>::Node*>(this->indexes.GetRoot());
}
inline Long IndexBinder::GetLength() const
{
	return this->length;
}

//함수포인터 선언
int CompareIndexes(void* one, void* other);
//재귀함수
void IndexArrange(BinaryTree<Index>::Node* binaryNode);

#endif // !_INDEXBINDER_H

