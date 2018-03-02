#pragma once
#include "AbstractMap.h"
#include<vector>
using namespace std;

class AbstractMapItem;

class ClassicMap :
	public AbstractMap
{
public:
	ClassicMap();
	~ClassicMap();
public:
	//implement the interfaces
	virtual int getItemType(int index){ return 0; }
	virtual CDuiString getItemContent(int index){ return _T(""); }
	virtual int getItemNumber(int index){ return 0; }
	virtual void getMapData(vector<MapData>&);
	virtual void LoadMapItems(CTileLayoutUI*layout);
	virtual void ClearMap(CTileLayoutUI *layout);

	//�����������Ϊ���߹���ͼ
	virtual int setToDisableView(int index);
	
	//�����������Ϊ��ǰλ����ͼ
	virtual int setToCurrentView(int index);
	//������㻹ԭΪ��׼��ͼ
	virtual int setToOrigionView(int index);
	
private:
	void load();
private:
	std::vector<AbstractMapItem*> vmapitems;
	vector<MapData> mapdata;
	CTileLayoutUI* maplayout;
};

