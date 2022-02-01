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
	WordCard first = { {"apple", "���", "���", "Apples are sweet."} };
	WordCard second = { {"kind", "�����", "ģ����", "She is so kind."} };
	WordCard third = { {"keep", "����", "���~�ϴ�", "I will keep practicing it."} };
	WordCard fourth = { {"kind", "���", "����", "We serve two kinds of tea."} };
	WordCard fifth = { {"very", "�λ�", "�ſ�", "He is very tall."} };
	WordCard sixth = { {"extremely", "�λ�", "�ſ�", "The mountain is extremely high."} };

	//�����׽�Ʈ�ó�����
	//1. �ܾ�ī��ö�� �����.
	WordCardBinder_Create(&wordCardBinder);
	//2. ����ö�� �����.
	IndexBinder_Create(&indexBinder);
	//WordCardBinder_Load
	WordCardBinder_Load(&wordCardBinder);
	//3. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, first);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//4. ����ö�� ���ο� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//5. �ܾ�ī��ö���� �ܾ�ī�带 ������.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//6. ����ö�� ���ο��� �ܾ�ī�带 ������.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %c\n", indexLink->alphabet);
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
	//7. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, second);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//8. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//9. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, third);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//10. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//11. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, first);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//12. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//13. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, fourth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//14. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//15. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, fifth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//16. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//17. �ܾ�ī��ö���� �ܾ�ī�带 �����.
	wordCardLink = WordCardBinder_TakeIn(&wordCardBinder, sixth);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//18. ����ö�� ���ο��� �ܾ�ī�带 �����.
	indexLink = IndexBinder_TakeIn(&indexBinder, wordCardLink);
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//19. �ܾ�ī��ö���� ó������ �̵��Ѵ�.
	wordCardLink = WordCardBinder_First(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//20. �ܾ�ī��ö���� �������� �̵��Ѵ�.
	wordCardLink = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//21. �ܾ�ī��ö���� �������� �̵��Ѵ�.
	wordCardLink = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//22. �ܾ�ī��ö���� ���������� �̵��Ѵ�.
	wordCardLink = WordCardBinder_Last(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//23. �ܾ�ī��ö���� �������� �̵��Ѵ�.
	wordCardLink = WordCardBinder_Next(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	//24. �ܾ�ī��ö���� �������� �̵��Ѵ�.
	wordCardLink = WordCardBinder_Previous(&wordCardBinder);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	printf("\n");
	//25. ����ö���� ���θ���Ʈ�� �����.
	IndexBinder_MakeList(&indexBinder, &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("�����̸�:%c\n", indexes[i].alphabet);
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
	//26. ����ö���� �����Ѵ�.
	IndexBinder_Arrange(&indexBinder);
	IndexBinderArrange_Printf(indexBinder.indexes.root);
	printf("\n");
	//27. �ܾ�ī��ö���� kind�� ã�´�.
	WordCardBinder_FindBySpellings(&wordCardBinder, "kind", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", wordCardLinks[i]->word.spellings, wordCardLinks[i]->word.partOfSpeech,
			wordCardLinks[i]->word.meanings, wordCardLinks[i]->word.example);
		i++;
	}
	printf("\n");
	//28. �ܾ�ī��ö���� ã�� kind �߿��� �ι�° kind�� ������.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLinks[count - 1]);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//29. ����ö�� ���ο��� �ι�° kind�� ������.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %c\n", indexLink->alphabet);
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
	//30. �ܾ�ī��ö���� "�ſ�"�� ã�´�.
	WordCardBinder_FindByMeanings(&wordCardBinder, "�ſ�", &wordCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", wordCardLinks[i]->word.spellings, wordCardLinks[i]->word.partOfSpeech,
			wordCardLinks[i]->word.meanings, wordCardLinks[i]->word.example);
		i++;
	}
	printf("\n");
	//31. �ܾ�ī��ö���� ã�� "�ſ�"�߿��� ù��° "�ſ�"�� ������.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLinks[0]);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//32. ����ö�� ���ο��� ù��° "�ſ�"�� ������.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLinks[0]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %c\n", indexLink->alphabet);
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
	//33. ����ö���� 'k'�� ã�´�.
	indexLink = IndexBinder_Find(&indexBinder, 'k');
	printf("�����̸�: %c\n", indexLink->alphabet);
	i = 0;
	while (i < indexLink->length)
	{
		wordCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
			wordCardLink->word.meanings, wordCardLink->word.example);
		i++;
	}
	printf("\n");
	//34. �ܾ�ī��û���� 'k'�� ������ ù��° �ܾ�ī��� �̵��Ѵ�.
	wordCardLink = Index_GetAt(indexLink, 0);
	wordCardLink = WordCardBinder_Move(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCardLink->word.spellings, wordCardLink->word.partOfSpeech,
		wordCardLink->word.meanings, wordCardLink->word.example);
	printf("\n");
	//35. �ܾ�ī��ö���� ���� �ܾ�ī�带 ������.
	wordCard = WordCardBinder_TakeOut(&wordCardBinder, wordCardLink);
	printf("%s %s %s %s\n", wordCard.word.spellings, wordCard.word.partOfSpeech, wordCard.word.meanings,
		wordCard.word.example);
	//36. ����ö�� ���ο��� ���� �ܾ�ī�带 ������.
	indexLink = IndexBinder_TakeOut(&indexBinder, wordCard.word.spellings[0], wordCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %c\n", indexLink->alphabet);
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
	//37. ����ö�� ���ش�.
	IndexBinder_Destroy(&indexBinder);
	//38. �ܾ�ī��ö�� ���ش�.
	WordCardBinder_Destroy(&wordCardBinder);

	return 0;
}

//Arrange ��¿� ����Լ�
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

