#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "TakingInForm.h"
#include "FindingForm.h"
#include "TakingOutForm.h"
#include "IndexBinder.h"
#include "resource.h"
#include<afxwin.h>//CDialog �������
#include<afxcmn.h>//CTreeCtrl �������
#include<afxdb.h>//ODBC class
//using namespace std;
//#include<string>

BEGIN_MESSAGE_MAP(WordCardBinderForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_TAKEOUT, OnTakeOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_ALPHABETINDEX, OnTreeViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

WordCardBinderForm::WordCardBinderForm(CWnd* parent)
:CDialog(WordCardBinderForm::IDD, parent)
{
	this->wordCardBinder = NULL;//NULL�� �ʱ�ȭ��Ŵ.
	this->indexBinder = NULL;//NULL�� �ʱ�ȭ��Ŵ.
}


//�����ͺ��̽� �������α׷��� ����
//Load
void WordCardBinderForm::Load()
{
		CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
		CRecordset rs(&db);//SELECT
		CString sql = "SELECT Word.spellings, Word.partOfSpeech, Word.meanings, Word.example FROM Word;";
		db.OpenEx("DSN=WordCardBinder;UID=root;PWD=1q2w3e");//Connection
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//Request, Response

		CString spellings;
		CString partOfSpeech;
		CString meanings;
		CString example;
		while (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0, spellings);
			rs.GetFieldValue((short)1, partOfSpeech);
			rs.GetFieldValue((short)2, meanings);
			rs.GetFieldValue((short)3, example);
			//1.2 ���� �����͸� ���� wordCard�� �����Ѵ�.
			WordCard wordCard((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings, (LPCTSTR)example);
			//1.3 ����ö���� �����.
			this->wordCardBinder->TakeIn(wordCard);
			rs.MoveNext();
		}
		//Disconnection
		rs.Close();
		db.Close();
}

//Save
void WordCardBinderForm::Save()
{
		CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
		CRecordset rs(&db);//SELECT
		CString sql = "SELECT Word.code FROM Word;";
		db.OpenEx("DSN=WordCardBinder;UID=root;PWD=1q2w3e");
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//�����ͺ��̽��� �ִ� ���� �����͵��� ����� ���� code���� Recordset�� ������.
		CString sql2 = "DELETE FROM Word;";//�����ͺ��̽��� ���ο� �����͵��� �����ϱ� ���� ������ �����͵��� ��� ����.
		db.ExecuteSQL(sql2);//�����ͺ��̽����� ������ �����͵��� ����� ����� ������.

		CString code;
		CString sql3;
		WordCard* previous = 0;
		WordCard* it = this->wordCardBinder->First();
		while (it != previous)
		{
			string example = it->GetExample();
			if (example.find("'") != string::npos)
			{
				example.insert(example.find("'"), "\\");//�������� �ι� �־��ָ� \�� �ܵ����� �����̳� ����� �����ϴ�!!!
			}
			rs.GetFieldValue((short)0, code);
			sql3.Format("INSERT INTO Word(code, spellings, partOfSpeech, meanings, example) "
				"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, it->GetSpellings().c_str(),
				it->GetPartOfSpeech().c_str(), it->GetMeanings().c_str(), example.c_str());
			db.ExecuteSQL(sql3);
			rs.MoveNext();
			previous = it;
			it = this->wordCardBinder->Next();
		}
		rs.Close();
		db.Close();
}

//GetCode
CString WordCardBinderForm::GetCode()
{
		CDatabase db;
		CRecordset rs(&db);
		CString sql = "SELECT Word.code FROM Word ORDER BY code DESC;";
		db.OpenEx("DSN=WordCardBinder;UID=root;PWD=1q2w3e");
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		CString code = "W0000";
		int number;
		if (!rs.IsEOF())//�����ͺ��̽��� ����� �����Ͱ� ������
		{
			rs.GetFieldValue((short)0, code);
		}
		number = _ttoi(code.Right(4));
		number++;
		code.Format("W%04d", number);
		rs.Close();
		db.Close();

		return code;
}

//Insert
void WordCardBinderForm::Insert(WordCard* index)
{
	CDatabase db;
	CString sql;
	string example = index->GetExample();
	if (example.find("'") != string::npos)
	{
		//�������� �ι� �־��ָ� \�� �ܵ����� �����̳� ����� ������
		example.insert(example.find("'"), "\\");
	}
	CString code = this->GetCode();
	sql.Format("INSERT INTO Word(code, spellings, partOfSpeech, meanings, example) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, index->GetSpellings().c_str(),
		index->GetPartOfSpeech().c_str(), index->GetMeanings().c_str(), example.c_str());
	db.OpenEx("DSN=WordCardBinder;UID=root;PWD=1q2w3e");
	db.ExecuteSQL(sql);//Request
	db.Close();//Disconnection
}

//Delete
void WordCardBinderForm::Delete(WordCard* index)
{
	CDatabase db;//Connection, INSERT, DELETE, UPDATE, Disconnection
	CRecordset rs(&db);//SELECT
	CString sql;
	string example = index->GetExample();
	if (example.find("'") != string::npos)
	{
		example.insert(example.find("'"), "\\");//�������� �ι� �־��ָ� \�� �ܵ����� �����̳� ����� �����ϴ�!!!
	}
	sql.Format("SELECT Word.code FROM Word WHERE spellings='%s' AND partOfSpeech='%s' AND meanings='%s' AND example='%s';",
		index->GetSpellings().c_str(), index->GetPartOfSpeech().c_str(), index->GetMeanings().c_str(), example.c_str());
	db.OpenEx("DSN=WordCardBinder;UID=root;PWD=1q2w3e");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString code;
	rs.GetFieldValue((short)0, code);
	sql.Format("DELETE FROM Word WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

//1. �ܾ�ī��ö �����찡 ������ ��
BOOL WordCardBinderForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 �ܾ�ī��ö�� �����.(������ȣ��)
	this->wordCardBinder = new WordCardBinder;
	//1.2 ����ö�� �����.
	this->indexBinder = new IndexBinder;
	//1.3 �����ͺ��̽��� ����� �����͵��� �ܾ�ī��ö�� �����Ѵ�.
	this->Load();
	//1.4 �ܾ�ī��ö�� ����� ������ŭ ����ö�� �����.
	if (this->wordCardBinder->GetLength() > 0)
	{
		WordCard* previous = NULL;
		WordCard* it = this->wordCardBinder->First();
		while (it != previous)
		{
			this->indexBinder->TakeIn(it);
			previous = it;
			it = this->wordCardBinder->Next();
		}
	}
	//1.5 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"Alphabets";
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
	//1.6 ���簡 �Ǿ�����
	if (this->indexBinder->GetLength() > 0)
	{
		//1.6.1 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
		WordCard* current = this->wordCardBinder->First();
		//1.4.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
		CString spellings = CString(current->GetSpellings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		CString partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		CString meanings = CString(current->GetMeanings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
		CString example = CString(current->GetExample().c_str());
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
		//1.6.3 ����ö���� ���θ���Ʈ�� �����.
		Index(*indexes);
		Long count;
		this->indexBinder->MakeList(&indexes, &count);
		//1.6.4 ���ΰ�����ŭ �ݺ��Ѵ�.
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
			//1.6.4.1 Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//1.6.4.2 ���ο� ����� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//1.6.4.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
				wordCard = indexes[i].GetAt(j);
				//1.6.4.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
				//1.6.4.2.3 ö���ߺ��� ������
				if (isDuplicatedSpellings == FALSE)
				{
					//1.6.4.2.3.1 Ʈ������Ʈ���� ���ĺ� �׸� �Ʒ��� ö�ڸ� �����Ѵ�.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//1.6.4.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//1.6.4.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
					Long m = 0;
					while (m < arrayCount)
					{
						//1.6.4.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
						//1.6.4.2.3.3.2 ǰ���ߺ��� ������
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//1.6.4.2.3.3.2.1 Ʈ������Ʈ���� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//1.6.4.2.3.3.2.2 Ʈ������Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//1.6.4.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
						else
						{
							//1.6.4.2.3.3.3.1 ���� ǰ�縦 ã�´�.
							hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
							TVITEM item = { 0, };
							item.mask = TVIF_TEXT;
							item.pszText = tPartOfSpeech;
							item.cchTextMax = 8;
							item.hItem = hPartOfSpeech;
							((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
							while (hPartOfSpeech != NULL && wordCard->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
							{
								hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
								item.hItem = hPartOfSpeech;
								((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
							}
							//1.6.4.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText =(LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
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
		//1.6.5 ����ö���� ������ ã�´�.
		Index* index = this->indexBinder->Find(current->GetSpellings()[0]);
		//1.6.6 ã�� ������ ���ĺ��� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
		hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_ROOT);
		hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabets, TVGN_CHILD);
		TCHAR tAlphabet[2];
		TVITEM item = { 0, };
		item.mask = TVIF_TEXT;
		item.pszText = tAlphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		indexAlphabet[0] = index->GetAlphabet();
		indexAlphabet[1] = '\0';
		while (hAlphabet != NULL && tAlphabet[0] != indexAlphabet[0])
		{
			hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_NEXT);
			item.hItem = hAlphabet;
			((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		}
		//1.6.7 Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
		hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_CHILD);
		TCHAR tSpellings[64];
		item.pszText = tSpellings;
		item.cchTextMax = 64;
		item.hItem = hSpellings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		while (hSpellings != NULL && current->GetSpellings().compare(tSpellings) != 0)
		{
			hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_NEXT);
			item.hItem = hSpellings;
			((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		}
		//1.6.8 Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
		hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
		item.pszText = tPartOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		while (hPartOfSpeech != NULL && current->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
		{
			hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
			item.hItem = hPartOfSpeech;
			((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		}
		//1.6.9 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
		HTREEITEM hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_CHILD);
		TCHAR tMeanings[32];
		item.pszText = tMeanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		while (hMeanings != NULL && current->GetMeanings().compare(tMeanings) != 0)
		{
			hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hMeanings, TVGN_NEXT);
			item.hItem = hMeanings;
			((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		}
		//1.6.10 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//1.6.11 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//1.6.12 Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//1.6.13 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//1.6.14 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//1.6.15 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
	}
	//1.7 ������.
	return FALSE;
}


//2. ������ư�� Ŭ������ ��
void WordCardBinderForm::OnTakeInButtonClicked()
{
	//2.1 ����� ������ �����츦 �����Ѵ�.
	TakingInForm takingInForm;//����O, �ּ�X, ���� ���漱���� �ƴ϶� #include "TakingInForm.h" ��������� �ʿ���.
	//2.2 ����� ������ �����츦 ����Ѵ�.
	takingInForm.DoModal();	
}

//3. ã���ư�� Ŭ������ ��
void WordCardBinderForm::OnFindButtonClicked()
{
	//3.1 ã�� ������ �����츦 �����Ѵ�.
	FindingForm findingForm;//����O, �ּ�X, ���� ���漱���� �ƴ϶� #include "FindingForm.h" ��������� �ʿ���.
	//3.2 ã�� ������ �����츦 ����Ѵ�.
	findingForm.DoModal();
}

//4. �������ư�� Ŭ������ ��
void WordCardBinderForm::OnTakeOutButtonClicked()
{
	//4.1 ������ ������ �����츦 �����Ѵ�.
	TakingOutForm takingOutForm;//����O, �ּ�X, ���� ���漱���� �ƴ϶� #include "TakingOutForm.h" ��������� �ʿ���.
	//4.2 ������ ������ �����츦 ����Ѵ�.
	takingOutForm.DoModal();
}

//5. �����ϱ� ��ư�� Ŭ������ ��
void WordCardBinderForm::OnArrangeButtonClicked()
{
	//5.1 ����ö���� �����Ѵ�.
	this->indexBinder->Arrange();
	//5.2 ����ö���� ���θ���Ʈ�� �����.
	Index(*indexes);
	Long count;
	this->indexBinder->MakeList(&indexes, &count);
	//5.3 Ʈ������Ʈ�ѿ� �ִ� ��� �׸���� �����.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
	//5.4 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� �����Ѵ�.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"Alphabets";
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
	//5.5 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
	WordCard* current = this->wordCardBinder->First();
	//5.6 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(current->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(current->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(current->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(current->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.7 ���ΰ�����ŭ �ݺ��Ѵ�.
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
		//5.7.1 Ʈ������Ʈ�ѿ� ���ĺ��׸��� �����Ѵ�.
		insertStruct.hParent = hAlphabets;
		indexAlphabet[0] = indexes[i].GetAlphabet();
		indexAlphabet[1] = '\0';
		insertStruct.item.pszText = indexAlphabet;
		hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
		//5.7.2 ���ο� ����� �ܾ�ī�尳����ŭ �ݺ��Ѵ�.
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			//5.7.2.1 ���ο� ����� �ܾ�ī�带 �˾Ƴ���.
			wordCard = indexes[i].GetAt(j);
			//5.7.2.2 �˾Ƴ� �ܾ�ī���� ö�ڿ� �ٸ� �ܾ�ī�� ���̿� ö���ߺ��� �ִ��� Ȯ���Ѵ�.
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
			//5.7.2.3 ö���ߺ��� ������
			if (isDuplicatedSpellings == FALSE)
			{
				//5.7.2.3.1 Ʈ������Ʈ���� ���ĺ� �׸� �Ʒ��� ö�ڸ� �����Ѵ�.
				insertStruct.hParent = hAlphabet;
				insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
				hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
				//5.7.2.3.2 ���ο� ����� �ܾ�ī��� �߿��� �ߺ��� ö���� �ܾ�ī����� ã�´�.
				Long(*arrayIndexes);
				Long arrayCount;
				indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
				//5.7.2.3.3 ã�� ������ŭ �ݺ��Ѵ�.
				Long m = 0;
				while (m < arrayCount)
				{
					//5.7.2.3.3.1 �ߺ��� ö���� �ܾ�ī�� �߿��� �ߺ��� ǰ�簡 �ִ��� Ȯ���Ѵ�.
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
					//5.7.2.3.3.2 ǰ���ߺ��� ������
					if (isDuplicatedPartOfSpeech == FALSE)
					{
						//5.7.2.3.3.2.1 Ʈ������Ʈ���� ö���׸� �Ʒ��� ǰ�縦 �����Ѵ�.
						insertStruct.hParent = hSpellings;
						insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
						hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						//5.7.2.3.3.2.2 Ʈ������Ʈ���� ǰ���׸� �Ʒ��� �ǹ̸� �����Ѵ�.
						insertStruct.hParent = hPartOfSpeech;
						insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
						((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					}
					//5.7.2.3.3.3 ǰ�簡 �ߺ��Ǹ�
					else
					{
						//5.7.2.3.3.3.1 ���� ǰ�縦 ã�´�.
						hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
						TVITEM item = { 0, };
						item.mask = TVIF_TEXT;
						item.pszText = tPartOfSpeech;
						item.cchTextMax = 8;
						item.hItem = hPartOfSpeech;
						((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
						while (hPartOfSpeech != NULL && wordCard->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
						{
							hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
							item.hItem = hPartOfSpeech;
							((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
						}
						//5.7.2.3.3.3.2 ���� ǰ�� �׸� �Ʒ��� �ǹ��׸��� �����Ѵ�.
						insertStruct.hParent = hPartOfSpeech;
						insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
						((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
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
	//5.8 ����ö���� ������ ã�´�.
	Index* index = this->indexBinder->Find(current->GetSpellings()[0]);
	//5.9 ã�� ������ ���ĺ��� Ʈ������Ʈ�ѿ��� ������ ���ĺ��׸��� ã�´�.
	hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_ROOT);
	hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabets, TVGN_CHILD);
	TCHAR tAlphabet[2];
	TVITEM item = { 0, };
	item.mask = TVIF_TEXT;
	item.pszText = tAlphabet;
	item.cchTextMax = 2;
	item.hItem = hAlphabet;
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	indexAlphabet[0] = index->GetAlphabet();
	indexAlphabet[1] = '\0';
	while (hAlphabet != NULL && tAlphabet[0] != indexAlphabet[0])
	{
		hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_NEXT);
		item.hItem = hAlphabet;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.10 Ʈ������Ʈ���� ���ĺ� �׸񿡼� ���� �ܾ�ī���� ö�ڸ� ã�´�.
	hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_CHILD);
	TCHAR tSpellings[64];
	item.pszText = tSpellings;
	item.cchTextMax = 64;
	item.hItem = hSpellings;
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hSpellings != NULL && current->GetSpellings().compare(tSpellings) != 0)
	{
		hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_NEXT);
		item.hItem = hSpellings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.11 Ʈ������Ʈ���� ö���׸� �Ʒ����� ���� �ܾ�ī���� ǰ�縦 ã�´�.
	hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_CHILD);
	item.pszText = tPartOfSpeech;
	item.cchTextMax = 8;
	item.hItem = hPartOfSpeech;
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hPartOfSpeech != NULL && current->GetPartOfSpeech().compare(tPartOfSpeech) != 0)
	{
		hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_NEXT);
		item.hItem = hPartOfSpeech;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//5.12 Ʈ������Ʈ�ѿ��� ���� ��µ� �ܾ�ī���� �ǹ̿� ������ �ǹ̸� ã�´�.
	HTREEITEM hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_CHILD);
	TCHAR tMeanings[32];
	item.pszText = tMeanings;
	item.cchTextMax = 32;
	item.hItem = hMeanings;
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	while (hMeanings != NULL && current->GetMeanings().compare(tMeanings) != 0)
	{
		hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hMeanings, TVGN_NEXT);
		item.hItem = hMeanings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
	}
	//15.13 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
	//5.14 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ���ĺ� �׸��� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
	//5.15 Ʈ������Ʈ�Ѿּ� ���� �ܾ�ī�尡 ���ϴ� ö���׸��� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
	//5.16 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� ǰ���׸��� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
	//5.17 Ʈ������Ʈ�ѿ��� ���� �ܾ�ī�尡 ���ϴ� �ǹ��׸��� �����Ѵ�.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
	//5.18 ���θ���Ʈ �迭�� �Ҵ������Ѵ�.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
}

//6. ó����ư�� Ŭ������ ��
void WordCardBinderForm::OnFirstButtonClicked()
{
	//6.1 �ܾ�ī��ö���� ó������ �̵��Ѵ�.
	WordCard* index = this->wordCardBinder->First();
	//6.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//7. ������ư�� Ŭ������ ��
void WordCardBinderForm::OnPreviousButtonClicked()
{
	//7.1 �ܾ�ī��ö���� �������� �̵��Ѵ�.
	WordCard* index = this->wordCardBinder->Previous();
	//7.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.������ư�� Ŭ������ ��
void WordCardBinderForm::OnNextButtonClicked()
{
	//8.1 �ܾ�ī��ö���� �������� �̵��Ѵ�.
	WordCard* index = this->wordCardBinder->Next();
	//8.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//9. ��������ư�� Ŭ������ ��
void WordCardBinderForm::OnLastButtonClicked()
{
	//9.1 �ܾ�ī��ö���� ���������� �̵��Ѵ�.
	WordCard* index = this->wordCardBinder->Last();
	//9.2 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//10. Ʈ������Ʈ�ѿ��� �ǹ̸� ����Ŭ������ ��
void WordCardBinderForm::OnTreeViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//10.1 Ʈ������Ʈ�ѿ��� ����Ŭ���� �ǹ��׸��� ��ġ�� �д´�.
	HTREEITEM hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_CARET);
	//10.2 Ʈ������Ʈ�ѿ��� ����Ŭ���� �ǹ��׸��� �θ�������(ǰ���׸�)�� ��ġ�� �д´�.
	HTREEITEM hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hMeanings, TVGN_PARENT);
	//10.3 Ʈ������Ʈ�ѿ��� ���� ǰ���׸��� �θ�������(ö���׸�)�� ��ġ�� �д´�.
	HTREEITEM hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_PARENT);
	//10.4 Ʈ������Ʈ�ѿ��� ���� ö���׸��� �θ�������(���ĺ��׸�)�� ��ġ�� �д´�.
	HTREEITEM hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_PARENT);
	//10.5 Ʈ������Ʈ�ѿ��� "Alphabets"�׸��� ��ġ�� �д´�.
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_PARENT);
	//10.6 Ʈ���� ��Ʈ�ѿ��� ����Ŭ���� �׸��� �ǹ��׸��� ������
	if (hAlphabets != NULL && hAlphabet != NULL && hSpellings != NULL && hPartOfSpeech != NULL && hMeanings != NULL)
	{
		//10.6.1 Ʈ������Ʈ�ѿ��� ��ġ�� ���� �ǹ��׸��� �ǹ��ؽ�Ʈ�� �д´�.
		TCHAR tMeanings[32];
		TVITEM item = { 0, };
		item.mask = TVIF_TEXT;
		item.pszText = tMeanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.2 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ǰ���׸��� ǰ���ؽ�Ʈ�� �д´�.
		TCHAR tPartOfSpeech[8];
		item.pszText = tPartOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.3 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ö���׸��� ö���ؽ�Ʈ�� �д´�.
		TCHAR tSpellings[64];
		item.pszText = tSpellings;
		item.cchTextMax =64;
		item.hItem = hSpellings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.4 Ʈ������Ʈ�ѿ��� ��ġ�� ���� ���ĺ��׸��� ���ĺ��ؽ�Ʈ�� �д´�.
		TCHAR tAlphabet[2];
		item.pszText = tAlphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.5 ����ö���� ã�´�.
		Index* index = this->indexBinder->Find(tAlphabet[0]);
		//10.6.6 ���ο� ����� �ܾ�ī�尳����ŭ �׸��� current�� null�ε��ȿ� �ݺ��Ѵ�.
		WordCard* current = NULL;
		Long i = 0;
		while (i < index->GetLength() && current == NULL)
		{
			//10.6.6.1 ���ο� ����� �ܾ�ī���� �ּҸ� �˾Ƴ���.
			WordCard* wordCard = index->GetAt(i);
			//10.6.6.2 ö�ڰ� ���� ǰ�簡 ���� �ǹ̰� ������
			if (wordCard->GetSpellings().compare(tSpellings) == 0 && wordCard->GetPartOfSpeech().compare(tPartOfSpeech) == 0
				&& wordCard->GetMeanings().compare(tMeanings) == 0)
			{
				//10.6.6.2.1 �ܾ�ī���� ��ġ�� �����Ѵ�.
				current = wordCard;
			}
			i++;
		}
		//10.6.7 �ܾ�ī��ö���� ������ �ܾ�ī���� ��ġ�� �̵��Ѵ�.
		current = this->wordCardBinder->Move(current);
		//10.6.8 �ܾ�ī��ö�� ���� �ܾ�ī�带 ����Ѵ�.
		CString spellings = CString(current->GetSpellings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		CString partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		CString meanings = CString(current->GetMeanings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
		CString example = CString(current->GetExample().c_str());
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	}
}

//11. �ݱ��ư�� Ŭ������ ��
void WordCardBinderForm::OnClose()
{
	//11.1 �ܾ�ī��ö�� ������
	if (this->wordCardBinder != NULL)
	{
		//11.1.1 �ܾ�ī��ö�� ������ �����ͺ��̽��� �����Ѵ�.
		this->Save();
		//11.1.2 �ܾ�ī��ö�� �����.
		delete this->wordCardBinder;
	}
	//11.2 �����츦 �ݴ´�.
	EndDialog(0);
}