#include "VisitingCard.h"

//기본생성자
VisitingCard::VisitingCard()
{

}

//매개변수를 갖는 생성자
VisitingCard::VisitingCard(string name, string position, string cellularPhoneNumber, string emailAddress,
	string companyName, string address, string telephoneNumber, string faxNumber, string url)
	:personal(name, position, cellularPhoneNumber, emailAddress),
	company(companyName, address, telephoneNumber, faxNumber, url)
{

}

//복사생성자
VisitingCard::VisitingCard(const VisitingCard& source)
	:personal(source.personal), company(source.company)
{

}

//소멸자
VisitingCard::~VisitingCard()
{

}

//논리함수
bool VisitingCard::IsEqual(const VisitingCard& other)
{
	bool ret = false;
	if (this->personal.IsEqual(other.personal) == true && this->company.IsEqual(other.company) == true)
	{
		ret = true;
	}
	return ret;
}

bool VisitingCard::IsNotEqual(const VisitingCard& other)
{
	bool ret = false;
	if (this->personal.IsNotEqual(other.personal) == true || this->company.IsNotEqual(other.company) == true)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
bool VisitingCard::operator==(const VisitingCard& other)
{
	bool ret = false;
	if (this->personal.IsEqual(other.personal) == true && this->company.IsEqual(other.company) == true)
	{
		ret = true;
	}
	return ret;
}

bool VisitingCard::operator!=(const VisitingCard& other)
{
	bool ret = false;
	if (this->personal.IsNotEqual(other.personal) == true || this->company.IsNotEqual(other.company) == true)
	{
		ret = true;
	}
	return ret;
}

//치환연산자
VisitingCard& VisitingCard::operator=(const VisitingCard& source)
{
	this->personal = source.personal;
	this->company = source.company;

	return *this;
}
#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. visitingCard를 생성한다.
	VisitingCard visitingCard;
	//2. 매개변수를 가지는 생성자를 만든다.
	VisitingCard other = VisitingCard("홍길동", "전무", "01099823847", "Hong@naver.com",
		"삼성전자", "서울시 서초구", "023456789", "023456780", "Samsung.com");
	cout << other.GetName() << ","
		<< other.GetPosition() << ","
		<< other.GetCellularPhoneNumber() << ","
		<< other.GetEmailAddress() << ","
		<< other.GetCompanyName() << ","
		<< other.GetAddress() << ","
		<< other.GetTelephoneNumber() << ","
		<< other.GetFaxNumber() << ","
		<< other.GetUrl() << endl;
	//3. 복사생성자를 만든다.
	VisitingCard theOther(other);
	cout << other.GetName() << ","
		<< other.GetPosition() << ","
		<< other.GetCellularPhoneNumber() << ","
		<< other.GetEmailAddress() << ","
		<< other.GetCompanyName() << ","
		<< other.GetAddress() << ","
		<< other.GetTelephoneNumber() << ","
		<< other.GetFaxNumber() << ","
		<< other.GetUrl() << endl;
	//4. other와 theOther가 같은지 비교한다.
	bool answer = other.IsEqual(theOther);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = other == theOther;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//5. visitingCard과 other가 다른지 비교한다.
	answer = visitingCard.IsNotEqual(other);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = visitingCard != other;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//6. 치환연산자로 visitingCard에 other를 대입한다.
	visitingCard = other;
	cout << visitingCard.GetName() << ","
		<< visitingCard.GetPosition() << ","
		<< visitingCard.GetCellularPhoneNumber() << ","
		<< visitingCard.GetEmailAddress() << ","
		<< visitingCard.GetCompanyName() << ","
		<< visitingCard.GetAddress() << ","
		<< visitingCard.GetTelephoneNumber() << ","
		<< visitingCard.GetFaxNumber() << ","
		<< visitingCard.GetUrl() << endl;
	//소멸자
	return 0;
}
#endif