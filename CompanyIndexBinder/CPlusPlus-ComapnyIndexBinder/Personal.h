#ifndef _PERSONAL_H
#define _PERSONAL_H
//STL(Standard Template Class Library)-C++ Class Library
using namespace std;
#include<string>

class Personal
{
public:
	Personal();//디폴트생성자
	Personal(string name, string position, string cellularPhoneNumber, string emailAddress);//매개변수를 갖는 생성자
	Personal(const Personal& source);//복사생성자
	~Personal();//소멸자
	//논리함수
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);
	//연산자함수
	bool operator==(const Personal& other);
	bool operator!=(const Personal& other);
	Personal& operator=(const Personal& source);//치환연산자
	//인라인함수
	string& GetName() const;
	string& GetPosition() const;
	string& GetCellularPhoneNumber() const;
	string& GetEmailAddress() const;

private:
	string name;
	string position;
	string cellularPhoneNumber;
	string emailAddress;
};

//인라인 함수 정의
inline string& Personal::GetName() const
{
	return const_cast<string&>(this->name);
}

inline string& Personal::GetPosition() const
{
	return const_cast<string&>(this->position);
}

inline string& Personal::GetCellularPhoneNumber() const
{
	return const_cast<string&>(this->cellularPhoneNumber);
}

inline string& Personal::GetEmailAddress() const
{
	return const_cast<string&>(this->emailAddress);
}

#endif // !_PERSONAL_H
