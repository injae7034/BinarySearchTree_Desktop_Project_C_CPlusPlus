#ifndef _TAKINGINFORM_H
#define _TAKINGINFORM_H
#include<Windows.h>

BOOL CALLBACK TakingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL TakingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakingInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL TakingInForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // ! _TAKINGINFORM_H

