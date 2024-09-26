#include "Stdafx.h"
#include "SaveLoader.h"
#include "StageScene.h"
#include "Stage.h"
#include "Player.h"
#include "ThunderFlash.h"
#include "IcicleSpark.h"
#include "Explosion.h"


/*
현재 스테이지가 결정 되는 수치 - stageScene의 currentStage
스테이지 맵이 결정 되는 수치 - Stage의 MapManager의 currentX, currentY
플레이어의 현재 정보 -> 맵안에 있는 플레이어

전방 선언으로 불러 오자

StageScene -> Stage -> MapManager-> Map -> MapManager -> Stage -> StageScene
*/

void SaveLoader::SaveData(StageScene* stageScene, Player* player, bool clear)
{
	cout << "현재 상황을 저장합니다." << endl;

	char stageType[32];
	sprintf_s(stageType, "%d", stageScene->getStageMemoryAddress()->getCurrentStage());
	INIDATAMANAGER->addData("Stage", "Game", stageType);
	
	char currentMapX[32];
	sprintf_s(currentMapX, "%d", stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getCurrentX());
	INIDATAMANAGER->addData("Stage", "CurrentMapX", currentMapX);
	
	char currentMapY[32];
	sprintf_s(currentMapY, "%d", stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getCurrentY());
	INIDATAMANAGER->addData("Stage", "CurrentMapY", currentMapY);
	
	char isVisitRoom[32];
	char isClearRoom[32];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j) != nullptr) &&
				stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getIsVisit())
			{
				sprintf_s(isVisitRoom, "%d%d", i, j);
				char numbering[32];
				sprintf_s(numbering, "VisitRoom_%s", isVisitRoom);
				char visit[32];
				sprintf_s(visit, "%d", 1);
				INIDATAMANAGER->addData("Stage", numbering, visit);
			}
			if ((stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j) != nullptr) &&
				(stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getMapName() == "노멀맵") && 
				stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getIsClear())
			{
				sprintf_s(isClearRoom, "%d%d", i, j);
				char numbering[64];
				sprintf_s(numbering, "ClearRoom_%s", isClearRoom);
				char clear[32];
				sprintf_s(clear, "%d", 1);
				INIDATAMANAGER->addData("Stage", numbering, clear);
			}
		}
	}


	char playerX[128];
	char playerY[128];
	char level[32];
	char exp[32];
	char maxHp[32];
	char currentHp[32];
	char maxMp[32];
	char currentMp[32];

	sprintf_s(playerX, "%d", player->getPosition().x);
	sprintf_s(playerY, "%d", player->getPosition().y);
	sprintf_s(level, "%d", *(player->getLevel()));
	sprintf_s(exp, "%d", (int)*(player->getExp()));
	sprintf_s(maxHp, "%d", *(player->getMaxHP()));
	sprintf_s(currentHp, "%d", *(player->getCurrentHP()));
	sprintf_s(maxMp, "%d", *(player->getMaxMP()));
	sprintf_s(currentMp, "%d", *(player->getCurrentMP()));


	INIDATAMANAGER->addData("Player", "playerX", playerX);
	INIDATAMANAGER->addData("Player", "playerY", playerY);
	INIDATAMANAGER->addData("Player", "Level", level);
	INIDATAMANAGER->addData("Player", "Exp", exp);
	INIDATAMANAGER->addData("Player", "MaxHP", maxHp);
	INIDATAMANAGER->addData("Player", "currentHP", currentHp);
	INIDATAMANAGER->addData("Player", "MaxMP", maxMp);
	INIDATAMANAGER->addData("Player", "currentMP", currentMp);


	INIDATAMANAGER->iniSave("Save", clear);
}


void SaveLoader::LoadData(StageScene* stageScene, Player* player)
{
	cout << "정보를 불러 옵니다." << endl;

	stageScene->setNumCurrentStage(INIDATAMANAGER->loadDataInteger("Save", "Stage", "Game"));
	
	if (INIDATAMANAGER->loadDataInteger("Save", "Stage", "Game") != 1)
	{
		stageScene->setCurrentStage(new Stage);
		stageScene->getStageMemoryAddress()->init(player, stageScene->getNumCurrentStage());
	}


	stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->setCurrentX(INIDATAMANAGER->loadDataInteger("Save", "Stage", "CurrentMapX"));
	stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->setCurrentY(INIDATAMANAGER->loadDataInteger("Save", "Stage", "CurrentMapY"));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char key[32];
			sprintf_s(key, "VisitRoom_%d%d", i, j);
			if (INIDATAMANAGER->loadDataInteger("Save", "Stage", key) == 1)
			{
				stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->setIsVisit();
			}

			sprintf_s(key, "ClearRoom_%d%d", i, j);
			if (INIDATAMANAGER->loadDataInteger("Save", "Stage", key) == 1)
			{
				stageScene->getStageMemoryAddress()->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->setIsClear();
			}		
		}
	}

	player->setPosition(INIDATAMANAGER->loadDataInteger("Save", "Player", "playerX"),
		INIDATAMANAGER->loadDataInteger("Save", "Player", "playerY"));
	player->setLevel(INIDATAMANAGER->loadDataInteger("Save", "Player", "Level"));
	switch (INIDATAMANAGER->loadDataInteger("Save", "Player", "Level"))
	{
	default:
	case 4:
		player->setSkill(new Explosion);
	case 3:
		player->setSkill(new IcicleSpark);
	case 2:
		player->setSkill(new ThunderFlash);
	case 1:
		break;
	}
	player->setExp(INIDATAMANAGER->loadDataInteger("Save", "Player", "Exp"));
	player->setMaxHP(-*player->getMaxHP() + INIDATAMANAGER->loadDataInteger("Save", "Player", "MaxHP"));
	player->setCurrentHP(-*player->getCurrentHP() + INIDATAMANAGER->loadDataInteger("Save", "Player", "currentHP"));
	player->setMaxMP(-*player->getMaxMP() + INIDATAMANAGER->loadDataInteger("Save", "Player", "MaxMP"));
	player->setCurrentMP(-*player->getCurrentMP() + INIDATAMANAGER->loadDataInteger("Save", "Player", "currentMP"));
}