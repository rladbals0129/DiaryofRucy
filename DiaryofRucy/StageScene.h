#pragma once
#include "GameNode.h"
#include "Player.h"
#include "UI.h"
#include "Stage.h"
#include "item.h"
#include "SaveLoader.h"

//class SaveLoader;

class StageScene : public GameNode
{
private:
	Player* _player;
	UI* _ui;


	Stage* _stage1;
	Stage* _stage2;
	Stage* _stage3;

	Stage* _currentStage;


	int _numCurrentStage;
	int _numPreStage;

private:
	SaveLoader* _saveLoad;
	bool _save;
	bool _load;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);
	void loadData(void);
	void saveData(void);

	Player* getPlayerMemoryAddress(void) { return _player; }
	Stage* getStageMemoryAddress(void) { return _currentStage; }
	int* getNumCurrentStage(void) { return &_numCurrentStage; }
	
	void setNumCurrentStage(int numStage) { this->_numCurrentStage = numStage; }
	void setSaveLoaderMemoryAddress(SaveLoader* saveLoad) { _saveLoad = saveLoad; }
	void setCurrentStage(Stage* stage) 
	{
		if (_currentStage) _currentStage = nullptr;
		_currentStage = stage; 
	}

	void setLoadData() { this->_load = true; }
	void setSaveData() { this->_save = true; }

	StageScene() {}
	~StageScene() {}
};
