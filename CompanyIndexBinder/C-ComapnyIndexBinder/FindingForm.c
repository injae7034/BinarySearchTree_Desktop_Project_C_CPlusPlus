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

	//1. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//1.1 ������ �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONALNAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//1.2 ����ö ������ �����츦 ã�´�.
		visitingCardBinderForm = FindWindow("#32770", "����ö");
		//1.3 ����ö ������ �������� ����ö���� ������ ã�´�.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		if (visitingCards != NULL)
		{
			free(visitingCards);
		}
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		VisitingCardBinder_Find(visitingCardBinder, name, &visitingCards, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)visitingCards);
		SetProp(hWnd, "FINDINGCOUNT", (HANDLE)count);
		//1.4 ã�� ������ ������
		if (count > 0)
		{
			//1.4.1 ã�� ���Ե��߿� ù��° ������ ����Ѵ�.
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
	HTREEITEM hCompanies = NULL; //"ȸ���" �׸� �ڵ鰪
	HTREEITEM hCompany = NULL; //��ȣ �׸� �ڵ鰪
	HTREEITEM hPersonal = NULL; //���� �׸� �ڵ鰪

	//2. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ������ ��ġ�� �д´�.
		visitingCards = (VisitingCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		//2.2 ����ö ������ �����츦 ã�´�.
		visitingCardBinderForm = FindWindow("#32770", "����ö");
		//2.3 ����ö ������ �����쿡 ������ ������ ����Ѵ�.
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
		//2.4 ����ö ������ �������� ����ö���� ���� ��ġ�� ������ ������ ��ġ�� �ٲ۴�.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		visitingCard = VisitingCardBinder_Move(visitingCardBinder, visitingCards[current]);
		//2.5 ����ö ������ �������� ����ö���� ã�´�.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_Find(indexBinder, visitingCard->company.name);
		//2.6 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
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
		//2.7 ����ö ������ �������� ���ο��� ã�´�.
		arrayIndex = Index_Find(index, visitingCard);
		//2.8 Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//2.9 Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//2.10 Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//2.11 Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);

		//2.12 �����츦 �ݴ´�.
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

	//3. ó�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 ��ġ�� �迭�� ù��° ������ ����Ѵ�.
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

	//4. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 ��ġ�� �迭�� ���� ��ġ�� ���� ��ġ�� ����Ѵ�.
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

	//5. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 ��ġ�� �迭�� ���� ��ġ�� ���� ��ġ�� ����Ѵ�.
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

	//6. ������ ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 ��ġ�� �迭�� ������ ������ ����Ѵ�.
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

	//7. �ݱ� ��ư�� Ŭ������ ��
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