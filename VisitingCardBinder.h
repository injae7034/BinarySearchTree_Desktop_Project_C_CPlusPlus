#ifndef _VISITINGCARDBINDER_H
#define _VISITINGCARDBINDER_H
//STL(Standard Template Class Library)-C++ Class Librabry
#include "LinkedList.h"
#include "VisitingCard.h"
#include<string>
using namespace std;

typedef signed long int Long;

class VisitingCardBinder
{
public:
	VisitingCardBinder();//디폴트생성자
	VisitingCardBinder(const VisitingCardBinder& source);//복사생성자
	~VisitingCardBinder();//소멸자
	VisitingCard* TakeIn(VisitingCard visitingCard);
	void Find(string name, VisitingCard** (*indexes), Long* count);
	VisitingCard* FindByCompanyName(string companyName);
	VisitingCard TakeOut(VisitingCard* index);
	VisitingCard* Move(VisitingCard* index);
	VisitingCard* First();
	VisitingCard* Previous();
	VisitingCard* Next();
	VisitingCard* Last();
	VisitingCardBinder& operator=(const VisitingCardBinder& source);//치환연산자
	VisitingCard& operator[](Long index);
	//인라인함수
	Long GetLength() const;
	VisitingCard* GetCurrent() const;
	
private:
	LinkedList<VisitingCard> visitingCards;//이렇게 선언만하면 나중에 기본생성자에서 호출될 때 LinkedList기본생성자를 호출함.
	Long length;
	VisitingCard* current;
};

//인라인함수 정의
inline Long VisitingCardBinder::GetLength() const
{
	return this->length;
}

inline VisitingCard* VisitingCardBinder::GetCurrent() const
{
	return const_cast<VisitingCard*>(this->current);
}

//함수포인터선언
int ComparePersonalNames(void* one, void* other);
int CompareCompanyNames(void* one, void* other);
int CompareVisitingCards(void* one, void* other);

#endif // !_VISITINGCARDBINDER_H
