#ifndef _TAKINGINFORM_H
#define _TAKINGINFORM_H
#include<afxwin.h>//CDialog 헤더파일
#include "resource.h"//IDD_TAKINGINFORM때문에 필요함

class TakingInForm :public CDialog
{
public:
	enum{IDD=IDD_TAKINGINFORM};
public:
	TakingInForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	virtual BOOL OnInitDialog();
protected://#
	afx_msg void OnTakeInButtonClicked();
	afx_msg void OnCompanyNameKillFocus();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // !_TAKINGINFORM_H

