#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	IMAGEMANAGER->addImage("블랙",
		"Resources/Images/title/black.bmp",
		WINSIZE_X, WINSIZE_Y);
	D2DMANAGER->loadImageD2D("Theend",
		L"Resources/Images/title/end.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);
	_piano = IMAGEMANAGER->addFrameImage("피아노",
		"Resources/Images/title/piano4.bmp",
		318*2, 97*2, 3, 1, true, RGB(255, 0, 255));
	D2DMANAGER->loadImageD2D("Theendtx",
		L"Resources/Images/title/end3.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);
	D2DMANAGER->loadImageD2D("피아노", L"Resources/Images/title/piano_track1.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);

	SOUNDMANAGER->addSound("liebestraum_short", "Resources/audio/liebestraum_short.ogg",true,true);
	SOUNDMANAGER->play("liebestraum_short", 100);
	count = pcount = 0;
	pindex = 0;
	alpha = 255; palpha = 0;
	piano = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 100, _piano->getFrameWidth(), _piano->getFrameHeight());
	return S_OK;
}

void EndingScene::release(void)
{

}

void EndingScene::update(void)
{

	
	count++;
	if (count % 3 == 0)
	{
		if (alpha <= 1)
		{
			alpha = 1;
		}
		alpha -= 1.2;

	} //fadeIn

	pcount++;
	if (pcount % 16 == 0)
	{
		if (pindex > 3)
		{
			pindex = 0;
		}
		_piano->setFrameX(pindex);
		pindex++;
	}
	endcount++;
	if (endcount > 400)
	{
		SCENEMANAGER->chanegeScene("오프닝씬");
		SOUNDMANAGER->stop("liebestraum_short");
	}
	cout << endcount << endl;

}

void EndingScene::render(void)
{

}

void EndingScene::d2drender(void)
{

	D2DMANAGER->render("Theend", 0, 0, WINSIZE_X, WINSIZE_Y);
	D2DMANAGER->render("Theendtx", 0, 0, WINSIZE_X, WINSIZE_Y);
	D2DMANAGER->render("피아노", 0, 0, WINSIZE_X, WINSIZE_Y);

}

void EndingScene::UIrender(void)
{
	_piano->frameRender(getMemDC(), piano.left, piano.top, _piano->getFrameX(), _piano->getFrameY());
	IMAGEMANAGER->alphaRender("블랙", getMemDC(), 0, 0, alpha);
}
