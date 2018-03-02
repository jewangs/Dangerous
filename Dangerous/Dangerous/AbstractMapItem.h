#pragma once
#include<string>
using namespace std;
#include "UIlib.h"
using namespace DuiLib;

#define MAPITEM_VIEW_TYPE_DISABLE 4001
#define MAPITEM_VIEW_TYPE_CURRENT 4002
#define MAPITEM_VIEW_TYPE_ORIGION 4003

class AbstractMapItem :public CContainerUI
{
public:
	AbstractMapItem();
	virtual ~AbstractMapItem();
public:
	virtual void setContent(int id,string type,string style,string tool,int mun,string pos) = 0;
	virtual int getid() = 0;
	virtual int getnum() = 0;
	virtual string gettype() = 0;
	virtual string gettool() = 0;
	virtual string getpos() = 0;
	virtual void setbgcolor(CDuiString clorr) = 0;

	virtual void setView(int type) = 0;
};

