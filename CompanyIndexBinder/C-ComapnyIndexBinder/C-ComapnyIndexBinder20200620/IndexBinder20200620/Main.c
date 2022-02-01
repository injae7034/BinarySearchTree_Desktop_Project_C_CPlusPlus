#include "VisitingCardBinder.h"
#include "IndexBinder.h"
#include "Index.h"
#include<stdio.h>//printf
#include<stdlib.h>//free
#include<string.h>//strcpy
#include<stddef.h>//size
#pragma warning(disable:4996)

void IndexBinderArrange_Printf(BinaryNode* node);

int main(int argc, char* argv[])
{
	VisitingCardBinder visitingCardBinder;
	IndexBinder indexBinder;
	VisitingCard* visitingCardLink;
	Index* indexLink;
	Long i;
	Long j;
	Long count;
	VisitingCard* (*visitingCardLinks);
	Index(*indexes);
	VisitingCard visitingCard;
	VisitingCard first = { {"정길동", "대리", "01024367967", "Jung@naver.com"}, {"삼성전자",
						 "경기도 용인", "0313692447", "0312234567", "SamSung.com"} };
	VisitingCard second = { {"홍길동", "대리", "01036937248", "Hong@naver.com"}, {"신한은행",
						 "서울시 중구", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard third = { {"차길동", "과장", "01036937789", "Cha@naver.com"}, {"엘지전자",
						 "경기도 파주", "0313392468", "0313392467", "LG.com"} };
	VisitingCard fourth = { {"김길동", "부장", "010197914429", "Kim@naver.com"}, {"현대자동차",
						 "울산시 북구", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard fifth = { {"나길동", "사원", "01044792918", "Na@naver.com"}, {"신한은행",
						 "서울시 중구", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard sixth = { {"신길동", "과장", "01099873962", "Shin@naver.com"}, {"신한은행",
						 "서울시 중구", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard seventh = { {"강길동", "부장", "01040677981", "Kang@naver.com"}, {"신한은행",
						   "서울시 중구", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard eighth = { {"봉길동", "차장", "01066894429", "Bong@naver.com"}, {"엘지전자",
						  "경기도 파주", "0313392468", "0313392467", "LG.com"} };
	VisitingCard nineth = { {"홍길동", "과장", "01098123469", "Hong2@naver.com"}, {"현대자동차",
						  "울산시 북구", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard tenth = { {"조길동", "사장", "01012997651", "Jo@naver.com"}, {"대한항공",
						 "서울시 종로구", "022742195", "022742194", "KoreanAir.com"} };
	VisitingCard eleventh = { {"홍길동", "부사장", "01034998871", "Hong3@naver.com"}, {"아시아나항공",
						  "서울시 중구", "023418901", "023418902", "AsianaAir.com"} };
	VisitingCard twelveth = { {"박길동", "전무", "01098744320", "Park@naver.com"}, {"현대자동차",
						"울산시 북구", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard thirteenth = { {"허길동", "부장", "01033692491", "Heo@naver.com"}, {"대한항공",
						 "서울시 종로구", "022742195", "022742194", "KoreanAir.com"} };

	//메인테스트시나리오
	//1. 명함철을 만든다.(VisitingCardBinder_Create)
	VisitingCardBinder_Create(&visitingCardBinder);
	//2. 색인철을 만든다.(IndexBinder_Create)
	IndexBinder_Create(&indexBinder);
	//3. 명함철에 명함을 끼운다(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, first);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//4. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//5. 명함철에서 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//6. 색인철의 색인에서 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name, visitingCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	//7. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, second);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//8. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//9. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, third);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//10. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//11. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, fourth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//12. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//13. 색인철에서 현대자동차를 찾는다.(IndexBinder_Find)
	indexLink = IndexBinder_Find(&indexBinder, "현대자동차");
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//14. 명함철에서 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//15. 색인철의 색인에서 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name, visitingCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	//16. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, fifth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//17. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//18. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, sixth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//19. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//20. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, seventh);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//21. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//22. 명함철에서 신길동을 찾는다.(VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "신길동", &visitingCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLinks[i]->personal.name,
			visitingCardLinks[i]->personal.position, visitingCardLinks[i]->personal.cellularPhoneNumber,
			visitingCardLinks[i]->personal.emailAddress, visitingCardLinks[i]->company.name,
			visitingCardLinks[i]->company.address, visitingCardLinks[i]->company.telephoneNumber,
			visitingCardLinks[i]->company.faxNumber, visitingCardLinks[i]->company.url);
		i++;
	}
	printf("\n");
	//23. 명함철에서 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count-1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//24. 색인철의 색인에서 신길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	if (visitingCardLinks != NULL)
	{
		free(visitingCardLinks);
	}
	//25. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, eighth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//26. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//27. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, nineth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//28. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//29. 명함철에서 처음으로 이동한다.(VisitingCardBinder_First)
	visitingCardLink = VisitingCardBinder_First(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//30. 명함철에서 이전으로 이동한다.(VisitingCardBinder_Previous)
	visitingCardLink = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//31. 명함철에서 다음으로 이동한다.(VisitingCardBinder_Next)
	visitingCardLink = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//32. 명함철에서 마지막으로 이동한다.(VisitingCardBinder_Last)
	visitingCardLink = VisitingCardBinder_Last(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//33. 명함철에서 다음으로 이동한다.(VisitingCardBinder_Next)
	visitingCardLink = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//34. 명함철에서 이전으로 이동한다.(VisitingCardBinder_Previous)
	visitingCardLink = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//35. 명함철에서 회사이름(엘지전자)로 찾는다.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "엘지전자");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//36. 명함철에서 해당위치로 움직인다.(VisitingCardBinder_Move)
	visitingCardLink = VisitingCardBinder_Move(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//37. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder,tenth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//38. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//39. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, eleventh);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//40. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//41. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, twelveth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//42. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	//43. 명함철에 명함을 끼운다.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, thirteenth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//44. 색인철의 색인에 명함을 끼운다.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("색인이름:%s\n", indexLink->companyName);
	i = 0;
	while (i < indexLink->length)
	{
		visitingCardLink = Index_GetAt(indexLink, i);
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
			visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
			visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
			visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
			visitingCardLink->company.faxNumber, visitingCardLink->company.url);
		i++;
	}
	printf("\n");
	printf("목록 만들기\n");
	//45. 색인리스트를 만든다.(IndexBinder_MakeList)
	IndexBinder_MakeList(&indexBinder, &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("색인이름: %s\n", indexes[i].companyName);
		j = 0;
		while (j < indexes[i].length)
		{
			visitingCardLink = Index_GetAt(indexes + i, j);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			j++;
		}
		i++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	printf("색인철 정렬하기\n");
	//46. 색인철의 색인들과 명람들을 정리한다.(IndexBinder_Arrange)
	IndexBinder_Arrange(&indexBinder);
	IndexBinderArrange_Printf(indexBinder.indexes.root);
	printf("\n");
	//47. 명함철에서 홍길동을 찾는다. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "홍길동", &visitingCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLinks[i]->personal.name,
			visitingCardLinks[i]->personal.position, visitingCardLinks[i]->personal.cellularPhoneNumber,
			visitingCardLinks[i]->personal.emailAddress, visitingCardLinks[i]->company.name,
			visitingCardLinks[i]->company.address, visitingCardLinks[i]->company.telephoneNumber,
			visitingCardLinks[i]->company.faxNumber, visitingCardLinks[i]->company.url);
		i++;
	}
	printf("\n");
	//48. 명함철에서 세번째 홍길동 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//49. 색인철의 색인에서 세번째 홍길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	//50. 명함철에서 세번째 홍길동 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 2]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//51. 색인철의 색인에서 세번째 홍길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 2]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	if (visitingCardLinks != NULL)
	{
		free(visitingCardLinks);
	}
	//52. 명함철에서 회사이름(현대자동차)로 찾는다.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "현대자동차");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//53. 명함철에서 현대자동차 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//54. 색인철의 색인에서 현대자동차 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	//55. 명함철에서 봉길동을 찾는다. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "봉길동", &visitingCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLinks[i]->personal.name,
			visitingCardLinks[i]->personal.position, visitingCardLinks[i]->personal.cellularPhoneNumber,
			visitingCardLinks[i]->personal.emailAddress, visitingCardLinks[i]->company.name,
			visitingCardLinks[i]->company.address, visitingCardLinks[i]->company.telephoneNumber,
			visitingCardLinks[i]->company.faxNumber, visitingCardLinks[i]->company.url);
		i++;
	}
	printf("\n");
	//56. 명함철에서 봉길동 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//57. 색인철의 색인에서 봉길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	if (visitingCardLinks != NULL)
	{
		free(visitingCardLinks);
	}
	printf("\n");
	//58. 명함철에서 차길동을 찾는다. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "차길동", &visitingCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLinks[i]->personal.name,
			visitingCardLinks[i]->personal.position, visitingCardLinks[i]->personal.cellularPhoneNumber,
			visitingCardLinks[i]->personal.emailAddress, visitingCardLinks[i]->company.name,
			visitingCardLinks[i]->company.address, visitingCardLinks[i]->company.telephoneNumber,
			visitingCardLinks[i]->company.faxNumber, visitingCardLinks[i]->company.url);
		i++;
	}
	printf("\n");
	//59. 명함철에서 차길동 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//60. 색인철의 색인에서 차길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	if (visitingCardLinks != NULL)
	{
		free(visitingCardLinks);
	}
	printf("\n");
	//61. 명함철에서 회사이름(신한은행)으로 찾는다.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "신한은행");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//62. 명함철에서 신한은행 첫번째 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//63. 색인철의 색인에서 첫번째 신한은행 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLink);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	printf("\n");
	//64. 명함철에서 허길동의 명함을 찾는다.(VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "허길동", &visitingCardLinks, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLinks[i]->personal.name,
			visitingCardLinks[i]->personal.position, visitingCardLinks[i]->personal.cellularPhoneNumber,
			visitingCardLinks[i]->personal.emailAddress, visitingCardLinks[i]->company.name,
			visitingCardLinks[i]->company.address, visitingCardLinks[i]->company.telephoneNumber,
			visitingCardLinks[i]->company.faxNumber, visitingCardLinks[i]->company.url);
		i++;
	}
	printf("\n");
	//65. 명함철에서 허길동 명함을 꺼낸다.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//66. 색인철의 색인에서 허길동의 명함을 꺼낸다.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("색인이 지워졌습니다.\n");
	}
	else
	{
		printf("색인이름: %s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
	}
	if (visitingCardLinks != NULL)
	{
		free(visitingCardLinks);
	}
	printf("\n");
	//67. 색인철을 없앤다.(IndexBinder_Destroy)
	IndexBinder_Destroy(&indexBinder);
	//68. 명함철을 없앤다.(VisitingCardBinder_Destroy)
	VisitingCardBinder_Destroy(&visitingCardBinder);

	return 0;
}

//Arrage 출력용 재귀함수
void IndexBinderArrange_Printf(BinaryNode* node)
{
	VisitingCard* visitingCardLink;
	Long i;
	Index* indexLink;

	if (node != NULL)
	{
		indexLink = (Index*)(node + 1);
		printf("%s\n", indexLink->companyName);
		i = 0;
		while (i < indexLink->length)
		{
			visitingCardLink = Index_GetAt(indexLink, i);
			printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
				visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
				visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
				visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
				visitingCardLink->company.faxNumber, visitingCardLink->company.url);
			i++;
		}
		IndexBinderArrange_Printf(node->left);
		IndexBinderArrange_Printf(node->right);
	}
}
