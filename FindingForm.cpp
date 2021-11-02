#include "FindingForm.h"
#include "VisitingCardBinderForm.h"
#include "resource.h"
#include "VisitingCard.h"
#include "VisitingCardBinder.h"
#include<afxwin.h>//CDialog �������
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl�������

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE, OnChooseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd* parent)
	:CDialog(FindingForm::IDD, parent)
{
	this->indexes = NULL;
	this->count = 0;
	this->current = 0;
}

//1. ã���ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked()
{
	//1.1 ������ �Է¹޴´�.
	CString name;
	GetDlgItem(IDC_EDIT_PERSONALNAME)->GetWindowText(name);
	//1.2 ����ö ������ �����츦 ã�´�.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
	//1.3 ����ö�������������� ����ö���� ������ ã�´�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	visitingCardBinderForm->visitingCardBinder->Find((LPCTSTR)name, &this->indexes, &this->count);
	//1.4 ã�� ������ ������
	if (this->count > 0)
	{
		//1.4.1 ã�� ���Ե� �߿� ù��° ������ ����Ѵ�.
		this->current = 0;
		name = CString(this->indexes[this->current]->GetName().c_str());
		GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
		CString position = CString(this->indexes[this->current]->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
		CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
		GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
		CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
		CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
		CString address = CString(this->indexes[this->current]->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
		CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
		CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
		CString url = CString(this->indexes[this->current]->GetUrl().c_str());
		GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
	}
	//1.5 ã�� ������ ������
	else
	{
		//1.5.1 �������� ������ش�.
		GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText("");
	}
}

//2. �����ϱ� ��ư�� Ŭ������ ��
void FindingForm::OnChooseButtonClicked()
{
	//2.1 ����ö ������ �����츦 ã�´�.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "����ö");
	//2.2 ����ö ������ �����쿡 ������ ������ �����Ѵ�.
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	visitingCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
	//2.3 ����ö ������ �������� ����ö���� ���� ��ġ�� ������ ������ ��ġ�� �ٲ۴�.
	VisitingCard* current = visitingCardBinderForm->visitingCardBinder->Move(this->indexes[this->current]);
	//2.4 ����ö ������ �������� ����ö���� ã�´�.
	Index* index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
	//2.5 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ã�� ������ ��ȣ�� ������ ��ȣ�׸��� ã�´�.
	HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(NULL, TVGN_ROOT);
	HTREEITEM hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompanies, TVGN_CHILD);
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
	//2.6 ����ö ������ �������� ���ο��� ���� ������ ��ġ�� ã�´�.
	Long arrayIndex = index->Find(current);
	//2.7 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ ã�´�.
	HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
	Long i = 0;
	while (i < arrayIndex)
	{
		hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
		i++;
	}
	//2.8 ����ö ������ �������� Ʈ������Ʈ�ѿ��� "ȸ���" �׸��� ��ģ��.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
	//2.9 ����ö ������ �������� Ʈ������Ʈ�ѿ��� ���� ������ ���ϴ� ��ȣ�׸��� ��ģ��.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
	//2.10 ����ö ������ �������� Ʈ������Ʈ���� ��ȣ�׸񿡼� ���� ������ ������ �����Ѵ�.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
	//2.11 �����츦 �ݴ´�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	EndDialog(0);
}

//3. ó����ư�� Ŭ������ ��
void FindingForm::OnFirstButtonClicked()
{
	//3.1 ã�� ���Ե� �߿��� ù��° ������ ����Ѵ�.
	this->current = 0;
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
}

//4. ������ư�� Ŭ������ ��
void FindingForm::OnPreviousButtonClicked()
{
	//4.1 ã�� ���Ե� �߿��� ���� ������ ����Ѵ�.
	this->current--;
	if (this->current < 0)
	{
		this->current = 0;
	}
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
}

//5. ������ư�� Ŭ������ ��
void FindingForm::OnNextButtonClicked()
{
	//5.1 ã�� ���Ե� �߿��� ���� ������ ����Ѵ�.
	this->current++;
	if (this->current >= this->count)
	{
		this->current = this->count - 1;
	}
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
}

//6. ��������ư�� Ŭ������ ��
void FindingForm::OnLastButtonClicked()
{
	//6.1 ã�� ���Ե� �߿��� ������ ������ ����Ѵ�.
	this->current = this->count - 1;
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PERSONALNAME)->SetWindowText(name);
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_EDIT_POSITION)->SetWindowText(position);
	CString cellularPhoneNumber = CString(this->indexes[this->current]->GetCellularPhoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_CELLULARPHONENUMBER)->SetWindowText(cellularPhoneNumber);
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_EDIT_COMPANYNAME)->SetWindowText(companyName);
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_EDIT_ADDRESS)->SetWindowText(address);
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_EDIT_URL)->SetWindowText(url);
}

//7.�ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose()
{
	//7.1 ���Ը�ũ�迭�� ���ش�.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//7.2 �����츦 �ݴ´�.
	EndDialog(0);
}