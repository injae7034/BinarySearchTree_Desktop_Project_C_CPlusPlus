#include "WordCardBinderApp.h"
#include "WordCardBinderForm.h"

BOOL WordCardBinderApp::InitInstance()
{
	WordCardBinderForm wordCardBinderForm;
	this->m_pMainWnd = &wordCardBinderForm;
	wordCardBinderForm.DoModal();

	return TRUE;
}
WordCardBinderApp wordCardBinderApp;