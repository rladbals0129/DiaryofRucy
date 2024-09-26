#include "Stdafx.h"
#include "Stage.h"


HRESULT Stage::init(Player* player, int* stage)
{
	_numCurrentStage = *stage;
	_mm = new MapManager;
	_mm->setPlayerMemoryAddress(player);

	_mm->init(player, stage);
	
	_em = _mm->getEnemyMemoryAddress();


	// 보스들 현재 스테이지에 맞게 이닛해줄것
	switch (*stage)
	{
	case 1:
		setKingSlime();
		break;
	case 2:
		setMegaFlime();
		break;
	case 3:
		setMushMamBoss();
		break;
	default:
		break;
	}

	//setSaveLoaderMemoryAddress(_saveLoad);
	//_mm->setSaveLoaderMemoryAddress(_saveLoad);

	SOUNDMANAGER->play("오프닝&배경", 0.1f);

	return S_OK;
}

void Stage::release(void)
{
	SAFE_DELETE(_mm);
}

void Stage::update(void)
{
	_mm->update();
	_em = _mm->getEnemyMemoryAddress();
}

void Stage::render(void)
{
	_mm->render();

}

void Stage::d2drender(void)
{
	_mm->d2drender();
}


void Stage::setKingSlime()
{
	_bossSlime = _mm->getKingSlimeMemoryAddress();
}

void Stage::setMegaFlime()
{
	_bossFlime = _mm->getMegaFlimeMemoryAddress();
}

void Stage::setMushMamBoss()
{
	_bossMushmam = _mm->getMushMamBossMemoryAddress();
}
