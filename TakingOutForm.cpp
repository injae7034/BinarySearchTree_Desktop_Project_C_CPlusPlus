#include "TakingOutForm.h"
#include "VisitingCardBinderForm.h"
#include "VisitingCardBinder.h"
#include "resource.h"
#include<afxwin.h>//CDialog헤더파일
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl헤더파일

BEGIN_MESSAGE_MAP(TakingOutForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingOutForm::TakingOutForm(CWnd* parent)
	:CDialog(TakingOutForm::IDD, parent)
{

}

//1. 꺼내기 윈도우가 생성될 때
BOOL TakingOutForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 명함철 프레임 윈도우를 찾는다.
	VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "명함철");
	//1.2 명함철 프레임 윈도우의 명함철에서 현재명함을 구한다.
	VisitingCard* current = visitingCardBinderForm->visitingCardBinder->GetCurrent();
	//1.3 명함철 프레임 윈도우의 명함철에서 꺼낸다.
	VisitingCard visitingCard = visitingCardBinderForm->visitingCardBinder->TakeOut(current);
	//1.4 데이터베이스에서 명함철에서 꺼낸 명함의 정보를 지운다.
	visitingCardBinderForm->Delete(&visitingCard);
	//1.5 명함철 프레임 윈도우의 색인철에서 꺼낸다.
	visitingCardBinderForm->indexBinder->TakeOut(visitingCard.GetCompanyName(), current);
	//1.6 꺼낸 명함을 출력한다.
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
	//1.7 명함철 프레임 윈도우에서 트리뷰 컨트롤의 모든 항목들을 없앤다.
	((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
	//1.8 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"회사들";
	HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
	//1.9 명함을 꺼낸 후에 명함철 프레임 윈도우의 명함철에 명함이 남아있으면
	current = visitingCardBinderForm->visitingCardBinder->GetCurrent();
	if (current != NULL)
	{
		//1.9.1 명함철 프레임 윈도우에 현재 명함을 출력한다.
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
		//1.9.2 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		Index(*indexes);
		Long count;
		visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//1.9.3 명함철 프레임 윈도우에서 색인개수만큼 반복한다.
		HTREEITEM hCompany;
		Long i = 0;
		while (i < count)
		{
			//1.9.3.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			//1.9.3.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//1.9.3.2.1 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목아래에 성명을 삽입한다.
				VisitingCard* visitingCardLink = indexes[i].GetAt(j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
				((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
				j++;
			}
			i++;
		}
		//1.9.4 명함철 프레임 윈도우의 색인철에서 찾는다.
		Index *index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
		//1.9.5 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
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
		//1.9.6 명함철 프레임 윈도우의 색인에서 현재 명함의 위치를 찾는다.
		Long arrayIndex = index->Find(current);
		//1.9.7 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
			i++;
		}
		//1.9.8 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
		//1.9.9 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
		//1.9.10 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
	}
	//1.10 명함철에 명함을 꺼낸 후에 명함이 없으면
	else 
	{
		//1.10.1 명함철 프레임 윈도우에 공란을 출력한다.
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
	//1.11 끝내다.
	return FALSE;
}

//2. 닫기버튼을 클릭했을 때
void TakingOutForm::OnClose()
{
	//2.1 "끼우시겠습니까?" 메세지박스를 출력한다.
	int messageBoxButton = MessageBox("끼우시겠습니까?", "질문", MB_YESNOCANCEL);
	//2.2 "예" 버튼을 클릭했을 때
	if (messageBoxButton == IDYES)
	{
		//2.2.1 명함의 정보를 읽는다.
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
		//2.2.2 visitingCard를 생성한다.
		VisitingCard visitingCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellularPhoneNumber, (LPCTSTR)emailAddress,
			(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		//2.2.3 명함철 프레임 윈도우를 찾는다.
		VisitingCardBinderForm* visitingCardBinderForm = (VisitingCardBinderForm*)CWnd::FindWindow("#32770", "명함철");
		//2.2.4 명함철 프레임 윈도우의 명람철에서 끼운다.
		VisitingCard* current = visitingCardBinderForm->visitingCardBinder->TakeIn(visitingCard);
		//2.2.5 데이터베이스에 끼운 명함을 저장한다.
		visitingCardBinderForm->Insert(current);
		//2.2.6 명함철 프레임 윈도우의 색인철에서 끼운다.
		Index* index = visitingCardBinderForm->indexBinder->TakeIn(current);
		//2.2.7 명함철 프레임 윈도우에 끼운 명함을 출력한다.
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
		//2.2.8 명함철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		Index(*indexes);
		Long count;
		visitingCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//2.2.9 명함철 푸레임 윈도우의 트리뷰컨트롤에 있는 모든 항목들으 지운다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->DeleteItem(TVI_ROOT);
        //2.2.10 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 삽입한다.
		TVINSERTSTRUCT insertStruct = { 0, };
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = (LPSTR)"회사들";
		HTREEITEM hCompanies = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
		//2.2.11 명함철 프레임 윈도우에서 색인개수만큼 반복한다.
		HTREEITEM hCompany;
		Long i = 0;
		while (i < count)
		{
			//2.2.11.1 명함철 프레임 윈도우의 트리뷰컨트롤에서 상호항목을 삽입한다.
			insertStruct.hParent = hCompanies;
			insertStruct.item.pszText = (char*)indexes[i].GetCompanyName().c_str();
			hCompany = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
			//2.2.11.2 명함철 프레임 윈도우의 색인에 저장된 명함의 개수만큼 반복한다.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//2.2.11.2.1 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목아래에 성명을 삽입한다.
				VisitingCard* visitingCardLink = indexes[i].GetAt(j);
				insertStruct.hParent = hCompany;
				insertStruct.item.pszText = (LPSTR)visitingCardLink->GetName().c_str();
				((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->InsertItem(&insertStruct);
				j++;
			}
			i++;
		}
		//2.2.12 명함철 프레임 윈도우의 색인철에서 찾는다.
		index = visitingCardBinderForm->indexBinder->Find(current->GetCompanyName());
		//2.2.13 명함철 프레임 윈도우의 트리뷰컨트롤에서 찾은 색인의 상호와 동일한 상호항목을 찾는다.
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
		//2.2.14 명함철 프레임 윈도우의 색인에서 현재 명함의 위치를 찾는다.
		Long arrayIndex = index->Find(current);
		//2.2.15 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 찾는다.
		HTREEITEM hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hCompany, TVGN_CHILD);
		i = 0;
		while (i < arrayIndex)
		{
			hPersonal = ((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->GetNextItem(hPersonal, TVGN_NEXT);
			i++;
		}
		//2.2.16 명함철 프레임 윈도우의 트리뷰컨트롤에서 "회사들" 항목을 펼친다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompanies, TVE_EXPAND);
		//2.2.17 명함철 프레임 윈도우의 트리뷰컨트롤에서 현재 명함이 속하는 상호항목을 펼친다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->Expand(hCompany, TVE_EXPAND);
		//2.2.18 명함철 프레임 윈도우의 트리뷰컨트롤의 상호항목에서 현재 명함의 성명을 선택한다.
		((CTreeCtrl*)visitingCardBinderForm->GetDlgItem(IDC_TREE_COMPANYINDEX))->SelectItem(hPersonal);
		//2.2.19. 색인리스트배열을 할당해제한다.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
		//2.2.20 윈도우를 닫는다.
		EndDialog(0);
	}
	//2.3 "아니오"버튼을 클릭했을 때
	else if (messageBoxButton == IDNO)
	{
		//2.3.1 윈도우를 닫는다.
		EndDialog(0);
	}
}