#include "MapConfigWnd.h"
#include "CommonUtils.h"
#include "CppSQLite3.h"

MapConfigWnd::MapConfigWnd()
{
}


MapConfigWnd::~MapConfigWnd()
{
}


LRESULT MapConfigWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

void MapConfigWnd::InitWindow()
{
	btnsave = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnsave")));
	listmap = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listmap")));
	if (btnsave)
	{
		btnsave->OnNotify += MakeDelegate(this, &MapConfigWnd::onButton);
	}
	initList();
}

bool MapConfigWnd::onButton(void *param)
{
	TNotifyUI *  msg = (TNotifyUI *)param;
	CDuiString strName = msg->pSender->GetName();
	if (msg->sType == DUI_MSGTYPE_CLICK)
	{
		if (strName == _T("btnsave"))
		{
			btnsave->SetEnabled(false);
			CppSQLite3DB db;
			db.open("map.db");
			db.execDML("delete from tbclassicmap");
			db.execDML("begin transaction;");
			if (listmap)
			{
				int ct = listmap->GetCount();
				for (int i = 0; (ct > -1 && i < ct);++i)
				{
					CDuiString id = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(0)->GetText();
					CDuiString type = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(1)->GetText();
					CDuiString style = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(2)->GetText();
					CDuiString tool = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(3)->GetText();
					CDuiString count = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(4)->GetText();
					CDuiString pos = static_cast<CListContainerElementUI*>(listmap->GetItemAt(i))->GetItemAt(5)->GetText();
					char buff[512];
					memset(buff,0,512);
					sprintf_s(buff, "insert into tbclassicmap (id,type,style,tool,num,pos) values (%d,'%s','%s','%s',%d,'%s');", CommonUtils::DuiStringToInt(id), CommonUtils::ASCII2UTF_8(CommonUtils::DuiStringToString(type)).c_str(), CommonUtils::ASCII2UTF_8(CommonUtils::DuiStringToString(style)).c_str(), CommonUtils::ASCII2UTF_8(CommonUtils::DuiStringToString(tool)).c_str(), CommonUtils::DuiStringToInt(count), CommonUtils::ASCII2UTF_8(CommonUtils::DuiStringToString(pos)).c_str());
					db.execDML(buff);
				}
			}
			
			db.execDML("commit transaction;");
			btnsave->SetEnabled(true);
		}
	}
	return true;
}

void MapConfigWnd::initList()
{
	if (listmap)
	{
		CppSQLite3DB db;
		db.open("map.db");
		CppSQLite3Query q = db.execQuery("select * from tbclassicmap order by id;");
		while (!q.eof())
		{
			
			int id = q.getIntField(0);
			string type = q.getStringField(1);
			string style = q.getStringField(2);
			string tool = q.getStringField(3);
			int num = q.getIntField(4);
			string pos = q.getStringField(5);

			type = CommonUtils::UTF_82ASCII(type);
			string ttool = CommonUtils::UTF_82ASCII(tool);
			string tstyle = CommonUtils::UTF_82ASCII(style);
			pos = CommonUtils::UTF_82ASCII(pos);

			CDialogBuilder builder;
			CListContainerElementUI *cont = static_cast<CListContainerElementUI*>(builder.Create(_T("maplistelement.xml"), 0, NULL, &m_PaintManager));
			cont->GetItemAt(0)->SetText(CommonUtils::IntToDuiString(id));
			cont->GetItemAt(1)->SetText(CommonUtils::StringToDuiString(type));
			cont->GetItemAt(2)->SetText(CommonUtils::StringToDuiString(tstyle));
			cont->GetItemAt(3)->SetText(CommonUtils::StringToDuiString(ttool));
			cont->GetItemAt(4)->SetText(CommonUtils::IntToDuiString(num));
			cont->GetItemAt(5)->SetText(CommonUtils::StringToDuiString(pos));
			listmap->Add(cont);

			q.nextRow();
		}
		/*for (int i = 0; i != 64; ++i)
		{
			CDialogBuilder builder;
			CListContainerElementUI *cont = static_cast<CListContainerElementUI*>(builder.Create(_T("maplistelement.xml"), 0, NULL, &m_PaintManager));
			cont->GetItemAt(0)->SetText(CommonUtils::IntToDuiString(i));
			cont->GetItemAt(1)->SetText(_T("³£¹æ"));
			cont->GetItemAt(2)->SetText(_T("\*"));
			cont->GetItemAt(3)->SetText(_T("\*"));
			cont->GetItemAt(4)->SetText(_T("0"));
			cont->GetItemAt(5)->SetText(_T("0"));
			listmap->Add(cont);
		}*/
	}
}
