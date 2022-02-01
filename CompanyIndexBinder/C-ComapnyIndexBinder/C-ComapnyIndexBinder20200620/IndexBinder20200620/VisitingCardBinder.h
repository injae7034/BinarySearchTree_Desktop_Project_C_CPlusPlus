#ifndef _VISITINGCARDBINDER_H
#define _VISITINGCARDBINDER_H
#include "LinkedList.h"
typedef signed long int Long;
//typedef enum _boolean { _FALSE = 0, _TRUE = 1 }Boolean;
typedef struct _personal
{
	char name[11];
	char position[8];
	char cellularPhoneNumber[12];
	char emailAddress[32];
}Personal;

typedef struct _company
{
	char name[32];
	char address[64];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[32];
}Company;

typedef struct _visitingCard
{
	Personal personal;
	Company company;
}VisitingCard;

typedef struct _visitingCardBinder
{
	LinkedList visitingCards;
	Long length;
	VisitingCard* current;
}VisitingCardBinder;

void VisitingCardBinder_Create(VisitingCardBinder* visitingCardBinder);
Long Load(VisitingCardBinder* visitingCardBinder);
VisitingCard* VisitingCardBinder_TakeIn(VisitingCardBinder* visitingCardBinder, VisitingCard visitingCard);
void VisitingCardBinder_Find(VisitingCardBinder* visitingCardBinder, char(*name), VisitingCard** (*indexes), Long* count);
VisitingCard* VisitingCardBinder_FindByCompanyName(VisitingCardBinder* visitingCardBinder, char(*companyName));
VisitingCard VisitingCardBinder_TakeOut(VisitingCardBinder* visitingCardBinder, VisitingCard* index);
VisitingCard* VisitingCardBinder_Move(VisitingCardBinder* visitingCardBinder, VisitingCard* index);
VisitingCard* VisitingCardBinder_First(VisitingCardBinder* visitingCardBinder);
VisitingCard* VisitingCardBinder_Previous(VisitingCardBinder* visitingCardBinder);
VisitingCard* VisitingCardBinder_Next(VisitingCardBinder* visitingCardBinder);
VisitingCard* VisitingCardBinder_Last(VisitingCardBinder* visitingCardBinder);
//void Arrange(VisitingCardBinder* visitingCardBinder);
Long Save(VisitingCardBinder* visitingCardBinder);
void VisitingCardBinder_Destroy(VisitingCardBinder* visitingCardBinder);
//함수포인터
int ComparePersoanlNames(void* one, void* other);
int CompareCompanyNames(void* one, void* other);
int CompareVisitingCards(void* one, void* other);

#endif // !_VISITINGCARDBINDER_H


