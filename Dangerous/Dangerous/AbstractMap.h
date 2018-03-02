#pragma once
#include "UIlib.h"
#include <vector>
using namespace std;


using namespace DuiLib;
struct MapData
{
	int id;
	string type;
	string style;
	string tool;
	int num;
	string pos;
};


class AbstractMap
{
public:
	AbstractMap();
	virtual ~AbstractMap();
public:
	//interfaces
	virtual int getItemType(int index) = 0;
	virtual CDuiString getItemContent(int index) = 0;
	virtual int getItemNumber(int index) = 0;
	virtual void getMapData(vector<MapData>&) = 0;
	virtual void LoadMapItems(CTileLayoutUI*layout) = 0;
	virtual void ClearMap(CTileLayoutUI *layout) = 0;

	//将坐标点设置为已走过视图
	virtual int setToDisableView(int index) = 0;
	//将坐标点设置为当前位置视图
	virtual int setToCurrentView(int index) = 0;
	//将坐标点还原为标准视图
	virtual int setToOrigionView(int index) = 0;
};

