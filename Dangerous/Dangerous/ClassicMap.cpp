#include "ClassicMap.h"
#include "CppSQLite3.h"
#include "CommonUtils.h"
#include<cstdlib>
#include<ctime>
#include "MapFactory.h"
#include "AbstractMapItem.h"


ClassicMap::ClassicMap()
{
	load();
}


ClassicMap::~ClassicMap()
{
	for (size_t i = 0; i < vmapitems.size();++i)
	{
		if (vmapitems[i])
		{
			delete vmapitems[i];
			vmapitems[i] = nullptr;
		}
	}
}

void ClassicMap::load()
{
	CppSQLite3DB db;
	db.open("map.db");
	CppSQLite3Query q = db.execQuery("select * from tbclassicmap order by id;");
	srand((unsigned)time(NULL));

	while (!q.eof())
	{
		MapData data;
		data.id = q.getIntField(0);
		data.type = q.getStringField(1);
		data.style = q.getStringField(2);
		data.tool = q.getStringField(3);
		data.num = q.getIntField(4);
		data.pos = q.getStringField(5);

		data.type = CommonUtils::UTF_82ASCII(data.type);
		data.tool = CommonUtils::UTF_82ASCII(data.tool);
		data.style = CommonUtils::UTF_82ASCII(data.style);
		data.pos = CommonUtils::UTF_82ASCII(data.pos);


		if (data.num == 0)
		{
			
			data.num = rand() % (100 - 20 + 1) + 20;

		}
		mapdata.push_back(data);

		MapFactory fac;
		AbstractMapItem *item = fac.createMapItem();
		item->setContent(data.id, data.type, data.style, data.tool, data.num, data.pos);
		vmapitems.push_back(item);

		q.nextRow();
	}
	
}


void ClassicMap::getMapData(vector<MapData>&mapd)
{
	mapd = mapdata;
}

void ClassicMap::LoadMapItems(CTileLayoutUI*layout)
{
	maplayout = layout;
	for (auto it = vmapitems.begin(); it != vmapitems.end(); ++it)
	{
		layout->Add(*it);
	}
}

void ClassicMap::ClearMap(CTileLayoutUI *layout)
{
	for (auto it = vmapitems.begin(); it != vmapitems.end(); ++it)
	{
		if (maplayout == layout)
		{
			layout->Remove(*it, true);
		}
	}
}

int ClassicMap::setToDisableView(int index)
{
	if (maplayout)
	{
		if (maplayout->GetItemAt(index))
		{
			((AbstractMapItem*)maplayout->GetItemAt(index))->setView(MAPITEM_VIEW_TYPE_DISABLE);
		}
	}

	return 0;
}

int ClassicMap::setToCurrentView(int index)
{
	if (maplayout)
	{
		if (maplayout->GetItemAt(index))
		{
			((AbstractMapItem*)maplayout->GetItemAt(index))->setView(MAPITEM_VIEW_TYPE_CURRENT);
		}
	}
	return 0;
}

int ClassicMap::setToOrigionView(int index)
{
	if (maplayout)
	{
		if (maplayout->GetItemAt(index))
		{
			((AbstractMapItem*)maplayout->GetItemAt(index))->setView(MAPITEM_VIEW_TYPE_ORIGION);
		}
	}
	return 0;
}

