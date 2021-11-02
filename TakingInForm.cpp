#include "TakingInForm.h"
#include "VisitingCardBinderForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include "IndexBinder.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CTreeCtrl헤더파일

BEGIN_MESSAGE_MAP(TakingInForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANYNAME, OnCompanyNameKillFocus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingInForm::TakingInForm(CWnd* parent)
	:CDialog(TakingInForm::IDD, parent)
{

}

//1. 끼우기 윈도우가 생성될 때
BOOL TakingInForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 직책콤보박스에 항목들을 추가한다.
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
	Long i = 0;
	while (i < sizeof(positions) / sizeof(positions[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString(positions[i]);
		i++;
	}
	//1.2 이메일콤보박스에 항목들을 추가한다.
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

//2. 상호에디트가 포커스를 잃을 때
void TakingInForm::OnCompanyNameKillFocus()
{
	//2.1 상호명을 입력받는다.
	CString companyName;
	GetDlgItem(IDC_EDIT_COMPANYNAME)->GetWindowText(companyName);
	//2.2 명함철 프레임 윈도우를 찾는다.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "명함철");
	//2.3 명함철 프레임 윈도우의 명함철에서 회사를 찾는다.
	VisitingCard* index = visitingCardBinderForm->visitingCardBinder->FindByCompanyName((LPCTSTR)companyName);
	//2.4 찾은 회사가 있으면
	if (index != 0)
	{
		//2.4.1 찾은 회사의 주소, 전화번호, 팩스번호, URL을 출력한다.
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

//3. 끼우기버튼을 클릭했을 때
void TakingInForm::OnTakeInButtonClicked()
{
	//3.1 성명, 직책, 휴대폰번호, 이메일주소, 상호, 주소, 전화번호, 팩스번호, URL을 읽는다.
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
	//3.2 명함철 프레임 윈도우를 찾는다.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "명함철");
	//3.3 입력받은 정보로 visitingCard를 생성한다.
	VisitingCard visitingCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellularPhoneNumber, (LPCTSTR)emailAddress, 
		(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
	//3.4 명함철 프레임 윈도우의 명함에서 끼운다.
	VisitingCard* current = visitingCardBinderForm->visitingCardBinder->TakeIn(visitingCard);
	//3.5 데이터베이스에 끼운 명함을 저장한다.
	visitingCardBinderForm->Insert(current);
	//3.6 명함철 프레임 윈도우의 색인철에서 끼운다.
	Index* index = visitingCardBinderForm->indexBinder->TakeIn(current);
	//3.7 명함철 프레임 윈도우에 끼운 명함을 출력한다.
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
	//3.8 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
	Index(*indexes);
	Long count;
	visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
	//3.9 명함철 프레임 윈도우의 트리뷰컨트롤에 있는 모든 항목들을 지운다.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
	//3.10 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"회사들";
	HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
	//3.11 명함철 프레임 윈도우에서 색인개수만큼 반복한다.
	HTREEITEM hCompany;
	Long i = 0;
	while (i < count)
	{
		//3.11.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
		insertStruct.hParent = hCompanies;
		insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
		hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
		//3.11.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			//3.11.2.1 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목아래에 성명을 삽입한다.
			VisitingCard* visitingCardLink = indexes[i].GetAt(j);
			insertStruct.hParent = hCompany;
			insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
			((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			j++;
		}
		i++;
	}
	//3.12 명함철 프레임 윈도우의 색인철에서 찾는다.
	index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
	//3.13 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
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
	//3.14 명함철 프레임 윈도우의 색인에서 현재 명함의 위치를 찾는다.
	Long arrayIndex = index->Find(current);
	//3.15 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
	HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
	i = 0;
	while (i < arrayIndex)
	{
		hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
		i++;
	}
	//3.16 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
	//3.17 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
	//3.18 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
	//3.19 색인리스트 배열을 할당해제한다.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
	//3.20 윈도우를 닫는다.
	EndDialog(0);
}

//4. 닫기버튼을 클릭했을 때
void TakingInForm::OnClose()
{
	//4.1 윈도우를 닫는다.
	EndDialog(0);
}


