#pragma once
#include<UIlib.h>
using namespace DuiLib;

class MapConfigWnd :
	public WindowImplBase
{
public:
	MapConfigWnd();
	~MapConfigWnd();
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("MapConfigFrame");
	}
	virtual CDuiString GetSkinFile()                { return _T("configmap.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T("skin"); }

	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	bool onButton(void *param);
	void initList();
private:
	CListUI *listmap;
	CButtonUI *btnsave;
};

