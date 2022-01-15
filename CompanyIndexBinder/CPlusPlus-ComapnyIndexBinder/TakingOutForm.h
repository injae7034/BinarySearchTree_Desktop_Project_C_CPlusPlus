#ifndef _TAKINGOUTFORM_H
#define _TAKINGOUTFORM_H
#include<afxwin.h>//CDialog헤더파일
#include "resource.h"

typedef signed long int Long;
class TakingOutForm :public CDialog
{
public:
	enum{IDD=IDD_TAKINGOUTFORM};
public:
	TakingOutForm(CWnd* parent = NULL);//생성자, NULL이 디폴트값
	virtual BOOL OnInitDialog();
protected://#
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // !_TAKINGOUTFORM_H

