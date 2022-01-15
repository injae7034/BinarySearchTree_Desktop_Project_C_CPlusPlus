#ifndef _WORDCARDBINDERFORM_H
#define _WORDCARDBINDERFORM_H
#include<afxwin.h>//CDialog 헤더파일
#include "resource.h"

class IndexBinder;//전방선언
class WordCard;//전방선언 데이터베이스 매개변수에서 WordCard의 주소가 쓰이기때문에!
class WordCardBinder;//전방선언
class WordCardBinderForm :public CDialog
{
public:
	enum { IDD = IDD_WORDCARDBINDERFORM };
public:
	WordCardBinderForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	void Load();
	void Save();
	void Insert(WordCard* index);
	void Delete(WordCard* index);
	CString GetCode();
	virtual BOOL OnInitDialog();
public://WordCardBinder는 WordCardBinderForm과 관계를 맺고 있기 때문에 public임!
	WordCardBinder* wordCardBinder;//주소는 전방선언이 필요, 내용일 경우 헤더파일을 include해줘야함.
	IndexBinder* indexBinder;//주소이므로 전방선언 필요

protected://#
	afx_msg void OnTakeInButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnTakeOutButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnTreeViewItemDoubleClicked(NMHDR* lpNotifyStruct, LRESULT* result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

};

#endif // !_WORDCARDBINDERFORM_H
