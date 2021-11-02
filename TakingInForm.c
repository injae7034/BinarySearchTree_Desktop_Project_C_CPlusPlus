#include "TakingInForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "IndexBinder.h"
#include "Index.h"
#include<stdio.h>//sprintf
#include<CommCtrl.h>
#pragma warning(disable:4996)

//TakingInFormProc
BOOL CALLBACK TakingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = TakingInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = TakingInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = TakingInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//TakingInForm_OnInitDialog
BOOL TakingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 끼우기 프레임 윈도우가 생성될 때
	TCHAR positions[][8] = {
		"사원",
		"주임",
		"대리",
		"과장",
		"차장",
		"부장",
		"이사",
		"상무",
		"전무",
		"부사장",
		"사장"
	};
	TCHAR emailAddresses[][32] = {
		"naver.com",
		"gmail.com",
		"daum.com",
		"nate.com",
		"hanmail.com"
	};
	Long i = 0;

	//1.1 직책 콤보박스에 항목들들 추가한다.
	while (i < sizeof(positions) / sizeof(positions[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, 0, (LPARAM)positions[i]);
		i++;
	}
	//1.2 이메일 콤보박스에 항목들을 추가한다.
	i = 0;
	while (i < sizeof(emailAddresses) / sizeof(emailAddresses[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_EMAILADDRESS), CB_ADDSTRING, 0, (LPARAM)emailAddresses[i]);
		i++;
	}
	return TRUE;
}

//TakingInForm_OnCommand
BOOL TakingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_TAKEIN: ret = TakingInForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_EDIT_COMPANYNAME: ret = TakingInForm_OnCompanyNameKillFocus(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//TakingInForm_OnCompanyNameKillFocus
BOOL TakingInForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	IndexBinder* indexBinder;
	HWND visitingCardBinderForm;
	TCHAR companyName[32];
	Index* index;
	VisitingCard* visitingCard;
	Long arrayIndex = 0;

	//2. 상호 에디트가 포커스를 잃을 때
	if (HIWORD(wParam) == EN_KILLFOCUS)
	{
		//2.1 상호명을 입력받는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)32, (LPARAM)companyName);
		//2.2 명함철 프레임 윈도우를 찾는다.
		visitingCardBinderForm = FindWindow("#32770", "명함철");
		//2.3 명함철 프레임 윈도우의 명함철에서 회사를 찾는다.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_Find(indexBinder, companyName);
		//2.4 찾는 회사가 있으면
		if (index != NULL)
		{
			//2.4.1 찾은 회사 색인에 저장된 첫번째 명함을 알아낸다.
			visitingCard = Index_GetAt(index, arrayIndex);
			//2.4.2 알아낸 명함의 회사정보를 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, 0, 
				(LPARAM)visitingCard->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, 0, 
				(LPARAM)visitingCard->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_FAXNUMBER), WM_SETTEXT, 0, 
				(LPARAM)visitingCard->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_URL), WM_SETTEXT, 0, 
				(LPARAM)visitingCard->company.url);
		}
	}
	return TRUE;
}

//TakingInForm_OnTakeInButtonClicked
BOOL TakingInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
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
	TCHAR emailAddressDomain[12];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hCompanies = NULL; //"회사들" 항목 핸들값
	HTREEITEM hCompany = NULL; //상호 항목 핸들값
	HTREEITEM hPersonal = NULL; //성명 항목 핸들값
	HWND visitingCardBinderForm;

	//3. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 성명, 직책, 휴대폰번호, 이메일주소, 상호, 주소, 전화번호, 팩스번호, URL을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONALNAME), WM_GETTEXT, (WPARAM)11,
			(LPARAM)visitingCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT, (WPARAM)8,
			(LPARAM)visitingCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_CELLULARPHONENUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.personal.cellularPhoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)20,
			(LPARAM)visitingCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_EMAILADDRESS), WM_GETTEXT, (WPARAM)12,
			(LPARAM)emailAddressDomain);
		sprintf(visitingCard.personal.emailAddress, "%s@%s", visitingCard.personal.emailAddress,
			emailAddressDomain);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)32,
			(LPARAM)visitingCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64,
			(LPARAM)visitingCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_FAXNUMBER), WM_GETTEXT, (WPARAM)12,
			(LPARAM)visitingCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_URL), WM_GETTEXT, (WPARAM)32,
			(LPARAM)visitingCard.company.url);
		//3.2 명함철 프레임 윈도우를 찾는다.
		visitingCardBinderForm = FindWindow("#32770", "명함철");
		//3.3 명함철 프레임 윈도우의 명함철에서 끼운다.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		currentVisitingCard = VisitingCardBinder_TakeIn(visitingCardBinder, visitingCard);
		//3.4 명함철 프레임 윈도우의 색인철에서 끼운다.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_TakeIn(indexBinder, currentVisitingCard);
		//3.5 명함철 프레임 윈도우의 명함에 끼운 명함을 출력한다.
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
		//3.6 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//3.7 명함철 프레임 윈도우의 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//3.8 명함철 프레임 윈도우의 트리뷰 컨트롤에서 "회사들" 항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "회사들";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//3.9 명함철 프레임 윈도우에서 색인개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//3.9.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//3.9.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//3.9.2.1 명함철 프레임 윈도우의 트리뷰 컨트롤에서 상호항목 아래에 성명을 삽입한다.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//3.10 명함철 프레임 윈도우의 색인철에서 찾는다.
		index = IndexBinder_Find(indexBinder, currentVisitingCard->company.name);
		//3.11 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
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
		//3.12 명함철 프레임 윈도우의 색인에서 찾는다.
		arrayIndex = Index_Find(index, currentVisitingCard);
		//3.13 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//3.14 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND, 
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//3.15 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND, 
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//3.16 명함철 프레임 윈도우의 트리뷰 컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, 
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
		//3.17 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//TakingInForm_OnClose
BOOL TakingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. 닫기 버튼을 클릭했을 때
	//4.1 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}