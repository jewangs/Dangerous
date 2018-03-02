#include "MapFactory.h"
#include "ClassicMap.h"
#include "ClassicMapItem.h"

MapFactory::MapFactory()
{
}


MapFactory::~MapFactory()
{
}

AbstractMap *MapFactory::createMap(int type)
{
	AbstractMap *rtmap = new ClassicMap();

	return rtmap;
}


AbstractMapItem *MapFactory::createMapItem()
{
	return new ClassicMapItem();
}