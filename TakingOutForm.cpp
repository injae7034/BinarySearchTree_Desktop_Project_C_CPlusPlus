#include "TakingOutForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "resource.h"
#include "IndexBinder.h"
#include<afxwin.h>//CDialog�������
#include<afxcmn.h>//CTreeCtrl �������


BEGIN_MESSAGE_MAP(TakingOutForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingOutForm::TakingOutForm(CWnd* parent)
	:CDialog(TakingOutForm::IDD, parent)
{

}

//1. ������ �����찡 ������ ��
BOOL TakingOutForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 �ܾ�ī��ö ������ �����츦 ã�´�.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//1.2 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� ���� �ܾ�ī���� ��ġ�� �д´�.
	WordCard* current = wordCardBinderForm->wordCardBinder->GetCurrent();
	//1.3 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� ������.
	WordCard card = wordCardBinderForm->wordCardBinder->TakeOut(current);
	//1.4 �����ͺ��̽����� ���� �ܾ�ī�带 �����.
	wordCardBinderForm->Delete(&card);
	//1.5 �ܾ�ī��ö ������ �������� ����ö���� ������.
	wordCardBinderForm->indexBinder->TakeOut(card.GetSpellings()[0], current);
	//1.6 ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(card.GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(card.GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(card.GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(card.GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIIT_EXAMPLE)->SetWindowText(example);
	//1.7 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
	//1.8 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"Alphabets";
	HTREEITEM hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
	//1.9 �ܾ�ī��ö ������ �������� �ܾ�ī��ö�� �ܾ�尡 ����������
	current = wordCardBinderForm->wordCardBinder->GetCurrent();
	if (current != NULL)
	{
		//1.6.1 �ܾ�ī��ö ������ �����쿡 ���� �ܾ�ī�带 ����Ѵ�.
		spellings = CString(current->GetSpellings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		meanings = CString(current->GetMeanings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_MEANINGS)->SetWindowText(meanings);
		example = CString(current->GetExample().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_EXAMPLE)->SetWindowText(example);
		//1.9.2 �ܾ�ī��ö ������ �������� ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		wordCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//1.9.3 �ܾ�ī��ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		HTREEITEM hAlphabet;
		HTREEITEM hSpellings;
		HTREEITEM hPartOfSpeech;
		TCHAR indexAlphabet[2];
		TCHAR tPartOfSpeech[8];
		WordCard* wordCard;
		WordCard* otherCard;
		Long i = 0;
		while (i < count)
		{
			//1.9.3.1 �ܾ�ī��ö ������ �������� Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//1.9.3.2 ���ο� ����� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//1.9.3.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = indexes[i].GetAt(j);
				//1.9.3.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//1.9.3.2.3 ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//1.9.3.2.3.1 Ʈ������Ʈ���� ���ĺ� �׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//1.9.3.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//1.9.3.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					Long m = 0;
					while (m < arrayCount)
					{
						//1.9.3.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//1.9.3.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//1.9.3.2.3.3.2.1 Ʈ������Ʈ���� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//1.9.3.2.3.3.2.2 Ʈ������Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//1.9.3.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//1.9.3.2.3.3.3.1 ���� ǰ�縦 ã�´�.
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
							//1.9.3.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//1.9.4 �ܾ�ī��ö �������������� ����ö���� ������ ã�´�
		Index *index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
		//1.9.5 ã�� ������ ���ĺ��� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
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
		//1.9.6 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//1.9.7 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
		//1.9.8 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//1.9.9 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//1.9.10 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//1.9.11 �ܾ�ī��ö �������������� Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//1.9.12 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//1.9.13 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//1.9.14 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
	}
	//1.10 �ܾ�ī��ö ������ �������� �ܾ�ī��û�� �����ִ� �ܾ�ī�尡 ������
	else
	{
		//1.7.1 �ܾ�ī��ö ������ �����쿡 ������ ����Ѵ�.
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText("");
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText("");
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText("");
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText("");
	}
	return FALSE;
}

//2. �ݱ��ư�� Ŭ������ ��
void TakingOutForm::OnClose()
{
	//2.1 "����ðڽ��ϱ�?" �޼����ڽ��� ����Ѵ�.
	int messageBoxButton = MessageBox("����ðڽ��ϱ�?", "������ ������", MB_YESNOCANCEL);
	//2.2 "��" ��ư�� Ŭ������ ��
	if (messageBoxButton == IDYES)
	{
		//2.2.1 �ܾ�ī���� ������ �д´�.
		CString spellings;
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->GetWindowText(spellings);
		CString partOfSpeech;
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->GetWindowText(partOfSpeech);
		CString meanings;
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->GetWindowText(meanings);
		CString example;
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->GetWindowText(example);
		//2.2.2 ���� ������ wordCard�� �����Ѵ�.
		WordCard card((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings, (LPCTSTR)example);
		//2.2.3 �ܾ�ī��ö ������ �����츦 ã�´�.
		WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
		//2.2.4 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� �����.
		WordCard* current = wordCardBinderForm->wordCardBinder->TakeIn(card);
		//2.2.5 �����ͺ��̽����� �����Ѵ�.
		wordCardBinderForm->Insert(current);
		//2.2.6 �ܾ�ī��ö ������ �������� ����ö���� �����.
		Index* index = wordCardBinderForm->indexBinder->TakeIn(current);
		//2.2.7 �ܾ�ī��ö ������ �����쿡 ���� �ܾ�ī�带 ����Ѵ�.
		spellings = CString(current->GetSpellings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		meanings = CString(current->GetMeanings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_MEANINGS)->SetWindowText(meanings);
		example = CString(current->GetExample().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_EXAMPLE)->SetWindowText(example);
		//2.2.8 �ܾ�ī��ö ������ ������ ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		wordCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//2.2.9 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
		//2.2.10 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
		TVINSERTSTRUCT insertStruct = { 0, };
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = (LPSTR)"Alphabets";
		HTREEITEM hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
		//2.2.11 �ܾ�ī��ö ������ �����쿡�� ���ΰ�����ŭ �ݺ��Ѵ�.
		HTREEITEM hAlphabet;
		HTREEITEM hSpellings;
		HTREEITEM hPartOfSpeech;
		TCHAR indexAlphabet[2];
		TCHAR tPartOfSpeech[8];
		WordCard* wordCard;
		WordCard* otherCard;
		Long i = 0;
		while (i < count)
		{
			//2.2.11.1 �ܾ�ī��ö ������ �������� Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//2.2.11.2 ���ο� ����� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//2.2.11.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = indexes[i].GetAt(j);
				//2.2.11.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//2.2.11.2.3  ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//2.2.11.2.3.1 Ʈ������Ʈ���� ���ĺ� �׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//2.2.11.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//2.2.11.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					Long m = 0;
					while (m < arrayCount)
					{
						//2.2.11.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//2.2.11.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//2.2.11.2.3.3.2.1 Ʈ������Ʈ���� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//2.2.11.2.3.3.2.2 Ʈ������Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//2.2.11.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//2.2.11.2.3.3.3.1 ���� ǰ�縦 ã�´�.
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
							//2.2.11.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//2.2.12 �ܾ�ī��ö ������ �������� ����ö���� ã�´�.
		index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
		//2.2.13 ã�� ������ ���ĺ��� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
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
		//2.2.14 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//2.2.15 �ܾ�ī��ö �������������� Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
		//2.2.16 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//2.2.17 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//2.2.18 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//2.2.19 �ܾ�ī��ö �������������� Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//2.2.20 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//2.2.21 �ܾ�ī��ö �������������� Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//2.2.22 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
		//2.2.23 �����츦 �ݴ´�.
		EndDialog(0);
	}
	//2.3 "�ƴϿ�"��ư�� Ŭ������ ��
	if (messageBoxButton == IDNO)
	{
		//2.3.1 �����츦 �ݴ´�.
		EndDialog(0);
	}
}