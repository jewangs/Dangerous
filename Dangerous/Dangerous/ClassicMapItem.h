#pragma once
#include "AbstractMapItem.h"
#include "UIlib.h"
using namespace DuiLib;

class ClassicMapItem :
	public AbstractMapItem
{
public:
	ClassicMapItem();
	~ClassicMapItem();
public:
	//implement of interfaces
	virtual void setContent(int id, string type, string style, string tool, int mun, string pos)
	{
		this->id = id;
		this->type = type;
		this->style = style;
		this->tool = tool;
		this->num = mun;
		this->pos = pos;
		updateview();
	}
	virtual int getid(){ return id; }
	virtual int getnum(){ return num; }
	virtual string gettype(){ return type; }
	virtual string gettool(){return tool;}
	virtual string getpos(){return pos;}
	virtual void setbgcolor(CDuiString clorr)
	{
		if (itembk)
		{
			itembk->SetAttribute(_T("bkcolor"), clorr.GetData());
		}
	}
	void updateview();

	void setView(int type);
private:
	int id;
	string type;
	string style;
	string tool;
	string pos;
	int num;
	CDuiString origincolor;

	//controls
	CVerticalLayoutUI *itembk;
	CLabelUI *lbstyle;
	CLabelUI *lbtool;
	CLabelUI *lbcount;
};

