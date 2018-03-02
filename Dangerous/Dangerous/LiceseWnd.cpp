#include "LiceseWnd.h"


LiceseWnd::LiceseWnd()
{
}


LiceseWnd::~LiceseWnd()
{
}


void LiceseWnd::InitWindow()
{
	btnaccept = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnaccept")));
	btnrespect = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnrespect")));
	txlicese = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("txlicese")));
	if (btnaccept)
	{
		btnaccept->OnNotify += MakeDelegate(this, &LiceseWnd::onButton);
	}
	if (btnrespect)
	{
		btnrespect->OnNotify += MakeDelegate(this, &LiceseWnd::onButton);
	}
	if (txlicese)
	{
		txlicese->SetAttribute(_T("showhtml"), _T("true"));
		txlicese->SetAttribute(_T("align"), _T("left"));
		txlicese->SetText(_T("{n}{v center}{x 225}{b}许可协议{/b}{/x}{/v}{n}{n}{p}本软件仅供娱乐使用，禁止用于任何商业用途。{n}{n}本软件禁止用于非法用途，如因使用本软件产生任何法律纠纷，开发者本人不负任何法律责任。{p}"));
	}
}

bool LiceseWnd::onButton(void *param)
{
	TNotifyUI *msg = (TNotifyUI*)param;
	CDuiString sdname = msg->pSender->GetName();
	if (msg->sType == DUI_MSGTYPE_CLICK)
	{
		if (sdname == _T("btnaccept"))
		{
			Close(1);
			return true;
		}
		else if (sdname == _T("btnrespect"))
		{
			Close(0);
			return false;
		}
	}
	return true;
}

LRESULT LiceseWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	return FALSE;
}


LRESULT LiceseWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}