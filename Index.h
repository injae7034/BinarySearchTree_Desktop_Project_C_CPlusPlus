#ifndef _INDEX_H
#define _INDEX_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Array.h"
#include<string>
using namespace std;
typedef signed long int Long;
class WordCard;//���漱��(�ּҷ� �̿�� ���)

class Index
{
public:
	Index(Long capacity = 100);//����Ʈ�Ű������� ������ ����Ʈ������
	Index(char alphabet, Long capacity = 100);//�Ű������� 2�������� ������
	Index(const Index& source);//���������
	Index& operator=(const Index& source);//ġȯ������
	~Index();//�Ҹ���
	//�����Լ�
	Long TakeIn(WordCard* wordCardLink);
	Long Find(WordCard* wordCardLink);
	Long TakeOut(Long arrayIndex);
	void FindBySpellings(string spellings, Long* (*arrayIndexes), Long* count);
	WordCard* GetAt(Long arrayIndex);
	void Arrange();
	//�ζ����Լ�
	char GetAlphabet() const;
	Long GetLength() const;
	Long GetCapacity() const;
private:
	char alphabet;
	Array<WordCard*> wordCards;
	Long capacity;
	Long length;
};
//�ζ��� �Լ� ����
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
//�Լ������� ����
int CompareArray_WordCards(void* one, void* other);
int CompareArray_Spellings(void* one, void* other);
int CompareArray_WordCardSpellings(void* one, void* other);

#endif // !_INDEX_H

