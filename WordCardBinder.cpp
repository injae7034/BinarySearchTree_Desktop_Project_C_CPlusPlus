#include "WordCardBinder.h"

//디폴트생성자
WordCardBinder::WordCardBinder()
{
	this->length = 0;
	this->current = 0;
}

//복사생성자
WordCardBinder::WordCardBinder(const WordCardBinder& source)
	:wordCards(source.wordCards)
{
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();
}

//소멸자
WordCardBinder::~WordCardBinder()
{

}

//TakeIn
WordCard* WordCardBinder::TakeIn(WordCard wordCard)
{
	//1. 단어카드를 입력받는다.
	//2. 단어카드를 끼운다.
	LinkedList<WordCard>::Node* node = this->wordCards.AppendFromTail(wordCard);
	//3. 단어카드철의 단어카드 개수를 늘린다.
	this->length++;
	//4. 단어카드철의 현재 단어카드를 변경한다.
	this->current = &node->GetObject();
	//5. 현재 위치를 츨력한다.
	return this->current;
	//6. 끝내다.
}

//FindBySpellings
void WordCardBinder::FindBySpellings(string spellings, WordCard** (*indexes), Long* count)
{
	//초기화
	*indexes = 0;
	*count = 0;
	//1. 철자를 입력받는다.
	//2. 단어카드철에서 철자로 단어를 찾는다.
	LinkedList<WordCard>::Node* (*nodes);
	this->wordCards.LinearSearchDuplicate(&spellings, &nodes, count, CompareSpellings);
	//3. 찾은 성명이 있으면
	if (*count > 0)
	{
		//3.1 단어카드링크 배열을 만든다.
		*indexes = new WordCard* [*count];
	}
	//4. 찾은 단어카드개수만큼 반복한다.
	Long i = 0;
	while (i < *count)
	{
		//4.1 단어카드링크배열에 찾은 단어카드들의 위치를 저장한다.
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	//5. 할당해제한다.
	if (nodes != 0)
	{
		delete[] nodes;
	}
	//6. 위치들과 개수를 출력한다.
	//7. 끝내다.
}

//FindBymeanings
void WordCardBinder::FindByMeanings(string meanings, WordCard** (*indexes), Long* count)
{
	//초기화
	*indexes = 0;
	*count = 0;
	//1. 의미를 입력받는다.
	//2. 단어카드청에서 의미로 단어카드를 찾는다.
	LinkedList<WordCard>::Node* (*nodes);
	this->wordCards.LinearSearchDuplicate(&meanings, &nodes, count, CompareMeanings);
	//3. 찾은 단어가 있으면
	if (*count > 0)
	{
		//3.1 단어카드링크 배열을 만든다.
		*indexes = new WordCard * [*count];
	}
	//4. 찾은 단어카드개수만큼 반복한다.
	Long i = 0;
	while (i < *count)
	{
		//4.1 단어카드링크배열에 찾은 단어카드들의 위치를 저장한다.
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	//5. 할당해제한다.
	if (nodes != 0)
	{
		delete[] nodes;
	}
	//6. 위치들과 개수를 출력한다.
	//7. 끝내다.
}

//TakeOut
WordCard WordCardBinder::TakeOut(WordCard* index)
{
	//1. 꺼낼 단어카드의 위치를 입력받는다.
	//2. 꺼낼 단어카드를 찾는다.
	LinkedList<WordCard>::Node* node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	//3. node에서 단어카드를 꺼낸다.
	WordCard wordCard = node->GetObject();
	//4. 단어카드철에서 단어카드를 없앤다.
	this->wordCards.Delete(node);
	//5. 단어카드철에 단어가 남아있으면
	if (this->wordCards.GetCurrent() != 0)
	{
		//5.1 단어카드철의 현재카드 위치를 변경한다.
		this->current = &this->wordCards.GetCurrent()->GetObject();
	}
	//6. 단어카드철에 남아있는 단어카드가 없으면
	else
	{
		this->current = 0;
	}
	//7. 단어카드철의 단어카드 개수를 감소시킨다.
	this->length--;
	//8. 단어카드를 출력한다.
	return wordCard;
	//9. 끝내다.
}

//Move
WordCard* WordCardBinder::Move(WordCard* index)
{
	//1. 위치를 입력받는다.
	//2. 단어카드의 위치로 node를 찾는다.
	LinkedList<WordCard>::Node* node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	//3. 현재 node위치를 이동한다.
	node = this->wordCards.Move(node);
	//4. 현재 단어카드를 구한다.
	this->current = &node->GetObject();
	//5. 현재 위치를 출력한다.
	return this->current;
	//6. 끝내다.
}

//First
WordCard* WordCardBinder::First()
{
	//1. 현재위치를 처음으로 이동시킨다.
	LinkedList<WordCard>::Node* node = this->wordCards.First();
	//2. 현재 단어카드 위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Previous
WordCard* WordCardBinder::Previous()
{
	//1. 현재위치를 처음으로 이동시킨다.
	LinkedList<WordCard>::Node* node = this->wordCards.Previous();
	//2. 현재 단어카드 위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Next
WordCard* WordCardBinder::Next()
{
	//1. 현재위치를 처음으로 이동시킨다.
	LinkedList<WordCard>::Node* node = this->wordCards.Next();
	//2. 현재 단어카드 위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//Last
WordCard* WordCardBinder::Last()
{
	//1. 현재위치를 처음으로 이동시킨다.
	LinkedList<WordCard>::Node* node = this->wordCards.Last();
	//2. 현재 단어카드 위치를 구한다.
	this->current = &node->GetObject();
	//3. 현재위치를 출력한다.
	return this->current;
	//4. 끝내다.
}

//치환연산자
WordCardBinder& WordCardBinder::operator=(const WordCardBinder& source)
{
	this->wordCards = source.wordCards;
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();

	return *this;
}

//첨자연산자
WordCard& WordCardBinder::operator[](Long index)
{
	return this->wordCards[index];
}

#if 0
#include "WordCardBinder.h"
#include "IndexBinder.h"
#include<iostream>
using namespace std;

//이분검색트리 Arrange 출력용 재귀함수 선언
void Printf(BinaryTree<Index>::Node* binaryNode);

int main(int argc, char* argv[])
{
	//INDEXBINDER 메인테스트 시나리오
	//1. 명함철을 만든다.
	WordCardBinder wordCardBinder;
	//2. 색인철을 만든다.
	IndexBinder indexBinder;
	//3. 단어카드철에 단어카드를 끼운다.
	WordCard first("apple", "명사", "사과", "Apples are sweet.");
	WordCard* wordCardLink = wordCardBinder.TakeIn(first);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//4. 색인철의 색인에 단어카드를 끼운다.
	Index* indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//5. 단어카드철에서 단어카드를 꺼낸다.
	WordCard wordCard = wordCardBinder.TakeOut(wordCardLink);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//6. 색인철의 색인에서 단어카드를 꺼낸다.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLink);
	if (indexLink == 0)
	{
		cout << "색인이 지워졌습니다." << endl;
	}
	else
	{
		cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//7. 단어카드철에 단어카드를 끼운다.
	WordCard second("very", "부사", "매우", "He is very tall.");
	wordCardLink = wordCardBinder.TakeIn(second);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//8. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//9. 단어카드철에 단어카드를 끼운다.
	WordCard third("keep", "동사", "계속~하다", "I keep studying programming.");
	wordCardLink = wordCardBinder.TakeIn(third);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//10. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//11. 단어카드철에 단어카드를 끼운다.
	WordCard fourth("kind", "명사", "종류", "We serve two kinds of tea.");
	wordCardLink = wordCardBinder.TakeIn(fourth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//12. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//13. 단어카드철에 단어카드를 끼운다.
	WordCard fifth("kind", "형용사", "친절한", "She is so kind.");
	wordCardLink = wordCardBinder.TakeIn(fifth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//14. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//15. 단어카드철에 단어카드를 끼운다.
	WordCard sixth("extremely", "부사", "매우", "The mountain is extremely high.");
	wordCardLink = wordCardBinder.TakeIn(sixth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//16. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//17. 단어카드철에 단어카드를 끼운다.
	WordCard seventh("keep", "동사", "막다", "He keeps her from studying.");
	wordCardLink = wordCardBinder.TakeIn(seventh);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//18. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//19. 단어카드철에 단어카드를 끼운다.
	WordCard eighth("eraser", "명사", "지우개", "I need good eraser.");
	wordCardLink = wordCardBinder.TakeIn(eighth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//20. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//21. 단어카드철에 단어카드를 끼운다.
	WordCard nineth("various", "형용사", "다양한", "I have various topic.");
	wordCardLink = wordCardBinder.TakeIn(nineth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//23. 단어카드철에 단어카드를 끼운다.
	WordCard tenth("apple", "명사", "사과", "Apples are sweet.");
	wordCardLink = wordCardBinder.TakeIn(tenth);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//24. 색인철의 색인에 단어카드를 끼운다.
	indexLink = indexBinder.TakeIn(wordCardLink);
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//21. 처음으로 이동한다.
	wordCardLink = wordCardBinder.First();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. 이전으로 이동한다.
	wordCardLink = wordCardBinder.Previous();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//21. 다음으로 이동한다.
	wordCardLink = wordCardBinder.Next();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//22. 마지막으로 이동한다.
	wordCardLink = wordCardBinder.Last();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//23. 다음으로 이동한다.
	wordCardLink = wordCardBinder.Next();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//24. 이전으로 이동한다.
	wordCardLink = wordCardBinder.Previous();
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//25. 색인리스트를 만든다.
	cout << endl;
	cout << "indexBinder색인리스트" << endl;
	Index(*indexes);
	Long count;
	indexBinder.MakeList(&indexes, &count);
	i = 0;
	while (i < count)
	{
		cout << "색인이름: " << indexes[i].GetAlphabet() << endl;
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
	//26. 복사생성자 + 색인리스트
	cout << endl;
	cout << "복사생성자 + 색인리스트" << endl;
	cout << "other색인리스트" << endl;
	IndexBinder other(indexBinder);
	other.MakeList(&indexes, &count);
	i = 0;
	while (i < count)
	{
		cout << "색인이름: " << indexes[i].GetAlphabet() << endl;
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
	//27. 색인철에서 정리한다.
	cout << endl;
	cout << "정리하기 전" << endl;
	Printf(indexBinder.GetRoot());
	cout << endl;
	cout << "정리한 후" << endl;
	indexBinder.Arrange();
	Printf(indexBinder.GetRoot());
	//28. 치환연산자
	cout << endl;
	cout << "원상복귀" << endl;
	indexBinder = other;
	Printf(indexBinder.GetRoot());
	//27. 단어카드철에서 "kind"를 찾는다.
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
	//28. 단어카드철에서 두번째 "kind"를 꺼낸다.
	wordCard = wordCardBinder.TakeOut(wordCardLinks[count - 1]);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//29. 색인철의 색인에서 단어카드를 꺼낸다.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLinks[count - 1]);
	if (indexLink == 0)
	{
		cout << "색인이 지워졌습니다." << endl;
	}
	else
	{
		cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//할당해제
	if (wordCardLinks != 0)
	{
		delete[] wordCardLinks;
	}
	//30. 단어카드에서 "매우"를 찾는다.
	wordCardBinder.FindByMeanings("매우", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		cout << wordCardLinks[i]->GetSpellings() << ", "
			<< wordCardLinks[i]->GetPartOfSpeech() << ", "
			<< wordCardLinks[i]->GetMeanings() << ", "
			<< wordCardLinks[i]->GetExample() << endl;
		i++;
	}
	//31. 단어카드철에서 첫번째 "매우"를 꺼낸다.
	wordCard = wordCardBinder.TakeOut(wordCardLinks[0]);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//32. 색인철의 색인에서 단어카드를 꺼낸다.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLinks[0]);
	if (indexLink == 0)
	{
		cout << "색인이 지워졌습니다." << endl;
	}
	else
	{
		cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//할당해제
	if (wordCardLinks != 0)
	{
		delete[] wordCardLinks;
	}
	//33. 색인철에서 'k'를 찾는다.
	indexLink = indexBinder.Find('k');
	cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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
	//34. 단어카드철에서 'k'의 두번째 단어카드로 이동한다.
	wordCardLink = indexLink->GetAt(1);
	wordCardLink = wordCardBinder.Move(wordCardLink);
	cout << wordCardLink->GetSpellings() << ", "
		<< wordCardLink->GetPartOfSpeech() << ", "
		<< wordCardLink->GetMeanings() << ", "
		<< wordCardLink->GetExample() << endl;
	//35. 단어카드철에서 단어카드를 꺼낸다.
	wordCard = wordCardBinder.TakeOut(wordCardLink);
	cout << wordCard.GetSpellings() << ", "
		<< wordCard.GetPartOfSpeech() << ", "
		<< wordCard.GetMeanings() << ", "
		<< wordCard.GetExample() << endl;
	//36. 색인철의 색인에서 단어카드를 꺼낸다.
	indexLink = indexBinder.TakeOut(wordCard.GetSpellings()[0], wordCardLink);
	if (indexLink == 0)
	{
		cout << "색인이 지워졌습니다." << endl;
	}
	else
	{
		cout << "색인이름: " << indexLink->GetAlphabet() << endl;
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


	//37. 소멸자
	return 0;
}

//Printf 재귀함수 정의
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
//함수포인터 정의
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