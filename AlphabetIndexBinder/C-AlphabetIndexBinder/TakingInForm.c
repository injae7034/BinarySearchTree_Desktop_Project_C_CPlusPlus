#include "TakingInForm.h"
#include "WordCardBinder.h"
#include "Index.h"
#include "IndexBinder.h"
#include "resource.h"
#include<CommCtrl.h>
#pragma warning(disable:4996)

// TakingInFormProc
BOOL CALLBACK TakingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = TakingInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = TakingInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = TakingInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL TakingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 끼우기 프레임 윈도우가 생성될 때
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

	//1.1 품사 콤보박스에 항목들을 추가한다.
	while (i < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), CB_ADDSTRING, 0, (LPARAM)partOfSpeechs[i]);
		i++;
	}
	return TRUE;
}

//OnCommand
BOOL TakingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_TAKEIN: ret = TakingInForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

// TakingInForm_OnTakeInButtonClicked
BOOL TakingInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard card;
	WordCard* wordCard;
	WordCard* otherCard;
	WordCard* currentCard;
	Index* indexLink;
	Index(*indexes);
	Long i;
	Long j;
	Long k;
	Long m;
	Long n;
	Long count;
	Long arrayCount;
	Long(*arrayIndexes);
	TCHAR indexesAlphabet[2];
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVINSERTSTRUCT insertStruct = { 0, };
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;
	BOOL isDuplicatedSpellings;
	BOOL isDuplicatedPartOfSpeech;
	HWND wordCardBinderForm;

	//2 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 철자, 품사, 의미, 예시를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_GETTEXT, (WPARAM)64, 
			(LPARAM)card.word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_GETTEXT, (WPARAM)8,
			(LPARAM)card.word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_GETTEXT, (WPARAM)32,
			(LPARAM)card.word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128,
			(LPARAM)card.word.example);
		//2.2 단어카드철 프레임 윈도우를 찾는다.
		wordCardBinderForm = FindWindow("#32770", "단어카드철");
		//2.3 단어카드철 프레임윈도우의 단어카드철에서 끼운다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(wordCardBinderForm, GWL_USERDATA);
		currentCard = WordCardBinder_TakeIn(wordCardBinder, card);
		//2.4 단어카드철 프레임 윈도우의 색인철에서 끼운다.
		indexBinder = (IndexBinder*)GetProp(wordCardBinderForm, "INDEXBINDER");
		indexLink = IndexBinder_TakeIn(indexBinder, currentCard);
		//2.5 단어카드철 프레임 윈도우에 현재 단어카드를 출력한다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.example);
		//2.6 단어카드철 프레임 윈도우의 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//2.7 단어카드철 프레임 윈도우의 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//2.8 단어카드철 프레임 윈도우의 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "Alphabets";
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//2.9 단어카드철 프레임윈도우에서 색인개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//2.9.1 단어카드철 프레임윈도우의 트리뷰컨트롤에 알파벳항목을 삽입한다.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//2.9.2 단어카드철 프레임윈도우에서 색인에 저장된 단어카드 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//2.9.2.1 단어카드철 프레임윈도우에서 색인에 저장된 단어카드를 알아낸다.
				wordCard = Index_GetAt(indexes + i, j);
				//2.9.2.2 단어카드철 프레임윈도우에서 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
				isDuplicatedSpellings = FALSE;
				k = 0;
				while (k < j && isDuplicatedSpellings == FALSE)
				{
					otherCard = Index_GetAt(indexes + i, k);
					if (strcmp(wordCard->word.spellings, otherCard->word.spellings) == 0)
					{
						isDuplicatedSpellings = TRUE;
					}
					k++;
				}
				//2.9.2.3 단어카드철 프레임윈도우에서 철자중복이 없으면
				if (isDuplicatedSpellings == FALSE)
				{
					//2.9.2.3.1 단어카드철 프레임윈도우에서 트리뷰컨트롤의 알파벳항목 아래에 철자를 삽입한다.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, 
						IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//2.9.2.3.2 단어카드철 프레임윈도우에서 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//2.9.2.3.3 단어카드철 프레임윈도우에서 찾은 개수만큼 반복한다.
					m = 0;
					while (m < arrayCount)
					{
						//2.9.2.3.3.1 단어카드철 프레임윈도우에서 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
						wordCard = Index_GetAt(indexes + i, arrayIndexes[m]);
						isDuplicatedPartOfSpeech = FALSE;
						n = 0;
						while (n < m && isDuplicatedPartOfSpeech == FALSE)
						{
							otherCard = Index_GetAt(indexes + i, arrayIndexes[n]);
							if (strcmp(wordCard->word.partOfSpeech, otherCard->word.partOfSpeech) == 0)
							{
								isDuplicatedPartOfSpeech = TRUE;
							}
							n++;
						}
						//2.9.2.3.3.2 단어카드철 프레임윈도우에서 품사중복이 없으면
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//2.9.2.3.3.2.1 단어카드철 프레임윈도우에서 트리뷰 컨트롤에 철자항목 아래에 품사를 삽입한다.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//2.9.2.3.3.2.2 단어카드철 프레임윈도우에서 트리뷰 컨트롤의 품사항목 아래에 의미를 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
								TVM_INSERTITEM, 0, (LPARAM)&insertStruct);

						}
						//2.9.2.3.3.3 단어카드철 프레임윈도우에서 품사가 중복되면
						else
						{
							//2.9.2.3.3.3.1 단어카드철 프레임윈도우에서 같은 품사를 찾는다.
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm,
								IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD,
								(LPARAM)hSpellings);
							item.mask = TVIF_TEXT;
							item.pszText = partOfSpeech;
							item.cchTextMax = 8;
							item.hItem = hPartOfSpeech;
							SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
								TVM_GETITEM, 0, (LPARAM)&item);
							while (hPartOfSpeech != NULL && strcmp(partOfSpeech,
								wordCard->word.partOfSpeech) != 0)
							{
								hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm,
									IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT,
									(LPARAM)hPartOfSpeech);
								item.hItem = hPartOfSpeech;
								SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
									TVM_GETITEM, 0, (LPARAM)&item);
							}
							//2.9.2.3.3.3.2 단어카드철 프레임윈도우에서 같은 품사 항목 아래에 의미항목을 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
								TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
						}
						m++;
					}
					if (arrayIndexes != NULL)
					{
						free(arrayIndexes);
					}
				}
				j++;
			}
			i++;
		}
		//2.10 단어카드철 프레임윈도우의 색인철에서 찾는다.
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//2.11 단어카드철 프레임윈도우의 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
			(LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//2.12 단어카드철 프레임윈도우에서 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
			(LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, currentCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
				(LPARAM)&item);
		}
		//2.13 단어카드철 프레임윈도우에서 트리뷰컨트롤의 철자항목에서 현재 단어카드의 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
			(LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, currentCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
				(LPARAM)&item);
		}
		//2.14 단어카드철 프레임윈도우에서 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
			(LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, currentCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
				(LPARAM)&item);
		}
		//2.15 단어카드철 프레임윈도우의 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//2.16 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//2.17 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//2.18 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//2.19 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//2.20 색인배열을 할당해제한다.
		if (indexes != NULL)
		{
			free(indexes);
		}
		//2.21 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//OnClose
BOOL TakingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. 닫기 버튼을 클릭했을 때
	//3.1 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}