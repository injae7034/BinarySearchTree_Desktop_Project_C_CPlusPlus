#include "IndexBinder.h"
#include "WordCard.h"

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

//�Ҹ���
IndexBinder::~IndexBinder()
{

}

//TakeIn
Index* IndexBinder::TakeIn(WordCard* wordCardLink)
{
	//1. �ܾ�ī���� �ּҸ� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	Index index(wordCardLink->GetSpellings()[0]);
	//3. ����ö�� ���� �߿� ���� ȸ���� �̸��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ����ö�� ���� ���ĺ��� ���� ��쿡
	if (binaryNode == 0)
	{
		//4.1 ������ ����ö�� �����.
		binaryNode = this->indexes.Insert(index, CompareIndexes);
		//4.2 ����ö�� ��뷮�� ������Ų��.
		this->length++;
	}
	//5. ����ö�� �ּҸ� ���Ѵ�.
	Index* indexLink = &binaryNode->GetKey();
	//6. ���ο� �ܾ�ī�带 �����.
	Long arrayIndex = indexLink->TakeIn(wordCardLink);
	//7. ������ ��ġ�� ����Ѵ�.
	return indexLink;
	//8. ������.
}

//Find
Index* IndexBinder::Find(char alphabet)
{
	//1. �ܾ�ī���� ���ĺ��� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	Index index(alphabet);
	//3. ����ö�� �����߿��� ���� ���ĺ��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ����ö�� �ߺ��Ǵ� ���ĺ��� ������
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
Index* IndexBinder::TakeOut(char alphabet, WordCard* wordCardLink)
{
	//1. ���ĺ��� �ܾ�ī���� �ּҸ� �Է¹޴´�.
	//2. ���ο� ���ĺ��� �����Ѵ�.
	Index index(alphabet);
	//3. ����ö���� ���ĺ��� �ִ��� ã�´�.
	BinaryTree<Index>::Node* binaryNode = this->indexes.Search(index, CompareIndexes);
	//4. ������ �ּҸ� ���Ѵ�.
	Index* key = &binaryNode->GetKey();
	//5. ���ο��� �ܾ�ī�带 ã�´�.
	Long arrayIndex = key->Find(wordCardLink);
	//6. ���ο��� �ܾ�ī�带 �����.
	arrayIndex = key->TakeOut(arrayIndex);
	//7. ������ �ܾ�ī�尳���� 0���̸�
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

//Arrange
void IndexBinder::Arrange()
{
	//1. ����ö�� ���ε��� �����Ѵ�.
	this->indexes.MakeBalance();
	//2. ������ ���ε��� ���Ե��� �����Ѵ�.
	IndexArrange(this->indexes.GetRoot());
	//3. ������.
}

//MakeList
void IndexBinder::MakeList(Index* (*indexes), Long* count)
{
	//1. ���ι迭�� �����.
	this->indexes.MakeKeys(indexes, count);
	//2. ������.
}

//�Լ�������
int CompareIndexes(void* one, void* other)
{
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;

	int ret;

	if (one_->GetAlphabet() > other_->GetAlphabet())
	{
		ret = 1;
	}
	else if (one_->GetAlphabet() == other_->GetAlphabet())
	{
		ret = 0;
	}
	else if (one_->GetAlphabet() < other_->GetAlphabet())
	{
		ret = -1;
	}

	return ret;
}

//����Լ�
//IndexArrange
void IndexArrange(BinaryTree<Index>::Node* binaryNode)
{
	//1. binaryNode�� �д´�.
	//2. binaryNode�� null�� �ƴϸ�
	if (binaryNode != 0)
	{
		//2.1 ������ �ܾ�ī����� �����Ѵ�.
		IndexArrange(binaryNode->GetLeft());
		Index* index = &binaryNode->GetKey();
		index->Arrange();
		IndexArrange(binaryNode->GetRight());
	}
	//3. ������.
}