#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
//STL(Standard Template Class Library)-C++ Class Library
#include "BinaryTree.h"
#include "Index.h"
#include<string>
using namespace std;

class WordCard;//�ּҷ� �̿�Ǳ� ������ ���漱���� �ʿ���

typedef signed long int Long;

class IndexBinder
{
public:
	IndexBinder();//����Ʈ������
	IndexBinder(const IndexBinder& source);//���������
	IndexBinder& operator=(const IndexBinder& source);//ġȯ������
	~IndexBinder();//�Ҹ���
	Index* TakeIn(WordCard* wordCardLink);
	Index* Find(char alphabet);
	Index* TakeOut(char alphabet, WordCard* wordCardLink);
	void Arrange();
	void MakeList(Index* (*indexes), Long* count);
	//�ζ����Լ�
	BinaryTree<Index>::Node* GetRoot() const;
	Long GetLength() const;
private:
	BinaryTree<Index> indexes;
	Long length;
};

//�ζ��� �Լ� ����
inline typename BinaryTree<Index>::Node* IndexBinder::GetRoot() const
{
	return const_cast<BinaryTree<Index>::Node*>(this->indexes.GetRoot());
}
inline Long IndexBinder::GetLength() const
{
	return this->length;
}

//�Լ������� ����
int CompareIndexes(void* one, void* other);
//����Լ�
void IndexArrange(BinaryTree<Index>::Node* binaryNode);

#endif // _INDEXBINDER_H

