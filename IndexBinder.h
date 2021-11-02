#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
//STL(Standard Template Class Library)-C++ Class Library
#include "BinaryTree.h"
#include "Index.h"
#include<string>
using namespace std;

//���漱�� //binaryNode�� ���漱�� �� �� �ʿ����. binaryNode�� BinaryTree.h�� �� �ֱ� ������!!!!!!
class VisitingCard;
typedef signed long int Long;

class IndexBinder
{
public:
	IndexBinder();//����Ʈ������
	IndexBinder(const IndexBinder& source);//���������
	IndexBinder& operator=(const IndexBinder& source);//ġȯ������
	~IndexBinder();//�Ҹ���
	Index* TakeIn(VisitingCard* visitingCardLink);
	Index* Find(string companyName);
	Index* TakeOut(string companyName, VisitingCard* visitingCardLink);
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

#endif // !_INDEXBINDER_H

