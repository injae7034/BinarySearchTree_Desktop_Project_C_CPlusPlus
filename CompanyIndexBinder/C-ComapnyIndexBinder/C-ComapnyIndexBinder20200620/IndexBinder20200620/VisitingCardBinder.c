#include "VisitingCardBinder.h"
#include<stdio.h>//printf, feof
#include<stdlib.h>//calloc, malloc, free
#include<string.h>//strcpy, strcmp
#pragma warning(disable:4996)

#if 0
int main(int argc, char* argv[])
{
	VisitingCardBinder visitingCardBinder;
	VisitingCard* index;
	VisitingCard* (*indexes);
	Long count;
	Long i;
	VisitingCard visitingCard;
	VisitingCard first = { {"정길동", "대리", "01024367967", "Jung@naver.com"}, {"삼성전자", "경기도 용인",
	"0313692447", "0312245674", "Samsung.com"}};

	VisitingCard second = { {"홍길동", "대리", "01036937428", "Hong@naver.com"}, {"신한은행", "서울 중구",
	"023798872", "023347713", "Shinhan.com"}};
	VisitingCard third = { {"차길동", "과장", "01036925571", "Cha@naver.com"}, {"엘지전자", "경기도 파주",
	"0312397871", "0313392468", "LG.com"}};
	VisitingCard fourth = { {"김길동", "부장", "01036901127", "Kim@naver.com"}, {"현대자동차", "울산 북구",
	"0524379702", "0524479981", "Hyundai.com"}};
	VisitingCard fifth = { {"나길동", "사원", "01036928827", "Na@naver.com"}, {"SK하이닉스", "경기도 이천",
	"0317789548", "0313692258", "SK.com"}};
	VisitingCard sixth = { {"장길동", "전무", "01044287990", "Jang@naver.com"}, {"노랑풍선", "서울 중구",
	"025578899", "029912970", "Yellow.com"}};

	//메인테스트 시나리오
	//1. 명함철을 만든다.
	VisitingCardBinder_Create(&visitingCardBinder);
	//Load
	Load(&visitingCardBinder);
	//2. 명함철에 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, first);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n");
	//3. 명함철에서 명함을 꺼낸다.
	visitingCard = TakeOut(&visitingCardBinder, index);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name, visitingCard.personal.position,
		visitingCard.personal.cellularPhoneNumber, visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber, visitingCard.company.faxNumber,
		visitingCard.company.url);
	printf("\n");
	//4. 명함철에 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, second);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//5. 명함철에 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, third);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//6. 명함철에 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, fourth);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n");
	//7. 명함철에서 세 번째 명함을 꺼낸다.
	visitingCard = TakeOut(&visitingCardBinder, index);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name, visitingCard.personal.position,
		visitingCard.personal.cellularPhoneNumber, visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber, visitingCard.company.faxNumber,
		visitingCard.company.url);
	printf("\n");
	//8. 명함철에 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, fifth);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//9. 명함철에서 차길동을 찾는다.
	Find(&visitingCardBinder, "차길동", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position,
			indexes[i]->personal.cellularPhoneNumber, indexes[i]->personal.emailAddress, 
			indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, 
			indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}
	printf("\n");
	//10. 차길동의 명함을 명함철에서 꺼낸다.
	visitingCard = TakeOut(&visitingCardBinder, indexes[count-1]);
	printf("%s %s %s %s %s %s %s %s %s\n", visitingCard.personal.name, visitingCard.personal.position,
		visitingCard.personal.cellularPhoneNumber, visitingCard.personal.emailAddress, visitingCard.company.name,
		visitingCard.company.address, visitingCard.company.telephoneNumber, visitingCard.company.faxNumber,
		visitingCard.company.url);
	printf("\n");
	if (indexes != NULL)
	{
		free(indexes);
	}
	//11. 명함철에서 명함을 끼운다.
	index = TakeIn(&visitingCardBinder, sixth);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//12. 명함철에서 명함을 끼운다.
	strcpy(visitingCard.personal.name, "홍길동");
	strcpy(visitingCard.personal.position, "이사");
	strcpy(visitingCard.personal.cellularPhoneNumber, "01098721234");
	strcpy(visitingCard.personal.emailAddress, "Hong@gmail.com");
	strcpy(visitingCard.company.name, "아시아나항공");
	strcpy(visitingCard.company.address, "서울 중구");
	strcpy(visitingCard.company.telephoneNumber, "028711297");
	strcpy(visitingCard.company.faxNumber, "023978819");
	strcpy(visitingCard.company.url, "Asiana.com");
	index = TakeIn(&visitingCardBinder, visitingCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n");
	//13. 명함철에서 홍길동을 찾는다.
	Find(&visitingCardBinder, "홍길동", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position,
			indexes[i]->personal.cellularPhoneNumber, indexes[i]->personal.emailAddress,
			indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber,
			indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}
	printf("\n");
	// 현재 명함의 위치를 바꾼다.
	index = VisitingCardBinder_Move(&visitingCardBinder, indexes[0]);
	printf("%s %s %s %s %s %s %s %s %s\n", indexes[0]->personal.name, indexes[0]->personal.position,
		indexes[0]->personal.cellularPhoneNumber, indexes[0]->personal.emailAddress,
		indexes[0]->company.name, indexes[0]->company.address, indexes[0]->company.telephoneNumber,
		indexes[0]->company.faxNumber, indexes[0]->company.url);
	printf("\n");
	if (indexes != NULL)
	{
		free(indexes);
	}
	//노랑풍선을 찾는다.
	index = FindByCompanyName(&visitingCardBinder, "노랑풍선");
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n");
	//14. 명함철에서 처음으로 이동한다.
	index = VisitingCardBinder_First(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//15. 명함철에서 이전으로 이동한다.
	index = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//16. 명함철에서 다음으로 이동한다.
	index = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//17. 명함철에서 마지막으로 이동한다.
	index = VisitingCardBinder_Last(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//18. 명함철에서 다음으로 이동한다.
	index = VisitingCardBinder_Next(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//19. 명함철에서 이전으로 이동한다.
	index = VisitingCardBinder_Previous(&visitingCardBinder);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
		index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
#if 0
	printf("정리하기전\n");
	//20. 개인의 성명을 기준으로 하여 자모음순으로 명함철을 정리한다.
	index = First(&visitingCardBinder);
	while (index != previous)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
			index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		previous = index;
		index = Next(&visitingCardBinder);
	}
	printf("정리한후\n");
	Arrange(&visitingCardBinder);
	index = First(&visitingCardBinder);
	while (index != previous)
	{
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position,
			index->personal.cellularPhoneNumber, index->personal.emailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		previous = index;
		index = Next(&visitingCardBinder);
	}
#endif
	//Save
	Save(&visitingCardBinder);
	//20. 명함철을 없앤다.
	VisitingCardBinder_Destroy(&visitingCardBinder);

	return 0;
}
#endif
//Create
void VisitingCardBinder_Create(VisitingCardBinder* visitingCardBinder)
{
	//1. 명함을 만든다.
	Create(&visitingCardBinder->visitingCards);
	visitingCardBinder->length = 0;
	visitingCardBinder->current = NULL;
	//2. 끝내다.
}

//Load
Long Load(VisitingCardBinder* visitingCardBinder)
{
	Node* node;
	VisitingCard visitingCard;
	Long i;
	Long index;//회사위치
	int flag;
	FILE* personalFile;
	FILE* companyFile;

	personalFile = fopen("PersonalVisitingCard.dat", "rb");
	companyFile = fopen("CompanyVisitingCard.dat", "rb");
	if (personalFile != NULL && companyFile != NULL)
	{
		//1.1 회사 위치, 개인의 성명, 직책, 휴대폰번호, 이메일주소를 입력받는다.
		fread(&index, sizeof(Long), 1, personalFile);
		flag = fread(&visitingCard.personal, sizeof(Personal), 1, personalFile);
		//1. 파일의 끝이 아닌동안 반복한다.
		while (!feof(personalFile) && flag != 0)
		{
			//1.2.1 회사의 상호명, 주소, 전화번호, 팩스번호, url을 입력받는다.
			fseek(companyFile, 0L, SEEK_SET);
			i = 1;
			flag = fread(&visitingCard.company, sizeof(Company), 1, companyFile);
			//1.2 회사의 위치를 찾는다.
			while (!feof(companyFile) && flag != 0 && i < index)
			{
				i++;
				//1.2.1 회사의 상호명, 주소, 전화번호, 팩스번호, url을 입력받는다.
				flag = fread(&visitingCard.company, sizeof(Company), 1, companyFile);
			}
			//1.3 명함을 끼운다.
			node = AppendFromTail(&visitingCardBinder->visitingCards, &visitingCard, sizeof(VisitingCard));
			visitingCardBinder->length++;
			visitingCardBinder->current = (VisitingCard*)(node + 1);
			//1.1 회사 위치, 개인의 성명, 직책, 휴대폰번호, 이메일주소를 입력받는다.
			fread(&index, sizeof(Long), 1, personalFile);
			flag = fread(&visitingCard.personal, sizeof(Personal), 1, personalFile);
		}
		fclose(companyFile);
		fclose(personalFile);
	}
	//2. 사용량을 출력한다.
	return visitingCardBinder->length;
	//3. 끝내다.
}


//TakeIn
VisitingCard* VisitingCardBinder_TakeIn(VisitingCardBinder* visitingCardBinder, VisitingCard visitingCard)
{
	Node* node;

	//1. 명함을 입력받는다.
	//2. 명함을 놓을 위치를 찾는다.
	//3. 명함을 넣는다.
	node = AppendFromTail(&visitingCardBinder->visitingCards, &visitingCard, sizeof(VisitingCard));
	//4. 명함철에서 개수를 늘린다.
	visitingCardBinder->length++;
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//5. 명함철의 현재 위치를 출력한다.
	return visitingCardBinder->current;
	//6. 끝내다.
}

//Find
void VisitingCardBinder_Find(VisitingCardBinder* visitingCardBinder, char(*name), VisitingCard** (*indexes), Long* count)
{
	Node* (*nodes);
	Long i = 0;

	*count = 0;
	*indexes = NULL;
	//1. 성명을 입력받는다.
	LinearSearchDuplicate(&visitingCardBinder->visitingCards, name, &nodes, count, ComparePersoanlNames);
	//2. 개수가 0보다 크면
	if (*count > 0)
	{
		//2.1 위치들 배열을 만든다.
		*indexes = (VisitingCard * (*))calloc(*count, sizeof(VisitingCard*));
	}
	//3. 찾은 개수만큼 반복한다.
	while (i < *count)
	{
		//3.1 위치를 저장한다.
		(*indexes)[i] = (VisitingCard*)(nodes[i] + 1);
		i++;
	}
	//4. 할당해제한다.
	if (nodes != NULL)
	{
		free(nodes);
	}
	//5. 위치들과 개수를 출력한다.
	//6. 끝내다.
}

//FindByCompanyName
VisitingCard* VisitingCardBinder_FindByCompanyName(VisitingCardBinder* visitingCardBinder, char(*companyName))
{
	Node* node;
	VisitingCard* index = NULL;

	//1. 회사이름을 입력받는다.
	//2. 명함철에 입력받은 회사가 있는지 찾는다.
	node = LinearSearchUnique(&visitingCardBinder->visitingCards, companyName, CompareCompanyNames);
	//3. 입력받은 회사가 명함철에 있으면
	if (node != NULL)
	{
		//3.1 위치를 저장한다.
		index = (VisitingCard*)(node + 1);
	}
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다
}

//TakeOut
VisitingCard VisitingCardBinder_TakeOut(VisitingCardBinder* visitingCardBinder, VisitingCard* index)
{
	VisitingCard visitingCard;
	Node* node;

	//1. 명함의 위치를 입력받는다.
	//2. 위치를 찾는다.
	node = LinearSearchUnique(&visitingCardBinder->visitingCards, index, CompareVisitingCards);
	//3. 명함을 꺼낸다.
	GetAt(&visitingCardBinder->visitingCards, node, &visitingCard, sizeof(VisitingCard));
	//4. 명함을 없앤다.
	Delete(&visitingCardBinder->visitingCards, node);
	//5. 명함철에 명함이 남아있는 경우에
	if (visitingCardBinder->visitingCards.current != NULL)
	{
		//5.1 현재위치를 조정한다.
		visitingCardBinder->current = (VisitingCard*)(visitingCardBinder->visitingCards.current + 1);
	}
	//6. 명함철에 명함이 없는 경우에
	else
	{
		visitingCardBinder->current = NULL;
	}
	//7. 명함철의 명함개수를 감소시킨다.
	visitingCardBinder->length--;
	//8. 명함을 출력한다.
	return visitingCard;
	//9. 끝내다.
}

//Move
VisitingCard* VisitingCardBinder_Move(VisitingCardBinder* visitingCardBinder, VisitingCard* index)
{
	Node* node;
	//1. 위치를 입력받는다.
	node = LinearSearchUnique(&visitingCardBinder->visitingCards, index, CompareVisitingCards);
	//2. 현재 위치에 입력받은 위치를 대입한다.
	node = Move(&visitingCardBinder->visitingCards, node);
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//3. 현재 위치를 출력한다.
	return visitingCardBinder->current;
	//4. 끝내다.
}


//First
VisitingCard* VisitingCardBinder_First(VisitingCardBinder* visitingCardBinder)
{
	Node* node;
	//1. 현재 위치를 처음으로 이동시킨다.
	node = First(&visitingCardBinder->visitingCards);
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//2. 현재위치를 출력한다.
	return visitingCardBinder->current;
	//3. 끝내다.
}

//Previous
VisitingCard* VisitingCardBinder_Previous(VisitingCardBinder* visitingCardBinder)
{
	Node* node;

	//1. 현재 위치를 이전으로 이동시킨다.
	node = Previous(&visitingCardBinder->visitingCards);
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return visitingCardBinder->current;
	//3. 끝내다.
}

//Next
VisitingCard* VisitingCardBinder_Next(VisitingCardBinder* visitingCardBinder)
{
	Node* node;
	
	//1. 현재 위치를 다음으로 이동시킨다.
	node = Next(&visitingCardBinder->visitingCards);
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return visitingCardBinder->current;
	//3. 끝내다.
}

//Last
VisitingCard* VisitingCardBinder_Last(VisitingCardBinder* visitingCardBinder)
{
	Node* node;

	//1. 현재 위치를 마지막으로 이동시킨다.
	node = Last(&visitingCardBinder->visitingCards);
	visitingCardBinder->current = (VisitingCard*)(node + 1);
	//2. 현재 위치를 출력한다.
	return visitingCardBinder->current;
	//3. 끝내다.

}
#if 0
//Arrange
void Arrange(VisitingCardBinder* visitingCardBinder)
{
	VisitingCard* previous;
	VisitingCard* next;
	Long i;
	Long j;
	Boolean flag = _TRUE;

	//1. 명함철의 명함들을 성명을 기준으로 자모음순으로 정렬한다.
	i = visitingCardBinder->length - 1;
	while (i >= 1 && flag == _TRUE)
	{
		previous = NULL;
		visitingCardBinder->current = visitingCardBinder->first;
		next = visitingCardBinder->current->next;
		flag = _FALSE;
		j = 1;
		while (j <= i)
		{
			if (strcmp(visitingCardBinder->current->personal.name, next->personal.name) > 0)
			{
				visitingCardBinder->current->next = next->next;
				next->next = visitingCardBinder->current;
				if (previous != NULL)
				{
					previous->next = next;
				}
				else
				{
					visitingCardBinder->first = next;
				}
				previous = next;
				next = visitingCardBinder->current->next;
				flag = _TRUE;
			}
			else
			{
				previous = visitingCardBinder->current;
				visitingCardBinder->current = next;
				next = visitingCardBinder->current->next;
			}
			j++;
		}
		i--;
	}
	//2. 끝내다.
}
#endif

//Save
Long Save(VisitingCardBinder* visitingCardBinder)
{
	VisitingCard visitingCard;
	Long index;
	Company company;
	Node* it;
	Node* previous = NULL;
	int flag;
	FILE* personalFile;
	FILE* companyFile;

	companyFile = fopen("CompanyVisitingCard.dat", "wb+");
	personalFile = fopen("PersonalVisitingCard.dat", "wb");
	if (companyFile != NULL && personalFile != NULL)
	{
		//1. 명함철의 끝이 아닌동안 반복한다.
		it = First(&visitingCardBinder->visitingCards);
		while (it != previous)
		{
			GetAt(&visitingCardBinder->visitingCards, it, &visitingCard, sizeof(VisitingCard));
			//1.1.1 디스크파일에서 회사의 상호명, 주소, 전화번호, 팩스번호, url을 읽는다.
			fseek(companyFile, 0L, SEEK_SET);
			index = 1;
			flag = fread(&company, sizeof(Company), 1, companyFile);
			//1.1 파일의 끝이 아닌동안 그리고 파일의 상호명과 명함철의 상호명이 서로 같지 않은동안 반복한다.
			while (!feof(companyFile) && flag != 0 && strcmp(visitingCard.company.name, company.name) != 0)
			{
				//1.1.2 회사의 위치를 센다.
				index++;
				//1.1.1 디스크파일에서 회사의 상호명, 주소, 전화번호, 팩스번호, url을 읽는다.
				flag = fread(&company, sizeof(Company), 1, companyFile);
			}
			//1.2 파일의 끝이면
			if (flag == 0)
			{
				//1.2.1 회사의 상호명, 주소, 전화번호, 팩스번호, url을 디스크파일에 출력한다.
				fwrite(&visitingCard.company, sizeof(Company), 1, companyFile);
			}
			//1.3 회사 위치, 개인의 성명, 직책, 휴대폰번호, 이메일주소를 디스크파일에 출력한다.
			fwrite(&index, sizeof(Long), 1, personalFile);
			fwrite(&visitingCard.personal, sizeof(Personal), 1, personalFile);
			previous = it;
			it = Next(&visitingCardBinder->visitingCards);
		}
		fclose(personalFile);
		fclose(companyFile);
	}
	//2. 사용령을 출력한다.
	return visitingCardBinder->length;
	//3. 끝내다.
}

//Destroy
void VisitingCardBinder_Destroy(VisitingCardBinder* visitingCardBinder)
{
	//1. 명함철에서 순서대로 명함을 지운다.
	Destroy(&visitingCardBinder->visitingCards);
	//2. 끝내다.
}

int ComparePersoanlNames(void* one, void* other)
{
	VisitingCard* one_ = (VisitingCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->personal.name, other_);
}

int CompareCompanyNames(void* one, void* other)
{
	VisitingCard* one_ = (VisitingCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->company.name, other_);
}

int CompareVisitingCards(void* one, void* other)
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
