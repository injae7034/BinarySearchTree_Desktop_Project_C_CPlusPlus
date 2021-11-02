#include "WordCardBinder.h"

//����Ʈ������
WordCardBinder::WordCardBinder()
{
	this->length = 0;
	this->current = 0;
}

//���������
WordCardBinder::WordCardBinder(const WordCardBinder& source)
	:wordCards(source.wordCards)
{
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();
}

//�Ҹ���
WordCardBinder::~WordCardBinder()
{

}

//TakeIn
WordCard* WordCardBinder::TakeIn(WordCard wordCard)
{
	//1. �ܾ�ī�带 �Է¹޴´�.
	//2. �ܾ�ī�带 �����.
	LinkedList<WordCard>::Node* node = this->wordCards.AppendFromTail(wordCard);
	//3. �ܾ�ī��ö�� �ܾ�ī�� ������ �ø���.
	this->length++;
	//4. �ܾ�ī��ö�� ���� �ܾ�ī�带 �����Ѵ�.
	this->current = &node->GetObject();
	//5. ���� ��ġ�� �����Ѵ�.
	return this->current;
	//6. ������.
}

//FindBySpellings
void WordCardBinder::FindBySpellings(string spellings, WordCard** (*indexes), Long* count)
{
	//�ʱ�ȭ
	*indexes = 0;
	*count = 0;
	//1. ö�ڸ� �Է¹޴´�.
	//2. �ܾ�ī��ö���� ö�ڷ� �ܾ ã�´�.
	LinkedList<WordCard>::Node* (*nodes);
	this->wordCards.LinearSearchDuplicate(&spellings, &nodes, count, CompareSpellings);
	//3. ã�� ������ ������
	if (*count > 0)
	{
		//3.1 �ܾ�ī�帵ũ �迭�� �����.
		*indexes = new WordCard* [*count];
	}
	//4. ã�� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
	Long i = 0;
	while (i < *count)
	{
		//4.1 �ܾ�ī�帵ũ�迭�� ã�� �ܾ�ī����� ��ġ�� �����Ѵ�.
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	//5. �Ҵ������Ѵ�.
	if (nodes != 0)
	{
		delete[] nodes;
	}
	//6. ��ġ��� ������ ����Ѵ�.
	//7. ������.
}

//FindBymeanings
void WordCardBinder::FindByMeanings(string meanings, WordCard** (*indexes), Long* count)
{
	//�ʱ�ȭ
	*indexes = 0;
	*count = 0;
	//1. �ǹ̸� �Է¹޴´�.
	//2. �ܾ�ī��û���� �ǹ̷� �ܾ�ī�带 ã�´�.
	LinkedList<WordCard>::Node* (*nodes);
	this->wordCards.LinearSearchDuplicate(&meanings, &nodes, count, CompareMeanings);
	//3. ã�� �ܾ ������
	if (*count > 0)
	{
		//3.1 �ܾ�ī�帵ũ �迭�� �����.
		*indexes = new WordCard * [*count];
	}
	//4. ã�� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
	Long i = 0;
	while (i < *count)
	{
		//4.1 �ܾ�ī�帵ũ�迭�� ã�� �ܾ�ī����� ��ġ�� �����Ѵ�.
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	//5. �Ҵ������Ѵ�.
	if (nodes != 0)
	{
		delete[] nodes;
	}
	//6. ��ġ��� ������ ����Ѵ�.
	//7. ������.
}

//TakeOut
WordCard WordCardBinder::TakeOut(WordCard* index)
{
	//1. ���� �ܾ�ī���� ��ġ�� �Է¹޴´�.
	//2. ���� �ܾ�ī�带 ã�´�.
	LinkedList<WordCard>::Node* node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	//3. node���� �ܾ�ī�带 ������.
	WordCard wordCard = node->GetObject();
	//4. �ܾ�ī��ö���� �ܾ�ī�带 ���ش�.
	this->wordCards.Delete(node);
	//5. �ܾ�ī��ö�� �ܾ ����������
	if (this->wordCards.GetCurrent() != 0)
	{
		//5.1 �ܾ�ī��ö�� ����ī�� ��ġ�� �����Ѵ�.
		this->current = &this->wordCards.GetCurrent()->GetObject();
	}
	//6. �ܾ�ī��ö�� �����ִ� �ܾ�ī�尡 ������
	else
	{
		this->current = 0;
	}
	//7. �ܾ�ī��ö�� �ܾ�ī�� ������ ���ҽ�Ų��.
	this->length--;
	//8. �ܾ�ī�带 ����Ѵ�.
	return wordCard;
	//9. ������.
}

//Move
WordCard* WordCardBinder::Move(WordCard* index)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. �ܾ�ī���� ��ġ�� node�� ã�´�.
	LinkedList<WordCard>::Node* node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	//3. ���� node��ġ�� �̵��Ѵ�.
	node = this->wordCards.Move(node);
	//4. ���� �ܾ�ī�带 ���Ѵ�.
	this->current = &node->GetObject();
	//5. ���� ��ġ�� ����Ѵ�.
	return this->current;
	//6. ������.
}

//First
WordCard* WordCardBinder::First()
{
	//1. ������ġ�� ó������ �̵���Ų��.
	LinkedList<WordCard>::Node* node = this->wordCards.First();
	//2. ���� �ܾ�ī�� ��ġ�� ���Ѵ�.
	this->current = &node->GetObject();
	//3. ������ġ�� ����Ѵ�.
	return this->current;
	//4. ������.
}

//Previous
WordCard* WordCardBinder::Previous()
{
	//1. ������ġ�� ó������ �̵���Ų��.
	LinkedList<WordCard>::Node* node = this->wordCards.Previous();
	//2. ���� �ܾ�ī�� ��ġ�� ���Ѵ�.
	this->current = &node->GetObject();
	//3. ������ġ�� ����Ѵ�.
	return this->current;
	//4. ������.
}

//Next
WordCard* WordCardBinder::Next()
{
	//1. ������ġ�� ó������ �̵���Ų��.
	LinkedList<WordCard>::Node* node = this->wordCards.Next();
	//2. ���� �ܾ�ī�� ��ġ�� ���Ѵ�.
	this->current = &node->GetObject();
	//3. ������ġ�� ����Ѵ�.
	return this->current;
	//4. ������.
}

//Last
WordCard* WordCardBinder::Last()
{
	//1. ������ġ�� ó������ �̵���Ų��.
	LinkedList<WordCard>::Node* node = this->wordCards.Last();
	//2. ���� �ܾ�ī�� ��ġ�� ���Ѵ�.
	this->current = &node->GetObject();
	//3. ������ġ�� ����Ѵ�.
	return this->current;
	//4. ������.
}

//ġȯ������
WordCardBinder& WordCardBinder::operator=(const WordCardBinder& source)
{
	this->wordCards = source.wordCards;
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();

	return *this;
}

//÷�ڿ�����
WordCard& WordCardBinder::operator[](Long index)
{
	return this->wordCards[index];
}

#if 0
#include "WordCardBinder.h"
#include "IndexBinder.h"
#include<iostream>
using namespace std;

//�̺а˻�Ʈ�� Arrange ��¿� ����Լ� ����
void Printf(BinaryTree<Index>::Node* binaryNode);

int main(int argc, char* argv[])
{
	//INDEXBINDER �����׽�Ʈ �ó�����
	//1. ����ö�� �����.
	WordCardBinder wordCardBinder;
	//2. ����ö�� �����.
	IndexBinder indexBinder;
	//3. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard first("apple", "���", "���", "Apples are sweet.");
	WordCard* wordCardLink = wordCardBinder.TakeIn(first);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//4. ����ö�� ���ο� �ܾ�ī�带 �����.
	Index* indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	Long i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//5. �ܾ�ī��ö���� �ܾ�ī�带 ������.
	WordCard wordCard = wordCardBinder.TakeOut(wordCardLink);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//6. ����ö�� ���ο��� �ܾ�ī�带 ������.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLink);
	if (indexLink == 0)
	{
		cout << "������ ���������ϴ�." << endl;
	}
	else
	{
		cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
		i = 0;
		while (i < indexLink->GetLength())
		{
			wordCardLink = indexLink->GetAt(i);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			i++;
		}
	}
	//7. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard second("very", "�λ�", "�ſ�", "He is very tall.");
	wordCardLink = wordCardBinder.TakeIn(second);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//8. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//9. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard third("keep", "����", "���~�ϴ�", "I keep studying programming.");
	wordCardLink = wordCardBinder.TakeIn(third);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//10. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//11. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard fourth("kind", "���", "����", "We serve two kinds of tea.");
	wordCardLink = wordCardBinder.TakeIn(fourth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//12. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//13. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard fifth("kind", "�����", "ģ����", "She is so kind.");
	wordCardLink = wordCardBinder.TakeIn(fifth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//14. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//15. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard sixth("extremely", "�λ�", "�ſ�", "The mountain is extremely high.");
	wordCardLink = wordCardBinder.TakeIn(sixth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//16. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//17. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard seventh("keep", "����", "����", "He keeps her from studying.");
	wordCardLink = wordCardBinder.TakeIn(seventh);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//18. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//19. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard eighth("eraser", "���", "���찳", "I need good eraser.");
	wordCardLink = wordCardBinder.TakeIn(eighth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//20. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//21. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard nineth("various", "�����", "�پ���", "I have various topic.");
	wordCardLink = wordCardBinder.TakeIn(nineth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//23. �ܾ�ī��ö�� �ܾ�ī�带 �����.
	WordCard tenth("apple", "���", "���", "Apples are sweet.");
	wordCardLink = wordCardBinder.TakeIn(tenth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//24. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//21. ó������ �̵��Ѵ�.
	wordCardLink = wordCardBinder.First();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. �������� �̵��Ѵ�.
	wordCardLink = wordCardBinder.Previous();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//21. �������� �̵��Ѵ�.
	wordCardLink = wordCardBinder.Next();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. ���������� �̵��Ѵ�.
	wordCardLink = wordCardBinder.Last();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//23. �������� �̵��Ѵ�.
	wordCardLink = wordCardBinder.Next();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//24. �������� �̵��Ѵ�.
	wordCardLink = wordCardBinder.Previous();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//25. ���θ���Ʈ�� �����.
	cout << endl;
	cout << "indexBinder���θ���Ʈ" << endl;
	Index(*indexes);
	Long count;
	indexBinder.MakeList(&indexes, &count);
	i = 0;
	while (i < count)
	{
		cout << "�����̸�: " << indexes[i].GetAlphabet() << endl;
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			wordCardLink = indexes[i].GetAt(j);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			j++;
		}
		i++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//26. ��������� + ���θ���Ʈ
	cout << endl;
	cout << "��������� + ���θ���Ʈ" << endl;
	cout << "other���θ���Ʈ" << endl;
	IndexBinder other(indexBinder);
	other.MakeList(&indexes, &count);
	i = 0;
	while (i < count)
	{
		cout << "�����̸�: " << indexes[i].GetAlphabet() << endl;
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			wordCardLink = indexes[i].GetAt(j);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			j++;
		}
		i++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//27. ����ö���� �����Ѵ�.
	cout << endl;
	cout << "�����ϱ� ��" << endl;
	Printf(indexBinder.GetRoot());
	cout << endl;
	cout << "������ ��" << endl;
	indexBinder.Arrange();
	Printf(indexBinder.GetRoot());
	//28. ġȯ������
	cout << endl;
	cout << "���󺹱�" << endl;
	indexBinder = other;
	Printf(indexBinder.GetRoot());
	//27. �ܾ�ī��ö���� "kind"�� ã�´�.
	WordCard* (*wordCardLinks);
	wordCardBinder.FindBySpellings("kind", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		cout << wordCardLinks[i]->GetSpellings() << ", "
			<< wordCardLinks[i]->GetPartOfSpeech() << ", "
			<< wordCardLinks[i]->GetMeanings() << ", "
			<< wordCardLinks[i]->GetExample() << endl;
		i++;
	}
	//28. �ܾ�ī��ö���� �ι�° "kind"�� ������.
	wordCard = wordCardBinder.TakeOut(wordCardLinks[count - 1]);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//29. ����ö�� ���ο��� �ܾ�ī�带 ������.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLinks[count - 1]);
	if (indexLink == 0)
	{
		cout << "������ ���������ϴ�." << endl;
	}
	else
	{
		cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
		i = 0;
		while (i < indexLink->GetLength())
		{
			wordCardLink = indexLink->GetAt(i);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			i++;
		}
	}
	//�Ҵ�����
	if (wordCardLinks != 0)
	{
		delete[] wordCardLinks;
	}
	//30. �ܾ�ī�忡�� "�ſ�"�� ã�´�.
	wordCardBinder.FindByMeanings("�ſ�", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		cout << wordCardLinks[i]->GetSpellings() << ", "
			<< wordCardLinks[i]->GetPartOfSpeech() << ", "
			<< wordCardLinks[i]->GetMeanings() << ", "
			<< wordCardLinks[i]->GetExample() << endl;
		i++;
	}
	//31. �ܾ�ī��ö���� ù��° "�ſ�"�� ������.
	wordCard = wordCardBinder.TakeOut(wordCardLinks[0]);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//32. ����ö�� ���ο��� �ܾ�ī�带 ������.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLinks[0]);
	if (indexLink == 0)
	{
		cout << "������ ���������ϴ�." << endl;
	}
	else
	{
		cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
		i = 0;
		while (i < indexLink->GetLength())
		{
			wordCardLink = indexLink->GetAt(i);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			i++;
		}
	}
	//�Ҵ�����
	if (wordCardLinks != 0)
	{
		delete[] wordCardLinks;
	}
	//33. ����ö���� 'k'�� ã�´�.
	indexLink = indexBinder.Find('k');
	cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
	i = 0;
	while (i < indexLink->GetLength())
	{
		wordCardLink = indexLink->GetAt(i);
		cout << wordCardLink->GetSpellings() << ", "
			<< wordCardLink->GetPartOfSpeech() << ", "
			<< wordCardLink->GetMeanings() << ", "
			<< wordCardLink->GetExample() << endl;
		i++;
	}
	//34. �ܾ�ī��ö���� 'k'�� �ι�° �ܾ�ī��� �̵��Ѵ�.
	wordCardLink = indexLink->GetAt(1);
	wordCardLink = wordCardBinder.Move(wordCardLink);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//35. �ܾ�ī��ö���� �ܾ�ī�带 ������.
	wordCard = wordCardBinder.TakeOut(wordCardLink);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//36. ����ö�� ���ο��� �ܾ�ī�带 ������.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLink);
	if (indexLink == 0)
	{
		cout << "������ ���������ϴ�." << endl;
	}
	else
	{
		cout << "�����̸�: " << indexLink->GetAlphabet() << endl;
		i = 0;
		while (i < indexLink->GetLength())
		{
			wordCardLink = indexLink->GetAt(i);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			i++;
		}
	}


	//37. �Ҹ���
	return 0;
}

//Printf ����Լ� ����
void Printf(BinaryTree<Index>::Node* binaryNode)
{
	if (binaryNode != 0)
	{
		Index* index = &binaryNode->GetKey();
		cout << index->GetAlphabet() << endl;
		Long i = 0;
		while (i < index->GetLength())
		{
			WordCard* wordCardLink = index->GetAt(i);
			cout << wordCardLink->GetSpellings() << ", "
				<< wordCardLink->GetPartOfSpeech() << ", "
				<< wordCardLink->GetMeanings() << ", "
				<< wordCardLink->GetExample() << endl;
			i++;
		}
		Printf(binaryNode->GetLeft());
		Printf(binaryNode->GetRight());
	}
}
#endif
//�Լ������� ����
//CompareSpellings
int CompareSpellings(void* one, void* other)
{
	WordCard* one_ = (WordCard*)one;
	string* other_ = (string*)other;

	return (one_->GetSpellings().compare(*other_));
}
//CompareMeanings
int CompareMeanings(void* one, void* other)
{
	WordCard* one_ = (WordCard*)one;
	string* other_ = (string*)other;

	return (one_->GetMeanings().compare(*other_));
}
//CompareWordCards
int CompareWordCards(void* one, void* other)
{
	int ret;
	if (one == other)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}