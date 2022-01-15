#include "Index.h"
#include "VisitingCard.h"


//디폴트 생성자
Index::Index(Long capacity)
	:companyName(""), visitingCards(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//매개변수를 2개가지는 생성자
Index::Index(string companyName, Long capacity)
	:companyName(companyName), visitingCards(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
Index::Index(const Index& source)
	:companyName(source.companyName), visitingCards(source.visitingCards)
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//치환연산자
Index& Index::operator=(const Index& source)
{
	this->companyName = source.companyName;
	this->visitingCards = source.visitingCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//TakeIn
Long Index::TakeIn(VisitingCard* visitingCardLink)
{
	Long arrayIndex;
	//1. 사용량이 할당량보다 작으면
	if (this->length < this->capacity)
	{
		//1.1 빈 칸에 명함의 위치를 저장한다.
		arrayIndex = this->visitingCards.Store(this->length, visitingCardLink);
	}
	//2. 그렇지 않으면
	else
	{
		//2.1 새 칸에 명함의 위치를 저장한다.
		arrayIndex = this->visitingCards.AppendFromRear(visitingCardLink);
		//2.2 색인의 할당량을 증가시킨다.
		this->capacity++;
	}
	//3. 색인의 사용량을 증가시킨다.
	this->length++;
	//4. 위치를 출력한다.
	return arrayIndex;
	//5. 끝내다.
}

//Find
Long Index::Find(VisitingCard* visitingCardLink)
{
	//1. 명함의 주소를 입력받는다.
	//2. 명함을 찾는다.
	Long arrayIndex = this->visitingCards.LinearSearchUnique(visitingCardLink, CompareArray_VisitingCards);
	//3. 위치를 출력한다.
	return arrayIndex;
	//4. 끝내다.
}

//TakeOut
Long Index::TakeOut(Long arrayIndex)
{
	//1. 명함의 위치를 저장한 배열 첨자를 입력받는다.
	//2. 해당 배열첨자에 저장된 명함을 지운다.
	arrayIndex = this->visitingCards.Delete(arrayIndex);
	//3. 할당량을 감소시킨다.
	this->capacity--;
	//4. 사용량을 감소시킨다.
	this->length--;
	//5. 위치를 출력한다.
	return arrayIndex;
	//6. 끝내다.
}

//Arrange
void Index::Arrange()
{
	//1. 오름차순으로 정렬한다.
	this->visitingCards.InsertionSort(CompareArray_PersonalNames);
	//2. 끝내다.
}

//GetAt
VisitingCard* Index::GetAt(Long arrayIndex)
{
	//1. 배열에 첨자를 입력받는다.
	//2. 색인 배열에 저장된 명함의 주소를 불러온다.
	VisitingCard* visitingCardLink = this->visitingCards.GetAt(arrayIndex);
	//3. 명함의 주소를 출력한다.
	return visitingCardLink;
	//4. 끝내다.
}


//소멸자
Index::~Index()
{

}

//함수포인터
//VistingCard 주소값으로 비교
int CompareArray_VisitingCards(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard* other_ = (VisitingCard*)other;

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

//개인성명으로 비교
int CompareArray_PersonalNames(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard** other_ = (VisitingCard**)other;

	return((*one_)->GetName().compare((*other_)->GetName()));
}

