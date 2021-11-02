#ifndef _VISITINGCARD_H
#define _VISITINGCARD_H
//STL(Standard Template Class Library)-C++ class Library
#include "Personal.h"
#include "Company.h"
#include<string>
using namespace std;

class VisitingCard
{
public:
	VisitingCard();//디폴트 생성자
	VisitingCard(string name, string position, string cellularPhoneNumber, string emailAddress,
		string companyName, string address, string telephoneNumber, string faxNumber, string url);//매개변수를 갖는 생성자
	VisitingCard(const VisitingCard& source);//복사생성자
	~VisitingCard();//소멸자

	//논리함수
	bool IsEqual(const VisitingCard& other);
	bool IsNotEqual(const VisitingCard& other);
	//연산자함수
	bool operator==(const VisitingCard& other);
	bool operator!=(const VisitingCard& other);
	VisitingCard& operator=(const VisitingCard& source);//치환연산자

	//인라인함수
	string& GetName() const;
	string& GetPosition() const;
	string& GetCellularPhoneNumber() const;
	string& GetEmailAddress() const;
	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;

private:
	Personal personal;
	Company company;
};

//인라인함수 정의
inline string& VisitingCard::GetName() const
{
	return const_cast<string&>(this->personal.GetName());
}

inline string& VisitingCard::GetPosition() const
{
	return const_cast<string&>(this->personal.GetPosition());
}

inline string& VisitingCard::GetCellularPhoneNumber() const
{
	return const_cast<string&>(this->personal.GetCellularPhoneNumber());
}

inline string& VisitingCard::GetEmailAddress() const
{
	return const_cast<string&>(this->personal.GetEmailAddress());
}

inline string& VisitingCard::GetCompanyName() const
{
	return const_cast<string&>(this->company.GetCompanyName());
}

inline string& VisitingCard::GetAddress() const
{
	return const_cast<string&>(this->company.GetAddress());
}

inline string& VisitingCard::GetTelephoneNumber() const
{
	return const_cast<string&>(this->company.GetTelephoneNumber());
}

inline string& VisitingCard::GetFaxNumber() const
{
	return const_cast<string&>(this->company.GetFaxNumber());
}

inline string& VisitingCard::GetUrl() const
{
	return const_cast<string&>(this->company.GetUrl());
}

#endif // !_VISITINGCARD_H

