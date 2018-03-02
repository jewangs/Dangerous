#include "MapManager.h"
#include "MapFactory.h"

MapManager* MapManager::_instance = 0;

MapManager::MapManager()
{
	currmap = nullptr;
}


MapManager::~MapManager()
{
	if (currmap != nullptr)
	{
		delete currmap;
		currmap = nullptr;
	}
}

MapManager* MapManager::Instance()
{
	if (0 == _instance)
	{
		_instance = new MapManager();
	}
	
	return _instance;
}


void MapManager::LoadMap(MAPTYPE type, CTileLayoutUI *layout)
{
	maptype = type;
	if (currmap != nullptr)
	{
		delete currmap;
		currmap = nullptr;
	}

	AbstarctMapFactory *fac = new MapFactory();
	currmap = fac->createMap(type);

	delete fac;
	fac = nullptr;

	if (currmap)
	{
		currmap->LoadMapItems(layout);
	}
}

void MapManager::ClearMap(CTileLayoutUI *layout)
{
	if (currmap)
	{
		currmap->ClearMap(layout);
	}
}

