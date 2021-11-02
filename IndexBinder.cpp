#include "IndexBinder.h"
#include "VisitingCard.h"
#include "Index.h"
#include "BinaryTree.h"


//����Ʈ������
IndexBinder::IndexBinder()
{
	this->length = 0;
}

//���������
IndexBinder::IndexBinder(const IndexBinder& source)
	:indexes(source.indexes)
{
	this->length = source.length;
}

//ġȯ������
IndexBinder& IndexBinder::operator=(const IndexBinder& source)
{
	this->indexes = source.indexes;
	this->length = source.length;

	return *this;
}

//TakeIn
Index* IndexBinder::TakeIn(VisitingCard* visitingCardLink)
{
	//1. ������ �ּҸ� �Է¹޴´�.
	//2. ���ο� ȸ���̸��� �����Ѵ�.
	Index index(visitingCardLink->GetCompanyName());
	//3. ����ö�� ���� �߿� ���� ȸ���� �̸��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ����ö�� ���� ȸ���̸��� ���� ��쿡
	if (binaryNode == 0)
	{
		//4.1 ������ ����ö�� �����.
		binaryNode = this->indexes.Insert(index, CompareIndexes);
		//4.2 ����ö�� ��뷮�� ������Ų��.
		this->length++;
	}
	//5. ����ö�� �ּҸ� ���Ѵ�.
	Index* indexLink = &binaryNode->GetKey();
	//6. ���ο� ������ �����.
	Long arrayIndex = indexLink->TakeIn(visitingCardLink);
	//7. ������ ��ġ�� ����Ѵ�.
	return indexLink;
	//8. ������.
}

//Find
Index* IndexBinder::Find(string companyName)
{
	//1. ������ ��ȣ�� �Է¹޴´�.
	//2. ���ο� ȸ���̸��� �����Ѵ�.
	Index index(companyName);
	//3. ����ö�� �����߿��� ���� ȸ���� �̸��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ����ö�� �ߺ��Ǵ� ȸ�簡 ������
	Index* indexLink = 0;
	if (binaryNode != 0)
	{
		//4.1 ������ �ּҸ� ���Ѵ�.
		indexLink = &binaryNode->GetKey();
	}
	//5. ������ ��ġ�� ����Ѵ�.
	return indexLink;
	//6. ������.
}

//TakeOut
Index* IndexBinder::TakeOut(string companyName, VisitingCard* visitingCardLink)
{
	//1. ȸ���̸��� ������ �ּҸ� �Է¹޴´�.
	//2. ���ο� ȸ���̸��� �����Ѵ�.
	Index index(companyName);
	//3. ����ö���� ȸ���̸��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ������ �ּҸ� ���Ѵ�.
	Index* key = &binaryNode->GetKey();
	//5. ���ο��� ������ ã�´�.
	Long arrayIndex = key->Find(visitingCardLink);
	//6. ���ο��� ������ �����.
	arrayIndex = key->TakeOut(arrayIndex);
	//7. ������ ���԰����� 0���̸�
	if (key->GetLength() == 0)
	{
		//7.1 ������ �����.
		binaryNode = this->indexes.Delete(*key, CompareIndexes);
		//7.2 ����ö�� ��뷮�� ���ҽ�Ų��.
		this->length--;
		key = 0;
	}
	//8. ������ �ּҸ� ����Ѵ�.
	return key;
	//9. ������.
}

//MakeList
void IndexBinder::MakeList(Index* (*indexes), Long* count)
{
	//1. ���ι迭�� �����.
	this->indexes.MakeKeys(indexes, count);
	//2. ������.
}

//Arrange
void IndexBinder::Arrange()
{
	//1. ����ö�� ���ε��� �����Ѵ�.
	this->indexes.MakeBalance();
	//2. ������ ���ε��� ���Ե��� �����Ѵ�.
	IndexArrange(this->indexes.GetRoot());
	//3. ������.
}

//�Ҹ���
IndexBinder::~IndexBinder()
{

}

//�Լ�������
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;

	return (one_->GetCompanyName().compare(other_->GetCompanyName()));
}

//����Լ�
//IndexArrange
void IndexArrange(BinaryTree<Index>::Node* binaryNode)
{
	//1. binaryNode�� �д´�.
	//2. binaryNode�� null�� �ƴϸ�
	if (binaryNode != 0)
	{
		//2.1 ������ ���Ե��� �����Ѵ�.
		IndexArrange(binaryNode->GetLeft());
		Index* index = &binaryNode->GetKey();
		index->Arrange();
		IndexArrange(binaryNode->GetRight());
	}
	//3. ������.
}