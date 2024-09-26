#include "Stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init(void)
{
	_numCurrentStage = 1;
	_numPreStage = 1;

	_stage1 = new Stage;
	_player = new Player;
	_player->init();
	_stage1->init(_player, &_numPreStage);

	_currentStage = _stage1;
	_player->setEnemyManagerMomoryAddress(_currentStage->getEnemyManagerMemoryAddress());

	_ui = new UI;
	_ui->setPlayerMemoryAddress(_player);
	_ui->setStageMemoryAddress(_currentStage);
	_ui->init();
	_player->setUIMemoryAddress(_ui);


	//_saveLoad->SaveStage(this, _currentStage, _player);
	//setSaveLoaderMemoryAddress(_saveLoad);
	//SD : 처음 스테이지 입장시 효과음 추가 '뾰롱~'
	if (_loadGame)
	{
		_saveLoad = new SaveLoader; 
		_saveLoad->LoadData(this, _player);
		_numPreStage = _numCurrentStage;
		_ui->setStageMemoryAddress(_currentStage);
		_player->setEnemyManagerMomoryAddress(_currentStage->getEnemyManagerMemoryAddress());
	}
	SOUNDMANAGER->play("스테이지시작", 0.1f);
	_save = false;
	_load = false;

	return S_OK;
}

void StageScene::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_ui);
	SAFE_DELETE(_stage1);
	SAFE_DELETE(_stage2);
	SAFE_DELETE(_stage3);
	SAFE_DELETE(_saveLoad);
}				
				
void StageScene::update(void)
{
	// 다음스테이지
	if (KEYMANAGER->isOnceKeyDown('0')) _numPreStage++;

	if (_numCurrentStage != _numPreStage)
	{
		//SD : 다음 스테이지 이동시 찰랑이는 효과음 추가 (입장음과 다르다)- > 페이드 아웃 기능 추가하면 추가 할 것.
		_numCurrentStage = _numPreStage;
		if (_numCurrentStage == 2)
		{
			_stage2 = new Stage;
			_currentStage = _stage2;
			_currentStage->init(this->getPlayerMemoryAddress(), &_numPreStage);
			_ui->setStageMemoryAddress(_currentStage);
			SOUNDMANAGER->play("스테이지시작", 0.1f);
			_saveLoad->SaveData(this, _player, true);
			_currentStage->getMapManagerMemoryAddress()->setSaveComplete();
			_save = false;
			_stage1->release();

		}
		else if (_numCurrentStage == 3)
		{
			_stage3 = new Stage;
			_currentStage = _stage3;
			_currentStage->init(this->getPlayerMemoryAddress(), &_numPreStage);
			_ui->setStageMemoryAddress(_currentStage);
			SOUNDMANAGER->play("스테이지끝", 0.1f);
			_saveLoad->SaveData(this, _player, true);
			_currentStage->getMapManagerMemoryAddress()->setSaveComplete();
			_save = false;
			_stage2->release();

		}
		_ui->setStageMemoryAddress(_currentStage);
		_player->setPosition(WINSIZE_X / 2, WINSIZE_Y / 2);
		_player->setEnemyManagerMomoryAddress(_currentStage->getEnemyManagerMemoryAddress());

	}

	_currentStage->update();
	if (_currentStage->getMapManagerMemoryAddress()->getCurrentMap()->getMapName() == "노멀맵") _player->setEnemyManagerMomoryAddress(_currentStage->getEnemyManagerMemoryAddress());
	else _player->setEnemyManagerMomoryAddress(nullptr);
	

	if (_currentStage->getMapManagerMemoryAddress()->getCurrentMap()->getMapName() == "보스맵")
	{
		switch (_numCurrentStage)
		{
		case 1:
			_player->setKingSlimeMemoryAddress(_currentStage->getKingSlimeMemoryAddress());
			_ui->setKingSlimeMemoryAddress(_currentStage->getKingSlimeMemoryAddress());
			break;
		case 2:
			_player->setMegaFlimeMemoryAddress(_currentStage->getMegaFlimeMemoryAddress());
			_ui->setMegaFlimeMemoryAddress(_currentStage->getMegaFlimeMemoryAddress());
			break;
		case 3:
			_player->setMushMamBossMemoryAddress(_currentStage->getMushMamBossMemoryAddress());
			_ui->setMushMamBossMemoryAddress(_currentStage->getMushMamBossMemoryAddress());
			break;
		default:
			break;
		}
	}
	else
	{
		_player->setKingSlimeMemoryAddress(nullptr);
		_player->setMegaFlimeMemoryAddress(nullptr);
		_player->setMushMamBossMemoryAddress(nullptr);
		_ui->setKingSlimeMemoryAddress(nullptr);
		_ui->setMegaFlimeMemoryAddress(nullptr);
		_ui->setMushMamBossMemoryAddress(nullptr);
	}
	
	if (IMAGEMANAGER->getAlpha() == 0)
	{
		_player->update();
	}
	if (_player->getBehaviorType(9))
	{
		IMAGEMANAGER->fadeOut(1);
		if (IMAGEMANAGER->getAlpha() > 250) SCENEMANAGER->chanegeScene("게임오버씬");

	}

	_ui->update();
	

	// 세이브
	if (_currentStage->getMapManagerMemoryAddress()->getSave() || _save ||
		_currentStage->getMapManagerMemoryAddress()->getCurrentMap()->getSave())
	{
		saveData();
	}

	// 로드
	if (_load)
	{
		loadData();
		_load = false;
	}
}

void StageScene::render(void)
{
	_currentStage->render();
	_player->render();
	_ui->render();
}

void StageScene::d2drender(void)
{
	_currentStage->d2drender();
	_player->d2drender();
	_ui->d2drender();
}

void StageScene::UIrender(void)
{
	_ui->UIrender();
}

void StageScene::loadData(void)
{
	_saveLoad->LoadData(this, _player);
	_load = false;
}

void StageScene::saveData(void)
{
	_saveLoad->SaveData(this, _player);
	_currentStage->getMapManagerMemoryAddress()->setSaveComplete();
	_currentStage->getMapManagerMemoryAddress()->getCurrentMap()->setSaveComplete();
	_save = false;
}
