#include "Index.h"
#include "VisitingCard.h"


//����Ʈ ������
Index::Index(Long capacity)
	:companyName(""), visitingCards(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//�Ű������� 2�������� ������
Index::Index(string companyName, Long capacity)
	:companyName(companyName), visitingCards(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//���������
Index::Index(const Index& source)
	:companyName(source.companyName), visitingCards(source.visitingCards)
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//ġȯ������
Index& Index::operator=(const Index& source)
{
	this->companyName = source.companyName;
	this->visitingCards = source.visitingCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//TakeIn
Long Index::TakeIn(VisitingCard* visitingCardLink)
{
	Long arrayIndex;
	//1. ��뷮�� �Ҵ緮���� ������
	if (this->length < this->capacity)
	{
		//1.1 �� ĭ�� ������ ��ġ�� �����Ѵ�.
		arrayIndex = this->visitingCards.Store(this->length, visitingCardLink);
	}
	//2. �׷��� ������
	else
	{
		//2.1 �� ĭ�� ������ ��ġ�� �����Ѵ�.
		arrayIndex = this->visitingCards.AppendFromRear(visitingCardLink);
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
Long Index::Find(VisitingCard* visitingCardLink)
{
	//1. ������ �ּҸ� �Է¹޴´�.
	//2. ������ ã�´�.
	Long arrayIndex = this->visitingCards.LinearSearchUnique(visitingCardLink, CompareArray_VisitingCards);
	//3. ��ġ�� ����Ѵ�.
	return arrayIndex;
	//4. ������.
}

//TakeOut
Long Index::TakeOut(Long arrayIndex)
{
	//1. ������ ��ġ�� ������ �迭 ÷�ڸ� �Է¹޴´�.
	//2. �ش� �迭÷�ڿ� ����� ������ �����.
	arrayIndex = this->visitingCards.Delete(arrayIndex);
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
	this->visitingCards.InsertionSort(CompareArray_PersonalNames);
	//2. ������.
}

//GetAt
VisitingCard* Index::GetAt(Long arrayIndex)
{
	//1. �迭�� ÷�ڸ� �Է¹޴´�.
	//2. ���� �迭�� ����� ������ �ּҸ� �ҷ��´�.
	VisitingCard* visitingCardLink = this->visitingCards.GetAt(arrayIndex);
	//3. ������ �ּҸ� ����Ѵ�.
	return visitingCardLink;
	//4. ������.
}


//�Ҹ���
Index::~Index()
{

}

//�Լ�������
//VistingCard �ּҰ����� ��
int CompareArray_VisitingCards(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard* other_ = (VisitingCard*)other;

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

//���μ������� ��
int CompareArray_PersonalNames(void* one, void* other)
{
	VisitingCard** one_ = (VisitingCard**)one;
	VisitingCard** other_ = (VisitingCard**)other;

	return((*one_)->GetName().compare((*other_)->GetName()));
}

