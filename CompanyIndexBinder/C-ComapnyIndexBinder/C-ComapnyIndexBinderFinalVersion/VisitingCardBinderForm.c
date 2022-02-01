#include "VisitingCardBinderForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "IndexBinder.h"
#include "Index.h"
#include "TakingInForm.h"
#include "FindingForm.h"
#include "TakingOutForm.h"
#include<stdlib.h>
#include<string.h>
#include<Commctrl.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmelLine, int nShowCmd)
{
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_VISITINGCARDBINDERFORM), NULL,
		VisitingCardBinderFormProc);
	return response;
}

BOOL CALLBACK VisitingCardBinderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = VisitingCardBinderForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = VisitingCardBinderForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = VisitingCardBinderForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = VisitingCardBinderForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//VisitingCardBinderForm_OnInitDialog
BOOL VisitingCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 윈도우가 생성될 때
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	VisitingCard* firstVisitingCard;
	VisitingCard* it;
	VisitingCard* previous = NULL;
	Index* indexLink;
	Index(*indexes);
	Long i;
	Long j;
	Long arrayIndex;
	Long count;
	TCHAR companyName[32];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL;//"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;//상호 항목 핸들값	
	HTREEITEM hPersonal = NULL;//성명 항목 핸들값
	
	//1.1 명함철을 만든다.
	visitingCardBinder = (VisitingCardBinder*)malloc(sizeof(VisitingCardBinder));
	VisitingCardBinder_Create(visitingCardBinder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)visitingCardBinder);
	//1.2 색인철을 만든다.
	indexBinder = (IndexBinder*)malloc(sizeof(IndexBinder));
	IndexBinder_Create(indexBinder);
	SetProp(hWnd, "INDEXBINDER", (HANDLE)indexBinder);
	//1.3 명함철에서 적재한다.
	count = VisitingCardBinder_Load(visitingCardBinder);
	//1.4 적재한 개수만큼 색인철에서 끼운다.
	if (count > 0)
	{
		it = VisitingCardBinder_First(visitingCardBinder);
		while (it != previous)
		{
			IndexBinder_TakeIn(indexBinder, it);
			previous = it;
			it = VisitingCardBinder_Next(visitingCardBinder);
		}
	}
	//1.5 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = "회사들";
	hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
		(LPARAM)&insertStruct);
	//1.6 적재가 되었으면
	if (count > 0)
	{
		//1.6.1 명함철에서 처음으로 이동한다.
		firstVisitingCard = VisitingCardBinder_First(visitingCardBinder);
		//1.6.2 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0, 
			(LPARAM)firstVisitingCard->company.url);
		//1.6.3 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//1.6.4 색인 개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//1.6.4.1 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
				(LPARAM)&insertStruct);
			//1.6.4.2 색인에 저장된 명함 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//1.6.4.2.1 트리뷰컨트롤의 상호항목 아래에 성명을 삽입한다.
				visitingCard = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCard->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//1.6.5 색인철에서 찾는다.
		indexLink = IndexBinder_Find(indexBinder, firstVisitingCard->company.name);
		//1.6.6 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
	    item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//1.6.7 색인에서 현재 명함의 위치를 찾는다.
		arrayIndex = Index_Find(indexLink, firstVisitingCard);
		//1.6.8 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex )
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);
			
			i++;
		}
		//1.6.9 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//1.6.10 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//1.6.11 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
		//1.6.12 색인배열을 할당해제한다.
		if (indexes != NULL)
		{
			free(indexes);
		}
	}
	return TRUE;
}


//VisitingCardBinderForm_OnCommand
BOOL VisitingCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_TAKEIN: ret = VisitingCardBinderForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = VisitingCardBinderForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_TAKEOUT: ret = VisitingCardBinderForm_OnTakeOutButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = VisitingCardBinderForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = VisitingCardBinderForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = VisitingCardBinderForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = VisitingCardBinderForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = VisitingCardBinderForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//VisitingCardBinderForm_OnNotify
BOOL VisitingCardBinderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam)
	{
	case IDC_TREE_COMPANYINDEX: ret = VisitingCardBinderForm_OnTreeViewItemDoubleClicked(hWnd,
		wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//VisitingCardBinderForm_OnTakeInButtonClicked
BOOL VisitingCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//2. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 끼우기 프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKINGINFORM), NULL,
			TakingInFormProc);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnFindButtonClicked
BOOL VisitingCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 끼우기 프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL,
			FindingFormProc);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnTakeOutButtonClicked
BOOL VisitingCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. 꺼내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 끼우기 프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKINGOUTFORM), NULL,
			TakingOutFormProc);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnArrangeButtonClicked
BOOL VisitingCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	VisitingCard* firstVisitingCard;
	Index* indexLink;
	Index(*indexes);
	Long i;
	Long j;
	Long count;
	Long arrayIndex;
	TCHAR companyName[32];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//5. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 색인철에서 정리한다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		IndexBinder_Arrange(indexBinder);
		//5.2 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//5.3 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
		//5.4 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "회사들";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
			(LPARAM)&insertStruct);
		//5.5 명함철에서 처음 위치로 이동한다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		firstVisitingCard = VisitingCardBinder_First(visitingCardBinder);
		//5.6 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)firstVisitingCard->company.url);
		//5.7 색인 개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//5.7.1 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
				(LPARAM)&insertStruct);
			//5.7.2 색인에 저장된 명함의 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//5.7.2.1 트리뷰 컨트롤의 상호항목 아래에 성명을 삽입한다.
				visitingCard = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCard->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//5.8 색인철에서 찾는다.
		indexLink = IndexBinder_Find(indexBinder, firstVisitingCard->company.name);
		//5.9 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//5.10 색인에서 찾는다.
		arrayIndex = Index_Find(indexLink, firstVisitingCard);
		//5.11 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//5.12 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//5.13 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//5.14 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
		//5.15 색인배열을 할당해제한다.
		if (indexes != NULL)
		{
			free(indexes);
		}
	}
	return TRUE;
}

//VisitingCardBinderForm_OnFirstButtonClicked
BOOL VisitingCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	Index* indexLink;
	Long i;
	Long arrayIndex;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//6. 처음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 명함철에서 처음 위치로 이동한다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		visitingCard = VisitingCardBinder_First(visitingCardBinder);
		//6.2 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.url);
		//6.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder,visitingCard->company.name);
		//6.4 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//6.5 색인에서 찾는다.
		arrayIndex = Index_Find(indexLink, visitingCard);
		//6.6 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//6.7 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//6.8 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//6.9 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnPreviousButtonClicked
BOOL VisitingCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	Index* indexLink;
	Long i;
	Long arrayIndex;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//7. 이전 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//7.1 명함철에서 이전으로 이동한다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		visitingCard = VisitingCardBinder_Previous(visitingCardBinder);
		//7.2 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.url);
		//7.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, visitingCard->company.name);
		//7.4 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//7.5 색인에서 찾는다.
		arrayIndex = Index_Find(indexLink, visitingCard);
		//7.6 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//7.7 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//7.8 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//7.9 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnNextButtonClicked
BOOL VisitingCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	Index* indexLink;
	Long i;
	Long arrayIndex;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//8. 다음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//8.1 명함철에서 다음위치로 이동한다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		visitingCard = VisitingCardBinder_Next(visitingCardBinder);
		//8.2 명함철의 현재 방향을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.url);
		//8.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, visitingCard->company.name);
		//8.4 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//8.5 색인에서 찾는다.
		arrayIndex = Index_Find(indexLink, visitingCard);
		//8.6 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//8.7 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//8.8 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//8.9 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
	}
	return TRUE;
}

// VisitingCardBinderForm_OnLastButtonClicked
BOOL VisitingCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	Index* indexLink;
	Long i;
	Long arrayIndex;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//9. 마지막 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//9.1 명함철에서 마지막 위치로 이동한다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		visitingCard = VisitingCardBinder_Last(visitingCardBinder);
		//9.2 명함철의 현재 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCard->company.url);
		//9.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, visitingCard->company.name);
		//9.4 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		item.mask = TVIF_TEXT;
		item.pszText = companyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hCompany != NULL && strcmp(companyName, indexLink->companyName) != 0)
		{
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//9.5 색인에서 찾는다.
		arrayIndex = Index_Find(indexLink, visitingCard);
		//9.6 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//9.7 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//9.8 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//9.9 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hPersonal);
	}
	return TRUE;
}

//VisitingCardBinderForm_OnTreeViewItemDoubleClicked
BOOL VisitingCardBinderForm_OnTreeViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* visitingCard;
	Index* indexLink;
	Long i;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; // "회사들" 항목 핸들값
	HTREEITEM hCompany = NULL;  //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값
	HTREEITEM hTemp = NULL; // 핸들값 비교를 위한 임시 저장소

	//10. 트리뷰 컨트롤에서 성명을 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//10.1 트리뷰컨트롤에서 더블클릭한 성명의 위치를 읽는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)NULL);
		//10.2 트리뷰 컨트롤에서 더블클릭한 성명의 부모윈도우(상호항목)의 위치를 읽는다.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hPersonal);
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		if (hCompany != NULL && hCompany != hCompanies)
		{
			//10.3 트리뷰컨트롤에서 상호항목을 읽는다.
			item.mask = TVIF_TEXT;
			item.pszText = companyName;
			item.cchTextMax = 32;
			item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.4 색인철에서 찾는다.
			indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
			indexLink = IndexBinder_Find(indexBinder, companyName);
			//10.5 색인에 저장된 명함 개수만큼 그리고 더블클릭한 위치값이 다른 동안 반복한다.
			i = 0;
			hTemp = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
			while (i < indexLink->length && hPersonal != hTemp)
			{
				hTemp = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANYINDEX), TVM_GETNEXTITEM,
					(WPARAM)TVGN_NEXT, (LPARAM)hTemp);
				//10.5.1 배열첨자를 센다.
				i++;
			}
			//10.6 색인에 저장된 명함을 알아낸다.
			visitingCard = Index_GetAt(indexLink, i);
			//10.7 명함철에서 알아낸 명함으로 이동한다.
			visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
			visitingCard = VisitingCardBinder_Move(visitingCardBinder, visitingCard);
			//10.8 명함철의 현재 명함을 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
				(LPARAM)visitingCard->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
				(LPARAM)visitingCard->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCard->personal.cellularPhoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
				(LPARAM)visitingCard->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
				(LPARAM)visitingCard->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
				(LPARAM)visitingCard->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCard->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCard->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
				(LPARAM)visitingCard->company.url);
		}
	}
	return TRUE;
}

//VisitingCardBinderForm_OnClose
BOOL VisitingCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//11. 닫기 버튼을 클릭했을 떄
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;

	visitingCardBinder = (VisitingCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
	if (visitingCardBinder != NULL && indexBinder != NULL)
	{
		//11.1 명함철을 저장한다.
		VisitingCardBinder_Save(visitingCardBinder);
		//11.2 색인철을 없앤다.
		IndexBinder_Destroy(indexBinder);
		free(indexBinder);
		RemoveProp(hWnd, "INDEXBINDER");
		//11.3 명함철을 없앤다.
		VisitingCardBinder_Destroy(visitingCardBinder);
		free(visitingCardBinder);
	}
	//11.4 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}