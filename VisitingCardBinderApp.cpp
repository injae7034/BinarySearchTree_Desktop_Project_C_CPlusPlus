#include "VisitingCardBinderApp.h"
#include "VisitingCardBinderForm.h"
BOOL VisitingCardBinderApp::InitInstance()
{
	VisitingCardBinderForm visitingCardBinderForm;
	this->m_pMainWnd = &visitingCardBinderForm;
	visitingCardBinderForm.DoModal();

	return TRUE;
}
VisitingCardBinderApp visitingCardBinderApp;