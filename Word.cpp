#include "Word.h"

//디폴트생성자
Word::Word()
	:spellings(""), partOfSpeech(""), meanings(""), example("")
{

}

//매개변수를 갖는 생성자
Word::Word(string spellings, string partOfSpeech, string meanings, string example)
	:spellings(spellings), partOfSpeech(partOfSpeech), meanings(meanings), example(example)
{

}

//복사생성자
Word::Word(const Word& source)
	:spellings(source.spellings), partOfSpeech(source.partOfSpeech), meanings(source.meanings), example(source.example)
{

}

//논리함수
//IsEqual
bool Word::IsEqual(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) == 0 && this->partOfSpeech.compare(other.partOfSpeech) == 0 &&
		this->meanings.compare(other.meanings) == 0 && this->example.compare(other.example) == 0)
	{
		ret = true;
	}
	return ret;
}
//IsNotEqual
bool Word::IsNotEqual(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) != 0 || this->partOfSpeech.compare(other.partOfSpeech) != 0 ||
		this->meanings.compare(other.meanings) != 0 || this->example.compare(other.example) != 0)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
//operator==
bool Word::operator==(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) == 0 && this->partOfSpeech.compare(other.partOfSpeech) == 0 &&
		this->meanings.compare(other.meanings) == 0 && this->example.compare(other.example) == 0)
	{
		ret = true;
	}
	return ret;
}
//operator!=
bool Word::operator!=(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) != 0 || this->partOfSpeech.compare(other.partOfSpeech) != 0 ||
		this->meanings.compare(other.meanings) != 0 || this->example.compare(other.example) != 0)
	{
		ret = true;
	}
	return ret;
}
//치환연산자
//operator=
Word& Word::operator=(const Word& source)
{
	this->spellings = source.spellings;
	this->partOfSpeech = source.partOfSpeech;
	this->meanings = source.meanings;
	this->example = source.example;

	return *this;
}

//소멸자
Word::~Word()
{

}

#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. Word를 만든다.
	Word word;
	//2. 매개변수를 가지는 생성자를 만든다.
	Word other = Word("kind", "형용사", "친절한", "She is so kind.");
	cout << other.GetSpellings() << ", "
		<< other.GetPartOfSpeech() << ", "
		<< other.GetMeanings() << ", "
		<< other.GetExample() << endl;
	//3. 복사생성자를 만든다.
	Word theOther(other);
	cout << theOther.GetSpellings() << ", "
		<< theOther.GetPartOfSpeech() << ", "
		<< theOther.GetMeanings() << ", "
		<< theOther.GetExample() << endl;
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
	//5. word와 other가 다른지 비교한다.
	answer = word.IsNotEqual(other);
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	answer = word != other;
	if (answer == true)
	{
		cout << "참입니다." << endl;
	}
	//6. 치환연산자로 word에 other를 대입한다.
	word = other;
	cout << word.GetSpellings() << ", "
		<< word.GetPartOfSpeech() << ", "
		<< word.GetMeanings() << ", "
		<< word.GetExample() << endl;
	//7. 끝내다.
	return 0;
}
#endif