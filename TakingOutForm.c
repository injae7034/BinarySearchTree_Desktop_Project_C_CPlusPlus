#include "TakingOutForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "Index.h"
#include "IndexBinder.h"
#include<CommCtrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK TakingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = TakingOutForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = TakingOutForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//TakingOutForm_OnInitDialog
BOOL TakingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 꺼내기 프레임 윈도우가 생성될 때
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard visitingCard;
	VisitingCard* current;
	VisitingCard* visitingCardLink;
	Index* index;
	Index(*indexes);
	Long i;
	Long j;
	Long count;
	Long arrayIndex;
	TCHAR companyName[32];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL;
	HTREEITEM hCompany = NULL;
	HTREEITEM hPersonal = NULL;
	HWND visitingCardBinderForm;

	//1.1 명함철 프레임 윈도우를 찾는다.
	visitingCardBinderForm = FindWindow("#32770", "명함철");
	//1.2 명함철 프레임 윈도우의 명함철에서 꺼낸다.
	visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
	current = visitingCardBinder->current;//명함꺼내기 전에 미리 꺼낼 명함의 주소를 저장하기
	visitingCard = VisitingCardBinder_TakeOut(visitingCardBinder, visitingCardBinder->current);
	//TakeOut 함수 실행 이후에는 현재 명함의 주소가 바뀜 그래서 함수 실행전에 미리 저장해야함.
	//1.3 명함철 프레임 윈도우의 색인철에서 꺼낸다.
	indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
	//아까 미리 저장한 꺼낸 카드 명함주소를 IndexBinder_TakeOut에서 이용함.
	index = IndexBinder_TakeOut(indexBinder, visitingCard.company.name, current);
	//1.4 꺼낸 명함을 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
		(LPARAM)visitingCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
		(LPARAM)visitingCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
		(LPARAM)visitingCard.personal.cellularPhoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
		(LPARAM)visitingCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
		(LPARAM)visitingCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
		(LPARAM)visitingCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
		(LPARAM)visitingCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
		(LPARAM)visitingCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
		(LPARAM)visitingCard.company.url);
	//1.5 명함철 프레임 윈도우에서 트리뷰컨트롤의 모든 항목들을 없앤다.
	SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
		(LPARAM)TVI_ROOT);
	//1.6 명함을 꺼낸 후에 명함철 프레임 윈도우의 명함철에 명함이 남아있으면
	//다시 명함철의 현재카드주소로 바꿔줌.
	current = visitingCardBinder->current;
	if (current != NULL)
	{
		//1.6.1 명함철 프레임 윈도우에 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)current->personal.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)current->personal.position);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)current->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)current->personal.emailAddress);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)current->company.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)current->company.address);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)current->company.telephoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)current->company.faxNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)current->company.url);
		//1.6.2 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//1.6.3 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "회사들";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//1.6.4 명함철 프레임 윈도우에서 색인개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//1.6.4.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//1.6.4.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//1.6.4.2.1 명함철 프레임 윈도우의 트리뷰 컨트롤에서 상호항목 아래에 성명을 삽입한다.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//1.6.5 명함철 프레임 윈도우의 색인철에서 찾는다.
		index = IndexBinder_Find(indexBinder, current->company.name);
		//1.6.6 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, index->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//1.6.7 명함철 프레임 윈도우의 색인에서 찾는다.
		arrayIndex = Index_Find(index, current);
		//1.6.8 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//1.6.9 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//1.6.10 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//1.6.11 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
	}
	//1.7 명함을 꺼낸 후에 명함철 프레임 윈도우의 명함철에 명함이 하나도 없으면
	else
	{
		//1.7.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "회사들";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//1.7.2 명함철 프레임 윈도우에 공란을 출력한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0, 
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)"");
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)"");
	}
	return TRUE;
}


//TakingOutForm_OnClose
BOOL TakingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//2. 닫기 버튼을 클릭했을 때
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard visitingCard;
	VisitingCard* visitingCardLink;
	VisitingCard* currentVisitingCard;
	Index* index;
	Index(*indexes);
	Long count;
	Long arrayIndex;
	Long i;
	Long j;
	TCHAR companyName[32];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL; //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값
	HWND visitingCardBinderForm;
	int messageBoxButton;

	//2.1 "끼우시겠습니까?" 메세지 박스를 출력한다.
	messageBoxButton = MessageBox(hWnd, "끼우시겠습니까?", "질문", MB_YESNOCANCEL);
	//2.2 "예" 버튼을 클릭했을 때
	if (messageBoxButton == IDYES)
	{
		//2.2.1 성명, 직책, 휴대폰번호, 이메일주소, 상호, 주소, 전화번호, 팩스번호, URL을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_GETTEXT, (WPARAM)11,
			(LPARAM)visitingCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_GETTEXT, (WPARAM)8,
			(LPARAM)visitingCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)32,
			(LPARAM)visitingCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)32,
			(LPARAM)visitingCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64,
			(LPARAM)visitingCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_GETTEXT, (WPARAM)32,
			(LPARAM)visitingCard.company.url);
		//2.2.2 명함철 프레임 윈도우를 찾는다.
		visitingCardBinderForm = FindWindow("#32770", "명함철");
		//2.2.3 명함철 프레임 윈도우의 명함철에서 끼운다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		currentVisitingCard = VisitingCardBinder_TakeIn(visitingCardBinder, visitingCard);
		//2.2.4 명함철 프레임 윈도우의 색인철에서 끼운다.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_TakeIn(indexBinder, currentVisitingCard);
		//2.2.5 명함철 프레임 윈도우에 끼운 명함을 출력한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->personal.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->personal.position);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->company.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->company.address);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->company.faxNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)currentVisitingCard->company.url);
		//2.2.6 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//2.2.7 명함철 프레임 윈도우의 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//2.2.8 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "회사들";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//2.2.9 명함철 프레임 윈도우에서 색인 개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//2.2.9.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//2.2.9.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//2.2.9.2.1 명함철 프레임 윈도우의 트리뷰 컨트롤에서 상호항목 아래에 성명을 삽입한다.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//2.2.10 명함철 프레임 윈도우의 색인철에서 찾는다.
		index = IndexBinder_Find(indexBinder, currentVisitingCard->company.name);
		//2.2.11 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, index->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//2.2.12 명함철 프레임 윈도우의 색인에서 찾는다.
		arrayIndex = Index_Find(index, currentVisitingCard);
		//2.2.13 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//2.2.14 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//2.2.15 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//2.2.16 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
		//2.2.17 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	//2.3 "아니오" 버튼을 클릭했을 때
	else if (messageBoxButton == IDNO)
	{
		//2.3.1 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}
