#include "TakingOutForm.h"
#include "VisitingCardBinderForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include<afxwin.h>//CDialog�������
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl�������

BEGIN_MESSAGE_MAP(TakingOutForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingOutForm::TakingOutForm(CWnd* parent)
	:CDialog(TakingOutForm::IDD, parent)
{

}

//1. ������ �����찡 ������ ��
BOOL TakingOutForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ����ö ������ �����츦 ã�´�.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
	//1.2 ����ö ������ �������� ����ö���� ��������� ���Ѵ�.
	VisitingCard* current = visitingCardBinderForm->visitingCardBinder->GetCurrent();
	//1.3 ����ö ������ �������� ����ö���� ������.
	VisitingCard visitingCard = visitingCardBinderForm->visitingCardBinder->TakeOut(current);
	//1.4 �����ͺ��̽����� ����ö���� ���� ������ ������ �����.
	visitingCardBinderForm->Delete(&visitingCard);
	//1.5 ����ö ������ �������� ����ö���� ������.
	visitingCardBinderForm->indexBinder->TakeOut(visitingCard.GetCompanyName(), current);
	//1.6 ���� ������ ����Ѵ�.
	CString name = CString(visitingCard.GetName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(visitingCard.GetPosition().c_str());
	GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(visitingCard.GetCellularPhoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(visitingCard.GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(visitingCard.GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(visitingCard.GetAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(visitingCard.GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(visitingCard.GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(visitingCard.GetUrl().c_str());
	GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
	//1.7 ����ö ������ �����쿡�� Ʈ���� ��Ʈ���� ��� �׸���� ���ش�.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
	//1.8 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"ȸ���";
	HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
	//1.9 ������ ���� �Ŀ� ����ö ������ �������� ����ö�� ������ ����������
	current = visitingCardBinderForm->visitingCardBinder->GetCurrent();
	if (current != NULL)
	{
		//1.9.1 ����ö ������ �����쿡 ���� ������ ����Ѵ�.
		name = CString(current->GetName().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
		position = CString(current->GetPosition().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
		cellularPhoneNumber = CString(current->GetCellularPhoneNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
		emailAddress = CString(current->GetEmailAddress().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
		companyName = CString(current->GetCompanyName().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
		address = CString(current->GetAddress().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
		telephoneNumber = CString(current->GetTelephoneNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
		faxNumber = CString(current->GetFaxNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
		url = CString(current->GetUrl().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
		//1.9.2 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//1.9.3 ����ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		HTREEITEM hCompany;
		Long i = 0;
		while (i < count)
		{
			//1.9.3.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			//1.9.3.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//1.9.3.2.1 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸�Ʒ��� ������ �����Ѵ�.
				VisitingCard* visitingCardLink = indexes[i].GetAt(j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
				((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
				j++;
			}
			i++;
		}
		//1.9.4 ����ö ������ �������� ����ö���� ã�´�.
		Index *index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
		//1.9.5 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
		hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(NULL, TVGN_ROOT);
		hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompanies, TVGN_CHILD);
		TVITEM item = { 0, };
		TCHAR tCompanyName[32];
		item.mask = TVIF_TEXT;
		item.pszText = tCompanyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetItem(&item);
		while (hCompany != NULL && index->GetCompanyName().compare(tCompanyName) != 0)
		{
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_NEXT);
			item.hItem = hCompany;
			((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetItem(&item);
		}
		//1.9.6 ����ö ������ �������� ���ο��� ���� ������ ��ġ�� ã�´�.
		Long arrayIndex = index->Find(current);
		//1.9.7 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
			i++;
		}
		//1.9.8 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
		//1.9.9 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
		//1.9.10 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
	}
	//1.10 ����ö�� ������ ���� �Ŀ� ������ ������
	else 
	{
		//1.10.1 ����ö ������ �����쿡 ������ ����Ѵ�.
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText("");
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText("");
	}
	//1.11 ������.
	return FALSE;
}

//2. �ݱ��ư�� Ŭ������ ��
void TakingOutForm::OnClose()
{
	//2.1 "����ðڽ��ϱ�?" �޼����ڽ��� ����Ѵ�.
	int messageBoxButton = MessageBox("����ðڽ��ϱ�?", "����", MB_YESNOCANCEL);
	//2.2 "��" ��ư�� Ŭ������ ��
	if (messageBoxButton == IDYES)
	{
		//2.2.1 ������ ������ �д´�.
		CString name;
		GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->GetWindowText(name);
		CString position;
		GetDlgItem(IDC_STATIC_EDIT_POSITION)->GetWindowText(position);
		CString cellularPhoneNumber;
		GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->GetWindowText(cellularPhoneNumber);
		CString emailAddress;
		GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
		CString companyName;
		GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->GetWindowText(companyName);
		CString address;
		GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->GetWindowText(address);
		CString telephoneNumber;
		GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
		CString faxNumber;
		GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->GetWindowText(faxNumber);
		CString url;
		GetDlgItem(IDC_STATIC_EDIT_URL)->GetWindowText(url);
		//2.2.2 visitingCard�� �����Ѵ�.
		VisitingCard visitingCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellularPhoneNumber, (LPCTSTR)emailAddress,
			(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		//2.2.3 ����ö ������ �����츦 ã�´�.
		VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
		//2.2.4 ����ö ������ �������� ���ö���� �����.
		VisitingCard* current = visitingCardBinderForm->visitingCardBinder->TakeIn(visitingCard);
		//2.2.5 �����ͺ��̽��� ���� ������ �����Ѵ�.
		visitingCardBinderForm->Insert(current);
		//2.2.6 ����ö ������ �������� ����ö���� �����.
		Index* index = visitingCardBinderForm->indexBinder->TakeIn(current);
		//2.2.7 ����ö ������ �����쿡 ���� ������ ����Ѵ�.
		name = CString(current->GetName().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
		position = CString(current->GetPosition().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
		cellularPhoneNumber = CString(current->GetCellularPhoneNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
		emailAddress = CString(current->GetEmailAddress().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
		companyName = CString(current->GetCompanyName().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
		address = CString(current->GetAddress().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
		telephoneNumber = CString(current->GetTelephoneNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
		faxNumber = CString(current->GetFaxNumber().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
		url = CString(current->GetUrl().c_str());
		visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
		//2.2.8 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//2.2.9 ����ö Ǫ���� �������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
        //2.2.10 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
		TVINSERTSTRUCT insertStruct = { 0, };
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = (LPSTR)"ȸ���";
		HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
		//2.2.11 ����ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		HTREEITEM hCompany;
		Long i = 0;
		while (i < count)
		{
			//2.2.11.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			//2.2.11.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//2.2.11.2.1 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸�Ʒ��� ������ �����Ѵ�.
				VisitingCard* visitingCardLink = indexes[i].GetAt(j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
				((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
				j++;
			}
			i++;
		}
		//2.2.12 ����ö ������ �������� ����ö���� ã�´�.
		index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
		//2.2.13 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
		hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(NULL, TVGN_ROOT);
		hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompanies, TVGN_CHILD);
		TVITEM item = { 0, };
		TCHAR tCompanyName[32];
		item.mask = TVIF_TEXT;
		item.pszText = tCompanyName;
		item.cchTextMax = 32;
		item.hItem = hCompany;
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetItem(&item);
		while (hCompany != NULL && index->GetCompanyName().compare(tCompanyName) != 0)
		{
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_NEXT);
			item.hItem = hCompany;
			((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetItem(&item);
		}
		//2.2.14 ����ö ������ �������� ���ο��� ���� ������ ��ġ�� ã�´�.
		Long arrayIndex = index->Find(current);
		//2.2.15 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
		HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
			i++;
		}
		//2.2.16 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
		//2.2.17 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
		//2.2.18 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
		//2.2.19. ���θ���Ʈ�迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
		//2.2.20 �����츦 �ݴ´�.
		EndDialog(0);
	}
	//2.3 "�ƴϿ�"��ư�� Ŭ������ ��
	else if (messageBoxButton == IDNO)
	{
		//2.3.1 �����츦 �ݴ´�.
		EndDialog(0);
	}
}