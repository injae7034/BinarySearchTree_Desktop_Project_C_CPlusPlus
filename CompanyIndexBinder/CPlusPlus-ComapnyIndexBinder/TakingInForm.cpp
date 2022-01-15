#include "TakingInForm.h"
#include "VisitingCardBinderForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "IndexBinder.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CTreeCtrl�������

BEGIN_MESSAGE_MAP(TakingInForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANYNAME, OnCompanyNameKillFocus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingInForm::TakingInForm(CWnd* parent)
	:CDialog(TakingInForm::IDD, parent)
{

}

//1. ����� �����찡 ������ ��
BOOL TakingInForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ��å�޺��ڽ��� �׸���� �߰��Ѵ�.
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
	Long i = 0;
	while (i < sizeof(positions) / sizeof(positions[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString(positions[i]);
		i++;
	}
	//1.2 �̸����޺��ڽ��� �׸���� �߰��Ѵ�.
	TCHAR emailAddresses[][32] = {
		"naver.com",
		"gmail.com",
		"daum.net",
		"nate.com",
		"hanmail.com"
	};
	i = 0;
	while (i < sizeof(emailAddresses) / sizeof(emailAddresses[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_EMAILADDRESS))->AddString(emailAddresses[i]);
		i++;
	}
	return FALSE;
}

//2. ��ȣ����Ʈ�� ��Ŀ���� ���� ��
void TakingInForm::OnCompanyNameKillFocus()
{
	//2.1 ��ȣ���� �Է¹޴´�.
	CString companyName;
	GetDlgItem(IDC_EDIT_COMPANYNAME)->GetWindowText(companyName);
	//2.2 ����ö ������ �����츦 ã�´�.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
	//2.3 ����ö ������ �������� ����ö���� ȸ�縦 ã�´�.
	VisitingCard* index = visitingCardBinderForm->visitingCardBinder->FindByCompanyName((LPCTSTR)companyName);
	//2.4 ã�� ȸ�簡 ������
	if (index != 0)
	{
		//2.4.1 ã�� ȸ���� �ּ�, ��ȭ��ȣ, �ѽ���ȣ, URL�� ����Ѵ�.
		CString address = CString(index->GetAddress().c_str());
		GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
		CString telephoneNumber = CString(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
		CString faxNumber = CString(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
		CString url = CString(index->GetUrl().c_str());
		GetDlgItem(IDC_EDIT_URL)->SetWindowText(url);
	}
}

//3. ������ư�� Ŭ������ ��
void TakingInForm::OnTakeInButtonClicked()
{
	//3.1 ����, ��å, �޴�����ȣ, �̸����ּ�, ��ȣ, �ּ�, ��ȭ��ȣ, �ѽ���ȣ, URL�� �д´�.
	CString name;
	GetDlgItem(IDC_EDIT_PERSONALNAME)->GetWindowText(name);
	CString position;
	GetDlgItem(IDC_COMBO_POSITION)->GetWindowText(position);
	CString cellularPhoneNumber;
	GetDlgItem(IDC_EDIT_CELLULARPHONENUMBER)->GetWindowText(cellularPhoneNumber);
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	CString emailAddressDomain;
	GetDlgItem(IDC_COMBO_EMAILADDRESS)->GetWindowText(emailAddressDomain);
	emailAddress.Format("%s@%s", (LPCTSTR)emailAddress, (LPCTSTR)emailAddressDomain);
	CString companyName;
	GetDlgItem(IDC_EDIT_COMPANYNAME)->GetWindowText(companyName);
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	CString faxNumber;
	GetDlgItem(IDC_EDIT_FAXNUMBER)->GetWindowText(faxNumber);
	CString url;
	GetDlgItem(IDC_EDIT_URL)->GetWindowText(url);
	//3.2 ����ö ������ �����츦 ã�´�.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
	//3.3 �Է¹��� ������ visitingCard�� �����Ѵ�.
	VisitingCard visitingCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellularPhoneNumber, (LPCTSTR)emailAddress, 
		(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
	//3.4 ����ö ������ �������� ���Կ��� �����.
	VisitingCard* current = visitingCardBinderForm->visitingCardBinder->TakeIn(visitingCard);
	//3.5 �����ͺ��̽��� ���� ������ �����Ѵ�.
	visitingCardBinderForm->Insert(current);
	//3.6 ����ö ������ �������� ����ö���� �����.
	Index* index = visitingCardBinderForm->indexBinder->TakeIn(current);
	//3.7 ����ö ������ �����쿡 ���� ������ ����Ѵ�.
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
	//3.8 ����ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
	Index(*indexes);
	Long count;
	visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
	//3.9 ����ö ������ �������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
	//3.10 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� �����Ѵ�.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"ȸ���";
	HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
	//3.11 ����ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
	HTREEITEM hCompany;
	Long i = 0;
	while (i < count)
	{
		//3.11.1 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ��ȣ�׸��� �����Ѵ�.
		insertStruct.hParent = hCompanies;
		insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
		hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
		//3.11.2 ����ö ������ �������� ���ο� ����� ������ ������ŭ �ݺ��Ѵ�.
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			//3.11.2.1 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸�Ʒ��� ������ �����Ѵ�.
			VisitingCard* visitingCardLink = indexes[i].GetAt(j);
			insertStruct.hParent = hCompany;
			insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
			((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			j++;
		}
		i++;
	}
	//3.12 ����ö ������ �������� ����ö���� ã�´�.
	index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
	//3.13 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
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
	//3.14 ����ö ������ �������� ���ο��� ���� ������ ��ġ�� ã�´�.
	Long arrayIndex = index->Find(current);
	//3.15 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
	HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
	i = 0;
	while (i < arrayIndex)
	{
		hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
		i++;
	}
	//3.16 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
	//3.17 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
	//3.18 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
	//3.19 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
	//3.20 �����츦 �ݴ´�.
	EndDialog(0);
}

//4. �ݱ��ư�� Ŭ������ ��
void TakingInForm::OnClose()
{
	//4.1 �����츦 �ݴ´�.
	EndDialog(0);
}


