#include "ClassicMapItem.h"
#include "CommonUtils.h"

ClassicMapItem::ClassicMapItem()
{
	CDialogBuilder builder;
	CContainerUI* pDesk = static_cast<CContainerUI*>(builder.Create(_T("mapitem.xml"), (UINT)0));
	if (pDesk == nullptr)
	{
		pDesk = static_cast<CContainerUI*>(builder.Create());
	}
	if (pDesk != nullptr)
	{
		this->Add(pDesk);
		pDesk = nullptr;
	}
	itembk = static_cast<CVerticalLayoutUI*>(this->FindSubControl(_T("itembk")));
	lbstyle = static_cast<CLabelUI*>(this->FindSubControl(_T("lbstyle")));
	lbtool = static_cast<CLabelUI*>(this->FindSubControl(_T("lbtool")));
	lbcount = static_cast<CLabelUI*>(this->FindSubControl(_T("lbcount")));
}


ClassicMapItem::~ClassicMapItem()
{
}

void ClassicMapItem::updateview()
{
	if (pos == "0")
	{
		itembk->SetVisible(false);
	}
	else
	{

		if (type == "常规")
		{
			itembk->SetAttribute(_T("bkcolor"), _T("#FFEEE9E9"));
			origincolor = _T("#FFEEE9E9");
			if (lbstyle)
			{
				lbstyle->SetText(CommonUtils::StringToDuiString(style).GetData());
			}
			if (lbtool)
			{
				lbtool->SetText(CommonUtils::StringToDuiString(tool).GetData());
			}
			if (lbcount)
			{
				lbcount->SetText(CommonUtils::IntToDuiString(num).GetData());
			}
		}
		else if (type == "飞行")
		{
			itembk->SetAttribute(_T("bkcolor"), _T("#FFB0E2FF"));
			origincolor = _T("#FFB0E2FF");
			if (lbstyle)
			{
				lbstyle->SetText(_T(""));
			}
			if (lbtool)
			{
				lbtool->SetText(CommonUtils::StringToDuiString(tool).GetData());
			}
			if (lbcount)
			{
				lbcount->SetText(_T(""));
			}
			

		}
		else if (type == "跳步")
		{
			itembk->SetAttribute(_T("bkcolor"), _T("#FFB0B0B0"));
			origincolor = _T("#FFB0B0B0");
			if (lbstyle)
			{
				lbstyle->SetText(_T(""));
			}
			if (lbtool)
			{
				lbtool->SetText(CommonUtils::StringToDuiString(tool).GetData());
			}
			if (lbcount)
			{
				lbcount->SetText(CommonUtils::IntToDuiString(num).GetData());
			}
		}
		else if (type == "开始" || type == "结束")
		{
			itembk->SetAttribute(_T("bkcolor"), _T("#FFB03060"));
			origincolor = _T("#FFB03060");
			if (lbstyle)
			{
				lbstyle->SetText(_T(""));
			}
			if (lbtool)
			{
				lbtool->SetText(CommonUtils::StringToDuiString(type).GetData());
			}
			if (lbcount)
			{
				lbcount->SetText(_T(""));
			}
		}
		

	}
	
}

void ClassicMapItem::setView(int type)
{
	switch (type)
	{
	case MAPITEM_VIEW_TYPE_DISABLE:
		setbgcolor(_T("FF79CDCD"));
		break;
	case MAPITEM_VIEW_TYPE_CURRENT:
		setbgcolor(_T("FFCAFF70")); 
		break;
	case MAPITEM_VIEW_TYPE_ORIGION:
		setbgcolor(origincolor);
		break;
	default:
		break;
	}
}
