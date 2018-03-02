#pragma once
#include<UIlib.h>
#include "Observer.h"
using namespace DuiLib;


class MainFrameWnd :public WindowImplBase,public Observer
{
public:
	MainFrameWnd();
	~MainFrameWnd();
public:
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("DUIMainFrame");
	}
	virtual CDuiString GetSkinFile()                { return _T("dangerous.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T("skin"); }
	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual int UpdateMessage(Subject * pSubject, unsigned int uMessage, unsigned lParam, unsigned int wParam);
	virtual void OnFinalMessage(HWND hWnd);
protected:
	bool OnButton(void *param);
private:
	NOTIFYICONDATA nid;
	CTabLayoutUI *tab_switch;
	CTileLayoutUI *classic_map;
	CButtonUI *btnclasic;
	CButtonUI *btngentle;
	CButtonUI *btnterrible;
	CLabelUI *lbplayername;
	CLabelUI *lbstatus;
	CButtonUI *play;
	CButtonUI *btnrestore;
	CButtonUI *btnsave;
	CButtonUI *btnconfigmap;
};

