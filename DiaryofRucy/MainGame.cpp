#include "Stdafx.h"
#include "MainGame.h"
#include "TeamReport.h"
#include "OpeningScene.h"
#include "StageScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"
#include "SceneChanger.h"
#include "LoadingScene.h"
#include "JsonDataScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_resources.init();


	SCENEMANAGER->addScene("¾ÀÃ¼ÀÎÀú", new SceneChanger);
	SCENEMANAGER->addScene("xÀÚ°úÁ¦¾À", new TeamReport);
	SCENEMANAGER->addScene("¿ÀÇÁ´×¾À", new OpeningScene);
	SCENEMANAGER->addScene("°ÔÀÓ¿À¹ö¾À", new GameOverScene);
	SCENEMANAGER->addScene("½ºÅ×ÀÌÁö¾À", new StageScene);
	SCENEMANAGER->addScene("¿£µù¾À", new EndingScene);
	SCENEMANAGER->addScene("·Îµù¾À", new LoadingScene);
	SCENEMANAGER->addScene("json1", new JsonDataScene);

	
	SCENEMANAGER->chanegeScene("¿ÀÇÁ´×¾À");
	Json::Value;
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	
	//_curruntGame->release();
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();
	SOUNDMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{	
		SCENEMANAGER->chanegeScene("¾ÀÃ¼ÀÎÀú");
	}

	

}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	//===============================================
	SCENEMANAGER->render();
	D2DMANAGER->beginDraw();
	SCENEMANAGER->d2drender();
	D2DMANAGER->endDraw();
	SCENEMANAGER->UIrender();
	if(KEYMANAGER->isToggleKey(VK_F1)) TIMEMANAGER->render(getMemDC());



	//=================================================
	this->getBackBuffer()->render(getHDC());
}
