#include "SetupWnd.h"
#include "MapConfigWnd.h"
#include "MapTableWnd.h"

SetupWnd::SetupWnd()
{
}


SetupWnd::~SetupWnd()
{
}

void SetupWnd::InitWindow()
{
	btnmaptable = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnmaptable")));
	btnallmap = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnallmap")));
	if (btnmaptable)
	{
		btnmaptable->OnNotify += MakeDelegate(this, &SetupWnd::onButton);
	}
	if (btnallmap)
	{
		btnallmap->OnNotify += MakeDelegate(this, &SetupWnd::onButton);
	}

}

bool SetupWnd::onButton(void *param)
{
	TNotifyUI* msg = (TNotifyUI*)param;
	if (msg->sType == DUI_MSGTYPE_CLICK)
	{
		if (msg->pSender->GetName() == _T("btnallmap"))
		{
			MapConfigWnd configwnd;
			configwnd.Create(NULL, _T("≈‰÷√"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
			configwnd.CenterWindow();
			configwnd.ShowModal();
		}
		else if (msg->pSender->GetName() == _T("btnmaptable"))
		{
			MapTableWnd tbwnd;
			tbwnd.Create(NULL, _T("≈‰÷√"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
			tbwnd.CenterWindow();
			tbwnd.ShowModal();
		}
	}
	return true;
}
