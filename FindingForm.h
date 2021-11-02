#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include<afxwin.h>//CDialog헤더파일
#include "resource.h"//IDD_FINIDINGFORM을 사용하기 위해 필요함

typedef signed long int Long;

class VisitingCard;//주소는 전방선언 내용일 경우 #include해서 header파일 추가
class FindingForm :public CDialog
{
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
protected://#
	afx_msg void OnFindButtonClicked();
	afx_msg void OnChooseButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	VisitingCard* (*indexes);//주소이므로 전방선언이 필요함.
	Long count;
	Long current;
};
#endif // !_FINDINGFORM_H

