#pragma once
#include "AbstractMap.h"
#include "UIlib.h"


using namespace DuiLib;
/************************************************************************/
/*�����ͼ����*/
/************************************************************************/
enum MAPTYPE{ CLASSIC, GENTLE,TERRIBLE};

class MapManager
{
public:
	MapManager();
	~MapManager();

public:
	void LoadMap(MAPTYPE type, CTileLayoutUI *);
	void ClearMap(CTileLayoutUI *);

	void getMapData(vector<MapData> &mapdata)
	{
		if (currmap)
		{
			currmap->getMapData(mapdata);
		}
	}

	//interface about item
	int getItemType(int index)
	{
		if (currmap != nullptr)
		{
			return currmap->getItemType(index);
		}
	}

	CDuiString getItemContent(int index)
	{
		if (currmap != nullptr)
		{
			return currmap->getItemContent(index);
		}
	}

	int getItemNumber(int index)
	{
		if (currmap != nullptr)
		{
			return currmap->getItemNumber(index);
		}
	}

	//�����������Ϊ���߹���ͼ
	int setToDisableView(int index){ return currmap->setToDisableView(index); }
	//�����������Ϊ��ǰλ����ͼ
	int setToCurrentView(int index){ return currmap->setToCurrentView(index); }
	//������㻹ԭΪ��׼��ͼ
	int setToOrigionView(int index){ return currmap->setToOrigionView(index); }

public:
	static MapManager *Instance();
	
private:
	MAPTYPE maptype;
	AbstractMap *currmap;
	
private:
	static MapManager *_instance;
};

