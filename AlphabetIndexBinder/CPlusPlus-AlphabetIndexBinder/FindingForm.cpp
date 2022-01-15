#include "FindingForm.h"
#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "WordCard.h"
#include "resource.h"
#include<afxwin.h>//CDialog Çì´õÆÄÀÏ
#include "IndexBinder.h"
#include<afxcmn.h>//CTreeCtrl Çì´õÆÄÀÏ


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

//1. Ã£±â À©µµ¿ì°¡ »ý¼ºµÄ ¶§
BOOL FindingForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 Ã¶ÀÚ¶óµð¿À¹öÆ°À» checkÇÑ´Ù.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_CHECKED);
	//1.2 ÀÇ¹Ì¶óµð¿À¹öÆ°À» uncheckÇÑ´Ù.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//1.3 ³¡³»´Ù.
	return FALSE;
}

//2. Ã¶ÀÚ¶óµð¿À ¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnSpellingsRadioButtonClicked()
{
	//2.1 ÀÇ¹Ì¶óµð¿À ¹öÆ°À» uncheckÇÑ´Ù.
	((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->SetCheck(BST_UNCHECKED);
	//2.2 ÀÇ¹Ì¿¡µðÆ®¸¦ °ø¶õÀ¸·Î ¸¸µç´Ù.
	GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->SetWindowText("");
}

//3. ÀÇ¹Ì¶óµð¿À ¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnMeaningsRadioButtonClicked()
{
	//3.1 Ã¶ÀÚ¶óµð¿À¹öÆ°À» uncheckÇÑ´Ù.
	((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->SetCheck(BST_UNCHECKED);
	//3.2 Ã¶ÀÚ¿¡µðÆ®¸¦ °ø¶õÀ¸·Î ¸¸µç´Ù.
	GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->SetWindowText("");
}

//4. Ã£±â ¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnFindButtonClicked()
{
	//4.1 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ì¸¦ Ã£´Â´Ù.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "´Ü¾îÄ«µåÃ¶");
	//ÇÒ´çÇØÁ¦
	//FindingFormÀ» ´ÝÁö ¾ÊÀº »óÅÂ¿¡¼­ °è¼ÓÇØ¼­ Ã£±â ¹öÆ°À» ´©¸¦ °æ¿ì ¸Þ¸ð¸® ´©¼ö°¡ »ý±æ ¼ö ÀÖ±â ¶§¹®¿¡
	//Ã£±â¹öÆ°À» ´©¸¦ ¶§ ¸¶´Ù ±âÁ¸ÀÇ indexes¸¦ ÇÒ´çÇØÁ¦½ÃÄÑ¼­ ¸Þ¸ð¸® ´©¼ö¸¦ ¸·¾Æ¾ßÇÔ.
	if (this->indexes != NULL)
	{
		delete[]this->indexes;
	}
	//4.2 ¼±ÅÃµÈ ¶óµð¿À¹öÆ°À» ÀÐ´Â´Ù.
	int spellingsChecked = ((CButton*)GetDlgItem(IDC_RADIO_SPELLINGS))->GetCheck();
	int meaningsChecked = ((CButton*)GetDlgItem(IDC_RADIO_MEANINGS))->GetCheck();
	//4.3 Ã¶ÀÚ¶óµð¿À¹öÆ°ÀÌ ¼±ÅÃµÇ¾î ÀÖÀ¸¸é
	CString spellings;
	if (spellingsChecked == BST_CHECKED)
	{
		//4.3.1 Ã¶ÀÚ¸¦ ÀÔ·Â¹Þ´Â´Ù.
		GetDlgItem(IDC_EDIT_STATIC_SPELLINGS)->GetWindowText(spellings);
		//4.3.2 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ìÀÇ ´Ü¾îÄ«µåÃ¶¿¡¼­ Ã¶ÀÚ·Î Ã£´Â´Ù.
		wordCardBinderForm->wordCardBinder->FindBySpellings((LPCTSTR)spellings, &this->indexes, &this->count);
	}
	//4.4 ÀÇ¹Ì¶óµð¿À¹öÆ°ÀÌ ¼±ÅÃµÇ¾î ÀÖÀ¸¸é
	CString meanings;
	if (meaningsChecked == BST_CHECKED)
	{
		//4.4.1 ÀÇ¹Ì¸¦ ÀÔ·Â¹Þ´Â´Ù.
		GetDlgItem(IDC_EDIT_STATIC_MEANINGS)->GetWindowText(meanings);
		//4.4.2 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ìÀÇ ´Ü¾îÄ«µåÃ¶¿¡¼­ ÀÇ¹Ì·Î Ã£´Â´Ù.
		wordCardBinderForm->wordCardBinder->FindByMeanings((LPCTSTR)meanings, &this->indexes, &this->count);
	}
	//4.5 Ã£Àº ´Ü¾î°¡ ÀÖÀ¸¸é
	if (this->count > 0)
	{
		//4.5.1 Ã£Àº ´Ü¾îÄ«µåµé Áß¿¡¼­ Ã¹¹øÂ° ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
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
	//4.6 Ã£Àº ´Ü¾î°¡µå°¡ ¾øÀ¸¸é
	else
	{
		//4.6.1 °ø¶õÀ» Ãâ·ÂÇÑ´Ù.
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText("");
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText("");
	}
}

//5. ¼±ÅÃÇÏ±â ¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnChooseButtonClicked()
{
	//5.1 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ì¸¦ Ã£´Â´Ù.
	WordCardBinderForm* wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "´Ü¾îÄ«µåÃ¶");
	//5.2 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ì¿¡ ¼±ÅÃÇÑ ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
	CString spellings = CString(this->indexes[this->current]->GetSpellings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(this->indexes[this->current]->GetPartOfSpeech().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(this->indexes[this->current]->GetMeanings().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(this->indexes[this->current]->GetExample().c_str());
	wordCardBinderForm->GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.3 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓ À©µµ¿ìÀÇ ´Ü¾îÄ«µåÃ¶¿¡¼­ ÇöÀç ´Ü¾îÄ«µå¸¦ ¼±ÅÃÇÑ ´Ü¾îÄ«µå·Î ¹Ù²Û´Ù.
	WordCard* current = wordCardBinderForm->wordCardBinder->Move(this->indexes[this->current]);
	//5.4 ´Ü¾îÄ«µåÃ» ÇÁ·¹ÀÓ À©µµ¿ìÀÇ »öÀÎÃ¶¿¡¼­ »öÀÎÀ» Ã£´Â´Ù.
	Index *index = wordCardBinderForm->indexBinder->Find(current->GetSpellings()[0]);
	//5.5 Ã£Àº »öÀÎÀÇ ¾ËÆÄºª°ú ´Ü¾î¯‹Æ®Ã¶ ÇÁ·¹ÀÓ À©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ µ¿ÀÏÇÑ ¾ËÆÄºªÇ×¸ñÀ» Ã£´Â´Ù.
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
	//5.6 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·ÑÀÇ ¾ËÆÄºª Ç×¸ñ¿¡¼­ ÇöÀç ´Ü¾îÄ«µåÀÇ Ã¶ÀÚ¸¦ Ã£´Â´Ù.
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
	//5.7 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·ÑÀÇ Ã¶ÀÚÇ×¸ñ ¾Æ·¡¿¡¼­ ÇöÀç ´Ü¾îÄ«µåÀÇ Ç°»ç¸¦ Ã£´Â´Ù.
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
	//5.8 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ ÇöÀç Ãâ·ÂµÈ ´Ü¾îÄ«µåÀÇ ÀÇ¹Ì¿Í µ¿ÀÏÇÑ ÀÇ¹Ì¸¦ Ã£´Â´Ù.
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
	//5.9 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ "Alphabets"Ç×¸ñÀ» ÆîÄ£´Ù.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
	//5.10 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ ÇöÀç ´Ü¾îÄ«µå°¡ ¼ÓÇÏ´Â ¾ËÆÄºª Ç×¸ñÀ» ÆîÄ£´Ù.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
	//5.11 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¾Ö¼­ ÇöÀç ´Ü¾îÄ«µå°¡ ¼ÓÇÏ´Â Ã¶ÀÚÇ×¸ñÀ» ÆîÄ£´Ù.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
	//5.12 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ ÇöÀç ´Ü¾îÄ«µå°¡ ¼ÓÇÏ´Â Ç°»çÇ×¸ñÀ» ÆîÄ£´Ù.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
	//5.13 ´Ü¾îÄ«µåÃ¶ ÇÁ·¹ÀÓÀ©µµ¿ìÀÇ Æ®¸®ºäÄÁÆ®·Ñ¿¡¼­ ÇöÀç ´Ü¾îÄ«µå°¡ ¼ÓÇÏ´Â ÀÇ¹ÌÇ×¸ñÀ» ¼±ÅÃÇÑ´Ù.
	((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
	//5.14 »öÀÎ¸®½ºÆ® ¹è¿­À» ÇÒ´çÇØÁ¦ÇÑ´Ù.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
	//5.15 À©µµ¿ì¸¦ ´Ý´Â´Ù.
	EndDialog(0);
}

//6.Ã³À½¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnFirstButtonClicked()
{
	//6.1 Ã£Àº ´Ü¾îÄ«µåµé Áß¿¡¼­ Ã¹¹øÂ° ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
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

//7. ÀÌÀü¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnPreviousButtonClicked()
{
	//7.1 Ã£Àº ´Ü¾îÄ«µåµé Áß¿¡¼­ ÀÌÀü ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
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

//8. ´ÙÀ½ ¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnNextButtonClicked()
{
	//8.1 Ã£Àº ´Ü¾îÄ«µåµé Áß¿¡¼­ ´ÙÀ½ ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
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

//9. ¸¶Áö¸·¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnLastButtonClicked()
{
	//9.1 Ã£Àº ´Ü¾îÄ«µåµé Áß¿¡¼­ ¸¶Áö¸· ´Ü¾îÄ«µå¸¦ Ãâ·ÂÇÑ´Ù.
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

//10. ´Ý±â¹öÆ°À» Å¬¸¯ÇßÀ» ¶§
void FindingForm::OnClose()
{
	//10.1 ´Ü¾îÄ«µå¸µÅ© ¹è¿­À» ¾ø¾Ø´Ù.
	if (this->indexes != NULL)
	{
		delete[] this->indexes;
	}
	//10.2 À©µµ¿ì¸¦ ´Ý´Â´Ù.
	EndDialog(0);
}