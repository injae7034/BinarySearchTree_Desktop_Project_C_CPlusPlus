#include "WordCardBinderForm.h"
#include "WordCardBinder.h"
#include "TakingInForm.h"
#include "FindingForm.h"
#include "TakingOutForm.h"
#include "IndexBinder.h"
#include "resource.h"
#include<afxwin.h>//CDialog 헤더파일
#include<afxcmn.h>//CTreeCtrl 헤더파일
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
	this->wordCardBinder = NULL;//NULL로 초기화시킴.
	this->indexBinder = NULL;//NULL로 초기화시킴.
}


//데이터베이스 응용프로그래밍 시작
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
			//1.2 읽은 데이터를 통해 wordCard를 생성한다.
			WordCard wordCard((LPCTSTR)spellings, (LPCTSTR)partOfSpeech, (LPCTSTR)meanings, (LPCTSTR)example);
			//1.3 명함철에서 끼운다.
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
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//데이터베이스에 있는 기존 데이터들을 지우기 전에 code들을 Recordset에 저장함.
		CString sql2 = "DELETE FROM Word;";//데이터베이스에 새로운 데이터들을 저장하기 전에 기존에 데이터들을 모두 지움.
		db.ExecuteSQL(sql2);//데이터베이스에서 기존의 데이터들을 지우는 명령을 실행함.

		CString code;
		CString sql3;
		WordCard* previous = 0;
		WordCard* it = this->wordCardBinder->First();
		while (it != previous)
		{
			string example = it->GetExample();
			if (example.find("'") != string::npos)
			{
				example.insert(example.find("'"), "\\");//역슬러시 두번 넣어주면 \를 단독으로 삽입이나 출력이 가능하다!!!
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
		if (!rs.IsEOF())//데이터베이스에 저장된 데이터가 있으면
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
		//역슬러시 두번 넣어주면 \를 단독으로 삽입이나 출력이 가능함
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
		example.insert(example.find("'"), "\\");//역슬러시 두번 넣어주면 \를 단독으로 삽입이나 출력이 가능하다!!!
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

//1. 단어카드철 윈도우가 생성될 때
BOOL WordCardBinderForm::OnInitDialog()
{
	CDialog::OnInitDialog();
	//1.1 단어카드철을 만든다.(생성자호출)
	this->wordCardBinder = new WordCardBinder;
	//1.2 색인철을 만든다.
	this->indexBinder = new IndexBinder;
	//1.3 데이터베이스에 저장된 데이터들을 단어카드철에 적재한다.
	this->Load();
	//1.4 단어카드철에 적재된 개수만큼 색인철에 끼운다.
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
	//1.5 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"Alphabets";
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
	//1.6 적재가 되었으면
	if (this->indexBinder->GetLength() > 0)
	{
		//1.6.1 단어카드철에서 처음으로 이동한다.
		WordCard* current = this->wordCardBinder->First();
		//1.4.2 단어카드철의 현재 단어카드를 출력한다.
		CString spellings = CString(current->GetSpellings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
		CString partOfSpeech = CString(current->GetPartOfSpeech().c_str());
		GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
		CString meanings = CString(current->GetMeanings().c_str());
		GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
		CString example = CString(current->GetExample().c_str());
		GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
		//1.6.3 색인철에서 색인리스트를 만든다.
		Index(*indexes);
		Long count;
		this->indexBinder->MakeList(&indexes, &count);
		//1.6.4 색인개수만큼 반복한다.
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
			//1.6.4.1 트리뷰컨트롤에 알파벳항목을 삽입한다.
			insertStruct.hParent = hAlphabets;
			indexAlphabet[0] = indexes[i].GetAlphabet();
			indexAlphabet[1] = '\0';
			insertStruct.item.pszText = indexAlphabet;
			hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
			//1.6.4.2 색인에 저장된 단어카드개수만큼 반복한다.
			Long j = 0;
			while (j < indexes[i].GetLength())
			{
				//1.6.4.2.1 색인에 저장된 단어카드를 알아낸다.
				wordCard = indexes[i].GetAt(j);
				//1.6.4.2.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
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
				//1.6.4.2.3 철자중복이 없으면
				if (isDuplicatedSpellings == FALSE)
				{
					//1.6.4.2.3.1 트리뷰컨트롤의 알파벳 항목 아래에 철자를 삽입한다.
					insertStruct.hParent = hAlphabet;
					insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
					hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					//1.6.4.2.3.2 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
					Long(*arrayIndexes);
					Long arrayCount;
					indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
					//1.6.4.2.3.3 찾은 개수만큼 반복한다.
					Long m = 0;
					while (m < arrayCount)
					{
						//1.6.4.2.3.3.1 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
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
						//1.6.4.2.3.3.2 품사중복이 없으면
						if (isDuplicatedPartOfSpeech == FALSE)
						{
							//1.6.4.2.3.3.2.1 트리뷰컨트롤의 철자항목 아래에 품사를 삽입한다.
							insertStruct.hParent = hSpellings;
							insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
							hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
							//1.6.4.2.3.3.2.2 트리뷰컨트롤의 품사항목 아래에 의미를 삽입한다.
							insertStruct.hParent = hPartOfSpeech;
							insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
							((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						}
						//1.6.4.2.3.3.3 품사가 중복되면
						else
						{
							//1.6.4.2.3.3.3.1 같은 품사를 찾는다.
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
							//1.6.4.2.3.3.3.2 같은 품사 항목 아래에 의미항목을 삽입한다.
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
		//1.6.5 색인철에서 색인을 찾는다.
		Index* index = this->indexBinder->Find(current->GetSpellings()[0]);
		//1.6.6 찾은 색인의 알파벳과 트리뷰컨트롤에서 동일한 알파벳항목을 찾는다.
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
		//1.6.7 트리뷰컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
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
		//1.6.8 트리뷰컨트롤의 철자항목 아래에서 현재 단어카드의 품사를 찾는다.
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
		//1.6.9 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
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
		//1.6.10 트리뷰컨트롤에서 "Alphabets"항목을 펼친다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
		//1.6.11 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
		//1.6.12 트리뷰컨트롤애서 현재 단어카드가 속하는 철자항목을 펼친다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
		//1.6.13 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
		//1.6.14 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
		//1.6.15 색인리스트 배열을 할당해제한다.
		if (indexes != NULL)
		{
			delete[] indexes;
		}
	}
	//1.7 끝내다.
	return FALSE;
}


//2. 끼우기버튼을 클릭했을 때
void WordCardBinderForm::OnTakeInButtonClicked()
{
	//2.1 끼우기 프레임 윈도우를 생성한다.
	TakingInForm takingInForm;//내용O, 주소X, 따라서 전방선언이 아니라 #include "TakingInForm.h" 헤더파일이 필요함.
	//2.2 끼우기 프레임 윈도우를 출력한다.
	takingInForm.DoModal();	
}

//3. 찾기버튼을 클릭했을 때
void WordCardBinderForm::OnFindButtonClicked()
{
	//3.1 찾기 프레임 윈도우를 생성한다.
	FindingForm findingForm;//내용O, 주소X, 따라서 전방선언이 아니라 #include "FindingForm.h" 헤더파일이 필요함.
	//3.2 찾기 프레임 윈도우를 출력한다.
	findingForm.DoModal();
}

//4. 꺼내기버튼을 클릭했을 때
void WordCardBinderForm::OnTakeOutButtonClicked()
{
	//4.1 꺼내기 프레임 윈도우를 생성한다.
	TakingOutForm takingOutForm;//내용O, 주소X, 따라서 전방선언이 아니라 #include "TakingOutForm.h" 헤더파일이 필요함.
	//4.2 꺼내기 프레임 윈도우를 출력한다.
	takingOutForm.DoModal();
}

//5. 정리하기 버튼을 클릭했을 때
void WordCardBinderForm::OnArrangeButtonClicked()
{
	//5.1 색인철에서 정리한다.
	this->indexBinder->Arrange();
	//5.2 색인철에서 색인리스트를 만든다.
	Index(*indexes);
	Long count;
	this->indexBinder->MakeList(&indexes, &count);
	//5.3 트리뷰컨트롤에 있는 모든 항목들을 지운다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->DeleteItem(TVI_ROOT);
	//5.4 트리뷰컨트롤에서 "Alphabets"항목을 삽입한다.
	TVINSERTSTRUCT insertStruct = { 0, };
	insertStruct.hParent = TVI_ROOT;
	insertStruct.item.mask = TVIF_TEXT;
	insertStruct.item.pszText = (LPSTR)"Alphabets";
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
	//5.5 단어카드철에서 처음으로 이동한다.
	WordCard* current = this->wordCardBinder->First();
	//5.6 단어카드철의 현재 단어카드를 출력한다.
	CString spellings = CString(current->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(current->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(current->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(current->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
	//5.7 색인개수만큼 반복한다.
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
		//5.7.1 트리뷰컨트롤에 알파벳항목을 삽입한다.
		insertStruct.hParent = hAlphabets;
		indexAlphabet[0] = indexes[i].GetAlphabet();
		indexAlphabet[1] = '\0';
		insertStruct.item.pszText = indexAlphabet;
		hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
		//5.7.2 색인에 저장된 단어카드개수만큼 반복한다.
		Long j = 0;
		while (j < indexes[i].GetLength())
		{
			//5.7.2.1 색인에 저장된 단어카드를 알아낸다.
			wordCard = indexes[i].GetAt(j);
			//5.7.2.2 알아낸 단어카드의 철자와 다른 단어카드 사이에 철자중복이 있는지 확인한다.
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
			//5.7.2.3 철자중복이 없으면
			if (isDuplicatedSpellings == FALSE)
			{
				//5.7.2.3.1 트리뷰컨트롤의 알파벳 항목 아래에 철자를 삽입한다.
				insertStruct.hParent = hAlphabet;
				insertStruct.item.pszText = (LPSTR)wordCard->GetSpellings().c_str();
				hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
				//5.7.2.3.2 색인에 저장된 단어카드들 중에서 중복된 철자의 단어카드들을 찾는다.
				Long(*arrayIndexes);
				Long arrayCount;
				indexes[i].FindBySpellings(wordCard->GetSpellings(), &arrayIndexes, &arrayCount);
				//5.7.2.3.3 찾은 개수만큼 반복한다.
				Long m = 0;
				while (m < arrayCount)
				{
					//5.7.2.3.3.1 중복된 철자의 단어카드 중에서 중복된 품사가 있는지 확인한다.
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
					//5.7.2.3.3.2 품사중복이 없으면
					if (isDuplicatedPartOfSpeech == FALSE)
					{
						//5.7.2.3.3.2.1 트리뷰컨트롤의 철자항목 아래에 품사를 삽입한다.
						insertStruct.hParent = hSpellings;
						insertStruct.item.pszText = (LPSTR)wordCard->GetPartOfSpeech().c_str();
						hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
						//5.7.2.3.3.2.2 트리뷰컨트롤의 품사항목 아래에 의미를 삽입한다.
						insertStruct.hParent = hPartOfSpeech;
						insertStruct.item.pszText = (LPSTR)wordCard->GetMeanings().c_str();
						((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->InsertItem(&insertStruct);
					}
					//5.7.2.3.3.3 품사가 중복되면
					else
					{
						//5.7.2.3.3.3.1 같은 품사를 찾는다.
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
						//5.7.2.3.3.3.2 같은 품사 항목 아래에 의미항목을 삽입한다.
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
	//5.8 색인철에서 색인을 찾는다.
	Index* index = this->indexBinder->Find(current->GetSpellings()[0]);
	//5.9 찾은 색인의 알파벳과 트리뷰컨트롤에서 동일한 알파벳항목을 찾는다.
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
	//5.10 트리뷰컨트롤의 알파벳 항목에서 현재 단어카드의 철자를 찾는다.
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
	//5.11 트리뷰컨트롤의 철자항목 아래에서 현재 단어카드의 품사를 찾는다.
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
	//5.12 트리뷰컨트롤에서 현재 출력된 단어카드의 의미와 동일한 의미를 찾는다.
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
	//15.13 트리뷰컨트롤에서 "Alphabets"항목을 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabets, TVE_EXPAND);
	//5.14 트리뷰컨트롤에서 현재 단어카드가 속하는 알파벳 항목을 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hAlphabet, TVE_EXPAND);
	//5.15 트리뷰컨트롤애서 현재 단어카드가 속하는 철자항목을 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hSpellings, TVE_EXPAND);
	//5.16 트리뷰컨트롤에서 현재 단어카드가 속하는 품사항목을 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->Expand(hPartOfSpeech, TVE_EXPAND);
	//5.17 트리뷰컨트롤에서 현재 단어카드가 속하는 의미항목을 선택한다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->SelectItem(hMeanings);
	//5.18 색인리스트 배열을 할당해제한다.
	if (indexes != NULL)
	{
		delete[] indexes;
	}
}

//6. 처음버튼을 클릭했을 때
void WordCardBinderForm::OnFirstButtonClicked()
{
	//6.1 단어카드철에서 처음으로 이동한다.
	WordCard* index = this->wordCardBinder->First();
	//6.2 단어카드철의 현재 단어카드를 출력한다.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//7. 이전버튼을 클릭했을 때
void WordCardBinderForm::OnPreviousButtonClicked()
{
	//7.1 단어카드철에서 이전으로 이동한다.
	WordCard* index = this->wordCardBinder->Previous();
	//7.2 단어카드철의 현재 단어카드를 출력한다.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//8.다음버튼을 클릭했을 때
void WordCardBinderForm::OnNextButtonClicked()
{
	//8.1 단어카드철에서 다음으로 이동한다.
	WordCard* index = this->wordCardBinder->Next();
	//8.2 단어카드철의 현재 단어카드를 출력한다.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//9. 마지막버튼을 클릭했을 때
void WordCardBinderForm::OnLastButtonClicked()
{
	//9.1 단어카드철에서 마지막으로 이동한다.
	WordCard* index = this->wordCardBinder->Last();
	//9.2 단어카드철의 현재 단어카드를 출력한다.
	CString spellings = CString(index->GetSpellings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_SPELLINGS)->SetWindowText(spellings);
	CString partOfSpeech = CString(index->GetPartOfSpeech().c_str());
	GetDlgItem(IDC_STATIC_EDIT_PARTOFSPEECH)->SetWindowText(partOfSpeech);
	CString meanings = CString(index->GetMeanings().c_str());
	GetDlgItem(IDC_STATIC_EDIT_MEANINGS)->SetWindowText(meanings);
	CString example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_STATIC_EDIT_EXAMPLE)->SetWindowText(example);
}

//10. 트리뷰컨트롤에서 의미를 더블클릭했을 때
void WordCardBinderForm::OnTreeViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result)
{
	//10.1 트리뷰컨트롤에서 더블클릭한 의미항목의 위치를 읽는다.
	HTREEITEM hMeanings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(NULL, TVGN_CARET);
	//10.2 트리뷰컨트롤에서 더블클릭한 의미항목의 부모윈도우(품사항목)의 위치를 읽는다.
	HTREEITEM hPartOfSpeech = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hMeanings, TVGN_PARENT);
	//10.3 트리뷰컨트롤에서 읽은 품사항목의 부모윈도우(철자항목)의 위치를 읽는다.
	HTREEITEM hSpellings = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hPartOfSpeech, TVGN_PARENT);
	//10.4 트리뷰컨트롤에서 읽은 철자항목의 부모윈도우(알파벳항목)의 위치를 읽는다.
	HTREEITEM hAlphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hSpellings, TVGN_PARENT);
	//10.5 트리뷰컨트롤에서 "Alphabets"항목의 위치를 읽는다.
	HTREEITEM hAlphabets = ((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetNextItem(hAlphabet, TVGN_PARENT);
	//10.6 트리뷰 컨트롤에서 더블클릭한 항목이 의미항목이 맞으면
	if (hAlphabets != NULL && hAlphabet != NULL && hSpellings != NULL && hPartOfSpeech != NULL && hMeanings != NULL)
	{
		//10.6.1 트리뷰컨트롤에서 위치를 읽은 의미항목의 의미텍스트를 읽는다.
		TCHAR tMeanings[32];
		TVITEM item = { 0, };
		item.mask = TVIF_TEXT;
		item.pszText = tMeanings;
		item.cchTextMax = 32;
		item.hItem = hMeanings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.2 트리뷰컨트롤에서 위치를 읽은 품사항목의 품사텍스트를 읽는다.
		TCHAR tPartOfSpeech[8];
		item.pszText = tPartOfSpeech;
		item.cchTextMax = 8;
		item.hItem = hPartOfSpeech;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.3 트리뷰컨트롤에서 위치를 읽은 철자항목의 철자텍스트를 읽는다.
		TCHAR tSpellings[64];
		item.pszText = tSpellings;
		item.cchTextMax =64;
		item.hItem = hSpellings;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.4 트리뷰컨트롤에서 위치를 읽은 알파벳항목의 알파벳텍스트를 읽는다.
		TCHAR tAlphabet[2];
		item.pszText = tAlphabet;
		item.cchTextMax = 2;
		item.hItem = hAlphabet;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_ALPHABETINDEX))->GetItem(&item);
		//10.6.5 색인철에서 찾는다.
		Index* index = this->indexBinder->Find(tAlphabet[0]);
		//10.6.6 색인에 저장된 단어카드개수만큼 그리고 current가 null인동안에 반복한다.
		WordCard* current = NULL;
		Long i = 0;
		while (i < index->GetLength() && current == NULL)
		{
			//10.6.6.1 색인에 저장된 단어카드의 주소를 알아낸다.
			WordCard* wordCard = index->GetAt(i);
			//10.6.6.2 철자가 같고 품사가 같고 의미가 같으면
			if (wordCard->GetSpellings().compare(tSpellings) == 0 && wordCard->GetPartOfSpeech().compare(tPartOfSpeech) == 0
				&& wordCard->GetMeanings().compare(tMeanings) == 0)
			{
				//10.6.6.2.1 단어카드의 위치를 저장한다.
				current = wordCard;
			}
			i++;
		}
		//10.6.7 단어카드철에서 저장한 단어카드의 위치로 이동한다.
		current = this->wordCardBinder->Move(current);
		//10.6.8 단어카드철의 현재 단어카드를 출력한다.
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

//11. 닫기버튼을 클릭했을 때
void WordCardBinderForm::OnClose()
{
	//11.1 단어카드철이 있으면
	if (this->wordCardBinder != NULL)
	{
		//11.1.1 단어카드철의 내용을 데이터베이스에 저장한다.
		this->Save();
		//11.1.2 단어카드철을 지운다.
		delete this->wordCardBinder;
	}
	//11.2 윈도우를 닫는다.
	EndDialog(0);
}