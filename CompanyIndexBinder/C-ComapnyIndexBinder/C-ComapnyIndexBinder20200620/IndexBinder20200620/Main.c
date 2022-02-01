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
	VisitingCard first = { {"���浿", "�븮", "01024367967", "Jung@naver.com"}, {"�Ｚ����",
						 "��⵵ ����", "0313692447", "0312234567", "SamSung.com"} };
	VisitingCard second = { {"ȫ�浿", "�븮", "01036937248", "Hong@naver.com"}, {"��������",
						 "����� �߱�", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard third = { {"���浿", "����", "01036937789", "Cha@naver.com"}, {"��������",
						 "��⵵ ����", "0313392468", "0313392467", "LG.com"} };
	VisitingCard fourth = { {"��浿", "����", "010197914429", "Kim@naver.com"}, {"�����ڵ���",
						 "���� �ϱ�", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard fifth = { {"���浿", "���", "01044792918", "Na@naver.com"}, {"��������",
						 "����� �߱�", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard sixth = { {"�ű浿", "����", "01099873962", "Shin@naver.com"}, {"��������",
						 "����� �߱�", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard seventh = { {"���浿", "����", "01040677981", "Kang@naver.com"}, {"��������",
						   "����� �߱�", "023347414", "023347415", "ShinHan.com"} };
	VisitingCard eighth = { {"���浿", "����", "01066894429", "Bong@naver.com"}, {"��������",
						  "��⵵ ����", "0313392468", "0313392467", "LG.com"} };
	VisitingCard nineth = { {"ȫ�浿", "����", "01098123469", "Hong2@naver.com"}, {"�����ڵ���",
						  "���� �ϱ�", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard tenth = { {"���浿", "����", "01012997651", "Jo@naver.com"}, {"�����װ�",
						 "����� ���α�", "022742195", "022742194", "KoreanAir.com"} };
	VisitingCard eleventh = { {"ȫ�浿", "�λ���", "01034998871", "Hong3@naver.com"}, {"�ƽþƳ��װ�",
						  "����� �߱�", "023418901", "023418902", "AsianaAir.com"} };
	VisitingCard twelveth = { {"�ڱ浿", "����", "01098744320", "Park@naver.com"}, {"�����ڵ���",
						"���� �ϱ�", "0524379702", "0524379701", "Hyundai.com"} };
	VisitingCard thirteenth = { {"��浿", "����", "01033692491", "Heo@naver.com"}, {"�����װ�",
						 "����� ���α�", "022742195", "022742194", "KoreanAir.com"} };

	//�����׽�Ʈ�ó�����
	//1. ����ö�� �����.(VisitingCardBinder_Create)
	VisitingCardBinder_Create(&visitingCardBinder);
	//2. ����ö�� �����.(IndexBinder_Create)
	IndexBinder_Create(&indexBinder);
	//3. ����ö�� ������ �����(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, first);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//4. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//5. ����ö���� ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//6. ����ö�� ���ο��� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name, visitingCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//7. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, second);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//8. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//9. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, third);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//10. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//11. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, fourth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//12. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//13. ����ö���� �����ڵ����� ã�´�.(IndexBinder_Find)
	indexLink = IndexBinder_Find(&indexBinder, "�����ڵ���");
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//14. ����ö���� ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//15. ����ö�� ���ο��� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name, visitingCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//16. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, fifth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//17. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//18. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, sixth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//19. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//20. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, seventh);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//21. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//22. ����ö���� �ű浿�� ã�´�.(VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "�ű浿", &visitingCardLinks, &count);
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
	//23. ����ö���� ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count-1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//24. ����ö�� ���ο��� �ű浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//25. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, eighth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//26. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//27. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, nineth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//28. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//29. ����ö���� ó������ �̵��Ѵ�.(VisitingCardBinder_First)
	visitingCardLink = VisitingCardBinder_First(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//30. ����ö���� �������� �̵��Ѵ�.(VisitingCardBinder_Previous)
	visitingCardLink = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//31. ����ö���� �������� �̵��Ѵ�.(VisitingCardBinder_Next)
	visitingCardLink = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//32. ����ö���� ���������� �̵��Ѵ�.(VisitingCardBinder_Last)
	visitingCardLink = VisitingCardBinder_Last(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//33. ����ö���� �������� �̵��Ѵ�.(VisitingCardBinder_Next)
	visitingCardLink = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	//34. ����ö���� �������� �̵��Ѵ�.(VisitingCardBinder_Previous)
	visitingCardLink = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//35. ����ö���� ȸ���̸�(��������)�� ã�´�.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "��������");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//36. ����ö���� �ش���ġ�� �����δ�.(VisitingCardBinder_Move)
	visitingCardLink = VisitingCardBinder_Move(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//37. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder,tenth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//38. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//39. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, eleventh);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//40. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//41. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, twelveth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//42. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	//43. ����ö�� ������ �����.(VisitingCardBinder_TakeIn)
	visitingCardLink = VisitingCardBinder_TakeIn(&visitingCardBinder, thirteenth);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//44. ����ö�� ���ο� ������ �����.(IndexBinder_TakeIn)
	indexLink = IndexBinder_TakeIn(&indexBinder, visitingCardLink);
	printf("�����̸�:%s\n", indexLink->companyName);
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
	printf("��� �����\n");
	//45. ���θ���Ʈ�� �����.(IndexBinder_MakeList)
	IndexBinder_MakeList(&indexBinder, &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("�����̸�: %s\n", indexes[i].companyName);
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
	printf("����ö �����ϱ�\n");
	//46. ����ö�� ���ε�� ������� �����Ѵ�.(IndexBinder_Arrange)
	IndexBinder_Arrange(&indexBinder);
	IndexBinderArrange_Printf(indexBinder.indexes.root);
	printf("\n");
	//47. ����ö���� ȫ�浿�� ã�´�. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "ȫ�浿", &visitingCardLinks, &count);
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
	//48. ����ö���� ����° ȫ�浿 ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//49. ����ö�� ���ο��� ����° ȫ�浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//50. ����ö���� ����° ȫ�浿 ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 2]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//51. ����ö�� ���ο��� ����° ȫ�浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 2]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//52. ����ö���� ȸ���̸�(�����ڵ���)�� ã�´�.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "�����ڵ���");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//53. ����ö���� �����ڵ��� ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//54. ����ö�� ���ο��� �����ڵ��� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//55. ����ö���� ���浿�� ã�´�. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "���浿", &visitingCardLinks, &count);
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
	//56. ����ö���� ���浿 ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//57. ����ö�� ���ο��� ���浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//58. ����ö���� ���浿�� ã�´�. (VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "���浿", &visitingCardLinks, &count);
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
	//59. ����ö���� ���浿 ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//60. ����ö�� ���ο��� ���浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//61. ����ö���� ȸ���̸�(��������)���� ã�´�.(VisitingCardBinder_FindByCompanyName)
	visitingCardLink = VisitingCardBinder_FindByCompanyName(&visitingCardBinder, "��������");
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCardLink->personal.name,
		visitingCardLink->personal.position, visitingCardLink->personal.cellularPhoneNumber,
		visitingCardLink->personal.emailAddress, visitingCardLink->company.name,
		visitingCardLink->company.address, visitingCardLink->company.telephoneNumber,
		visitingCardLink->company.faxNumber, visitingCardLink->company.url);
	printf("\n");
	//62. ����ö���� �������� ù��° ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLink);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//63. ����ö�� ���ο��� ù��° �������� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLink);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//64. ����ö���� ��浿�� ������ ã�´�.(VisitingCardBinder_Find)
	VisitingCardBinder_Find(&visitingCardBinder, "��浿", &visitingCardLinks, &count);
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
	//65. ����ö���� ��浿 ������ ������.(VisitingCardBinder_TakeOut)
	visitingCard = VisitingCardBinder_TakeOut(&visitingCardBinder, visitingCardLinks[count - 1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name,
		visitingCard.personal.position, visitingCard.personal.cellularPhoneNumber,
		visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber,
		visitingCard.company.faxNumber, visitingCard.company.url);
	printf("\n");
	//66. ����ö�� ���ο��� ��浿�� ������ ������.(IndexBinder_TakeOut)
	indexLink = IndexBinder_TakeOut(&indexBinder, visitingCard.company.name,
		visitingCardLinks[count - 1]);
	if (indexLink == NULL)
	{
		printf("������ ���������ϴ�.\n");
	}
	else
	{
		printf("�����̸�: %s\n", indexLink->companyName);
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
	//67. ����ö�� ���ش�.(IndexBinder_Destroy)
	IndexBinder_Destroy(&indexBinder);
	//68. ����ö�� ���ش�.(VisitingCardBinder_Destroy)
	VisitingCardBinder_Destroy(&visitingCardBinder);

	return 0;
}

//Arrage ��¿� ����Լ�
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
