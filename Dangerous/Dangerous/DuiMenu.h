#pragma once
#include<UIlib.h>
#include"Subject.h"
using namespace DuiLib;

#define MENU_MSG_QUIT 3556

class CDuiMenu:public WindowImplBase,public Subject
{
public:
	CDuiMenu();
protected:
	~CDuiMenu();
	CDuiString  m_strXMLPath;
public:
	explicit CDuiMenu(LPCTSTR xmlpath) :m_strXMLPath(xmlpath){}
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("CDuiMenu");
	}
	virtual CDuiString GetSkinFolder()
	{
		return _T("skin");
	}
	virtual CDuiString GetSkinFile()            { return m_strXMLPath; }
	virtual void       OnFinalMessage(HWND hWnd){ delete this; }

	void init(HWND hwndParent,POINT pt);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam);
private:
	LRESULT OnKillFocus(bool& bhanled)
	{
		Close();
		bhanled = false;
		return 0;
	}

	bool OnMenu(void *param);

	CListUI* melist;
};

