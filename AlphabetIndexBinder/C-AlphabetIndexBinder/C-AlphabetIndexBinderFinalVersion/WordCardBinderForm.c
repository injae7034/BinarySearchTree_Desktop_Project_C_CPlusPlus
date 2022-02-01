#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "resource.h"
#include "TakingInForm.h"
#include "FindingForm.h"
#include "TakingOutForm.h"
#include "IndexBinder.h"
#include "Index.h"
#include<stdlib.h>//malloc, free
#include<string.h>//strcmp
#include<CommCtrl.h>
#pragma warning(disable:4996)

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmelLine, int nShowCmd)
{
	int response;

	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_WORDCARDBINDERFORM), NULL, WordCardBinderFormProc);

	return response;
}

// WordCardBinderFormProc
BOOL CALLBACK WordCardBinderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = WordCardBinderForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = WordCardBinderForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = WordCardBinderForm_OnTreeViewItemDoubleClicked(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = WordCardBinderForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL WordCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 윈도우가 생성될 때
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* wordCard;
	WordCard* otherCard;
	WordCard* firstCard;
	WordCard* it;
	WordCard* previous = NULL;
	Index* indexLink;
	Index(*indexes);
	Long i;
	Long j;
	Long k;
	Long m;
	Long n;
	Long count;
	Long arrayCount;
	// arrayIndex;
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

	//1.1 단어카드철을 만든다.
	wordCardBinder = (WordCardBinder*)malloc(sizeof(WordCardBinder));
	WordCardBinder_Create(wordCardBinder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordCardBinder);
	//1.2 색인철을 만든다.
	indexBinder = (IndexBinder*)malloc(sizeof(IndexBinder));
	IndexBinder_Create(indexBinder);
	SetProp(hWnd, "INDEXBINDER", (HANDLE)indexBinder);
	//1.3 단어카드철에서 적재한다.
	count = WordCardBinder_Load(wordCardBinder);
	//1.4 적재한 개수만큼 색인철에 끼운다.
	if (count > 0)
	{
		it = WordCardBinder_First(wordCardBinder);
		while (it != previous)
		{
			IndexBinder_TakeIn(indexBinder, it);
			previous = it;
			it = WordCardBinder_Next(wordCardBinder);
		}
	}
	//1.5 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = "Alphabets";
	hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
		(LPARAM)&insertStruct);
	//1.6 적재가 되었으면
	if (count > 0)
	{
		//1.6.1 단어카드철에서 처음으로 이동한다.
		firstCard = WordCardBinder_First(wordCardBinder);
		//1.6.2 단어카드철의 첫번째 단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)firstCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)firstCard->word.example);
		//1.6.3 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//1.6.4 색인개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//1.6.4.1 트리뷰컨트롤에 알파벳항목을 삽입한다.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM,
				0, (LPARAM)&insertStruct);
			//1.6.4.2 색인에 저장된 단어카드 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//1.6.4.2.1 색인에 저장된 단어카드를 알아낸다.
				wordCard = Index_GetAt(indexes + i, j);
				//1.6.4.2.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
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
				//1.6.4.2.3 철자중복이 없으면(중복되는 경우 바로 탈출해서 쓸데없는 반복을 단축시킴)(이미 중복이 있는 것은 트리뷰에 다 추가되어 있기 때문에)
				if (isDuplicatedSpellings == FALSE)
				{
					//1.6.4.2.3.1 트리뷰컨트롤의 알파벳항목 아래에 철자를 삽입한다.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
						TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//1.6.4.2.3.2 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//1.6.4.2.3.3 찾은 개수만큼 반복한다.
					m = 0;
					while (m < arrayCount)
					{
						//1.6.4.2.3.3.1 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
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
						//1.6.4.2.3.3.2 품사중복이 없으면
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//1.6.4.2.3.3.2.1 트리뷰 컨트롤에 철자항목 아래에 품사를 삽입한다.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//1.6.4.2.3.3.2.2 트리뷰 컨트롤의 품사항목 아래에 의미를 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);
						
						}
						//1.6.4.2.3.3.3 품사가 중복되면
						else
						{
							//1.6.4.2.3.3.3.1 같은 품사를 찾는다.
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD,
								(LPARAM)hSpellings);
							item.mask = TVIF_TEXT;
							item.pszText = partOfSpeech;
							item.cchTextMax = 8;
							item.hItem = hPartOfSpeech;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, 
								(LPARAM)&item);
							while (hPartOfSpeech != NULL && strcmp(partOfSpeech, 
								wordCard->word.partOfSpeech) != 0)
							{
								hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, 
									IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, 
									(LPARAM)hPartOfSpeech);
								item.hItem = hPartOfSpeech;
								SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
									(LPARAM)&item);
							}
							//1.6.4.2.3.3.3.2 같은 품사 항목 아래에 의미항목을 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);
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
		//1.6.5 색인철에서 찾는다.
		indexLink = IndexBinder_Find(indexBinder, firstCard->word.spellings[0]);
		//1.6.6 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//1.6.7 색인에서 찾는다.
		//arrayIndex = Index_Find(indexLink, firstCard);
		//1.6.8 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, firstCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
#if 0
		i = 0;
		while (i < arrayIndex)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			i++;
		}
#endif
		//1.6.9 트리뷰컨트롤의 철자항목에서 현재 단어카드의 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, firstCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//1.6.10 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings=(HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, 
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, firstCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//1.6.11 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//1.6.12 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//1.6.13 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//1.6.14 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//1.6.15 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//1.6.16 색인배열을 할당해제한다.
		if (indexes != NULL)
		{
			free(indexes);
		}
	}
	return TRUE;
}

//OnCommand
BOOL WordCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_TAKEIN: ret = WordCardBinderForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = WordCardBinderForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_TAKEOUT: ret = WordCardBinderForm_OnTakeOutButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = WordCardBinderForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = WordCardBinderForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = WordCardBinderForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = WordCardBinderForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = WordCardBinderForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

// WordCardBinderForm_OnNotify
BOOL WordCardBinderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam)
	{
	case IDC_TREE_ALPHABETINDEX: ret = WordCardBinderForm_OnTreeViewItemDoubleClicked(hWnd,
		wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}


// WordCardBinderForm_OnTakeInButtonClicked
BOOL WordCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//2. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 끼우기 프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKINGINFORM), NULL,
			TakingInFormProc);
	}
	return TRUE;
}

//WordCardBinderForm_OnFindButtonClicked
BOOL WordCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 찾기프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL,
			FindingFormProc);
	}
	return TRUE;
}

// WordCardBinderForm_OnTakeOutButtonClicked
BOOL WordCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. 꺼내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 꺼내기 프레임 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKINGOUTFORM), NULL,
			TakingOutFormProc);
	}
	return TRUE;
}

//WordCardBinderForm_OnArrangeButtonClicked
BOOL WordCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* wordCard;
	WordCard* otherCard;
	WordCard* firstCard;
	Index* indexLink;
	Index(*indexes);
	Long i;
	Long j;
	Long k;
	Long m;
	Long n;
	Long count;
	Long arrayCount;
	//Long arrayIndex;
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

	//5. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 색인철에서 정리한다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		IndexBinder_Arrange(indexBinder);
		//5.2 색인철에서 색인리스트를 만든다.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//5.3 트리뷰컨트롤에 있는 모든 항목들을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
		//5.4 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "Alphabets";
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
			(LPARAM)&insertStruct);
		//5.5 단어카드철에서 처음으로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		firstCard = WordCardBinder_First(wordCardBinder);
		//5.6 단어카드철의 현재 단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)firstCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)firstCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)firstCard->word.example);
		//5.7 색인개수만큼 반복한다.
		i = 0;
		while (i < count)
		{
			//5.7.1 트리뷰컨트롤에 알파벳항목을 삽입한다.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM,
				0, (LPARAM)&insertStruct);
			//5.7.2 색인에 저장된 단어카드 개수만큼 반복한다.
			j = 0;
			while (j < indexes[i].length)
			{
				//5.7.2.1 색인에 저장된 단어카드를 알아낸다.
				wordCard = Index_GetAt(indexes + i, j);
				//5.7.2.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
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
				//5.7.2.3 철자중복이 없으면
				if (isDuplicatedSpellings == FALSE)
				{
					//5.7.2.3.1 트리뷰컨트롤의 알파벳항목 아래에 철자를 삽입한다.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
						TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//5.7.2.3.2 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//5.7.2.3.3 찾은 개수만큼 반복한다.
					m = 0;
					while (m < arrayCount)
					{
						//5.7.2.3.3.1 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
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
						//5.7.2.3.3.2 품사중복이 없으면
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//5.7.2.3.3.2.1 트리뷰 컨트롤에 철자항목 아래에 품사를 삽입한다.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//5.7.2.3.3.2.2 트리뷰 컨트롤의 품사항목 아래에 의미를 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);

						}
						//5.7.2.3.3.3 품사가 중복되면
						else
						{
							//5.7.2.3.3.3.1 같은 품사를 찾는다.
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD,
								(LPARAM)hSpellings);
							item.mask = TVIF_TEXT;
							item.pszText = partOfSpeech;
							item.cchTextMax = 8;
							item.hItem = hPartOfSpeech;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
								(LPARAM)&item);
							while (hPartOfSpeech != NULL && strcmp(partOfSpeech,
								wordCard->word.partOfSpeech) != 0)
							{
								hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
									IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT,
									(LPARAM)hPartOfSpeech);
								item.hItem = hPartOfSpeech;
								SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
									(LPARAM)&item);
							}
							//5.7.2.3.3.3.2 같은 품사 항목 아래에 의미항목을 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);
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
		//5.8 색인철에서 찾는다.
		indexLink = IndexBinder_Find(indexBinder, firstCard->word.spellings[0]);
		//5.9 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//5.10 색인에서 찾는다.
		//arrayIndex = Index_Find(indexLink, firstCard);
		//5.11 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, firstCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}

#if 0
		i = 0;
		while (i < arrayIndex)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			i++;
		}
#endif
		//5.12 트리뷰컨트롤에서 현재 출력된 단어카드의 품사와 동일한 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, firstCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//5.13 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, firstCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//5.14 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//5.15 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//5.16 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//5.17 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//5.18 트리뷰컨트롤에서 현대 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//5.19 색인배열을 할당해제한다.
		if (indexes != NULL)
		{
			free(indexes);
		}
	}
	return TRUE;
}

//WordCardBinderForm_OnFirstButtonClicked
BOOL WordCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* currentCard;
	Index* indexLink;
	TCHAR indexesAlphabet[2];
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;

	//6. 처음으로 이동하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 단어카드철에서 처음으로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_First(wordCardBinder);
		//6.2 단어카드철의 현재 단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//6.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//6.4 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//6.5 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, currentCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//6.6 트리뷰컨트롤에서 현재 출력된 단어카드의 품사와 동일한 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, currentCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//6.7 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, currentCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//6.8 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//6.9 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//6.10 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//6.11 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//6.12 트리뷰컨트롤에서 현대 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);

	}
	return TRUE;	
}

// WordCardBinderForm_OnPreviousButtonClicked
BOOL WordCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* currentCard;
	Index* indexLink;
	TCHAR indexesAlphabet[2];
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;

	//7. 이전으로 이동하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//7.1 단어카드철에서 이전으로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Previous(wordCardBinder);
		//7.2 단어카드철의 현재단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//7.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//7.4 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//7.5 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, currentCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//7.6 트리뷰컨트롤에서 현재 출력된 단어카드의 품사와 동일한 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, currentCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//7.7 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, currentCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//7.8 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//7.9 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//7.10 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//7.11 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//7.12 트리뷰컨트롤에서 현대 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
	}
	return TRUE;
}

// WordCardBinderForm_OnNextButtonClicked
BOOL WordCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* currentCard;
	Index* indexLink;
	TCHAR indexesAlphabet[2];
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;
	//8. 다음으로 이동하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//8.1 단어카드철에서 다음으로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Next(wordCardBinder);
		//8.2 단어카드철의 현재 단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//8.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//8.4 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//8.5 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, currentCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//8.6 트리뷰컨트롤에서 현재 출력된 단어카드의 품사와 동일한 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, currentCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//8.7 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, currentCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//8.8 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//8.9 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//8.10 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//8.11 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//8.12 트리뷰컨트롤에서 현대 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
	}
	return TRUE;
}

//WordCardBinderForm_OnLastButtonClicked
BOOL WordCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* currentCard;
	Index* indexLink;
	TCHAR indexesAlphabet[2];
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;

	//9. 마지막으로 이동하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//9.1 단어카드철에서 마지막으로 이동한다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Last(wordCardBinder);
		//9.2 단어카드철의 현재단어카드를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//9.3 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//9.4 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_ROOT, (LPARAM)NULL);
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabets);
		item.mask = TVIF_TEXT;
		item.pszText = alphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		indexesAlphabet[0] = indexLink->alphabet;
		indexesAlphabet[1] = '\0';
		while (hAlphabet != NULL && strcmp(alphabet, indexesAlphabet) != 0)
		{
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hAlphabet);
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//9.5 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, currentCard->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//9.6 트리뷰컨트롤에서 현재 출력된 단어카드의 품사와 동일한 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, currentCard->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//9.7 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, currentCard->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
		}
		//9.8 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//6.9 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//9.10 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//9.11 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//9.12 트리뷰컨트롤에서 현대 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);


	}
	return TRUE;
}

//WordCardBinderForm_OnTreeViewItemDoubleClicked
BOOL WordCardBinderForm_OnTreeViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
	WordCard* currentCard = NULL;
	WordCard* wordCard;
	Index* index;
	Long i;
	TCHAR alphabet[2];
	TCHAR spellings[64];
	TCHAR partOfSpeech[8];
	TCHAR meanings[32];
	TVITEM item = { 0, };
	HTREEITEM hAlphabets = NULL;
	HTREEITEM hAlphabet = NULL;
	HTREEITEM hSpellings = NULL;
	HTREEITEM hPartOfSpeech = NULL;
	HTREEITEM hMeanings = NULL;

	//10. 트리뷰 컨트롤에서 의미를 더블클릭했을 때
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//10.1 트리뷰 컨트롤에서 더블클릭한 의미항목의 위치를 읽는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)NULL);
		//10.2 트리뷰 컨트롤에서 더블클릭한 의미항목의 부모윈도우(품사항목)의 위치를 읽는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hMeanings);
		//10.3 트리뷰 컨트롤에서 읽은 품사항목의 부모윈도우(철자항목)의 위치를 읽는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hPartOfSpeech);
		//10.4 트리뷰 컨트롤에서 읽은 철자항목의 부모윈도우(알파벳항목)의 위치를 읽는다.
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hSpellings);
		//10.5 트리뷰 컨트롤에서 "Alphabets" 항목의 위치를 읽는다.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hAlphabet);
		//10.6 트리뷰 컨트롤에서 더블클릭한 항목이 의미항목이 맞으면
		if (hAlphabets != NULL && hAlphabet != NULL && hSpellings != NULL && hPartOfSpeech != NULL
			&& hMeanings != NULL)
		{
			//10.6.1 트리뷰컨트롤에서 위치를 읽은 의미항목의 의미를 읽는다.
			item.mask = TVIF_TEXT;
			item.pszText = meanings;
			item.cchTextMax = 32;
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.2 트리뷰컨트롤에서 위치를 읽은 품사항목의 품사를 읽는다.
			item.mask = TVIF_TEXT;
			item.pszText = partOfSpeech;
			item.cchTextMax = 8;
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.3 트리뷰컨트롤에서 위치를 읽은 철자항목의 철자를 읽는다.
			item.mask = TVIF_TEXT;
			item.pszText = spellings;
			item.cchTextMax = 64;
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.4 트리뷰컨트롤에서 위치를 읽은 알파벳항목의 알파벳을 읽는다.
			item.mask = TVIF_TEXT;
			item.pszText = alphabet;
			item.cchTextMax = 2;
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.5 색인철에서 찾는다.
			indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
			index = IndexBinder_Find(indexBinder, alphabet[0]);
			//10.6.6 색인에 저장된 단어카드개수만큼 그리고 currentWordCard가 null인동안 반복한다.
			i = 0;
			while (i < index->length && currentCard == NULL)
			{
				//10.6.6.1 색인에 저장된 단어카드의 주소를 알아낸다.
				wordCard = Index_GetAt(index, i);
				//10.6.6.2 철자가 같고 품사가 같고 의미가 같으면
				if (strcmp(wordCard->word.spellings, spellings) == 0 && strcmp(wordCard->word.partOfSpeech,
					partOfSpeech) == 0 && strcmp(wordCard->word.meanings, meanings) == 0)
				{
					//10.6.6.2.1 단어카드의 위치를 저장한다.
					currentCard = wordCard;
				}
				i++;
			}
			//10.6.7 단어카드철에서 저장한 단어카드의 위치로 이동한다.
			wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
			currentCard = WordCardBinder_Move(wordCardBinder, currentCard);
			//10.6.8 단어카드철의 현재 단어카드를 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
				(LPARAM)currentCard->word.spellings);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
				(LPARAM)currentCard->word.partOfSpeech);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
				(LPARAM)currentCard->word.meanings);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
				(LPARAM)currentCard->word.example);
		}
	}
	return TRUE;
}

//OnClose
BOOL WordCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//11. 닫기 버튼을 클릭했을 때
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;

	wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
	if (wordCardBinder != NULL && indexBinder != NULL)
	{
		//11.1 단어카드철을 저장한다.
		WordCardBinder_Save(wordCardBinder);
		//11.2 색인철을 없앤다.
		IndexBinder_Destroy(indexBinder);
		free(indexBinder);
		RemoveProp(hWnd, "INDEXBINDER");
		//11.3 단어카드철을 없앤다.
		WordCardBinder_Destroy(wordCardBinder);
		free(wordCardBinder);
	}
	//10.3 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}
