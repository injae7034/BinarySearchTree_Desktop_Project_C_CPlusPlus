#include "TakingInForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "WordCard.h"
#include "resource.h"
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl 헤더파일
#include<afxwin.h>//CDialog 헤더파일

BEGIN_MESSAGE_MAP(TakingInForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
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
	//1.1 품사콤보박스에 항목들을 추가한다.
	TCHAR partOfSpeechs[][8] = {
		"명사",
		"대명사",
		"동사",
		"형용사",
		"부사",
		"전치사",
		"접속사",
		"감탄사"
	};
	Long i = 0;
	while (i < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[i]);
		i++;
	}
	//1.2 끝내다.
	return FALSE;
}

//2. 끼우기버튼을 클릭했을 때
void TakingInForm::OnTakeInButtonClicked()
{
	//2.1 철자, 품사, 의미, 예시를 읽는다.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 단어카드철 프레임 윈도우를 찾는다.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//2.3 읽은 정보로 wordCard를 생성한다.
	WordCard card((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings, (LPCTSTR)example);
	//2.4 생성된 wordCard가 중복되는지 확인한다.
	Index* index = wordCardBinderForm->indexBinder->Find(card.GetSpellings()[0]);
	BOOL isDuplicatedWordCard = FALSE;
	Long i = 0;
	//알파벳 색인이 있으면
	if (index != 0)
	{
		while (i < index->GetLength() && isDuplicatedWordCard == FALSE)
		{
			//2.4.1 색인에 저장된 단어카드를 알아낸다.
			WordCard* cardLink = index->GetAt(i);
			//2.4.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
			if (card.GetSpellings().compare(cardLink->GetSpellings()) == 0)
			{
				//2.4.2.1 알아낸 단어카드의 철자와 다른 단어카드 사이에 품사중복이 있는지 확인한다.
				if (card.GetPartOfSpeech().compare(cardLink->GetPartOfSpeech()) == 0)
				{
					//2.4.2.1.1 알아낸 단어카드의 철자와 다른 단어카드 사이에 의미중복이 있는지 확인한다.
					if (card.GetMeanings().compare(cardLink->GetMeanings()) == 0)
					{
						isDuplicatedWordCard = TRUE;
					}
				}
			}
			i++;
		}
	}
	//2.5 알파벳색인이 없거나 단어카드가 중복이 안되면
	if (index == 0 || isDuplicatedWordCard == FALSE)
	{
		//2.5.1 단어카드철 프레임 윈도우의 단어카드철에서 끼운다.
		WordCard* current = wordCardBinderForm->wordCardBinder->TakeIn(card);
		//2.5.2 데이터베이스에서 끼운다.
		wordCardBinderForm->Insert(current);
		//2.5.3 단어카드철 프레임 윈도우의 색인철에 끼운다.
		index = wordCardBinderForm->indexBinder->TakeIn(current);
		//2.5.4 단어카드철 프레임 윈도우에 끼운 단어카드를 출력한다.
		spellings = CString(current->GetSpellings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		meanings = CString(current->GetMeanings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_MEANINGS)->SetWindowText(meanings);
		example = CString(current->GetExample().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_EXAMPLE)->SetWindowText(example);
		//2.5.5 색인철에서 색인리스트를 만든다.
		Index(*indexes);
		Long count;
		wordCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//2.5.6 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
		//2.5.7 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
		TVINSERTSTRUCT insertStruct = { 0, };
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = (LPSTR)"Alphabets";
		HTREEITEM hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
		//2.5.8 색인개수만큼 반복한다.
		HTREEITEM hAlphabet;
		HTREEITEM hSpellings;
		HTREEITEM hPartOfSpeech;
		TCHAR indexAlphabet[2];
		TCHAR tPartOfSpeech[8];
		WordCard* wordCard;
		WordCard* otherCard;
		i = 0;
		while (i < count)
		{
			//2.5.8.1 트리뷰컨트롤에 알파벳항목을 삽입한다.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//2.5.8.2 색인에 저장된 단어카드개수만큼 반복한다.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//2.5.8.2.1 색인에 저장된 단어카드를 알아낸다.
				wordCard = indexes[i].GetAt(j);
				//2.5.8.2.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
				BOOL isDuplicatedSpellings = FALSE;
				Long k = 0;
				while (k < j && isDuplicatedSpellings == FALSE)
				{
					otherCard = indexes[i].GetAt(k);
					if (wordCard->GetSpellings().compare(otherCard->GetSpellings()) == 0)
					{
						isDuplicatedSpellings = TRUE;
					}
					k++;
				}
				//2.5.8.2.2.3 철자중복이 없으면
				if (isDuplicatedSpellings == FALSE)
				{
					//2.5.8.2.2.3.1 트리뷰컨트롤의 알파벳 항목 아래에 철자를 삽입한다.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//2.5.8.2.2.3.2 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//2.5.8.2.2.3.3 찾은 개수만큼 반복한다.
					Long m = 0;
					while (m < arrayCount)
					{
						//2.5.8.2.2.3.3.1 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
						wordCard = indexes[i].GetAt(arrayIndexes[m]);
						BOOL isDuplicatedPartOfSpeech = FALSE;
						Long n = 0;
						while (n < m && isDuplicatedPartOfSpeech == FALSE)
						{
							otherCard = indexes[i].GetAt(arrayIndexes[n]);
							if (wordCard->GetPartOfSpeech().compare(otherCard->GetPartOfSpeech()) == 0)
							{
								isDuplicatedPartOfSpeech = TRUE;
							}
							n++;
						}
						//2.5.8.2.2.3.3.2 품사중복이 없으면
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//2.5.8.2.2.3.3.2.1 트리뷰컨트롤의 철자항목 아래에 품사를 삽입한다.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//2.5.8.2.2.3.3.2.2 트리뷰컨트롤의 품사항목 아래에 의미를 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//2.5.8.2.2.3.3.2 품사가 중복되면
						else
						{
							//2.5.8.2.2.3.3.2.1 같은 품사를 찾는다.
							hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
							TVITEM item = { 0, };
							item.mask = TVIF_TEXT;
							item.pszText = tPartOfSpeech;
							item.cchTextMax = 8;
							item.hItem = hPartOfSpeech;
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
							while (hPartOfSpeech != NULL && wordCard->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
							{
								hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
								item.hItem = hPartOfSpeech;
								((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
							}
							//2.5.8.2.2.3.3.2.2 같은 품사 항목 아래에 의미항목을 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						m++;
					}
					if (arrayIndexes != NULL)
					{
						delete[] arrayIndexes;
					}
				}
				j++;
			}
			i++;
		}
		//2.5.9 색인철에서 색인을 찾는다.
		index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
		//2.5.10 찾은 색인의 알파벳과 트리뷰컨트롤에서 동일한 알파벳항목을 찾는다.
		hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_ROOT);
		hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabets, TVGN_CHILD);
		TCHAR tAlphabet[2];
		TVITEM item = { 0, };
		item.mask = TVIF_TEXT;
		item.pszText = tAlphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		indexAlphabet[0] = index->GetAlphabet();
		indexAlphabet[1] = '\0';
		while (hAlphabet != NULL && tAlphabet[0] != indexAlphabet[0])
		{
			hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_NEXT);
			item.hItem = hAlphabet;
			((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		}
		//2.5.11 트리뷰컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_CHILD);
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
		//2.5.12 트리뷰컨트롤의 철자항목 아래에서 현재 단어카드의 품사를 찾는다.
		hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
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
		//2.5.13 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
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
		//2.5.14 트리뷰컨트롤에서 "Alphabets"항목을 펼친다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//2.5.15 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//2.5.16 트리뷰컨트롤애서 현재 단어카드가 속하는 철자항목을 펼친다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//2.5.17 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//2.5.18 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//2.5.19 색인리스트 배열을 할당해제한다.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
		//2.5.20 윈도우를 닫는다.
		EndDialog(0);
	}
	//2.6 단어카드가 중복되면
	else
	{
		//2.6.1 "단어카드가 중복되었습니다." 메세지박스를 출력한다.
		int messageBoxButton = MessageBox("단어카드가 중복되었습니다.", "끼우기 윈도우", MB_OK);
    }
}

//3. 닫기버튼을 클릭했을 때
void TakingInForm::OnClose()
{
	//3.1 윈도우를 닫는다.
	EndDialog(0);
}