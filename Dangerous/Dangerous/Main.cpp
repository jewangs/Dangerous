#include<Windows.h>
#include<tchar.h>
#include "MainFrameWnd.h"
#include "LiceseWnd.h"



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR lpCmdLine, int nCmdShow)
{
	
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	LiceseWnd licewnd;
	licewnd.Create(NULL, _T("许可协议"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	licewnd.CenterWindow();
	int sta = licewnd.ShowModal();
	if (0 == sta)
	{
		return -1;
	}

	MainFrameWnd framewnd;
	framewnd.Create(NULL, _T("冒险"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	framewnd.CenterWindow();
	framewnd.ShowModal();


	return 0;
}