#ifndef _WORDCARD_H
#define _WORDCARD_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Word.h"
#include<string>
using namespace std;

class WordCard
{
public:
	WordCard();//디폴트생성자
	WordCard(string spellings, string partOfSpeech, string meanings, string example);//매개변수를 4개 갖는 생성자
	WordCard(const WordCard& source);//복사생성자
	~WordCard();//소멸자
	//논리함수
	bool IsEqual(const WordCard& other);
	bool IsNotEqual(const WordCard& other);
	//연산자함수
	bool operator==(const WordCard& other);
	bool operator!=(const WordCard& other);
	WordCard& operator=(const WordCard& source);//치환연산자
	//인라인함수
	string& GetSpellings() const;
	string& GetPartOfSpeech() const;
	string& GetMeanings() const;
	string& GetExample() const;
private:
	Word word;
};

//인라인함수 정의
inline string& WordCard::GetSpellings() const
{
	return const_cast<string&>(this->word.GetSpellings());
}

inline string& WordCard::GetPartOfSpeech() const
{
	return const_cast<string&>(this->word.GetPartOfSpeech());
}
inline string& WordCard::GetMeanings() const
{
	return const_cast<string&>(this->word.GetMeanings());
}
inline string& WordCard::GetExample() const
{
	return const_cast<string&>(this->word.GetExample());
}

#endif // !_WORDCARD_H

