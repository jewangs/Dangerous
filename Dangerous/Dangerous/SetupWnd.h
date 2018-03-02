#pragma once
#include "UIlib.h"
using namespace DuiLib;

class SetupWnd :public WindowImplBase
{
public:
	SetupWnd();
	~SetupWnd();
public:
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("SetUpFrame");
	}
	virtual CDuiString GetSkinFile()                { return _T("setup.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T("skin"); }

	virtual void InitWindow();

private:
	bool onButton(void *);

private:
	CButtonUI* btnmaptable;
	CButtonUI* btnallmap;
};

