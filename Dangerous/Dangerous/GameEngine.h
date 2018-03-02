#pragma once
#include "Subject.h"
#include <boost/random.hpp>
#include "MapManager.h"

#define GAME_MSG_DICE_NUM 3050
#define GAME_MSG_STATUES 3051
#define GAME_MSG_GAME_END 3052
#define GAME_MSG_NEXT_STEP 3053
#define GAME_MSG_TO_END 3054
#define GAME_MSG_TO_ORG 3055
#define GAME_MSG_GO_BACK 3056
#define GAME_MSG_GO_FOWARD 3057

class GameEngine :
	public Subject
{
public:
	GameEngine();
	~GameEngine();
public:
	static GameEngine *Instance();
	void playGame();
	void rolldice();
	bool isGaming(){ return isgaming; }
	void ForceEndGame(){ isgaming = false; }
private:
	void dorolldice();
	void dothegame();
	void execute(int dicen);
	void movenext();
	void moveback();
	void movetoorigion();
private:
	static GameEngine *_instance;
	static int dicenum;
	bool isgaming;
	int currstep;
	int sumsetp;
	boost::variate_generator<boost::minstd_rand, boost::uniform_int<> > die;
	vector<MapData> vmap;
};

