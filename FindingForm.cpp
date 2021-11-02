#include "FindingForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "WordCard.h"
#include "resource.h"
#include<afxwin.h>//CDialog �������
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl �������


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

//1. ã�� �����찡 ������ ��
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ö�ڶ�����ư�� check�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_CHECKED);
	//1.2 �ǹ̶�����ư�� uncheck�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//1.3 ������.
	return FALSE;
}

//2. ö�ڶ��� ��ư�� Ŭ������ ��
void FindingForm::OnSpellingsRadioButtonClicked()
{
	//2.1 �ǹ̶��� ��ư�� uncheck�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//2.2 �ǹ̿���Ʈ�� �������� �����.
	GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->SetWindowText("");
}

//3. �ǹ̶��� ��ư�� Ŭ������ ��
void FindingForm::OnMeaningsRadioButtonClicked()
{
	//3.1 ö�ڶ�����ư�� uncheck�Ѵ�.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_UNCHECKED);
	//3.2 ö�ڿ���Ʈ�� �������� �����.
	GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->SetWindowText("");
}

//4. ã�� ��ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked()
{
	//4.1 �ܾ�ī��ö ������ �����츦 ã�´�.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//�Ҵ�����
	//FindingForm�� ���� ���� ���¿��� ����ؼ� ã�� ��ư�� ���� ��� �޸� ������ ���� �� �ֱ� ������
	//ã���ư�� ���� �� ���� ������ indexes�� �Ҵ��������Ѽ� �޸� ������ ���ƾ���.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//4.2 ���õ� ������ư�� �д´�.
	int spellingsChecked = ((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->GetCheck();
	int meaningsChecked = ((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->GetCheck();
	//4.3 ö�ڶ�����ư�� ���õǾ� ������
	CString spellings;
	if (spellingsChecked == BST_CHECKED)
	{
		//4.3.1 ö�ڸ� �Է¹޴´�.
		GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->GetWindowText(spellings);
		//4.3.2 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� ö�ڷ� ã�´�.
		wordCardBinderForm->wordCardBinder->FindBySpellings((LPCTSTR)spellings, &this->indexes, &this->count);
	}
	//4.4 �ǹ̶�����ư�� ���õǾ� ������
	CString meanings;
	if (meaningsChecked == BST_CHECKED)
	{
		//4.4.1 �ǹ̸� �Է¹޴´�.
		GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->GetWindowText(meanings);
		//4.4.2 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� �ǹ̷� ã�´�.
		wordCardBinderForm->wordCardBinder->FindByMeanings((LPCTSTR)meanings, &this->indexes, &this->count);
	}
	//4.5 ã�� �ܾ ������
	if (this->count > 0)
	{
		//4.5.1 ã�� �ܾ�ī��� �߿��� ù��° �ܾ�ī�带 ����Ѵ�.
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
	//4.6 ã�� �ܾ�尡 ������
	else
	{
		//4.6.1 ������ ����Ѵ�.
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText("");
	}
}

//5. �����ϱ� ��ư�� Ŭ������ ��
void FindingForm::OnChooseButtonClicked()
{
	//5.1 �ܾ�ī��ö ������ �����츦 ã�´�.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//5.2 �ܾ�ī��ö ������ �����쿡 ������ �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.3 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� ���� �ܾ�ī�带 ������ �ܾ�ī��� �ٲ۴�.
	WordCard* current = wordCardBinderForm->wordCardBinder->Move(this->indexes[this->current]);
	//5.4 �ܾ�ī��û ������ �������� ����ö���� ������ ã�´�.
	Index *index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
	//5.5 ã�� ������ ���ĺ��� �ܾƮö ������ �������� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
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
	//5.6 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
	//5.7 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
	//5.8 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
	//5.9 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
	//5.10 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
	//5.11 �ܾ�ī��ö �������������� Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
	//5.12 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
	//5.13 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
	//5.14 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
	//5.15 �����츦 �ݴ´�.
	EndDialog(0);
}

//6.ó����ư�� Ŭ������ ��
void FindingForm::OnFirstButtonClicked()
{
	//6.1 ã�� �ܾ�ī��� �߿��� ù��° �ܾ�ī�带 ����Ѵ�.
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

//7. ������ư�� Ŭ������ ��
void FindingForm::OnPreviousButtonClicked()
{
	//7.1 ã�� �ܾ�ī��� �߿��� ���� �ܾ�ī�带 ����Ѵ�.
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

//8. ���� ��ư�� Ŭ������ ��
void FindingForm::OnNextButtonClicked()
{
	//8.1 ã�� �ܾ�ī��� �߿��� ���� �ܾ�ī�带 ����Ѵ�.
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

//9. ��������ư�� Ŭ������ ��
void FindingForm::OnLastButtonClicked()
{
	//9.1 ã�� �ܾ�ī��� �߿��� ������ �ܾ�ī�带 ����Ѵ�.
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

//10. �ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose()
{
	//10.1 �ܾ�ī�帵ũ �迭�� ���ش�.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//10.2 �����츦 �ݴ´�.
	EndDialog(0);
}