#pragma once
class AbstractMap;
class AbstractMapItem;

class AbstarctMapFactory
{
public:
	AbstarctMapFactory();
	virtual ~AbstarctMapFactory();
	virtual AbstractMap *createMap(int type) = 0;
	virtual AbstractMapItem*createMapItem() = 0;
};

