#include "Index.h"
#include "WordCard.h"//함수포인터에서 WordCard->GetSpellings()연산을 사용하기 위해 필요!


//디폴트생성자
Index::Index(Long capacity)
	:wordCards(capacity)
{
	this->alphabet = ' ';
	this->capacity = capacity;
	this->length = 0;
}

//매개변수를 2개 가지는 생성자
Index::Index(char alphabet, Long capacity)
	:wordCards(capacity)
{
	if (alphabet >= 'a' && alphabet <= 'z')
	{
		alphabet -= 32;
	}
	this->alphabet = alphabet;
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
Index::Index(const Index& source)
	:wordCards(source.wordCards)
{
	this->alphabet = source.alphabet;
	this->capacity = source.capacity;
	this->length = source.length;
}

//치환연산자
Index& Index::operator=(const Index& source)
{
	this->alphabet = source.alphabet;
	this->wordCards = source.wordCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//TakeIn
Long Index::TakeIn(WordCard* wordCardLink)
{
	Long arrayIndex;
	//1. 사용량이 할당량보다 작으면
	if (this->length < this->capacity)
	{
		//1.1 빈 칸에 단어카드의 위치를 저장한다.
		arrayIndex = this->wordCards.Store(this->length, wordCardLink);
	}
	//2. 그렇지 않으면
	else
	{
		//2.1 새 칸에 단어카드의 위치를 저장한다.
		arrayIndex = this->wordCards.AppendFromRear(wordCardLink);
		//2.2 색인의 할당량을 증가시킨다.
		this->capacity++;
	}
	//3. 색인의 사용량을 증가시킨다.
	this->length++;
	//4. 위치를 출력한다.
	return arrayIndex;
	//5. 끝내다.
}

//Find
Long Index::Find(WordCard* wordCardLink)
{
	//1. 단어카드의 주소를 입력받는다.
	//2. 단어카드를 찾는다.
	Long arrayIndex = this->wordCards.LinearSearchUnique(wordCardLink, CompareArray_WordCards);
	//3. 위치를 출력한다.
	return arrayIndex;
	//4. 끝내다.
}

//FindBySpellings
void Index::FindBySpellings(string spellings, Long* (*arrayIndexes), Long* count)
{
	//1. 철자를 입력받는다.
	//2. 같은 철자를 찾는다.
	this->wordCards.LinearSearchDuplicate(&spellings, arrayIndexes, count, CompareArray_Spellings);
	//3. 첨자배열을 출력한다.
	//4. 끝내다.
}

//TakeOut
Long Index::TakeOut(Long arrayIndex)
{
	//1. 단어카드의 위치를 저장한 배열 첨자를 입력받는다.
	//2. 해당 배열첨자에 저장된 단어카드를 지운다.
	arrayIndex = this->wordCards.Delete(arrayIndex);
	//3. 할당량을 감소시킨다.
	this->capacity--;
	//4. 사용량을 감소시킨다.
	this->length--;
	//5. 위치를 출력한다.
	return arrayIndex;
	//6. 끝내다.
}

//Arrange
void Index::Arrange()
{
	//1. 오름차순으로 정렬한다.
	this->wordCards.InsertionSort(CompareArray_WordCardSpellings);
	//2. 끝내다.
}

//GetAt
WordCard* Index::GetAt(Long arrayIndex)
{
	//1. 배열에 첨자를 입력받는다.
	//2. 색인 배열에 저장된 단어카드의 주소를 불러온다.
	WordCard* wordCardLink = this->wordCards.GetAt(arrayIndex);
	//3. 단어카드의 주소를 출력한다.
	return wordCardLink;
	//4. 끝내다.
}

//소멸자
Index::~Index()
{

}

//함수포인터
//WordCard 주소값으로 비교
int CompareArray_WordCards(void* one, void* other)
{
	WordCard** one_ = (WordCard**)one;
	WordCard* other_ = (WordCard*)other;

	int ret;
	if (*one_ == other_)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}

//철자로 비교
int CompareArray_Spellings(void* one, void* other)
{
	WordCard** one_ = (WordCard**)one;
	string* other_ = (string*)other;

	return((*one_)->GetSpellings().compare((*other_)));
}

int CompareArray_WordCardSpellings(void* one, void* other)
{
	WordCard** one_ = (WordCard**)one;
	WordCard** other_ = (WordCard**)other;

	return((*one_)->GetSpellings().compare(((*other_)->GetSpellings())));
}

