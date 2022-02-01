#include "FindingForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "Index.h"
#include "IndexBinder.h"
#include<CommCtrl.h>
#include<stdlib.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CHOOSE: ret = FindingForm_OnChooseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	TCHAR name[11];
	VisitingCard* (*visitingCards) = NULL;
	Long count;
	HWND visitingCardBinderForm;
	Long current;

	//1. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//1.1 성명을 입력받는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONALNAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//1.2 명함철 프레임 윈도우를 찾는다.
		visitingCardBinderForm = FindWindow("#32770", "명함철");
		//1.3 명함철 프레임 윈도우의 명함철에서 명함을 찾는다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		if (visitingCards != NULL)
		{
			free(visitingCards);
		}
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		VisitingCardBinder_Find(visitingCardBinder, name, &visitingCards, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)visitingCards);
		SetProp(hWnd, "FINDINGCOUNT", (HANDLE)count);
		//1.4 찾은 명함이 있으면
		if (count > 0)
		{
			//1.4.1 찾은 명함들중에 첫번째 명함을 출력한다.
			current = 0;
			SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
				(LPARAM)visitingCards[current]->company.url);
		}
		else
		{
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0, (LPARAM)"");
		}
	}
	return TRUE;
}

//FindingForm_OnChooseButtonClicked
BOOL FindingForm_OnChooseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCardBinder* visitingCardBinder;
	IndexBinder* indexBinder;
	VisitingCard* (*visitingCards) = NULL;
	VisitingCard* visitingCard;
	HWND visitingCardBinderForm;
	Long current;
	Long i;
	Long arrayIndex;
	Index* index;
	TCHAR companyName[32];
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL; //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값

	//2. 선택하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 명함의 위치를 읽는다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		//2.2 명함철 프레임 윈도우를 찾는다.
		visitingCardBinderForm = FindWindow("#32770", "명함철");
		//2.3 명함철 프레임 윈도우에 선택한 명함을 출력한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.position);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.emailAddress);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.name);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.address);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.faxNumber);
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.url);
		//2.4 명함철 프레임 윈도우의 명함철에서 현재 위치를 선택한 명함의 위치로 바꾼다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		visitingCard = VisitingCardBinder_Move(visitingCardBinder, visitingCards[current]);
		//2.5 명함철 프레임 윈도우의 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_Find(indexBinder, visitingCard->company.name);
		//2.6 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
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
		//2.7 명함철 프레임 윈도우의 색인에서 찾는다.
		arrayIndex = Index_Find(index, visitingCard);
		//2.8 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//2.9 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//2.10 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//2.11 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);

		//2.12 윈도우를 닫는다.
		if (visitingCards != NULL)
		{
			free(visitingCards);
		}
		RemoveProp(hWnd, "FINDINGCOUNT");
		RemoveProp(hWnd, "CURRENTPOSITION");
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//FindingForm_OnFirstButtonClicked
BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	VisitingCard* (*visitingCards);

	//3. 처음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 위치들 배열의 첫번째 명함을 출력한다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = 0;
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.url);
	}
	return TRUE;
}

// FindingForm_OnPreviousButtonClicked
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	VisitingCard* (*visitingCards);

	//4. 이전 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 위치들 배열의 현재 위치의 이전 위치를 출력한다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		current--;
		if (current < 0)
		{
			current = 0;
		}
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.url);
	}
	return TRUE;
}

//FindingForm_OnNextButtonClicked
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	VisitingCard* (*visitingCards);
	Long count;

	//5. 다음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 위치들 배열의 현재 위치의 다음 위치를 출력한다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		count = (Long)GetProp(hWnd, "FINDINGCOUNT");
		current++;
		if (current >= count)
		{
			current = count - 1;
		}
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.url);
	}
	return TRUE;
}

// FindingForm_OnLastButtonClicked
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	VisitingCard* (*visitingCards);
	Long count;

	//6. 마지막 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 위치들 배열의 마지막 명함을 출력한다.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "FINDINGCOUNT");
		current = count - 1;
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PERSONALNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_POSITION), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_CELLULARPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EMAILADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_COMPANYNAME), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_ADDRESS), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_FAXNUMBER), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_URL), WM_SETTEXT, 0,
			(LPARAM)visitingCards[current]->company.url);
	}
	return TRUE;
}


BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	VisitingCard* (*visitingCards);

	//7. 닫기 버튼을 클릭했을 때
	visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
	if (visitingCards != NULL)
	{
		free(visitingCards);
	}
	RemoveProp(hWnd, "FINDINGCOUNT");
	RemoveProp(hWnd, "CURRENTPOSITION");
	EndDialog(hWnd, 0);
	return TRUE;
}