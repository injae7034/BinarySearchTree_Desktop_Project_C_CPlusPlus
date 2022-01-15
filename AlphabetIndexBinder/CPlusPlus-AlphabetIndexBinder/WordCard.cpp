#include "WordCard.h"

//디폴트생성자
WordCard::WordCard()
{

}

//매개변수를 갖는 생성자
WordCard::WordCard(string spellings, string partOfSpeech, string meanings, string example)
	:word(spellings, partOfSpeech, meanings, example)
{

}

//복사생성자
WordCard::WordCard(const WordCard& source)
	:word(source.word)
{

}

//소멸자
WordCard::~WordCard()
{

}

//논리함수
//IsEqual
bool WordCard::IsEqual(const WordCard& other)
{
	bool ret = false;
	if (this->word.IsEqual(other.word) == true)
	{
		ret = true;
	}
	return ret;
}
//IsNotEqual
bool WordCard::IsNotEqual(const WordCard& other)
{
	bool ret = false;
	if (this->word.IsNotEqual(other.word) == true)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
//operator==
bool WordCard::operator==(const WordCard& other)
{
	bool ret = false;
	if (this->word.IsEqual(other.word) == true)
	{
		ret = true;
	}
	return ret;
}
//operator!=
bool WordCard::operator!=(const WordCard& other)
{
	bool ret = false;
	if (this->word.IsNotEqual(other.word) == true)
	{
		ret = true;
	}
	return ret;
}
//치환연산자
//operator=
WordCard& WordCard::operator=(const WordCard& source)
{
	this->word = source.word;

	return *this;
}

#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. wordCard를 생성한다.
	WordCard wordCard;
	//2. 매개변수를 가지는 생성자를 만든다.
	WordCard other = WordCard("kind", "형용사", "친절한", "She is so kind.");
	cout << other.GetSpellings() << ", "
		<< other.GetPartOfSpeech() << ", "
		<< other.GetMeanings() << ", "
		<< other.GetExample() << endl;
	//3. 복사생성자를 만든다.
	WordCard theOther(other);
	cout << other.GetSpellings() << ", "
		<< other.GetPartOfSpeech() << ", "
		<< other.GetMeanings() << ", "
		<< other.GetExample() << endl;
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
	//5. wordCard와 other가 다른지 비교한다.
	answer = wordCard.IsNotEqual(other);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = wordCard != other;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//6. 치환연산자로 wordCard에 other를 대입한다.
	wordCard = other;
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//7.끝내다.
	return 0;
}
#endif