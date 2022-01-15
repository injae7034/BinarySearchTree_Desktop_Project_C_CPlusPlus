#include "Index.h"
#include "WordCard.h"//�Լ������Ϳ��� WordCard->GetSpellings()������ ����ϱ� ���� �ʿ�!


//����Ʈ������
Index::Index(Long capacity)
	:wordCards(capacity)
{
	this->alphabet = ' ';
	this->capacity = capacity;
	this->length = 0;
}

//�Ű������� 2�� ������ ������
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

//���������
Index::Index(const Index& source)
	:wordCards(source.wordCards)
{
	this->alphabet = source.alphabet;
	this->capacity = source.capacity;
	this->length = source.length;
}

//ġȯ������
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
	//1. ��뷮�� �Ҵ緮���� ������
	if (this->length < this->capacity)
	{
		//1.1 �� ĭ�� �ܾ�ī���� ��ġ�� �����Ѵ�.
		arrayIndex = this->wordCards.Store(this->length, wordCardLink);
	}
	//2. �׷��� ������
	else
	{
		//2.1 �� ĭ�� �ܾ�ī���� ��ġ�� �����Ѵ�.
		arrayIndex = this->wordCards.AppendFromRear(wordCardLink);
		//2.2 ������ �Ҵ緮�� ������Ų��.
		this->capacity++;
	}
	//3. ������ ��뷮�� ������Ų��.
	this->length++;
	//4. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//5. ������.
}

//Find
Long Index::Find(WordCard* wordCardLink)
{
	//1. �ܾ�ī���� �ּҸ� �Է¹޴´�.
	//2. �ܾ�ī�带 ã�´�.
	Long arrayIndex = this->wordCards.LinearSearchUnique(wordCardLink, CompareArray_WordCards);
	//3. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//4. ������.
}

//FindBySpellings
void Index::FindBySpellings(string spellings, Long* (*arrayIndexes), Long* count)
{
	//1. ö�ڸ� �Է¹޴´�.
	//2. ���� ö�ڸ� ã�´�.
	this->wordCards.LinearSearchDuplicate(&spellings, arrayIndexes, count, CompareArray_Spellings);
	//3. ÷�ڹ迭�� ����Ѵ�.
	//4. ������.
}

//TakeOut
Long Index::TakeOut(Long arrayIndex)
{
	//1. �ܾ�ī���� ��ġ�� ������ �迭 ÷�ڸ� �Է¹޴´�.
	//2. �ش� �迭÷�ڿ� ����� �ܾ�ī�带 �����.
	arrayIndex = this->wordCards.Delete(arrayIndex);
	//3. �Ҵ緮�� ���ҽ�Ų��.
	this->capacity--;
	//4. ��뷮�� ���ҽ�Ų��.
	this->length--;
	//5. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//6. ������.
}

//Arrange
void Index::Arrange()
{
	//1. ������������ �����Ѵ�.
	this->wordCards.InsertionSort(CompareArray_WordCardSpellings);
	//2. ������.
}

//GetAt
WordCard* Index::GetAt(Long arrayIndex)
{
	//1. �迭�� ÷�ڸ� �Է¹޴´�.
	//2. ���� �迭�� ����� �ܾ�ī���� �ּҸ� �ҷ��´�.
	WordCard* wordCardLink = this->wordCards.GetAt(arrayIndex);
	//3. �ܾ�ī���� �ּҸ� ����Ѵ�.
	return wordCardLink;
	//4. ������.
}

//�Ҹ���
Index::~Index()
{

}

//�Լ�������
//WordCard �ּҰ����� ��
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

//ö�ڷ� ��
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

