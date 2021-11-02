#ifndef _WORDCARDBINDER_H
#define _WORDCARDBINDER_H
//STL(Standard Template Class Library)-C++ Class Library
#include "LinkedList.h"
#include "WordCard.h"
#include "Word.h"
#include<string>
using namespace std;

typedef signed long int Long;

class WordCardBinder
{
public:
	WordCardBinder();//디폴트생성자
	WordCardBinder(const WordCardBinder& source);//복사생성자
	~WordCardBinder();//소멸자
	WordCard* TakeIn(WordCard wordCard);
	void FindBySpellings(string spellings, WordCard** (*indexes), Long* count);
	void FindByMeanings(string meanings, WordCard** (*indexes), Long* count);
	WordCard TakeOut(WordCard* index);
	WordCard* Move(WordCard* index);
	WordCard* First();
	WordCard* Previous();
	WordCard* Next();
	WordCard* Last();
	WordCardBinder& operator=(const WordCardBinder& source);//치환연산자
	WordCard& operator[](Long index);//첨자연산자
	//인라인함수
	Long GetLength() const;
	WordCard* GetCurrent() const;
private:
	LinkedList<WordCard> wordCards;
	Long length;
	WordCard* current;
};

//인라인함수 정의
inline Long WordCardBinder::GetLength() const
{
	return this->length;
}
inline WordCard* WordCardBinder::GetCurrent() const
{
	return const_cast<WordCard*>(this->current);
}

//함수포인터 선언
int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWordCards(void* one, void* other);

#endif // !_WORDCARDBINDER_H

