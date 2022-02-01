#include "WordCardBinder.h"
#include "IndexBinder.h"
#include "Index.h"
#include<stdio.h>//printf
#include<stdlib.h>//free

void IndexBinderArrange_Printf(BinaryNode* node);

int main(int argc, char* argv[])
{
	WordCardBinder wordCardBinder;
	IndexBinder indexBinder;
	WordCard* wordCardLink;
	WordCard*(*wordCardLinks);
	WordCard wordCard;
	Long count;
	Long i;
	Long j;
	Index* indexLink;
	Index(*indexes);
	WordCard first = { {"apple", "명사", "사과", "Apples are sweet."} };
	WordCard second = { {"kind", "형용사", "친절한", "She is so kind."} };
	WordCard third = { {"keep", "동사", "계속~하다", "I will keep practicing it."} };
	WordCard fourth = { {"kind", "명사", "종류", "We serve two kinds of tea."} };
	WordCard fifth = { {"very", "부사", "매우", "He is very tall."} };
	WordCard sixth = { {"extremely", "부사", "매우", "The mountain is extremely high."} };

	//메인테스트시나리오
	//1. 단어카드철을 만든다.
	WordCardBinder_Create(&wordCardBinder);
	//2. 색인철을 만든다.
	IndexBinder_Create(&indexBinder);
	//WordCardBinder_Load
	WordCardBinder_Load(&wordCardBinder);
	//3. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, first);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//4. 색인철의 색인에 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//5. 단어카드철에서 단어카드를 꺼낸다.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//6. 색인철의 색인에서 단어카드를 꺼낸다.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %c\n", indexLink->alphabet);
		i = 0;
		while (i < indexLink->length)
		{
			wordCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
				wordCardLink->word.meanings, wordCardLink->word.example);
			i++;
		}
	}
	printf("\n");
	//7. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, second);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//8. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//9. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, third);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//10. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//11. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, first);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//12. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//13. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, fourth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//14. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//15. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, fifth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//16. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//17. 단어카드철에서 단어카드를 끼운다.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, sixth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//18. 색인철의 색인에서 단어카드를 끼운다.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//19. 단어카드철에서 처음으로 이동한다.
	wordCardLink = WordCardBinder_First(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//20. 단어카드철에서 이전으로 이동한다.
	wordCardLink = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//21. 단어카드철에서 다음으로 이동한다.
	wordCardLink = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//22. 단어카드철에서 마지막으로 이동한다.
	wordCardLink = WordCardBinder_Last(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//23. 단어카드철에서 다음으로 이동한다.
	wordCardLink = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//24. 단어카드철에서 이전으로 이동한다.
	wordCardLink = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	printf("\n");
	//25. 색인철에서 색인리스트를 만든다.
	IndexBinder_MakeList(&indexBinder, &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("색인이름:%c\n", indexes[i].alphabet);
		j = 0;
		while (j < indexes[i].length)
		{
			wordCardLink = Index_GetAt(indexes + i, j);
			printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
				wordCardLink->word.meanings, wordCardLink->word.example);
			j++;
		}
		i++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//26. 색인철에서 정리한다.
	IndexBinder_Arrange(&indexBinder);
	IndexBinderArrange_Printf(indexBinder.indexes.root);
	printf("\n");
	//27. 단어카드철에서 kind를 찾는다.
	WordCardBinder_FindBySpellings(&wordCardBinder, "kind", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", wordCardLinks[i]->word.spellings, wordCardLinks[i]->word.partOfSpeech,
			wordCardLinks[i]->word.meanings, wordCardLinks[i]->word.example);
		i++;
	}
	printf("\n");
	//28. 단어카드철에서 찾은 kind 중에서 두번째 kind를 꺼낸다.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLinks[count - 1]);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//29. 색인철의 색인에서 두번째 kind를 꺼낸다.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %c\n", indexLink->alphabet);
		i = 0;
		while (i < indexLink->length)
		{
			wordCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
				wordCardLink->word.meanings, wordCardLink->word.example);
			i++;
		}
	}
	printf("\n");
	if (wordCardLinks != NULL)
	{
		free(wordCardLinks);
	}
	//30. 단어카드철에서 "매우"를 찾는다.
	WordCardBinder_FindByMeanings(&wordCardBinder, "매우", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", wordCardLinks[i]->word.spellings, wordCardLinks[i]->word.partOfSpeech,
			wordCardLinks[i]->word.meanings, wordCardLinks[i]->word.example);
		i++;
	}
	printf("\n");
	//31. 단어카드철에서 찾은 "매우"중에서 첫번째 "매우"를 꺼낸다.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLinks[0]);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//32. 색인철의 색인에서 첫번째 "매우"를 꺼낸다.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLinks[0]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %c\n", indexLink->alphabet);
		i = 0;
		while (i < indexLink->length)
		{
			wordCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
				wordCardLink->word.meanings, wordCardLink->word.example);
			i++;
		}
	}
	printf("\n");
	if (wordCardLinks != NULL)
	{
		free(wordCardLinks);
	}
	//33. 색인철에서 'k'를 찾는다.
	indexLink = IndexBinder_Find(&indexBinder, 'k');
	printf("색인이름: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//34. 단어카드청에서 'k'의 색인의 첫번째 단어카드로 이동한다.
	wordCardLink = Index_GetAt(indexLink, 0);
	wordCardLink = WordCardBinder_Move(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	printf("\n");
	//35. 단어카드철에서 현재 단어카드를 꺼낸다.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//36. 색인철의 색인에서 현재 단어카드를 꺼낸다.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %c\n", indexLink->alphabet);
		i = 0;
		while (i < indexLink->length)
		{
			wordCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
				wordCardLink->word.meanings, wordCardLink->word.example);
			i++;
		}
	}
	printf("\n");
	//WordCardBinder_Save
	WordCardBinder_Save(&wordCardBinder);
	//37. 색인철을 없앤다.
	IndexBinder_Destroy(&indexBinder);
	//38. 단어카드철을 없앤다.
	WordCardBinder_Destroy(&wordCardBinder);

	return 0;
}

//Arrange 출력용 재귀함수
//IndexBinderArrange_Printf
void IndexBinderArrange_Printf(BinaryNode* node)
{
	WordCard* wordCard;
	Long i;
	Index* index;

	if (node != NULL)
	{
		index = (Index*)(node + 1);
		printf("%c\n", index->alphabet);
		i = 0;
		while (i < index->length)
		{
			wordCard = Index_GetAt(index, i);
			printf("%s %s %s %s\n", wordCard->word.spellings, wordCard->word.partOfSpeech,
				wordCard->word.meanings, wordCard->word.example);
			i++;
		}
		IndexBinderArrange_Printf(node->left);
		IndexBinderArrange_Printf(node->right);
	}
}

