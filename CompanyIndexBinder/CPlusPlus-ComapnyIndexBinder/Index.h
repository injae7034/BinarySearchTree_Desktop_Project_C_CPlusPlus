#ifndef _INDEX_H
#define _INDEX_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Array.h"
#include<string>
using namespace std;
typedef signed long int Long;
class VisitingCard;

class Index
{
public:
	Index(Long capacity = 36);//����Ʈ�Ű������� ������ ����Ʈ������
	Index(string companyName, Long capacity = 36);//�Ű������� 2�������� ������
	Index(const Index& source);//���������
	Index& operator=(const Index& source);//ġȯ������
	~Index();//�Ҹ���
	//�����Լ�
	Long TakeIn(VisitingCard* visitingCardLink);
	Long Find(VisitingCard* visitingCardLink);
	Long TakeOut(Long arrayIndex);
	VisitingCard* GetAt(Long arrayIndex);
	void Arrange();
	//�ζ����Լ�
	string& GetCompanyName() const;
	Long GetLength() const;
	Long GetCapacity() const;
private:
	string companyName;
	Array<VisitingCard*> visitingCards;
	Long capacity;
	Long length;
};

//�ζ����Լ� ����
inline string& Index::GetCompanyName() const
{
	return const_cast<string&>(this->companyName);
}
inline Long Index::GetLength() const
{
	return this->length;
}
inline Long Index::GetCapacity() const
{
	return this->capacity;
}


//�Լ������� ����
int CompareArray_VisitingCards(void* one, void* other);
int CompareArray_PersonalNames(void* one, void* other);

#endif //_INDEX_H
