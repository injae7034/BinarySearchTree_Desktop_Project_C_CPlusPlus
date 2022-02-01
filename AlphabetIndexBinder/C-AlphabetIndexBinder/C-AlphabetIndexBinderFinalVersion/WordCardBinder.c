#include "WordCardBinder.h"
#include<stdio.h>//printf
#include<stdlib.h>//calloc, malloc, free
#include<string.h>//strcmp, strcpy
#pragma warning(disable:4996)

#if 0
int main(int argc, char* argv[])
{
	WordCardBinder wordCardBinder;
	WordCard* index;
	WordCard* (*indexes);
	Long count;
	Long i;
	//WordCard* previous = NULL;
	WordCard wordCard;
	WordCard first = { {"apple", "명사", "사과", "Apples are sweet."}};
	WordCard second = { {"kind", "형용사", "친절한", "She is so kind."}};
	WordCard third = { {"flower", "명사", "꽃", "The flowers are beautiful."}};
	WordCard fourth = { {"very", "부사", "매우", "He is very tall."}};
	WordCard fifth = { {"banana", "명사", "바나나", "A banana is very sweet."}};
	WordCard sixth = { {"coffee", "명사", "커피", "This coffee is good."}};
	WordCard seventh = { {"kind", "명사", "종류", "We serve two kinds of tea."}};

	//메인테스트 시나리오
	//1. 단어카드철을 만든다.
	WordCardBinder_Create(&wordCardBinder);
	//Load
	Load(&wordCardBinder);
	//2. 단어카드(apple, 명사, 사과, Apples are sweet.)을 끼운다.
	index = TakeIn(&wordCardBinder, first);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	printf("\n");
	//3. 단어카드를 꺼낸다.
	wordCard = TakeOut(&wordCardBinder, index);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	printf("\n");
	//4. 단어카드(kind, 형용사, 친절한, She is so kind.)를 끼운다.
	index = TakeIn(&wordCardBinder, second);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//5. 단어카드(flower, 명사, 꽃, The flowers are beautiful.)을 끼운다.
	index = TakeIn(&wordCardBinder, third);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//6. 단어카드(very, 부사, 매우, He is very tall.)을 끼운다.
	index = TakeIn(&wordCardBinder, fourth);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//7 단어카드(banana, 명사, 바나나, A banana is very sweet.)을 끼운다.
	index = TakeIn(&wordCardBinder, fifth);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	printf("\n");
	//8. 네번째 명함을 꺼낸다.
	wordCard = TakeOut(&wordCardBinder, index);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	printf("\n");
	//9. 단어카드(coffee, 명사, 커피, This coffee is good.)을 끼운다.
	index = TakeIn(&wordCardBinder, sixth);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//10. 단어카드(kind, 명사, 종류, We serve two kinds of tea.)를 끼운다.
	index = TakeIn(&wordCardBinder, seventh);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//11. 단어카드(extremely,  부사, 매우, "The mountain is extremely high.)를 끼운다.
	strcpy(wordCard.word.spellings, "extremely");
	strcpy(wordCard.word.partOfSpeech, "부사");
	strcpy(wordCard.word.meanings, "매우");
	strcpy(wordCard.word.example, "The mountain is extremely high.");
	index = TakeIn(&wordCardBinder, wordCard);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	printf("\n");
	//12. coffee를 찾는다.
	FindBySpellings(&wordCardBinder, "coffee", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", indexes[i]->word.spellings, indexes[i]->word.partOfSpeech, 
			indexes[i]->word.meanings, indexes[i]->word.example);
		i++;
	}
	printf("\n");
	//13. coffee 단어카드를 꺼낸다.
	wordCard = TakeOut(&wordCardBinder, indexes[count - 1]);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//14. 꽃을 찾는다.
	FindByMeanings(&wordCardBinder, "꽃", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", indexes[i]->word.meanings, indexes[i]->word.spellings, 
			indexes[i]->word.partOfSpeech, indexes[i]->word.example);
		i++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//15. 단어카드(smell,  명사, 냄새, "The smell is good.)를 끼운다.
	strcpy(wordCard.word.spellings, "smell");
	strcpy(wordCard.word.partOfSpeech, "명사");
	strcpy(wordCard.word.meanings, "냄새");
	strcpy(wordCard.word.example, "The smell is good.");
	index = TakeIn(&wordCardBinder, wordCard);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	printf("\n");
	//16. kind를 찾는다.
	FindBySpellings(&wordCardBinder, "kind", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", indexes[i]->word.spellings, indexes[i]->word.partOfSpeech,
			indexes[i]->word.meanings, indexes[i]->word.example);
		i++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//17. 매우를 찾는다.
	FindByMeanings(&wordCardBinder, "매우", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", indexes[i]->word.meanings, indexes[i]->word.spellings,
			indexes[i]->word.partOfSpeech, indexes[i]->word.example);
		i++;
	}
	//Move
	i = 1;
	index = WordCardBinder_Move(&wordCardBinder, indexes[i]);
	printf("Move\n");
	printf("%s %s %s %s\n", indexes[i]->word.spellings, indexes[i]->word.partOfSpeech, indexes[i]->word.meanings,
		indexes[i]->word.example);
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//18. 처음으로 이동한다.
	index = WordCardBinder_First(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//19. 이전위치로 이동한다.
	index = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//20. 다음으로 이동한다.
	index = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//21. 마지막으로 이동한다.
	index = WordCardBinder_Last(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//22. 다음으로 이동한다.
	index = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	//23. 이전으로 이동한다.
	index = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
		index->word.example);
	printf("\n");
#if 0
	printf("정리하기전\n");
	index = First(&wordCardBinder);
	while (index != previous)
	{
		printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
			index->word.example);
		previous = index;
		index = Next(&wordCardBinder);
	}
	printf("정리한후\n");
	//24. 철자를 기준으로 정리한다.
	Arrange(&wordCardBinder);
	index = First(&wordCardBinder);
	while (index != previous)
	{
		printf("%s %s %s %s\n", index->word.spellings, index->word.partOfSpeech, index->word.meanings,
			index->word.example);
		previous = index;
		index = Next(&wordCardBinder);
	}
#endif
	//Save
	Save(&wordCardBinder);
	//25. 단어카드철을 없앤다.
	WordCardBinder_Destroy(&wordCardBinder);

	return 0;
}
#endif

//Create
void WordCardBinder_Create(WordCardBinder* wordCardBinder)
{
	//1. 단어카드철을 만든다.
	Create(&wordCardBinder->wordCards);
	wordCardBinder->length = 0;
	wordCardBinder->current = NULL;
	//2. 끝내다.
}

//Load
Long WordCardBinder_Load(WordCardBinder* wordCardBinder)
{
	WordCard wordCard;
	Node* node;
	int flag;
	FILE* file;

	file = fopen("WordCard.dat", "rb");
	if (file != NULL)
	{
		//1.1 철자, 품사, 의미, 예시를 입력받는다.
		flag = fread(&wordCard.word, sizeof(Word), 1, file);
		//1. 파일의 끝이 아닌동안 반복한다.
		while (!feof(file) && flag != 0)
		{
			//1.2 단어카드를 끼운다.
			node = AppendFromTail(&wordCardBinder->wordCards, &wordCard, sizeof(WordCard));
			wordCardBinder->length++;
			wordCardBinder->current = (WordCard*)(node + 1);
			//1.1 철자, 품사, 의미, 예시를 입력받는다.
			flag = fread(&wordCard.word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. 개수를 출력한다.
	return wordCardBinder->length;
	//3. 끝내다.
}

//TakeIn
WordCard* WordCardBinder_TakeIn(WordCardBinder* wordCardBinder, WordCard wordCard)
{
	Node* node;
	
	//1. 단어카드를 입력받는다.
	//2. 단어카드를 끼운다.
	node = AppendFromTail(&wordCardBinder->wordCards, &wordCard, sizeof(WordCard));
	//3. 단어카드철의 개수를 늘린다.
	wordCardBinder->length++;
	//4. 단어카드의 현재 위치를 조정한다.
	wordCardBinder->current = (WordCard*)(node + 1);
	//5. 현재위치를 출력한다.
	return wordCardBinder->current;
	//6. 끝내다.
}

//FindBySpellings
void WordCardBinder_FindBySpellings(WordCardBinder* wordCardBinder, char(*spellings), WordCard** (*indexes), Long* count)
{
	Node* (*nodes);
	Long i = 0;

	*indexes = NULL;
	*count = 0;
	//1. 철자를 입력받는다.
	//2. 단어카드철에 찾고자 하는 단어가 있는지 찾는다.
	LinearSearchDuplicate(&wordCardBinder->wordCards, spellings, &nodes, count, CompareSpellings);
	//3. 찾은 단어가 있으면
	if (*count > 0)
	{
		//3.1  위치들 배열을 만든다.
		*indexes = (WordCard * (*))calloc(*count, sizeof(WordCard*));
	}
	//4. 찾은 단어개수만큼 반복한다.
	while (i < *count)
	{
		//4.1 찾은 단어의 위치를 저장한다.
		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	//5. 할당해제한다.
	if (nodes != NULL)
	{
		free(nodes);
	}
	//6. 위치들과 개수를 출력한다.
	//7. 끝내다.
}

//FindByMeanings
void WordCardBinder_FindByMeanings(WordCardBinder* wordCardBinder, char(*meanings), WordCard** (*indexes), Long* count)
{
	Node* (*nodes);
	Long i = 0;

	*indexes = NULL;
	*count = 0;
	//1. 의미를 입력받는다.
	//2. 단어카드철에 찾고자 하는 단어가 있는지 찾는다.
	LinearSearchDuplicate(&wordCardBinder->wordCards, meanings, &nodes, count, CompareMeanings);
	//3. 찾은 단어가 있으면
	if (*count > 0)
	{
		//3.1  위치들 배열을 만든다.
		*indexes = (WordCard * (*))calloc(*count, sizeof(WordCard*));
	}
	//4. 찾은 단어개수만큼 반복한다.
	while (i < *count)
	{
		//4.1 찾은 단어의 위치를 저장한다.
		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	//5. 할당해제한다.
	if (nodes != NULL)
	{
		free(nodes);
	}
	//6. 위치들과 개수를 출력한다.
	//7. 끝내다.
}

//TakeOut
WordCard WordCardBinder_TakeOut(WordCardBinder* wordCardBinder, WordCard* index)
{
	WordCard wordCard;
	Node* node;

	//1. 위치를 입력받는다.
	//2. 위치를 찾는다.
	node = LinearSearchUnique(&wordCardBinder->wordCards, index, CompareWordCards);
	//3. 단어카드를 꺼낸다.
	GetAt(&wordCardBinder->wordCards, node, &wordCard, sizeof(WordCard));
	//4. 단어카드를 없앤다.
	Delete(&wordCardBinder->wordCards, node);
	//5. 단어카드철에 단어가 남아있으면
	if (wordCardBinder->wordCards.current != NULL)
	{
		wordCardBinder->current = (WordCard*)(wordCardBinder->wordCards.current + 1);
	}
	//6. 단어카드철에 단어가 없으면
	else
	{
		wordCardBinder->current = NULL;
	}
	//7. 단어카드개수를 감소시킨다.
	wordCardBinder->length--;
	//8. 단어카드를 출력한다.
	return wordCard;
	//9. 끝내다.
}

//Move
WordCard* WordCardBinder_Move(WordCardBinder* wordCardBinder, WordCard* index)
{
	Node* node;
	//1. 위치를 입력받는다.
	//2. 현재 위치를 입력받은 위치로 바꾼다.
	node = LinearSearchUnique(&wordCardBinder->wordCards, index, CompareWordCards);
	node = Move(&wordCardBinder->wordCards, node);
	wordCardBinder->current = (WordCard*)(node + 1);
	//3. 현재 위치를 출력한다.
	return wordCardBinder->current;
	//4. 끝내다.
}

//First
WordCard* WordCardBinder_First(WordCardBinder* wordCardBinder)
{
	Node* node;
	//1. 현재 위치를 처음으로 이동시킨다.
	node = First(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return wordCardBinder->current;
	//3. 끝내다.
}

//Previous
WordCard* WordCardBinder_Previous(WordCardBinder* wordCardBinder)
{
	Node* node;
	//1. 현재 위치를 이전으로 이동시킨다.
	node = Previous(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return wordCardBinder->current;
	//3. 끝내다.
}

//Next
WordCard* WordCardBinder_Next(WordCardBinder* wordCardBinder)
{
	Node* node;
	//1. 현재 위치를 다음으로 이동시킨다.
	node = Next(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return wordCardBinder->current;
	//3. 끝내다.
}

//Last
WordCard* WordCardBinder_Last(WordCardBinder* wordCardBinder)
{
	Node* node;
	//1. 현재 위치를 마지막으로 이동시킨다.
	node = Last(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return wordCardBinder->current;
	//3. 끝내다.
}
#if 0
//Arrange
void Arrange(WordCardBinder* wordCardBinder)
{
	WordCard* previous;
	WordCard* next;
	Long i;
	Long j;
	Boolean flag = _TRUE;

	//1. 단어들을 철자를 기준으로 하여 오름차순으로 정렬한다.
	i = wordCardBinder->length - 1;
	while (i >= 1 && flag == _TRUE)
	{
		previous = NULL;
		wordCardBinder->current = wordCardBinder->first;
		next = wordCardBinder->current->next;
		flag = _FALSE;
		j = 1;
		while (j <= i)
		{
			if (strcmp(wordCardBinder->current->word.spellings, next->word.spellings) > 0)
			{
				if (previous != NULL)
				{
					previous->next = next;
				}
				else
				{
					wordCardBinder->first = next;
				}
				wordCardBinder->current->next = next->next;
				next->next = wordCardBinder->current;
				previous = next;
				next = wordCardBinder->current->next;flag = _TRUE;
			}
			else
			{
				previous = wordCardBinder->current;
				wordCardBinder->current = next;
				next = wordCardBinder->current->next;
			}
			j++;
		}
		i--;
	}
	//2. 끝내다.
}
#endif

//Save
Long WordCardBinder_Save(WordCardBinder* wordCardBinder)
{
	WordCard wordCard;
	Node* it;
	Node* previous = NULL;
	FILE* file;

	file = fopen("WordCard.dat", "wb");
	if (file != NULL)
	{
		//1. 단어카드철의 끝이 아닌동안 반복한다.
		it = First(&wordCardBinder->wordCards);
		while (it != previous)
		{
			GetAt(&wordCardBinder->wordCards, it, &wordCard, sizeof(WordCard));
			fwrite(&wordCard.word, sizeof(Word), 1, file);
			previous = it;
			it = Next(&wordCardBinder->wordCards);
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return wordCardBinder->length;
	//3.끝내다.
}

//Destroy
void WordCardBinder_Destroy(WordCardBinder* wordCardBinder)
{
	//1. 단어카드철에서 단어카드를 순서대로 지운다.
	Destroy(&wordCardBinder->wordCards);
	//2. 끝내다.
}

//CompareSpellings
int CompareSpellings(void* one, void* other)
{
	WordCard* one_ = (WordCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->word.spellings, other_);
}

//CompareMeanings
int CompareMeanings(void* one, void* other)
{
	WordCard* one_ = (WordCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->word.meanings, other_);
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

