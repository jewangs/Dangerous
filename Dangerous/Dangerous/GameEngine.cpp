#include "GameEngine.h"
#include<thread>

#include<time.h>
#include<windows.h>


GameEngine* GameEngine::_instance = 0;
int GameEngine::dicenum = 0;

GameEngine::GameEngine() :die(boost::minstd_rand((uint32_t)time(0)), boost::uniform_int<>(1, 6))
{
}


GameEngine::~GameEngine()
{
}


GameEngine* GameEngine::Instance()
{
	if (0 == _instance)
	{
		_instance = new GameEngine();
	}
	return _instance;
}

void GameEngine::rolldice()
{
	thread th(&GameEngine::dorolldice, this);
	th.detach();
	
}

void GameEngine::playGame()
{
	isgaming = true;
	thread thgame(&GameEngine::dothegame,this);
	thgame.detach();
}

void GameEngine::dorolldice()
{


	for (int i = 0; i != 20; ++i)
	{
		dicenum = die();
		Notify(GAME_MSG_DICE_NUM, dicenum, 0, 0);
		::Sleep(100);
	}

	if (isgaming)
	{
		execute(dicenum);
	}
}
	

static bool cmppos(MapData& l, MapData& r)
{
	int il = atoi(l.pos.c_str());
	int ir = atoi(r.pos.c_str());
	return il <= ir;
}

void GameEngine::dothegame()
{
	//加载地图数据
	vmap.clear();
	vector<MapData> mapdta;
	MapManager::Instance()->getMapData(mapdta);
	for (auto it = mapdta.begin(); it != mapdta.end();++it)
	{
		if (it->pos == "0")
		{
			continue; 
		}
		vmap.push_back(*it);
	}

	sort(vmap.begin(), vmap.end(), cmppos);
	currstep = 0;
	sumsetp = vmap.size() - 1;
	Notify(GAME_MSG_STATUES, currstep, sumsetp, 0);

}

void GameEngine::execute(int dicen)
{
	if (currstep <= sumsetp)
	{
		//通知UI移动
		for (int i = 0; i < dicen && currstep < sumsetp; ++i)
		{
			movenext();
			::Sleep(300);
		}
		if (currstep >= sumsetp)
		{
			MapManager::Instance()->setToCurrentView(vmap[sumsetp].id);
			Notify(GAME_MSG_GAME_END, vmap[sumsetp].id, 0, 0);
			Notify(GAME_MSG_STATUES, currstep, sumsetp, 0);
			return;
		}

		//处理地图信息
		MapData data = vmap[currstep];
		if (data.type == "飞行")
		{
			if (data.tool == "直到终点")
			{
				Notify(GAME_MSG_GAME_END, vmap[sumsetp].id, 0, 0);
				Notify(GAME_MSG_STATUES, currstep, sumsetp, 0);
				return;
			}
			else if (data.tool == "回到原点")
			{
				movetoorigion();
			}
		}
		else if (data.type == "跳步")
		{
			if(data.tool == "前进")
			{
				for (int i = 0; i < data.num && currstep < sumsetp; ++i)
				{
					movenext();
					::Sleep(300);
				}
				if (currstep >= sumsetp)
				{
					Notify(GAME_MSG_GAME_END, vmap[sumsetp].id, 0, 0);
					Notify(GAME_MSG_STATUES, currstep, sumsetp, 0);
					return;
				}
			}
			else if (data.tool == "后退")
			{
				int i = 0,c = currstep;
				for (i = c; i > 0 && data.num > 0; --i)
				{
					moveback();
					::Sleep(200);
					--data.num;
				}
				
				
				
			}
		}
		Notify(GAME_MSG_STATUES, currstep, sumsetp, 0);
	}
}

void GameEngine::movenext()
{
	MapManager::Instance()->setToDisableView(vmap[currstep].id);
	MapManager::Instance()->setToCurrentView(vmap[currstep + 1].id);
	++currstep;
}

void GameEngine::moveback()
{
	MapManager::Instance()->setToOrigionView(vmap[currstep].id);
	MapManager::Instance()->setToCurrentView(vmap[currstep - 1].id);
	--currstep;
}

void GameEngine::movetoorigion()
{
	for (int i = currstep; i > 0; --i)
	{
		MapManager::Instance()->setToCurrentView(vmap[i - 1].id);
		MapManager::Instance()->setToOrigionView(vmap[i].id);
		::Sleep(200);
	}
	currstep = 0;
}