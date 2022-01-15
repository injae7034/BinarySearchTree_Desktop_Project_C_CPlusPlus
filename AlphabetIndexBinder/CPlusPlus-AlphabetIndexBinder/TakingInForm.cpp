#include "TakingInForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "WordCard.h"
#include "resource.h"
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl �������
#include<afxwin.h>//CDialog �������

BEGIN_MESSAGE_MAP(TakingInForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakingInForm::TakingInForm(CWnd* parent)
	:CDialog(TakingInForm::IDD, parent)
{

}

//1. ����� �����찡 ������ ��
BOOL TakingInForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 ǰ���޺��ڽ��� �׸���� �߰��Ѵ�.
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
	while (i < sizeof(partOfSpeechs) / sizeof(partOfSpeechs[0]))
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_PARTOFSPEECH))->AddString(partOfSpeechs[i]);
		i++;
	}
	//1.2 ������.
	return FALSE;
}

//2. ������ư�� Ŭ������ ��
void TakingInForm::OnTakeInButtonClicked()
{
	//2.1 ö��, ǰ��, �ǹ�, ���ø� �д´�.
	CString spellings;
	GetDlgItem(IDC_EDIT_SPELLINGS)->GetWindowText(spellings);
	CString partOfSpeech;
	GetDlgItem(IDC_COMBO_PARTOFSPEECH)->GetWindowText(partOfSpeech);
	CString meanings;
	GetDlgItem(IDC_EDIT_MEANINGS)->GetWindowText(meanings);
	CString example;
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);
	//2.2 �ܾ�ī��ö ������ �����츦 ã�´�.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//2.3 ���� ������ wordCard�� �����Ѵ�.
	WordCard card((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings, (LPCTSTR)example);
	//2.4 ������ wordCard�� �ߺ��Ǵ��� Ȯ���Ѵ�.
	Index* index = wordCardBinderForm->indexBinder->Find(card.GetSpellings()[0]);
	BOOL isDuplicatedWordCard = FALSE;
	Long i = 0;
	//���ĺ� ������ ������
	if (index != 0)
	{
		while (i < index->GetLength() && isDuplicatedWordCard == FALSE)
		{
			//2.4.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
			WordCard* cardLink = index->GetAt(i);
			//2.4.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
			if (card.GetSpellings().compare(cardLink->GetSpellings()) == 0)
			{
				//2.4.2.1 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ǰ���ߺ��� �ִ��� Ȯ���Ѵ�.
				if (card.GetPartOfSpeech().compare(cardLink->GetPartOfSpeech()) == 0)
				{
					//2.4.2.1.1 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� �ǹ��ߺ��� �ִ��� Ȯ���Ѵ�.
					if (card.GetMeanings().compare(cardLink->GetMeanings()) == 0)
					{
						isDuplicatedWordCard = TRUE;
					}
				}
			}
			i++;
		}
	}
	//2.5 ���ĺ������� ���ų� �ܾ�ī�尡 �ߺ��� �ȵǸ�
	if (index == 0 || isDuplicatedWordCard == FALSE)
	{
		//2.5.1 �ܾ�ī��ö ������ �������� �ܾ�ī��ö���� �����.
		WordCard* current = wordCardBinderForm->wordCardBinder->TakeIn(card);
		//2.5.2 �����ͺ��̽����� �����.
		wordCardBinderForm->Insert(current);
		//2.5.3 �ܾ�ī��ö ������ �������� ����ö�� �����.
		index = wordCardBinderForm->indexBinder->TakeIn(current);
		//2.5.4 �ܾ�ī��ö ������ �����쿡 ���� �ܾ�ī�带 ����Ѵ�.
		spellings = CString(current->GetSpellings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		meanings = CString(current->GetMeanings().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_MEANINGS)->SetWindowText(meanings);
		example = CString(current->GetExample().c_str());
		wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIIT_EXAMPLE)->SetWindowText(example);
		//2.5.5 ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		wordCardBinderForm->indexBinder->MakeList(&indexes, &count);
		//2.5.6 Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
		//2.5.7 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
		TVINSERTSTRUCT insertStruct = { 0, };
		insertStruct.hParent = TVI_ROOT;
		insertStruct.item.mask = TVIF_TEXT;
		insertStruct.item.pszText = (LPSTR)"Alphabets";
		HTREEITEM hAlphabets = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
		//2.5.8 ���ΰ�����ŭ �ݺ��Ѵ�.
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
			//2.5.8.1 Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//2.5.8.2 ���ο� ����� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//2.5.8.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = indexes[i].GetAt(j);
				//2.5.8.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//2.5.8.2.2.3 ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//2.5.8.2.2.3.1 Ʈ������Ʈ���� ���ĺ� �׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//2.5.8.2.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//2.5.8.2.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					Long m = 0;
					while (m < arrayCount)
					{
						//2.5.8.2.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//2.5.8.2.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//2.5.8.2.2.3.3.2.1 Ʈ������Ʈ���� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//2.5.8.2.2.3.3.2.2 Ʈ������Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//2.5.8.2.2.3.3.2 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//2.5.8.2.2.3.3.2.1 ���� ǰ�縦 ã�´�.
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
							//2.5.8.2.2.3.3.2.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
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
		//2.5.9 ����ö���� ������ ã�´�.
		index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
		//2.5.10 ã�� ������ ���ĺ��� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
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
		//2.5.11 Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
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
		//2.5.12 Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
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
		//2.5.13 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
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
		//2.5.14 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//2.5.15 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//2.5.16 Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//2.5.17 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//2.5.18 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//2.5.19 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
		//2.5.20 �����츦 �ݴ´�.
		EndDialog(0);
	}
	//2.6 �ܾ�ī�尡 �ߺ��Ǹ�
	else
	{
		//2.6.1 "�ܾ�ī�尡 �ߺ��Ǿ����ϴ�." �޼����ڽ��� ����Ѵ�.
		int messageBoxButton = MessageBox("�ܾ�ī�尡 �ߺ��Ǿ����ϴ�.", "����� ������", MB_OK);
    }
}

//3. �ݱ��ư�� Ŭ������ ��
void TakingInForm::OnClose()
{
	//3.1 �����츦 �ݴ´�.
	EndDialog(0);
}