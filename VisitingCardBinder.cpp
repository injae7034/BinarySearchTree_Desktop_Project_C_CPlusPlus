#include "VisitingCardBinder.h"

//기본생성자
VisitingCardBinder::VisitingCardBinder()
{
	this->length = 0;
	this->current = 0;
}

//복사생성자
VisitingCardBinder::VisitingCardBinder(const VisitingCardBinder& source)
	:visitingCards(source.visitingCards)
{
	this->length = source.length;
	this->current = &this->visitingCards.GetCurrent()->GetObject();
}

//소멸자
VisitingCardBinder::~VisitingCardBinder()
{

}

//TakeIn
VisitingCard* VisitingCardBinder::TakeIn(VisitingCard visitingCard)
{
	//1. 명함을 입력받는다.
	//2. 명함을 놓을 위치를 찾는다.
	//3. 명함을 넣는다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.AppendFromTail(visitingCard);
	//4. 명함철에 개수를 늘린다.
	this->length++;
	//5. 명함철의 현재 위치를 설정한다.
	this->current = &node->GetObject();
	//6. 현재위치를 출력한다.
	return this->current;
	//7. 끝내다.
}

//Find
void VisitingCardBinder::Find(string name, VisitingCard** (*indexes), Long* count)
{
	*indexes = 0;
	*count = 0;
	//1. 입력받은 성명으로 명함철에서 찾는다.
	LinkedList<VisitingCard>::Node* (*nodes);
	this->visitingCards.LinearSearchDuplicate(&name, &nodes, count, ComparePersonalNames);
	//2. 찾은 성명이 있으면
	if (*count > 0)
	{
		//2.1 위치들 배열을 만든다.
		*indexes = new VisitingCard * [*count];
	}
	//3. 찾은 개수만큼 반복한다.
	Long i = 0;
	while (i < *count)
	{
		//3.1 위치를 저장한다.
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	//4. 할당해제한다.
	if (nodes != 0)
	{
		delete[] nodes;
	}
	//5. 위치들과 개수를 출력한다.
	//6. 끝내다.
}

//FindByCompanyName
VisitingCard* VisitingCardBinder::FindByCompanyName(string companyName)
{
	VisitingCard* index = 0;
	//1. 회사이름을 입력받는다.
	//2. 명함철에 입력받은 회사가 있는지 찾는다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.LinearSearchUnique(&companyName, CompareCompanyNames);
	//3. 입력받은 회사가 명함철에 있으면
	if (node != 0)
	{
		//3.1 위치를 저장한다.
		index = &node->GetObject();
	}
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//TakeOut
VisitingCard VisitingCardBinder::TakeOut(VisitingCard* index)
{
	//1. 명함의 위치를 입력받는다.
	//2. 명함의 위치로 node의 위치를 찾는다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.LinearSearchUnique(index, CompareVisitingCards);
	//3. 명함을 꺼낸다.
	VisitingCard visitingCard = node->GetObject();
	//4. 명함을 없앤다.
	this->visitingCards.Delete(node);
	//5. 명함철에 명함이 남아 있으면
	if (this->visitingCards.GetCurrent() != 0)
	{
		//5.1 현재 명함의 위치를 조정한다.
		this->current = &this->visitingCards.GetCurrent()->GetObject();
	}
	//6. 명함철에 명함이 없으면
	else
	{
		this->current = 0;
	}
	//7. 명함철의 명함 개수를 감소시킨다.
	this->length--;
	//8. 명함을 출력한다.
	return visitingCard;
	//9. 끝내다.
}

//Move
VisitingCard* VisitingCardBinder::Move(VisitingCard* index)
{
	//1. 위치를 입력받는다.
	//2. 명함의 위치로 node의 위치를 찾는다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.LinearSearchUnique(index, CompareVisitingCards);
	//3. 현재 위치를 입력받은 위치로 바꾼다.
	node = this->visitingCards.Move(node);
	//4. node에서 명함의 현재위치를 구한다.
	this->current = &node->GetObject();
	//5. 현재위치를 출력한다.
	return this->current;
	//6. 끝내다.
}

//First
VisitingCard* VisitingCardBinder::First()
{
	//1. 현재위치를 처음으로 이동시킨다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.First();
	//2. 현재위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Previous
VisitingCard* VisitingCardBinder::Previous()
{
	//1. 현재위치를 이전으로 이동시킨다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.Previous();
	//2. 현재위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Next
VisitingCard* VisitingCardBinder::Next()
{
	//1. 현재위치를 다음으로 이동시킨다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.Next();
	//2. 현재위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Last
VisitingCard* VisitingCardBinder::Last()
{
	//1. 현재위치를 마지막으로 이동시킨다.
	LinkedList<VisitingCard>::Node* node = this->visitingCards.Last();
	//2. 현재위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//치환연산자
VisitingCardBinder& VisitingCardBinder::operator=(const VisitingCardBinder& source)
{
	this->visitingCards = source.visitingCards;
	this->length = source.length;
	this->current = &this->visitingCards.GetCurrent()->GetObject();

	return *this;
}

//첨자연산자
VisitingCard& VisitingCardBinder::operator[](Long index)
{
	return this->visitingCards[index];
}

#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. visitingCardBinder를 생성한다.
	VisitingCardBinder visitingCardBinder;
	//2. 명함철에 명함을 끼운다.
	VisitingCard first("정길동", "대리", "01024367967", "Jung@naver.com", "삼성전자", "서울시 서초구", "023692447",
		"023692448", "Samsung.com");
	VisitingCard* index = visitingCardBinder.TakeIn(first);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//3. 명함을 꺼낸다.
	VisitingCard vistingCard = visitingCardBinder.TakeOut(index);
	cout << vistingCard.GetName() << ","
		<< vistingCard.GetPosition() << ","
		<< vistingCard.GetCellularPhoneNumber() << ","
		<< vistingCard.GetEmailAddress() << ","
		<< vistingCard.GetCompanyName() << ","
		<< vistingCard.GetAddress() << ","
		<< vistingCard.GetTelephoneNumber() << ","
		<< vistingCard.GetFaxNumber() << ","
		<< vistingCard.GetUrl() << endl;
	//4. 명함철에 명함을 끼운다.
	VisitingCard second("홍길동", "대리", "01036937428", "Hong@naver.com", "신한은행", "서울 중구",
		"023347714", "023347715", "Shinhan.com");
	index = visitingCardBinder.TakeIn(second);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//5. 명함철에 명함을 끼운다.
	VisitingCard third("차길동", "과장", "01036925571", "Cha@naver.com", "엘지전자", "서울시 강서구",
		"022397821", "022397822", "LG.com");
	index = visitingCardBinder.TakeIn(third);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//6. 명함철에 명함을 끼운다.
	VisitingCard fourth("김길동", "부장", "01036901127", "Kim@naver.comn", "현대자동차", "울산 북구",
		"0524379702", "0524379701", "Hyundai.com");
	index = visitingCardBinder.TakeIn(fourth);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//7. 명함철에서 마지막 명함을 꺼낸다.
	vistingCard = visitingCardBinder.TakeOut(index);
	cout << vistingCard.GetName() << ","
		<< vistingCard.GetPosition() << ","
		<< vistingCard.GetCellularPhoneNumber() << ","
		<< vistingCard.GetEmailAddress() << ","
		<< vistingCard.GetCompanyName() << ","
		<< vistingCard.GetAddress() << ","
		<< vistingCard.GetTelephoneNumber() << ","
		<< vistingCard.GetFaxNumber() << ","
		<< vistingCard.GetUrl() << endl;
	//8. 명함철에서 명함을 끼운다.
	VisitingCard fifth("나길동", "사원", "01036928827", "Na@naver.com", "SK하이닉스", "경기도 이천",
		"-0313692248", "0313692249", "SK.com");
	index = visitingCardBinder.TakeIn(fifth);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//9. 명함철에서 차길동을 찾는다.
	VisitingCard* (*indexes);
	Long count;
	visitingCardBinder.Find("차길동", &indexes, &count);
	Long i = 0;
	while (i < count)
	{
		cout << indexes[i]->GetName() << ","
			<< indexes[i]->GetPosition() << ","
			<< indexes[i]->GetCellularPhoneNumber() << ","
			<< indexes[i]->GetEmailAddress() << ","
			<< indexes[i]->GetCompanyName() << ","
			<< indexes[i]->GetAddress() << ","
			<< indexes[i]->GetTelephoneNumber() << ","
			<< indexes[i]->GetFaxNumber() << ","
			<< indexes[i]->GetUrl() << endl;
		i++;
	}
	//10. 차길동의 명함을 명함철에서 꺼낸다.
	vistingCard = visitingCardBinder.TakeOut(indexes[count-1]);
	cout << vistingCard.GetName() << ","
		<< vistingCard.GetPosition() << ","
		<< vistingCard.GetCellularPhoneNumber() << ","
		<< vistingCard.GetEmailAddress() << ","
		<< vistingCard.GetCompanyName() << ","
		<< vistingCard.GetAddress() << ","
		<< vistingCard.GetTelephoneNumber() << ","
		<< vistingCard.GetFaxNumber() << ","
		<< vistingCard.GetUrl() << endl;
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//11. 명함철에 명함을 끼운다.
	VisitingCard sixth("장길동", "전무", "01044287990", "Jang@naver.com", "노랑풍선", "서울 중구",
		"029912970", "029912971", "Yellow.com");
	index = visitingCardBinder.TakeIn(sixth);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//12. 명함철에 명함을 끼운다.
	VisitingCard seventh("홍길동", "이사", "01098712341", "Hong@gmail.com", "아시아나항공", "서울 종로구",
		"028711297", "028711298", "Asiana.com");
	index = visitingCardBinder.TakeIn(seventh);
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//13. 명함철에서 홍길동을 찾는다.
	visitingCardBinder.Find("홍길동", &indexes, &count);
	i = 0;
	while (i < count)
	{
		cout << indexes[i]->GetName() << ","
			<< indexes[i]->GetPosition() << ","
			<< indexes[i]->GetCellularPhoneNumber() << ","
			<< indexes[i]->GetEmailAddress() << ","
			<< indexes[i]->GetCompanyName() << ","
			<< indexes[i]->GetAddress() << ","
			<< indexes[i]->GetTelephoneNumber() << ","
			<< indexes[i]->GetFaxNumber() << ","
			<< indexes[i]->GetUrl() << endl;
		i++;
	}
	//14. 현재 명함의 위치를 첫 번째 홍길동 명함으로 옮긴다.
	index = visitingCardBinder.Move(indexes[0]);
	cout << indexes[0]->GetName() << ","
		<< indexes[0]->GetPosition() << ","
		<< indexes[0]->GetCellularPhoneNumber() << ","
		<< indexes[0]->GetEmailAddress() << ","
		<< indexes[0]->GetCompanyName() << ","
		<< indexes[0]->GetAddress() << ","
		<< indexes[0]->GetTelephoneNumber() << ","
		<< indexes[0]->GetFaxNumber() << ","
		<< indexes[0]->GetUrl() << endl;
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//15. 회사명 "노랑풍선"을 찾는다.
	index = visitingCardBinder.FindByCompanyName("노랑풍선");
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//16. 명함철에서 처음으로 이동한다.
	index = visitingCardBinder.First();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//17. 명함철에서 이전으로 이동한다.
	index = visitingCardBinder.Previous();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//18. 명함철에서 다음으로 이동한다.
	index = visitingCardBinder.Next();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//19. 명함철에서 마지막으로 이동한다.
	index = visitingCardBinder.Last();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//20. 명함철에서 다음으로 이동한다.
	index = visitingCardBinder.Next();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//21. 명함철에서 이전으로 이동한다.
	index = visitingCardBinder.Previous();
	cout << index->GetName() << ","
		<< index->GetPosition() << ","
		<< index->GetCellularPhoneNumber() << ","
		<< index->GetEmailAddress() << ","
		<< index->GetCompanyName() << ","
		<< index->GetAddress() << ","
		<< index->GetTelephoneNumber() << ","
		<< index->GetFaxNumber() << ","
		<< index->GetUrl() << endl;
	//22. 치환연산자
	cout << "치환연산자" << endl;
	VisitingCardBinder other;
	other = visitingCardBinder;
	VisitingCard* previous = 0;
	VisitingCard* it = other.First();
	while (it!=previous)
	{
		cout << it->GetName() << ","
			<< it->GetPosition() << ","
			<< it->GetCellularPhoneNumber() << ","
			<< it->GetEmailAddress() << ","
			<< it->GetCompanyName() << ","
			<< it->GetAddress() << ","
			<< it->GetTelephoneNumber() << ","
			<< it->GetFaxNumber() << ","
			<< it->GetUrl() << endl;
		previous = it;
		it = other.Next();
	}
	//23. 첨자연산자
	cout << "첨자연산자" << endl;
	cout << other[2].GetName() << ","
		<< other[2].GetPosition() << ","
		<< other[2].GetCellularPhoneNumber() << ","
		<< other[2].GetEmailAddress() << ","
		<< other[2].GetCompanyName() << ","
		<< other[2].GetAddress() << ","
		<< other[2].GetTelephoneNumber() << ","
		<< other[2].GetFaxNumber() << ","
		<< other[2].GetUrl() << endl;
	//24. 명함철을 없앤다.
	return 0;
}
#endif
//함수포인터 정의
int ComparePersonalNames(void* one, void* other)
{
	VisitingCard* one_ = (VisitingCard*)one;
	string* other_ = (string*)other;

	return (one_->GetName().compare(*other_));
}

int CompareCompanyNames(void* one, void* other)
{
	VisitingCard* one_ = (VisitingCard*)one;
	string* other_ = (string*)other;

	return (one_->GetCompanyName().compare(*other_));
}

int CompareVisitingCards(void* one, void* other)
{
	int ret;
	if (one == other)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}
