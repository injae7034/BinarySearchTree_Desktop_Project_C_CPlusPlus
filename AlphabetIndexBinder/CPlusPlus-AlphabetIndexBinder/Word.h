#ifndef _WORD_H
#define _WORD_H
//STL(Standard Template Class Library)-C++ Class Library
#include<string>
using namespace std;

class Word
{
public:
	Word();//디폴트생성자
	Word(string spellings, string partOfSpeech, string meanings, string example);//매개변수를 4개가지는 생성자
	Word(const Word& source);//복사생성자
	~Word();//소멸자
	//논리함수
	bool IsEqual(const Word& other);
	bool IsNotEqual(const Word& other);
	//연산자함수
	bool operator==(const Word& other);
	bool operator!=(const Word& other);
	Word& operator=(const Word& source);//치환연산자
	//인라인함수
	string& GetSpellings() const;
	string& GetPartOfSpeech() const;
	string& GetMeanings() const;
	string& GetExample() const;
private:
	string spellings;
	string partOfSpeech;
	string meanings;
	string example;
};

//인라인함수 정의
inline string& Word::GetSpellings() const
{
	return const_cast<string&>(this->spellings);
}
inline string& Word::GetPartOfSpeech() const
{
	return const_cast<string&>(this->partOfSpeech);
}
inline string& Word::GetMeanings() const
{
	return const_cast<string&>(this->meanings);
}
inline string& Word::GetExample() const
{
	return const_cast<string&>(this->example);
}

#endif // !_WORD_H

