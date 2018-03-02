#pragma once
#include "UIlib.h"
using namespace DuiLib;

class LiceseWnd :public WindowImplBase
{
public:
	LiceseWnd();
	~LiceseWnd();
	virtual void InitWindow();
	virtual CDuiString GetSkinFolder(){ return _T("skin"); }
	virtual CDuiString GetSkinFile(){ return _T("license.xml"); }
	virtual LPCTSTR GetWindowClassName(void) const{ return _T("LicenseFrame"); }
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	bool onButton(void *param);
private:
	CButtonUI* btnaccept;
	CButtonUI* btnrespect;
	CTextUI *txlicese;
};

