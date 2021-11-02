#include "Personal.h"

//디폴트생성자
Personal::Personal()
	:name(""), position(""), cellularPhoneNumber(""), emailAddress("")
{

}

//매개변수를 갖는 생성자
Personal::Personal(string name, string position, string cellularPhoneNumber, string emailAddress)
	:name(name), position(position), cellularPhoneNumber(cellularPhoneNumber), emailAddress(emailAddress)
{

}

//복사생성자
Personal::Personal(const Personal& source)
	:name(source.name), position(source.position), 
	cellularPhoneNumber(source.cellularPhoneNumber), emailAddress(source.emailAddress)
{

}

//소멸자
Personal::~Personal()
{

}

//논리함수
bool Personal::IsEqual(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 &&
		this->cellularPhoneNumber.compare(other.cellularPhoneNumber) == 0 
		&& this->emailAddress.compare(other.emailAddress) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 ||
		this->cellularPhoneNumber.compare(other.cellularPhoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
bool Personal::operator==(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 &&
		this->cellularPhoneNumber.compare(other.cellularPhoneNumber) == 0
		&& this->emailAddress.compare(other.emailAddress) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Personal::operator!=(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 ||
		this->cellularPhoneNumber.compare(other.cellularPhoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0)
	{
		ret = true;
	}
	return ret;
}

//치환연산자
Personal& Personal::operator=(const Personal& source)
{
	this->name = source.name;
	this->position = source.position;
	this->cellularPhoneNumber = source.cellularPhoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}

//메인테스트시나리오
#include<iostream>
using namespace std;

#if 0
int main(int argc, char* argv[])
{
	//1. Personal을 만든다.
	Personal personal;
	//2. 매개변수를 가지는 생성자를 만든다.
	Personal other = Personal("홍길동", "전무", "01099823847", "Hong@naver.com");
	cout << other.GetName() << ","
		<< other.GetPosition() << ","
		<< other.GetCellularPhoneNumber() << ","
		<< other.GetEmailAddress() << endl;
	//3. 복사생성자를 만든다.
	Personal theOther(other);
	cout << theOther.GetName() << ","
		<< theOther.GetPosition() << ","
		<< theOther.GetCellularPhoneNumber() << ","
		<< theOther.GetEmailAddress() << endl;
	//4. other와 theOther가 같은지 비교한다.
	bool answer = other.IsEqual(theOther);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = other==theOther;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//5. personal과 other가 다른지 비교한다.
	answer = personal.IsNotEqual(other);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = personal!=other;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//6. 치환연산자로 personal에 other를 대입한다.
	personal = other;
	cout << personal.GetName() << ","
		<< personal.GetPosition() << ","
		<< personal.GetCellularPhoneNumber() << ","
		<< personal.GetEmailAddress() << endl;
	
	//7. 끝내다.
	return 0;
}
#endif

