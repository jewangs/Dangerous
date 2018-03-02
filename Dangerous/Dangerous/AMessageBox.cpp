#include "AMessageBox.h"


AMessageBox::AMessageBox()
{
}


AMessageBox::~AMessageBox()
{
}

void AMessageBox::InitWindow()
{
	msg = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("msg")));
}

void AMessageBox::Show(CDuiString mg, HWND hparent)
{
	AMessageBox box;
	box.Create(hparent, _T("֪ͨ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	box.CenterWindow();
	box.setText(mg);
	box.ShowModal();
}
