#ifndef _COMPANY_H
#define _COMPANY_H
//STL(Standard Template Class Library)-C++ Class Library
#include<string>
using namespace std;
class Company
{
public:
	Company();//디폴트생성자
	Company(string companyName, string address, string telephoneNumber, string faxNumber, string url);//매개변수를 갖는 생성자
	Company(const Company& source);//복사생성자
	~Company();//소멸자
	//논리함수
	bool IsEqual(const Company& other);
	bool IsNotEqual(const Company& other);
	//연산자함수
	bool operator==(const Company& other);
	bool operator!=(const Company& other);
	Company& operator=(const Company& source);//치환연산자
	//인라인함수
	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;

private:
	string companyName;
	string address;
	string telephoneNumber;
	string faxNumber;
	string url;
};

//인라인 함수 정의
inline string& Company::GetCompanyName() const
{
	return const_cast<string&>(this->companyName);
}

inline string& Company::GetAddress() const
{
	return const_cast<string&>(this->address);
}

inline string& Company::GetTelephoneNumber() const
{
	return const_cast<string&>(this->telephoneNumber);
}

inline string& Company::GetFaxNumber() const
{
	return const_cast<string&>(this->faxNumber);
}

inline string& Company::GetUrl() const
{
	return const_cast<string&>(this->url);
}

#endif // !_COMPANY_H

