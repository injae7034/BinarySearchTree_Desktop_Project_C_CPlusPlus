#ifndef _WORDCARDBINDER_H
#define _WORDCARDBINDER_H
#include "LinkedList.h"

typedef signed long int Long;
//typedef enum _boolean { _FALSE = 0, _TRUE = 1 }Boolean;
typedef struct _word
{
	char spellings[64];
	char partOfSpeech[8];
	char meanings[32];
	char example[128];
}Word;
//typedef struct _wordCard WordCard;
typedef struct _wordCard
{
	Word word;
	//WordCard* next;
}WordCard;
typedef struct _wordCardBinder
{
	LinkedList wordCards;
	Long length;
	WordCard* current;
}WordCardBinder;

void WordCardBinder_Create(WordCardBinder* wordCardBinder);
Long WordCardBinder_Load(WordCardBinder* wordCardBinder);
WordCard* WordCardBinder_TakeIn(WordCardBinder* wordCardBinder, WordCard wordCard);
void WordCardBinder_FindBySpellings(WordCardBinder* wordCardBinder, char(*spellings), WordCard** (*indexes), Long* count);
void WordCardBinder_FindByMeanings(WordCardBinder* wordCardBinder, char(*meanings), WordCard** (*indexes), Long* count);
WordCard WordCardBinder_TakeOut(WordCardBinder* wordCardBinder, WordCard* index);
//void Arrange(WordCardBinder* wordCardBinder);
WordCard* WordCardBinder_Move(WordCardBinder* wordCardBinder, WordCard* index);
WordCard* WordCardBinder_First(WordCardBinder* wordCardBinder);
WordCard* WordCardBinder_Previous(WordCardBinder* wordCardBinder);
WordCard* WordCardBinder_Next(WordCardBinder* wordCardBinder);
WordCard* WordCardBinder_Last(WordCardBinder* wordCardBinder);
Long WordCardBinder_Save(WordCardBinder* wordCardBinder);
void WordCardBinder_Destroy(WordCardBinder* wordCardBinder);

int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWordCards(void* one, void* other);

#endif // !_WORDCARDBINDER_H

