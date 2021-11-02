#ifndef _INDEX_H
#define _INDEX_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Array.h"
#include<string>
using namespace std;
typedef signed long int Long;
class WordCard;//전방선언(주소로 이용될 경우)

class Index
{
public:
	Index(Long capacity = 100);//디폴트매개변수를 가지는 디폴트생성자
	Index(char alphabet, Long capacity = 100);//매개변수를 2개가지는 생성자
	Index(const Index& source);//복사생성자
	Index& operator=(const Index& source);//치환연산자
	~Index();//소멸자
	//연산함수
	Long TakeIn(WordCard* wordCardLink);
	Long Find(WordCard* wordCardLink);
	Long TakeOut(Long arrayIndex);
	void FindBySpellings(string spellings, Long* (*arrayIndexes), Long* count);
	WordCard* GetAt(Long arrayIndex);
	void Arrange();
	//인라인함수
	char GetAlphabet() const;
	Long GetLength() const;
	Long GetCapacity() const;
private:
	char alphabet;
	Array<WordCard*> wordCards;
	Long capacity;
	Long length;
};
//인라인 함수 정의
inline char Index::GetAlphabet() const
{
	return this->alphabet;
}
inline Long Index::GetLength() const
{
	return this->length;
}
inline  Long Index::GetCapacity() const
{
	return this->capacity;
}
//함수포인터 선언
int CompareArray_WordCards(void* one, void* other);
int CompareArray_Spellings(void* one, void* other);
int CompareArray_WordCardSpellings(void* one, void* other);

#endif // !_INDEX_H

