#include "MainFrameWnd.h"
#include "DuiMenu.h"
#include "resource.h"
#include "MapManager.h"
#include "CommonUtils.h"
#include "MapConfigWnd.h"
#include "GameEngine.h"
#include "SetupWnd.h"
#include "AbstractMapItem.h"
#include "AMessageBox.h"

#define WM_NOTIFYICON WM_USER + 1

MainFrameWnd::MainFrameWnd()
{
	GameEngine::Instance()->Attach(this);
}


MainFrameWnd::~MainFrameWnd()
{
	GameEngine::Instance()->Detach(this);
}

void MainFrameWnd::InitWindow()
{
	//初始化控件
	tab_switch = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_switch")));
	classic_map = static_cast<CTileLayoutUI*>(m_PaintManager.FindControl(_T("classicmap")));
	btnclasic = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnclasic")));
	btngentle = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btngentle")));
	btnterrible = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnterrible")));
	lbplayername = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lbplayername")));
	lbstatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lbstatus")));
	play = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("play")));
	btnrestore = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnrestore")));
	btnsave = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnsave")));
	btnconfigmap = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnconfigmap")));
	//绑定按钮事件
	if (nullptr != btnclasic)
	{
		btnclasic->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (nullptr != btngentle)
	{
		btngentle->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (nullptr != btnterrible)
	{
		btnterrible->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (nullptr != play)
	{
		play->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (nullptr != btnrestore)
	{
		btnrestore->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (nullptr != btnsave)
	{
		btnsave->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}
	if (btnconfigmap)
	{
		btnconfigmap->OnNotify += MakeDelegate(this, &MainFrameWnd::OnButton);
	}




	SetIcon(IDI_ICON_APP);
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->GetHWND();
	nid.uID = IDI_ICON_SMALL;
	nid.hIcon = ::LoadIcon(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_ICON_APP));
	nid.uCallbackMessage = WM_NOTIFYICON;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	_tcscpy_s(nid.szTip, L"大冒险");
	::Shell_NotifyIcon(NIM_ADD, &nid);

}

void MainFrameWnd::OnFinalMessage(HWND hWnd)
{

	SetIcon(IDI_ICON_APP);
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = IDI_ICON_SMALL;
	nid.hIcon = ::LoadIcon(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_ICON_APP));
	nid.uCallbackMessage = WM_NOTIFYICON;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	_tcscpy_s(nid.szTip, L"大冒险");
	::Shell_NotifyIcon(NIM_DELETE, &nid);
}


bool MainFrameWnd::OnButton(void *param)
{
	TNotifyUI *  msg = (TNotifyUI *)param;
	CDuiString strName = msg->pSender->GetName();
	if (msg->sType == DUI_MSGTYPE_CLICK)
	{
		if (strName == _T("btnclasic"))
		{

			if (btnclasic->GetText() == _T("结束游戏"))
			{
				MapManager::Instance()->ClearMap(classic_map);

				btnclasic->SetText(_T("经典模式"));
				GameEngine::Instance()->ForceEndGame();
				return true;
			}

			MapManager::Instance()->LoadMap(CLASSIC, classic_map);		
			tab_switch->SelectItem(0);
			GameEngine::Instance()->playGame();
			btnclasic->SetText(_T("结束游戏"));
		}
		else if (strName == _T("btngentle"))
		{

		}
		else if (strName == _T("btnterrible"))
		{

		}
		else if (strName == _T("play"))
		{
			GameEngine::Instance()->rolldice();
		}
		else if (strName == _T("btnrestore"))
		{

		}
		else if (strName == _T("btnsave"))
		{

		}
		else if (strName == _T("btnconfigmap"))
		{		
			SetupWnd swnd;
			swnd.Create(NULL, _T("设置"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
			swnd.CenterWindow();
			swnd.ShowModal();
		}
	}
	return true;
}


LRESULT MainFrameWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (uMsg)
	{
	case WM_NOTIFYICON:
		{
			if (wParam == IDI_ICON_SMALL && lParam == WM_RBUTTONDOWN)
			{			
				POINT pt;
				GetCursorPos(&pt);
				CDuiMenu *pMenu = new CDuiMenu(_T("menu.xml"));
				pMenu->Attach(this);
				pMenu->init(*this, pt);
				pMenu->ShowWindow(TRUE);
				::SetFocus(*pMenu);
			}
		}
		break;
	default:
		break;
	}
	bHandled = FALSE;
	return 0;
}

int MainFrameWnd::UpdateMessage(Subject * pSubject, unsigned int uMessage, unsigned lParam, unsigned int wParam)
{
	if (pSubject == GameEngine::Instance())
	{
		if (!GameEngine::Instance()->isGaming())
		{
			return 0;
		}
		CDuiString str;
		switch (uMessage)
		{
			
		case GAME_MSG_DICE_NUM:
			str.Format(_T("file='%d.png' dest='9,9,81,81' corner='5,5,5,5'"), lParam);
			play->SetAttribute(_T("bkimage"), str.GetData());
			break;
		case GAME_MSG_STATUES:
			str.Format(_T("%d/%d"), lParam, wParam);
			lbstatus->SetText(str.GetData());
			break;
		case GAME_MSG_GAME_END:
			AMessageBox::Show(_T("{y 80}恭喜通关！{/y}"),*this);
			break;
		case GAME_MSG_NEXT_STEP:
			
			break;
		case GAME_MSG_TO_ORG:
			
			break;
		default:
			break;
		}

	}
	
	return 0;
}