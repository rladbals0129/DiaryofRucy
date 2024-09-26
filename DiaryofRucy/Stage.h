#pragma once
#include "GameNode.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "KingSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"
#include "SaveLoader.h"

class Stage : public GameNode
{
private:
	int _numCurrentStage;
	EnemyManager* _em;
	MapManager* _mm;
	KingSlime*	 _bossSlime;
	MegaFlime*	_bossFlime;
	MushMamBoss* _bossMushmam;

private:
	bool _save;
	
	SaveLoader* _saveLoad;

	int _saveX;
	int _saveY;

public:
	HRESULT init(Player* player, int* stage);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	EnemyManager* getEnemyManagerMemoryAddress() { return _em; }
	MapManager* getMapManagerMemoryAddress()	{ return _mm; }
	KingSlime*	 getKingSlimeMemoryAddress()   { return _bossSlime; }
	MegaFlime*	 getMegaFlimeMemoryAddress()   { return _bossFlime; }
	MushMamBoss* getMushMamBossMemoryAddress() { return _bossMushmam; }

	int getCurrentStage() { return this->_numCurrentStage; }
	
	void setSaveLoaderMemoryAddress(SaveLoader* saveLoad) { _saveLoad = saveLoad; }

	void setKingSlime();
	void setMegaFlime();
	void setMushMamBoss();

	bool getSave() { return this->_save; }


	Stage() {}
	// 복사 생성자
	//Stage(Stage& stageLoad, Player* player)
	//{
	//	_numCurrentStage = stageLoad._numCurrentStage;
	//	
	//	_mm = new MapManager;
	//	_mm->setPlayerMemoryAddress(player);
	//	_mm->init(player, &stageLoad._numCurrentStage);
	//	_em = _mm->getEnemyMemoryAddress();
	//	switch (stageLoad._numCurrentStage)
	//	{
	//	case 1:
	//		setKingSlime();
	//		break;
	//	case 2:
	//		setMegaFlime();
	//		break;
	//	case 3:
	//		setMushMamBoss();
	//		break;
	//	default:
	//		break;
	//	}
	//	setSaveLoaderMemoryAddress(_saveLoad);
	//	_mm->setSaveLoaderMemoryAddress(_saveLoad);
	//}
	~Stage() {}
};

