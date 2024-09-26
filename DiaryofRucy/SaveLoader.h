#pragma once

class StageScene;
class Stage;
class Player;
class TunderFlash;
class IcicleSpark;
class Explosion;

class SaveLoader 
{
private:
	Stage* _loadStage;

	int _stageNumber;
	int _preStageNumber;

public:

	void SaveData(StageScene* stageScene, Player* player, bool clear = false);
	void LoadData(StageScene* stageScene, Player* player);


	SaveLoader() {}
	~SaveLoader() {}
};

