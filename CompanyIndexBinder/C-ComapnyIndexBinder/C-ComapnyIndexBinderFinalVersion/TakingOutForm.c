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
	//1. ������ ������ �����찡 ������ ��
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

	//1.1 ����ö ������ �����츦 ã�´�.
	visitingCardBinderForm = FindWindow("#32770", "����ö");
	//1.2 ����ö ������ �������� ����ö���� ������.
	visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
	current = visitingCardBinder->current;//���Բ����� ���� �̸� ���� ������ �ּҸ� �����ϱ�
	visitingCard = VisitingCardBinder_TakeOut(visitingCardBinder, visitingCardBinder->current);
	//TakeOut �Լ� ���� ���Ŀ��� ���� ������ �ּҰ� �ٲ� �׷��� �Լ� �������� �̸� �����ؾ���.
	//1.3 ����ö ������ �������� ����ö���� ������.
	indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
	//�Ʊ� �̸� ������ ���� ī�� �����ּҸ� IndexBinder_TakeOut���� �̿���.
	index = IndexBinder_TakeOut(indexBinder, visitingCard.company.name, current);
	//1.4 ���� ������ ����Ѵ�.
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
	//1.5 ����ö ������ �����쿡�� Ʈ������Ʈ���� ��� �׸���� ���ش�.
	SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
		(LPARAM)TVI_ROOT);
	//1.6 ������ ���� �Ŀ� ����ö ������ �������� ����ö�� ������ ����������
	//�ٽ� ����ö�� ����ī���ּҷ� �ٲ���.
	current = visitingCardBinder->current;
	if (current != NULL)
	{
		//1.6.1 ����ö ������ �����쿡 ����ö�� ���� ������ ����Ѵ�.
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
		//1.6.2 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//1.6.3 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "ȸ���";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//1.6.4 ����ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//1.6.4.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//1.6.4.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//1.6.4.2.1 ����ö ������ �������� Ʈ���� ��Ʈ�ѿ��� ��ȣ�׸� �Ʒ��� ������ �����Ѵ�.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//1.6.5 ����ö ������ �������� ����ö���� ã�´�.
		index = IndexBinder_Find(indexBinder, current->company.name);
		//1.6.6 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
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
		//1.6.7 ����ö ������ �������� ���ο��� ã�´�.
		arrayIndex = Index_Find(index, current);
		//1.6.8 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//1.6.9 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//1.6.10 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//1.6.11 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
	}
	//1.7 ������ ���� �Ŀ� ����ö ������ �������� ����ö�� ������ �ϳ��� ������
	else
	{
		//1.7.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "ȸ���";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//1.7.2 ����ö ������ �����쿡 ������ ����Ѵ�.
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
	//2. �ݱ� ��ư�� Ŭ������ ��
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
	HTREEITEM hCompanies = NULL; //"ȸ���" �׸� �ڵ鰪
	HTREEITEM hCompany = NULL; //��ȣ �׸� �ڵ鰪
	HTREEITEM hPersonal = NULL; //���� �׸� �ڵ鰪
	HWND visitingCardBinderForm;
	int messageBoxButton;

	//2.1 "����ðڽ��ϱ�?" �޼��� �ڽ��� ����Ѵ�.
	messageBoxButton = MessageBox(hWnd, "����ðڽ��ϱ�?", "����", MB_YESNOCANCEL);
	//2.2 "��" ��ư�� Ŭ������ ��
	if (messageBoxButton == IDYES)
	{
		//2.2.1 ����, ��å, �޴�����ȣ, �̸����ּ�, ��ȣ, �ּ�, ��ȭ��ȣ, �ѽ���ȣ, URL�� �д´�.
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
		//2.2.2 ����ö ������ �����츦 ã�´�.
		visitingCardBinderForm = FindWindow("#32770", "����ö");
		//2.2.3 ����ö ������ �������� ����ö���� �����.
		visitingCardBinder = (VisitingCardBinder*)GetWindowLong(visitingCardBinderForm, GWL_USERDATA);
		currentVisitingCard = VisitingCardBinder_TakeIn(visitingCardBinder, visitingCard);
		//2.2.4 ����ö ������ �������� ����ö���� �����.
		indexBinder = (IndexBinder*)GetProp(visitingCardBinderForm, "INDEXBINDER");
		index = IndexBinder_TakeIn(indexBinder, currentVisitingCard);
		//2.2.5 ����ö ������ �����쿡 ���� ������ ����Ѵ�.
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
		//2.2.6 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//2.2.7 ����ö ������ �������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//2.2.8 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "ȸ���";
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//2.2.9 ����ö ������ �����쿡�� ���� ������ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//2.2.9.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = indexes[i].companyName;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//2.2.9.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//2.2.9.2.1 ����ö ������ �������� Ʈ���� ��Ʈ�ѿ��� ��ȣ�׸� �Ʒ��� ������ �����Ѵ�.
				visitingCardLink = Index_GetAt(indexes + i, j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = visitingCardLink->personal.name;
				SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_INSERTITEM, 0,
					(LPARAM)&insertStruct);
				j++;
			}
			i++;
		}
		//2.2.10 ����ö ������ �������� ����ö���� ã�´�.
		index = IndexBinder_Find(indexBinder, currentVisitingCard->company.name);
		//2.2.11 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
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
		//2.2.12 ����ö ������ �������� ���ο��� ã�´�.
		arrayIndex = Index_Find(index, currentVisitingCard);
		//2.2.13 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = (HTREEITEM)SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPersonal);

			i++;
		}
		//2.2.14 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//2.2.15 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_EXPAND,
			(WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//2.2.16 ����ö ������ �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		SendMessage(GetDlgItem(visitingCardBinderForm, IDC_TREE_COMPANYINDEX), TVM_SELECTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)hPersonal);
		//2.2.17 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	//2.3 "�ƴϿ�" ��ư�� Ŭ������ ��
	else if (messageBoxButton == IDNO)
	{
		//2.3.1 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}
