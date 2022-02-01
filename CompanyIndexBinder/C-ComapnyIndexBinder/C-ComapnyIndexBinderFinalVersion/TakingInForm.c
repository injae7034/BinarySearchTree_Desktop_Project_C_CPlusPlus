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
	//1. ����� ������ �����찡 ������ ��
	TCHAR positions[][8] = {
		"���",
		"����",
		"�븮",
		"����",
		"����",
		"����",
		"�̻�",
		"��",
		"����",
		"�λ���",
		"����"
	};
	TCHAR emailAddresses[][32] = {
		"naver.com",
		"gmail.com",
		"daum.com",
		"nate.com",
		"hanmail.com"
	};
	Long i = 0;

	//1.1 ��å �޺��ڽ��� �׸��� �߰��Ѵ�.
	while (i < sizeof(positions) / sizeof(positions[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, 0, (LPARAM)positions[i]);
		i++;
	}
	//1.2 �̸��� �޺��ڽ��� �׸���� �߰��Ѵ�.
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

	//2. ��ȣ ����Ʈ�� ��Ŀ���� ���� ��
	if (HIWORD(wParam) == EN_KILLFOCUS)
	{
		//2.1 ��ȣ���� �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)32, (LPARAM)companyName);
		//2.2 ����ö ������ �����츦 ã�´�.
		visitingCardBinderForm = FindWindow("#32770", "����ö");
		//2.3 ����ö ������ �������� ����ö���� ȸ�縦 ã�´�.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_Find(indexBinder, companyName);
		//2.4 ã�� ȸ�簡 ������
		if (index != NULL)
		{
			//2.4.1 ã�� ȸ�� ���ο� ����� ù��° ������ �˾Ƴ���.
			visitingCard = Index_GetAt(index, arrayIndex);
			//2.4.2 �˾Ƴ� ������ ȸ�������� ����Ѵ�.
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
	HTREEITEM hCompanies = NULL; //"ȸ���" �׸� �ڵ鰪
	HTREEITEM hCompany = NULL; //��ȣ �׸� �ڵ鰪
	HTREEITEM hPersonal = NULL; //���� �׸� �ڵ鰪
	HWND visitingCardBinderForm;

	//3. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 ����, ��å, �޴�����ȣ, �̸����ּ�, ��ȣ, �ּ�, ��ȭ��ȣ, �ѽ���ȣ, URL�� �д´�.
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
		//3.2 ����ö ������ �����츦 ã�´�.
		visitingCardBinderForm = FindWindow("#32770", "����ö");
		//3.3 ����ö ������ �������� ����ö���� �����.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		currentVisitingCard = VisitingCardBinder_TakeIn(visitingCardBinder, visitingCard);
		//3.4 ����ö ������ �������� ����ö���� �����.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_TakeIn(indexBinder, currentVisitingCard);
		//3.5 ����ö ������ �������� ���Կ� ���� ������ ����Ѵ�.
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
		//3.6 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//3.7 ����ö ������ �������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//3.8 ����ö ������ �������� Ʈ���� ��Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "ȸ���";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//3.9 ����ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//3.9.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//3.9.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//3.9.2.1 ����ö ������ �������� Ʈ���� ��Ʈ�ѿ��� ��ȣ�׸� �Ʒ��� ������ �����Ѵ�.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//3.10 ����ö ������ �������� ����ö���� ã�´�.
		index = IndexBinder_Find(indexBinder, currentVisitingCard->company.name);
		//3.11 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
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
		//3.12 ����ö ������ �������� ���ο��� ã�´�.
		arrayIndex = Index_Find(index, currentVisitingCard);
		//3.13 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), 
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//3.14 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND, 
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//3.15 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND, 
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//3.16 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM, 
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
		//3.17 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//TakingInForm_OnClose
BOOL TakingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. �ݱ� ��ư�� Ŭ������ ��
	//4.1 �����츦 �ݴ´�.
	EndDialog(hWnd, 0);
	return TRUE;
}