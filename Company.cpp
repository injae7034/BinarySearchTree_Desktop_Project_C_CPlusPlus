#include "Company.h"

//기본생성자
Company::Company()
	:companyName(""), address(""), telephoneNumber(""), faxNumber(""), url("")
{

}

//매개변수를 갖는 생성자
Company::Company(string companyName, string address, string telephoneNumber, string faxNumber, string url)
	:companyName(companyName), address(address), telephoneNumber(telephoneNumber), faxNumber(faxNumber), url(url)
{

}

//복사생성자
Company::Company(const Company& source)
	:companyName(source.companyName), address(source.address), telephoneNumber(source.telephoneNumber),
	faxNumber(source.faxNumber), url(source.url)
{

}

//소멸자
Company::~Company()
{

}

//논리함수
bool Company::IsEqual(const Company& other)
{
	bool ret = false;
	if (this->companyName.compare(other.companyName) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Company::IsNotEqual(const Company& other)
{
	bool ret = false;
	if (this->companyName.compare(other.companyName) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) != 0)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
bool Company::operator==(const Company& other)
{
	bool ret = false;
	if (this->companyName.compare(other.companyName) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Company::operator!=(const Company& other)
{
	bool ret = false;
	if (this->companyName.compare(other.companyName) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) != 0)
	{
		ret = true;
	}
	return ret;
}

//치환연산자
Company& Company::operator=(const Company& source)
{
	this->companyName = source.companyName;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->faxNumber = source.faxNumber;
	this->url = source.url;

	return *this;
}

#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. company를 만든다.
	Company company;
	//2. 매개변수를 가지는 생성자를 만든다.
	Company other = Company("삼성전자", "서울시 서초구", "023456789", "023456780", "Samsung.com");
	cout << other.GetCompanyName() << ","
		<< other.GetAddress() << ","
		<< other.GetTelephoneNumber() << ","
		<< other.GetFaxNumber() << ","
		<< other.GetUrl() << endl;
	//3. 복사생성자를 만든다.
	Company theOther(other);
	cout << other.GetCompanyName() << ","
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
	//5. company과 other가 다른지 비교한다.
	answer = company.IsNotEqual(other);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = company != other;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//6. 치환연산자로 company에 other를 대입한다.
	company = other;
	cout << other.GetCompanyName() << ","
		<< other.GetAddress() << ","
		<< other.GetTelephoneNumber() << ","
		<< other.GetFaxNumber() << ","
		<< other.GetUrl() << endl;
	//7.끝내다
	return 0;
}
#endif