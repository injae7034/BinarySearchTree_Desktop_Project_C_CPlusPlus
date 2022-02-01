#include "FindingForm.h"
#include "WordCardBinder.h"
#include "Index.h"
#include "IndexBinder.h"
#include "resource.h"
#include<CommCtrl.h>
#pragma warning(disable:4996)

// FindingFormProc
BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
    case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//OnInitDialog
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//1. 찾기 프레임 윈도우가 생성될 때
	//1.1 철자 라디오버튼을 선택한다.
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLINGS), BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANINGS), BM_SETCHECK, BST_UNCHECKED, 0);

	return TRUE;
}

//OnCommand
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam))
	{
	case IDC_RADIO_SPELLINGS: 
		ret = FindingForm_OnSpellingsRadioButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_RADIO_MEANINGS: 
		ret = FindingForm_OnMeaningsRadioButtonClicked(hWnd, wParam, lParam); 
		break;

	case IDC_BUTTON_FIND: 
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); 
		break;

	case IDC_BUTTON_CHOOSE: 
		ret = FindingForm_OnChooseButtonClicked(hWnd, wParam, lParam); 
		break;

	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); 
		break;

	case IDC_BUTTON_PREVIOUS: 
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); 
		break;

	case IDC_BUTTON_NEXT:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;

	case IDC_BUTTON_LAST:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;

	default: 
		ret = FALSE; 
		break;
	}
	return ret;
}

//FindingForm_OnSpellingsRadioButtonClicked
BOOL FindingForm_OnSpellingsRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//2. 철자 라디오 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 의미에디트를 공란으로 만든다.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANINGS), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_STATIC_MEANINGS), WM_SETTEXT, 0, (LPARAM)"");
	}
	return TRUE;
}

//FindingForm_OnMeaningsRadioButtonClicked
BOOL FindingForm_OnMeaningsRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. 의미 라디오 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 철자에디트를 공란으로 만든다.
		SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLINGS), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_STATIC_SPELLINGS), WM_SETTEXT, 0, (LPARAM)"");
	}
	return TRUE;
}

//FindingForm_OnFindButtonClicked
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	TCHAR spellings[64];
	TCHAR meanings[32];
	WordCard* (*indexes) = NULL;
	Long count;
	Long current;
	HWND wordCardBinderForm;
	int spellingsChecked;
	int meaningsChecked;

	//4. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 단어카드철 프레임 윈도우를 찾는다.
		wordCardBinderForm = FindWindow("#32770", "단어카드철");
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL)
		{
			free(indexes);
		}
		wordCardBinder = (WordCardBinder*)GetWindowLong(wordCardBinderForm, GWL_USERDATA);
		//4.2 선택된 라디오 버튼을 읽는다.
		spellingsChecked = (int)SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLINGS), BM_GETCHECK, 0, 0);
		meaningsChecked = (int)SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANINGS), BM_GETCHECK, 0, 0);
		//4.3 철자라디오버튼이 선택되어 있으면
		if (spellingsChecked == BST_CHECKED)
		{
			//4.3.1 철자를 입력받는다.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_STATIC_SPELLINGS), WM_GETTEXT, (WPARAM)64, 
				(LPARAM)spellings);
			//4.3.2 단어카드철 프레임윈도우의 단어카드철에서 찾는다.
			WordCardBinder_FindBySpellings(wordCardBinder, spellings, &indexes, &count);
		}
		//4.4 의미라디오버튼이 선택되어 있으면
		else if (meaningsChecked == BST_CHECKED)
		{
			//4.4.1 의미를 입력받는다.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_STATIC_MEANINGS), WM_GETTEXT, (WPARAM)32,
				(LPARAM)meanings);
			//4.4.2 단어카드철 프레임윈도위 단어카드철에서 찾는다.
			WordCardBinder_FindByMeanings(wordCardBinder, meanings, &indexes, &count);
		}
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
		SetProp(hWnd, "FINDINGCOUNT", (HANDLE)count);
		//4.5 찾은 단어카드가 있으면
		if (count > 0)
		{
			//4.5.1 찾은 단어카드들 중에 첫번째 단어카드를 출력한다.
			current = 0;
			SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)
				indexes[current]->word.spellings);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0, (LPARAM)
				indexes[current]->word.partOfSpeech);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)
				indexes[current]->word.meanings);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)
				indexes[current]->word.example);
		}
		//4.6 찾는 단어카드가 없으면
		else
		{
			//4.6.1 공란을 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)"");
		}
	}
	return TRUE;
}

//FindingForm_OnChooseButtonClicked
BOOL FindingForm_OnChooseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;
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
	WordCard* (*indexes);
	Long current;
	HWND wordCardBinderForm;

	//5. 선택하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 단어카드의 위치를 읽는다.
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		//5.2 단어카드철 프레임 윈도우를 찾는다.
		wordCardBinderForm = FindWindow("#32770", "단어카드철");
		//5.3 단어카드철 프레임 윈도우에 선택한 단어카드를 출력한다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.spellings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.partOfSpeech);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.meanings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.example);
		//5.4 단어카드철 프레임윈도우의 단어카드철에서 현재단어카드를 선택한 단어카드로 바꾼다.
		wordCardBinder = (WordCardBinder*)GetWindowLong(wordCardBinderForm, GWL_USERDATA);
		WordCardBinder_Move(wordCardBinder, indexes[current]);
		//5.5 단어카드철 프레임윈도우의 색인철에서 찾는다.
		indexBinder = (IndexBinder*)GetProp(wordCardBinderForm, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, indexes[current]->word.spellings[0]);
		//5.6 단어카드철 프레임윈도우의 트리뷰컨트롤에서 찾은 색인의 알파벳 항목과 동일한 알파벳 항목을 찾는다.
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
		//5.7 단어카드철 프레임윈도우에서 트리뷰 컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hAlphabet);
		item.mask = TVIF_TEXT;
		item.pszText = spellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hSpellings != NULL && strcmp(spellings, indexes[current]->word.spellings) != 0)
		{
			hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hSpellings);
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//5.8 단어카드철 프레임윈도우에서 트리뷰컨트롤의 철자항목에서 현재 단어카드의 품사를 찾는다.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hSpellings);
		item.mask = TVIF_TEXT;
		item.pszText = partOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hPartOfSpeech != NULL && strcmp(partOfSpeech, indexes[current]->word.partOfSpeech) != 0)
		{
			hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hPartOfSpeech);
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//5.9 단어카드철 프레임윈도우에서 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hPartOfSpeech);
		item.mask = TVIF_TEXT;
		item.pszText = meanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
			(LPARAM)&item);
		while (hMeanings != NULL && strcmp(meanings, indexes[current]->word.meanings) != 0)
		{
			hMeanings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
				TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hMeanings);
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0,
				(LPARAM)&item);
		}
		//5.10 단어카드철 프레임윈도우의 트리뷰컨트롤에서 "Alphabet"항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//5.11 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//5.12 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 철자항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//5.13 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//5.14 단어카드철 프레임윈도우의 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//5.15 윈도우를 닫는다.
		if (indexes != NULL)
		{
			free(indexes);
		}
		RemoveProp(hWnd, "FINDINGCOUNT");
		RemoveProp(hWnd, "CURRENTPOSITION");
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//FindingForm_OnFirstButtonClicked
BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	WordCard* (*indexes);
	//6. 처음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 찾은 단어카드 중 첫번째 단어카드를 출력한다.
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = 0;
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.example);
	}
	return TRUE;
}

//FindingForm_OnPreviousButtonClicked
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	WordCard* (*indexes);
	//7. 이전버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//7.1 찾은 단어카드 중 현재 단어카드의 이전 단어카드를 출력한다.
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		current--;
		if (current < 0)
		{
			current = 0;
		}
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.example);
	}
	return TRUE;
}

// FindingForm_OnNextButtonClicked
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	Long count;
	WordCard* (*indexes);
	//8. 다음버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//8.1 찾은 단어카드 중 현재 단어카드의 다음 단어카드를 출력한다.
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "CURRENTPOSITION");
		count = (Long)GetProp(hWnd, "FINDINGCOUNT");
		current++;
		if (current >= count)
		{
			current = count - 1;
		}
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.example);
	}
	return TRUE;
}

//FindingForm_OnLastButtonClicked
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long current;
	Long count;
	WordCard* (*indexes);
	//9. 마지막버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//9.1 찾은 단어카드 중 마지막 단어카드를 출력한다.
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "FINDINGCOUNT");
		current = count - 1;
		SetProp(hWnd, "CURRENTPOSITION", (HANDLE)current);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)indexes[current]->word.example);
	}
	return TRUE;
}

//OnClose
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//10. 닫기 버튼을 클릭했을 때
	WordCard* (*indexes);

	//10.1 윈도우를 닫는다.
	indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL)
	{
		free(indexes);
	}
	RemoveProp(hWnd, "FINDINGCOUNT");
	RemoveProp(hWnd, "CURRENTPOSITION");
	EndDialog(hWnd, 0);

	return TRUE;
}