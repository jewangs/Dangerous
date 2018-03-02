#pragma once
#include "AbstarctMapFactory.h"
class MapFactory :
	public AbstarctMapFactory
{
public:
	MapFactory();
	~MapFactory();
public:
	//interface defined in AbstarctMapFactory
	virtual AbstractMap *createMap(int type);
	virtual AbstractMapItem*createMapItem();
};

