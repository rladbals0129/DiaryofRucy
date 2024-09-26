#pragma once
#include "GameNode.h"
#include "Map.h"
#include "Kruskal.h"
#include "StartMap.h"
#include "NormalMap.h"
#include "ShopMap.h"
#include "EndMap.h"
#include "BossMap.h"
#include "EventMap.h"
#include "ChestMap.h"
#include "SaveLoader.h"

class Player;
class EnemyManager;
class KingSlime;
class MegaFlime;
class MushMamBoss;
class GImage;

class MapManager : public GameNode
{
private:

	Player* _player;
	EnemyManager* _em;
	Kruskal* _kruskal;
	Map* _currentMap;
	KingSlime* _kingSlime;
	MegaFlime* _megaFlime;
	MushMamBoss* _mushMamBoss;
	bool _changeRoomFadeOut;

	bool _colTop;
	bool _colBottom;
	bool _colLeft;
	bool _colRight;

	int _colSign;

	RECT _rc[4];

	GImage* _collisionImage;
	string _collisionNameR;
	string _collisionNameL;

	SaveLoader* _saveLoad;
private:

	string _imageName;

private:

	int _playerX;
	int _playerY;

	int _currentX;
	int _currentY;
	int _saveX;
	int _saveY;

	int* _currentStage;

	Map* _stage1[4][5] =
	{
	   {nullptr,	nullptr,		new StartMap,	 nullptr,		nullptr},
	   {nullptr,	nullptr,		new NormalMap,	 new EventMap,	nullptr},
	   {nullptr,	new ChestMap,   new NormalMap,	 nullptr,		nullptr},
	   {nullptr,	nullptr,		new NormalMap,	 new BossMap,	new EndMap}
	};

	Map* _stage2[4][5] =
	{
	   {nullptr,	 new StartMap,		new ChestMap,	nullptr,		 nullptr},
	   {nullptr,	 new NormalMap,		nullptr,		nullptr,		 nullptr},
	   {new EventMap, new NormalMap,	nullptr,	    nullptr,		 new EndMap},
	   {nullptr,	  new NormalMap,	new NormalMap,	new NormalMap,	 new BossMap}
	};

	Map* _stage3[4][5] =
	{
	   {new ChestMap,	new NormalMap, 	new NormalMap,	new NormalMap,	 new EventMap},
	   {nullptr,		new BossMap,	nullptr,		new NormalMap,	 nullptr},
	   {nullptr,		new EndMap,		nullptr,		new NormalMap,	 nullptr},
	   {nullptr,		nullptr,		nullptr,		new StartMap,	 new NormalMap}
	};

	bool _save;

public:

	HRESULT init(Player* player, int* stage);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	int pixelCollision(RECT object, string imageName);

	string getImageName() { return _imageName; }
	EnemyManager* getEnemyMemoryAddress(void) { return _em; }
	Map* getCurrentMap(void) { return _currentMap; }
	Map* getTotalStageMap(int x, int y) 
	{ 
		switch (*_currentStage)
		{
		case 1:
			return _stage1[y][x];
			break;
		case 2:
			return _stage2[y][x];
			break;
		case 3:
			return _stage3[y][x];
			break;
		default:
			break;
		}
		return 0;
	}


	void setPlayerMemoryAddress(Player* player) { _player = player; }
	void setEnemyMemoryAddress(EnemyManager* enemy) { _em = enemy; }
	void setSaveLoaderMemoryAddress(SaveLoader* saveLoad) { _saveLoad = saveLoad; }
	Player* getPlayerMemoryAddress() { return _player; }
	KingSlime* getKingSlimeMemoryAddress() { return _kingSlime; }
	MegaFlime* getMegaFlimeMemoryAddress() { return _megaFlime; }
	MushMamBoss* getMushMamBossMemoryAddress() { return _mushMamBoss; }

	bool getSave() { return _save; }
	int getCurrentX() { return _currentX; }
	int getCurrentY() { return _currentY; }
	void setCurrentX(int x) {_currentX = x; }
	void setCurrentY(int y) {_currentY = y; }

	void setSaveComplete() { this->_save = false; }
	void setStage(int stage);
	void moveRoom();
	void setChangeRoomFadeOut() { _changeRoomFadeOut = true; }

	MapManager() {}
	~MapManager() {}
};

