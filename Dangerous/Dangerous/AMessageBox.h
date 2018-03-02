#pragma once
#include "UIlib.h"
using namespace DuiLib;

class AMessageBox :public WindowImplBase
{
public:
	AMessageBox();
	~AMessageBox();
public:
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("MessageBoxFrame");
	}
	virtual CDuiString GetSkinFile()                { return _T("messagebox.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T("skin"); }

	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	void setText(CDuiString mg)
	{
		if (msg)
		{
			msg->SetText(mg);
		}
	}

	static void Show(CDuiString mg,HWND hparent=0);
private:
	CTextUI *msg;
};

