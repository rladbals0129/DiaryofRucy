#include "Stdafx.h"
#include "GameOverScene.h"

HRESULT GameOverScene::init(void)
{
	D2DMANAGER->loadImageD2D("¿£µù1", L"Resources/Images/title/game_over.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);
	D2DMANAGER->loadImageD2D("¿£µù2", L"Resources/Images/title/game_over1.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);
	D2DMANAGER->loadImageD2D("¿£µù3", L"Resources/Images/title/game_over2.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);


	IMAGEMANAGER->addImage("ºí·¢",
		"Resources/Images/title/black.bmp",
		WINSIZE_X, WINSIZE_Y);
	_text = IMAGEMANAGER->addImage("±¦Âú²Þ",
		"Resources/Images/title/±¦Âú²Þ.bmp", 674, 117, 500, 87, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼±ÅÃ1", "Resources/Images/title/¼±ÅÃ2.bmp",
		250, 80);

	SOUNDMANAGER->addSound("die", "Resources/audio/me01.ogg", true, true);
	SOUNDMANAGER->play("die", 100);
	SOUNDMANAGER->addSound("ui_cursor", "Resources/audio/ui_cursor.ogg", true, false);
	SOUNDMANAGER->addSound("ui_ok", "Resources/audio/ui_ok.ogg", true, false);

	D2DMANAGER->loadImageD2D("¼±ÅÃÃ¢1", L"Resources/Images/title/´Ù½Ãµ¹¾Æ°¡.png",
		412, 319);
	width = _text->getWidth();
	rc1 = RectMakeCenter(WINSIZE_X / 2 - 20, WINSIZE_Y / 3 + 260, 240, 80);
	rc2 = RectMakeCenter(WINSIZE_X / 2 - 20, WINSIZE_Y / 3 + 340, 240, 80);
	es1 = RectMakeCenter(WINSIZE_X / 2 - 20, WINSIZE_Y / 3 + 255, 240, 10);
	es2 = RectMakeCenter(WINSIZE_X / 2 - 20, WINSIZE_Y / 3 + 315, 240, 10);
	text = RectMakeCenter(WINSIZE_X / 2 - 160, WINSIZE_Y / 3 + 120, 240, 80);
	alpha = 255;
	alpha1 = 255;
	count = 0;
	count1 = 0;
	speed = 0;
	clicked = false;
	return S_OK;
}

void GameOverScene::release(void)
{
	
}

void GameOverScene::update(void)
{
	if (!clicked)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			clicked = true;
		}
	}
	count++;
	if (count % 3 == 0)
	{
		if (alpha <= 1)
		{
			alpha = 1;
		}
		alpha -= 1.2;

	} //fadeIn
	count1++;
	if (count1 % 3 == 0)
	{
		if (alpha1 >= 255)
		{
			alpha1 = 1;
		}
		alpha1 += 50;

	} //fadeIn
	speed++;
}

void GameOverScene::render(void)
{

}

void GameOverScene::d2drender(void)
{
	D2DMANAGER->render("¿£µù1", 0, 0, 0, 0);
	D2DMANAGER->render("¿£µù2", 0, 0, 0, 0);
	D2DMANAGER->render("¿£µù3", 0, 0, WINSIZE_X, WINSIZE_Y);

	if (clicked)
	{
		D2DMANAGER->render("¼±ÅÃÃ¢1", WINSIZE_X / 2 - 160, WINSIZE_Y / 3 + 180, 300, 260);

	}
}

void GameOverScene::UIrender(void)
{
	IMAGEMANAGER->render("±¦Âú²Þ", getMemDC(), text.left, text.top);
	IMAGEMANAGER->alphaRender("ºí·¢", getMemDC(), 0, 0, alpha);
	if (clicked && PtInRect(&es1, _ptMouse))
	{
		SOUNDMANAGER->play("ui_cursor", 100);
	}
	if (clicked && PtInRect(&es2, _ptMouse))
	{
		SOUNDMANAGER->play("ui_cursor", 100);
	}
	if (clicked && PtInRect(&rc1, _ptMouse))
	{
		IMAGEMANAGER->alphaRender("¼±ÅÃ1", getMemDC(), rc1.left, rc1.top, alpha1);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("ui_ok", 100);
			_loadGame = true;
			SCENEMANAGER->chanegeScene("·Îµù¾À");
		}
	}
	if (clicked && PtInRect(&rc2, _ptMouse))
	{
		IMAGEMANAGER->alphaRender("¼±ÅÃ1", getMemDC(), rc2.left, rc2.top, alpha1);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("ui_ok", 100);
			SCENEMANAGER->chanegeScene("¿ÀÇÁ´×¾À");
		}

	}


}
