#include "FindingForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "WordCard.h"
#include "resource.h"
#include<afxwin.h>//CDialog 헤더파일
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl 헤더파일


BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SPELLINGS, OnSpellingsRadioButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_MEANINGS, OnMeaningsRadioButtonClicked)
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

//1. 찾기 윈도우가 생성돨 때
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 철자라디오버튼을 check한다.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_CHECKED);
	//1.2 의미라디오버튼을 uncheck한다.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//1.3 끝내다.
	return FALSE;
}

//2. 철자라디오 버튼을 클릭했을 때
void FindingForm::OnSpellingsRadioButtonClicked()
{
	//2.1 의미라디오 버튼을 uncheck한다.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//2.2 의미에디트를 공란으로 만든다.
	GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->SetWindowText("");
}

//3. 의미라디오 버튼을 클릭했을 때
void FindingForm::OnMeaningsRadioButtonClicked()
{
	//3.1 철자라디오버튼을 uncheck한다.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_UNCHECKED);
	//3.2 철자에디트를 공란으로 만든다.
	GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->SetWindowText("");
}

//4. 찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked()
{
	//4.1 단어카드철 프레임 윈도우를 찾는다.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//할당해제
	//FindingForm을 닫지 않은 상태에서 계속해서 찾기 버튼을 누를 경우 메모리 누수가 생길 수 있기 때문에
	//찾기버튼을 누를 때 마다 기존의 indexes를 할당해제시켜서 메모리 누수를 막아야함.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//4.2 선택된 라디오버튼을 읽는다.
	int spellingsChecked = ((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->GetCheck();
	int meaningsChecked = ((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->GetCheck();
	//4.3 철자라디오버튼이 선택되어 있으면
	CString spellings;
	if (spellingsChecked == BST_CHECKED)
	{
		//4.3.1 철자를 입력받는다.
		GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->GetWindowText(spellings);
		//4.3.2 단어카드철 프레임 윈도우의 단어카드철에서 철자로 찾는다.
		wordCardBinderForm->wordCardBinder->FindBySpellings((LPCTSTR)spellings, &this->indexes, &this->count);
	}
	//4.4 의미라디오버튼이 선택되어 있으면
	CString meanings;
	if (meaningsChecked == BST_CHECKED)
	{
		//4.4.1 의미를 입력받는다.
		GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->GetWindowText(meanings);
		//4.4.2 단어카드철 프레임 윈도우의 단어카드철에서 의미로 찾는다.
		wordCardBinderForm->wordCardBinder->FindByMeanings((LPCTSTR)meanings, &this->indexes, &this->count);
	}
	//4.5 찾은 단어가 있으면
	if (this->count > 0)
	{
		//4.5.1 찾은 단어카드들 중에서 첫번째 단어카드를 출력한다.
		this->current = 0;
		spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
		CString example = CString(this->indexes[this->current]->GetExample().c_str());
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	}
	//4.6 찾은 단어가드가 없으면
	else
	{
		//4.6.1 공란을 출력한다.
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText("");
	}
}

//5. 선택하기 버튼을 클릭했을 때
void FindingForm::OnChooseButtonClicked()
{
	//5.1 단어카드철 프레임 윈도우를 찾는다.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//5.2 단어카드철 프레임 윈도우에 선택한 단어카드를 출력한다.
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.3 단어카드철 프레임 윈도우의 단어카드철에서 현재 단어카드를 선택한 단어카드로 바꾼다.
	WordCard* current = wordCardBinderForm->wordCardBinder->Move(this->indexes[this->current]);
	//5.4 단어카드청 프레임 윈도우의 색인철에서 색인을 찾는다.
	Index *index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
	//5.5 찾은 색인의 알파벳과 단어칻트철 프레임 윈도우의 트리뷰컨트롤에서 동일한 알파벳항목을 찾는다.
	HTREEITEM hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_ROOT);
	HTREEITEM hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabets, TVGN_CHILD);
	TCHAR tAlphabet[2];
	TVITEM item = { 0, };
	item.mask = TVIF_TEXT;
	item.pszText = tAlphabet;
	item.cchTextMax = 2;
	item.hItem = hAlphabet;
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	TCHAR indexAlphabet[2];
	indexAlphabet[0] = index->GetAlphabet();
	indexAlphabet[1] = '\0';
	while (hAlphabet != NULL && tAlphabet[0] != indexAlphabet[0])
	{
		hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_NEXT);
		item.hItem = hAlphabet;
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.6 단어카드철 프레임윈도우의 트리뷰컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
	HTREEITEM hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_CHILD);
	TCHAR tSpellings[64];
	item.pszText = tSpellings;
	item.cchTextMax = 64;
	item.hItem = hSpellings;
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hSpellings != NULL && current->GetSpellings().compare(tSpellings) != 0)
	{
		hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_NEXT);
		item.hItem = hSpellings;
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.7 단어카드철 프레임윈도우의 트리뷰컨트롤의 철자항목 아래에서 현재 단어카드의 품사를 찾는다.
	HTREEITEM hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
	TCHAR tPartOfSpeech[8];
	item.pszText = tPartOfSpeech;
	item.cchTextMax = 8;
	item.hItem = hPartOfSpeech;
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hPartOfSpeech != NULL && current->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
	{
		hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
		item.hItem = hPartOfSpeech;
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.8 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
	HTREEITEM hMeanings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_CHILD);
	TCHAR tMeanings[32];
	item.pszText = tMeanings;
	item.cchTextMax = 32;
	item.hItem = hMeanings;
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hMeanings != NULL && current->GetMeanings().compare(tMeanings) != 0)
	{
		hMeanings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hMeanings, TVGN_NEXT);
		item.hItem = hMeanings;
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.9 단어카드철 프레임윈도우의 트리뷰컨트롤에서 "Alphabets"항목을 펼친다.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
	//5.10 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
	//5.11 단어카드철 프레임윈도우의 트리뷰컨트롤애서 현재 단어카드가 속하는 철자항목을 펼친다.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
	//5.12 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
	//5.13 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
	//5.14 색인리스트 배열을 할당해제한다.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
	//5.15 윈도우를 닫는다.
	EndDialog(0);
}

//6.처음버튼을 클릭했을 때
void FindingForm::OnFirstButtonClicked()
{
	//6.1 찾은 단어카드들 중에서 첫번째 단어카드를 출력한다.
	this->current = 0;
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//7. 이전버튼을 클릭했을 때
void FindingForm::OnPreviousButtonClicked()
{
	//7.1 찾은 단어카드들 중에서 이전 단어카드를 출력한다.
	this->current--;
	if (this->current < 0)
	{
		this->current = 0;
	}
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8. 다음 버튼을 클릭했을 때
void FindingForm::OnNextButtonClicked()
{
	//8.1 찾은 단어카드들 중에서 다음 단어카드를 출력한다.
	this->current++;
	if (this->current >= this->count)
	{
		this->current = this->count - 1;
	}
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//9. 마지막버튼을 클릭했을 때
void FindingForm::OnLastButtonClicked()
{
	//9.1 찾은 단어카드들 중에서 마지막 단어카드를 출력한다.
	this->current = this->count - 1;
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//10. 닫기버튼을 클릭했을 때
void FindingForm::OnClose()
{
	//10.1 단어카드링크 배열을 없앤다.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//10.2 윈도우를 닫는다.
	EndDialog(0);
}