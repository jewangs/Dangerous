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

	//�����������Ϊ���߹���ͼ
	virtual int setToDisableView(int index) = 0;
	//�����������Ϊ��ǰλ����ͼ
	virtual int setToCurrentView(int index) = 0;
	//������㻹ԭΪ��׼��ͼ
	virtual int setToOrigionView(int index) = 0;
};

