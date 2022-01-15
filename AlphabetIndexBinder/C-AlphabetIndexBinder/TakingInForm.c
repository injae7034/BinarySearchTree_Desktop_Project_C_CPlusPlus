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
	//1. ����� ������ �����찡 ������ ��
	TCHAR partOfSpeechs[][8] = {
		"���",
		"����",
		"����",
		"�����",
		"�λ�",
		"��ġ��",
		"���ӻ�",
		"��ź��"
	};
	Long i = 0;

	//1.1 ǰ�� �޺��ڽ��� �׸���� �߰��Ѵ�.
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

	//2 ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 ö��, ǰ��, �ǹ�, ���ø� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLINGS), WM_GETTEXT, (WPARAM)64, 
			(LPARAM)card.word.spellings);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PARTOFSPEECH), WM_GETTEXT, (WPARAM)8,
			(LPARAM)card.word.partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANINGS), WM_GETTEXT, (WPARAM)32,
			(LPARAM)card.word.meanings);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128,
			(LPARAM)card.word.example);
		//2.2 �ܾ�ī��ö ������ �����츦 ã�´�.
		wordCardBinderForm = FindWindow("#32770", "�ܾ�ī��ö");
		//2.3 �ܾ�ī��ö �������������� �ܾ�ī��ö���� �����.
		wordCardBinder = (WordCardBinder*)GetWindowLong(wordCardBinderForm, GWL_USERDATA);
		currentCard = WordCardBinder_TakeIn(wordCardBinder, card);
		//2.4 �ܾ�ī��ö ������ �������� ����ö���� �����.
		indexBinder = (IndexBinder*)GetProp(wordCardBinderForm, "INDEXBINDER");
		indexLink = IndexBinder_TakeIn(indexBinder, currentCard);
		//2.5 �ܾ�ī��ö ������ �����쿡 ���� �ܾ�ī�带 ����Ѵ�.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_SPELLINGS), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.spellings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_PARTOFSPEECH), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.partOfSpeech);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_MEANINGS), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.meanings);
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_STATIC_EDIT_EXAMPLE), WM_SETTEXT, 0,
			(LPARAM)currentCard->word.example);
		//2.6 �ܾ�ī��ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		IndexBinder_MakeList(indexBinder, &indexes, &count);
		//2.7 �ܾ�ī��ö ������ �������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_DELETEITEM, 0,
			(LPARAM)TVI_ROOT);
		//2.8 �ܾ�ī��ö ������ �������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = "Alphabets";
		hAlphabets = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX),
			TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
		//2.9 �ܾ�ī��ö �����������쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//2.9.1 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexesAlphabet[0] = indexes[i].alphabet;
			indexesAlphabet[1] = '\0';
			insertStruct.item.pszText = indexesAlphabet;
			hAlphabet = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
				TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
			//2.9.2 �ܾ�ī��ö �����������쿡�� ���ο� ����� �ܾ�ī�� ������ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < indexes[i].length)
			{
				//2.9.2.1 �ܾ�ī��ö �����������쿡�� ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = Index_GetAt(indexes + i, j);
				//2.9.2.2 �ܾ�ī��ö �����������쿡�� �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//2.9.2.3 �ܾ�ī��ö �����������쿡�� ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//2.9.2.3.1 �ܾ�ī��ö �����������쿡�� Ʈ������Ʈ���� ���ĺ��׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = wordCard->word.spellings;
					hSpellings = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm, 
						IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
					//2.9.2.3.2 �ܾ�ī��ö �����������쿡�� ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Index_FindBySpellings(indexes + i, wordCard->word.spellings, &arrayIndexes,
						&arrayCount);
					//2.9.2.3.3 �ܾ�ī��ö �����������쿡�� ã�� ������ŭ �ݺ��Ѵ�.
					m = 0;
					while (m < arrayCount)
					{
						//2.9.2.3.3.1 �ܾ�ī��ö �����������쿡�� �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//2.9.2.3.3.2 �ܾ�ī��ö �����������쿡�� ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//2.9.2.3.3.2.1 �ܾ�ī��ö �����������쿡�� Ʈ���� ��Ʈ�ѿ� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = wordCard->word.partOfSpeech;
							hPartOfSpeech = (HTREEITEM)SendMessage(GetDlgItem(wordCardBinderForm,
								IDC_TREE_ALPHABETINDEX), TVM_INSERTITEM, 0, (LPARAM)&insertStruct);
							//2.9.2.3.3.2.2 �ܾ�ī��ö �����������쿡�� Ʈ���� ��Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = wordCard->word.meanings;
							SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), 
								TVM_INSERTITEM, 0, (LPARAM)&insertStruct);

						}
						//2.9.2.3.3.3 �ܾ�ī��ö �����������쿡�� ǰ�簡 �ߺ��Ǹ�
						else
						{
							//2.9.2.3.3.3.1 �ܾ�ī��ö �����������쿡�� ���� ǰ�縦 ã�´�.
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
							//2.9.2.3.3.3.2 �ܾ�ī��ö �����������쿡�� ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//2.10 �ܾ�ī��ö �������������� ����ö���� ã�´�.
		indexLink = IndexBinder_Find(indexBinder, currentCard->word.spellings[0]);
		//2.11 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ã�� ������ ���ĺ� �׸�� ������ ���ĺ� �׸��� ã�´�.
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
		//2.12 �ܾ�ī��ö �����������쿡�� Ʈ���� ��Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//2.13 �ܾ�ī��ö �����������쿡�� Ʈ������Ʈ���� ö���׸񿡼� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
		//2.14 �ܾ�ī��ö �����������쿡�� Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//2.15 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabet"�׸��� ��ģ��.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabets);
		//2.16 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hAlphabet);
		//2.17 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hSpellings);
		//2.18 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hPartOfSpeech);
		//2.19 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		SendMessage(GetDlgItem(wordCardBinderForm, IDC_TREE_ALPHABETINDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET,
			(LPARAM)hMeanings);
		//2.20 ���ι迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			free(indexes);
		}
		//2.21 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

//OnClose
BOOL TakingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//3. �ݱ� ��ư�� Ŭ������ ��
	//3.1 �����츦 �ݴ´�.
	EndDialog(hWnd, 0);
	return TRUE;
}