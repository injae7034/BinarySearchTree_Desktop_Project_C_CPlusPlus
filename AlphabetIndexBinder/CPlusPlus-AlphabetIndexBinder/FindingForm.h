#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include<afxwin.h>//CDialog헤더파일
#include "resource.h"//IDD_FINDINGFORM

typedef signed long int Long;

class WordCard;//주소가 사용될 경우 전방선언, 내용이 사용될 경우 #include해서 헤더파일 추가
class FindingForm :public CDialog
{
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	virtual BOOL OnInitDialog();
protected://#
	afx_msg void OnSpellingsRadioButtonClicked();
	afx_msg void OnMeaningsRadioButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnChooseButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	WordCard* (*indexes);//주소이므로 전방선언이 필요함.
	Long count;
	Long current;
};

#endif // !_FINDINGFORM_H
