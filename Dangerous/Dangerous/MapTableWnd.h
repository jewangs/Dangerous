#pragma once

#include "UIlib.h"
using namespace DuiLib;

class MapTableWnd:public WindowImplBase
{
public:
	MapTableWnd();
	~MapTableWnd();
public:
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("MapTableFrame");
	}
	virtual CDuiString GetSkinFile()                { return _T("maptable.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T("skin"); }

	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	bool onButton(void *);
	void dosave();
private:
	CListUI* plist;
	CButtonUI* btnsave;
};

