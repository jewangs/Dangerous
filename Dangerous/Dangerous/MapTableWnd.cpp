#include "MapTableWnd.h"
#include "CommonUtils.h"
#include "CppSQLite3.h"

MapTableWnd::MapTableWnd()
{
}


MapTableWnd::~MapTableWnd()
{
}


void MapTableWnd::InitWindow()
{
	plist = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list")));
	btnsave = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnsave")));
	if (btnsave)
	{
		btnsave->OnNotify += MakeDelegate(this, &MapTableWnd::onButton);
	}

	if (plist)
	{
		//≥ı ºªØ±Ì
		for (int i = 0; i != 8; ++i)
		{
			CDialogBuilder builder;
			CListContainerElementUI *cont = static_cast<CListContainerElementUI*>(builder.Create(_T("maptableelement.xml"), 0, NULL, &m_PaintManager));
			cont->GetItemAt(0)->SetText(CommonUtils::IntToDuiString(i));
			plist->Add(cont);
		}
		
	}
}

LRESULT MapTableWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

bool MapTableWnd::onButton(void *param)
{
	TNotifyUI *msg = (TNotifyUI*)param;
	if (msg->sType == DUI_MSGTYPE_CLICK)
	{
		if (msg->pSender->GetName() == _T("btnsave"))
		{
			dosave();
		}
	}

	return true;
}

void MapTableWnd::dosave()
{
	CppSQLite3DB db;
	db.open("map.db");

	int ct = plist->GetCount();
	int colct = plist->GetHeader()->GetCount();
	for (int i = 0; i != ct; ++i)
	{
		for (int j = 1; j != colct; ++j)
		{
			int index = i * (colct - 1) + j;
			CDuiString step = (static_cast<CListContainerElementUI*>(plist->GetItemAt(i)))->GetItemAt(j)->GetText();
			if (step == _T(""))
			{
				step = _T("0");
			}
			char buff[256];
			memset(buff,0,256);
			sprintf_s(buff, "update tbclassicmap set pos = '%s' where id = %d;", CommonUtils::DuiStringToString(step).c_str(), index);
			db.execDML(buff);
		}
	}
	Close();
}
