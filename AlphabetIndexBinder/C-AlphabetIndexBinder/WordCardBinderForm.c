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
	//1. �����찡 ������ ��
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

	//1.1 �ܾ�ī��ö�� �����.
	wordCardBinder = (WordCardBinder*)malloc(sizeof(WordCardBinder));
	WordCardBinder_Create(wordCardBinder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordCardBinder);
	//1.2 ����ö�� �����.
	indexBinder = (IndexBinder*)malloc(sizeof(IndexBinder));
	IndexBinder_Create(indexBinder);
	SetProp(hWnd, "INDEXBINDER", (HANDLE)indexBinder);
	//1.3 �ܾ�ī��ö���� �����Ѵ�.
	count = WordCardBinder_Load(wordCardBinder);
	//1.4 ������ ������ŭ ����ö�� �����.
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
	//1.5 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = "Alphabets";
	hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
		(LPARAM)&insertStruct);
	//1.6 ���簡 �Ǿ�����
	if (count > 0)
	{
		//1.6.1 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
		firstCard = WordCardBinder_First(wordCardBinder);
		//1.6.2 �ܾ�ī��ö�� ù��° �ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)firstCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)firstCard->word.example);
		//1.6.3 ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//1.6.4 ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//1.6.4.1 Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM,
				0, (LPARAM)&insertStruct);
			//1.6.4.2 ���ο� ����� �ܾ�ī�� ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//1.6.4.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = Index_GetAt(indexes + i, j);
				//1.6.4.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//1.6.4.2.3 ö���ߺ��� ������(�ߺ��Ǵ� ��� �ٷ� Ż���ؼ� �������� �ݺ��� �����Ŵ)(�̹� �ߺ��� �ִ� ���� Ʈ���信 �� �߰��Ǿ� �ֱ� ������)
				if (isDuplicatedSpellings == FALSE)
				{
					//1.6.4.2.3.1 Ʈ������Ʈ���� ���ĺ��׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
						TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//1.6.4.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//1.6.4.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					m = 0;
					while (m < arrayCount)
					{
						//1.6.4.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//1.6.4.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//1.6.4.2.3.3.2.1 Ʈ���� ��Ʈ�ѿ� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//1.6.4.2.3.3.2.2 Ʈ���� ��Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);
						
						}
						//1.6.4.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//1.6.4.2.3.3.3.1 ���� ǰ�縦 ã�´�.
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
							//1.6.4.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//1.6.5 ����ö���� ã�´�.
		indexLink = IndexBinder_Find(indexBinder, firstCard->word.spellings[0]);
		//1.6.6 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//1.6.7 ���ο��� ã�´�.
		//arrayIndex = Index_Find(indexLink, firstCard);
		//1.6.8 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//1.6.9 Ʈ������Ʈ���� ö���׸񿡼� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
		//1.6.10 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//1.6.11 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//1.6.12 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//1.6.13 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//1.6.14 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//1.6.15 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//1.6.16 ���ι迭�� �Ҵ������Ѵ�.
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
	//2. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ����� ������ �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKINGINFORM), NULL,
			TakingInFormProc);
	}
	return TRUE;
}

//WordCardBinderForm_OnFindButtonClicked
BOOL WordCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//3.1 ã�������� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL,
			FindingFormProc);
	}
	return TRUE;
}

// WordCardBinderForm_OnTakeOutButtonClicked
BOOL WordCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4. ������ ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 ������ ������ �����츦 ����Ѵ�.
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

	//5. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 ����ö���� �����Ѵ�.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		IndexBinder_Arrange(indexBinder);
		//5.2 ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//5.3 Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
		//5.4 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "Alphabets";
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
			(LPARAM)&insertStruct);
		//5.5 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		firstCard = WordCardBinder_First(wordCardBinder);
		//5.6 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, (LPARAM)firstCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)firstCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, (LPARAM)firstCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, (LPARAM)firstCard->word.example);
		//5.7 ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//5.7.1 Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM,
				0, (LPARAM)&insertStruct);
			//5.7.2 ���ο� ����� �ܾ�ī�� ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//5.7.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = Index_GetAt(indexes + i, j);
				//5.7.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//5.7.2.3 ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//5.7.2.3.1 Ʈ������Ʈ���� ���ĺ��׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX),
						TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//5.7.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//5.7.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					m = 0;
					while (m < arrayCount)
					{
						//5.7.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//5.7.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//5.7.2.3.3.2.1 Ʈ���� ��Ʈ�ѿ� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//5.7.2.3.3.2.2 Ʈ���� ��Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0,
								(LPARAM)&insertStruct);

						}
						//5.7.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//5.7.2.3.3.3.1 ���� ǰ�縦 ã�´�.
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
							//5.7.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//5.8 ����ö���� ã�´�.
		indexLink = IndexBinder_Find(indexBinder, firstCard->word.spellings[0]);
		//5.9 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//5.10 ���ο��� ã�´�.
		//arrayIndex = Index_Find(indexLink, firstCard);
		//5.11 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//5.12 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� ǰ��� ������ ǰ�縦 ã�´�.
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
		//5.13 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//5.14 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//5.15 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//5.16 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//5.17 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//5.18 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//5.19 ���ι迭�� �Ҵ������Ѵ�.
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

	//6. ó������ �̵��ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_First(wordCardBinder);
		//6.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//6.3 ����ö���� ã�´�.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//6.4 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//6.5 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//6.6 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� ǰ��� ������ ǰ�縦 ã�´�.
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
		//6.7 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//6.8 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//6.9 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//6.10 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//6.11 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//6.12 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
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

	//7. �������� �̵��ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//7.1 �ܾ�ī��ö���� �������� �̵��Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Previous(wordCardBinder);
		//7.2 �ܾ�ī��ö�� ����ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//7.3 ����ö���� ã�´�.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//7.4 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//7.5 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//7.6 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� ǰ��� ������ ǰ�縦 ã�´�.
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
		//7.7 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//7.8 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//7.9 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//7.10 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//7.11 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//7.12 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
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
	//8. �������� �̵��ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//8.1 �ܾ�ī��ö���� �������� �̵��Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Next(wordCardBinder);
		//8.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//8.3 ����ö���� ã�´�.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//8.4 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//8.5 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//8.6 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� ǰ��� ������ ǰ�縦 ã�´�.
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
		//8.7 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//8.8 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//8.9 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//8.10 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//8.11 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//8.12 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
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

	//9. ���������� �̵��ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//9.1 �ܾ�ī��ö���� ���������� �̵��Ѵ�.
		wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		currentCard = WordCardBinder_Last(wordCardBinder);
		//9.2 �ܾ�ī��ö�� ����ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0, 
			(LPARAM)currentCard->word.example);
		//9.3 ����ö���� ã�´�.
		indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//9.4 Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//9.5 Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//9.6 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� ǰ��� ������ ǰ�縦 ã�´�.
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
		//9.7 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//9.8 Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//6.9 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//9.10 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//9.11 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//9.12 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
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

	//10. Ʈ���� ��Ʈ�ѿ��� �ǹ̸� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//10.1 Ʈ���� ��Ʈ�ѿ��� ����Ŭ���� �ǹ��׸��� ��ġ�� �д´�.
		hMeanings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CARET, (LPARAM)NULL);
		//10.2 Ʈ���� ��Ʈ�ѿ��� ����Ŭ���� �ǹ��׸��� �θ�������(ǰ���׸�)�� ��ġ�� �д´�.
		hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hMeanings);
		//10.3 Ʈ���� ��Ʈ�ѿ��� ���� ǰ���׸��� �θ�������(ö���׸�)�� ��ġ�� �д´�.
		hSpellings = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hPartOfSpeech);
		//10.4 Ʈ���� ��Ʈ�ѿ��� ���� ö���׸��� �θ�������(���ĺ��׸�)�� ��ġ�� �д´�.
		hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hSpellings);
		//10.5 Ʈ���� ��Ʈ�ѿ��� "Alphabets" �׸��� ��ġ�� �д´�.
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hAlphabet);
		//10.6 Ʈ���� ��Ʈ�ѿ��� ����Ŭ���� �׸��� �ǹ��׸��� ������
		if (hAlphabets != NULL && hAlphabet != NULL && hSpellings != NULL && hPartOfSpeech != NULL
			&& hMeanings != NULL)
		{
			//10.6.1 Ʈ������Ʈ�ѿ��� ��ġ�� ���� �ǹ��׸��� �ǹ̸� �д´�.
			item.mask = TVIF_TEXT;
			item.pszText = meanings;
			item.cchTextMax = 32;
			item.hItem = hMeanings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.2 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ǰ���׸��� ǰ�縦 �д´�.
			item.mask = TVIF_TEXT;
			item.pszText = partOfSpeech;
			item.cchTextMax = 8;
			item.hItem = hPartOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.3 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ö���׸��� ö�ڸ� �д´�.
			item.mask = TVIF_TEXT;
			item.pszText = spellings;
			item.cchTextMax = 64;
			item.hItem = hSpellings;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.4 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ���ĺ��׸��� ���ĺ��� �д´�.
			item.mask = TVIF_TEXT;
			item.pszText = alphabet;
			item.cchTextMax = 2;
			item.hItem = hAlphabet;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_ALPHABETINDEX), TVM_GETITEM, 0, (LPARAM)&item);
			//10.6.5 ����ö���� ã�´�.
			indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
			index = IndexBinder_Find(indexBinder, alphabet[0]);
			//10.6.6 ���ο� ����� �ܾ�ī�尳����ŭ �׸��� currentWordCard�� null�ε��� �ݺ��Ѵ�.
			i = 0;
			while (i < index->length && currentCard == NULL)
			{
				//10.6.6.1 ���ο� ����� �ܾ�ī���� �ּҸ� �˾Ƴ���.
				wordCard = Index_GetAt(index, i);
				//10.6.6.2 ö�ڰ� ���� ǰ�簡 ���� �ǹ̰� ������
				if (strcmp(wordCard->word.spellings, spellings) == 0 && strcmp(wordCard->word.partOfSpeech,
					partOfSpeech) == 0 && strcmp(wordCard->word.meanings, meanings) == 0)
				{
					//10.6.6.2.1 �ܾ�ī���� ��ġ�� �����Ѵ�.
					currentCard = wordCard;
				}
				i++;
			}
			//10.6.7 �ܾ�ī��ö���� ������ �ܾ�ī���� ��ġ�� �̵��Ѵ�.
			wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
			currentCard = WordCardBinder_Move(wordCardBinder, currentCard);
			//10.6.8 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
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
	//11. �ݱ� ��ư�� Ŭ������ ��
	WordCardBinder* wordCardBinder;
	IndexBinder* indexBinder;

	wordCardBinder = (WordCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
	indexBinder = (IndexBinder*)GetProp(hWnd, "INDEXBINDER");
	if (wordCardBinder != NULL && indexBinder != NULL)
	{
		//11.1 �ܾ�ī��ö�� �����Ѵ�.
		WordCardBinder_Save(wordCardBinder);
		//11.2 ����ö�� ���ش�.
		IndexBinder_Destroy(indexBinder);
		free(indexBinder);
		RemoveProp(hWnd, "INDEXBINDER");
		//11.3 �ܾ�ī��ö�� ���ش�.
		WordCardBinder_Destroy(wordCardBinder);
		free(wordCardBinder);
	}
	//10.3 �����츦 �ݴ´�.
	EndDialog(hWnd, 0);
	return TRUE;
}
