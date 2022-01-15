#ifndef _INDEX_H
#define _INDEX_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Array.h"
#include<string>
using namespace std;
typedef signed long int Long;
class VisitingCard;

class Index
{
public:
	Index(Long capacity = 36);//디폴트매개변수를 가지는 디폴트생성자
	Index(string companyName, Long capacity = 36);//매개변수를 2개가지는 생성자
	Index(const Index& source);//복사생성자
	Index& operator=(const Index& source);//치환연산자
	~Index();//소멸자
	//연산함수
	Long TakeIn(VisitingCard* visitingCardLink);
	Long Find(VisitingCard* visitingCardLink);
	Long TakeOut(Long arrayIndex);
	VisitingCard* GetAt(Long arrayIndex);
	void Arrange();
	//인라인함수
	string& GetCompanyName() const;
	Long GetLength() const;
	Long GetCapacity() const;
private:
	string companyName;
	Array<VisitingCard*> visitingCards;
	Long capacity;
	Long length;
};

//인라인함수 정의
inline string& Index::GetCompanyName() const
{
	return const_cast<string&>(this->companyName);
}
inline Long Index::GetLength() const
{
	return this->length;
}
inline Long Index::GetCapacity() const
{
	return this->capacity;
}


//함수포인터 선언
int CompareArray_VisitingCards(void* one, void* other);
int CompareArray_PersonalNames(void* one, void* other);

#endif //_INDEX_H
