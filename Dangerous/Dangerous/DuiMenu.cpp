#include "DuiMenu.h"


CDuiMenu::CDuiMenu()
{
}


CDuiMenu::~CDuiMenu()
{
	//delete this;
}


void CDuiMenu::init(HWND phwmd,POINT pt)
{
	

	Create(phwmd, _T("MenuWnd"), WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_TOOLWINDOW);
	
	//::ClientToScreen(phwmd, &pt);
	//::ScreenToClient(phwmd, &pt);
	RECT rc;
	GetWindowRect(*this, &rc);
	::SetWindowPos(*this, NULL, pt.x, pt.y - (rc.bottom - rc.top) - 20, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	melist = static_cast<CListUI*>(m_PaintManager.FindControl(_T("menulist")));
	int ct = melist->GetCount();
	for (int i = 0; i != ct; ++i)
	{
		melist->GetItemAt(i)->OnNotify += MakeDelegate(this, &CDuiMenu::OnMenu);
	}

	
}

bool CDuiMenu::OnMenu(void *param)
{
	TNotifyUI *  msg = (TNotifyUI *)param;
	CDuiString strName = msg->pSender->GetName();
	if (msg->sType == _T("setfocus"))
	{
		if (strName = _T("menu_exit"))
		{
			Subject::Notify(MENU_MSG_QUIT, 0, 0, 0);
			::PostQuitMessage(0);
		}
		
		Close();
	}
	
	return true;
}

LRESULT CDuiMenu::HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lret;
	bool bhandled = true;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		lret = OnKillFocus(bhandled);
		break;
	default:
		bhandled = false;
		break;
	}

	if (bhandled || m_PaintManager.MessageHandler(uMsg, wparam, lparam, lret))
	{
		return lret;
	}

	return __super::HandleMessage(uMsg, wparam, lparam);
}