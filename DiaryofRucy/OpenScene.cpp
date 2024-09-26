#include "Stdafx.h"
#include "OpenScene.h"

HRESULT OpenScene::init(void)
{
	D2DMANAGER->loadImageD2D("타이틀", L"Resources/Images/title/layer1.png",
		WINSIZE_X, WINSIZE_Y,1, 1);
	
	D2DMANAGER->loadImageD2D("인물들", L"Resources/Images/title/opening2.png",
		WINSIZE_X, WINSIZE_Y,1,1);
	
	D2DMANAGER->loadImageD2D("인물들2", L"Resources/Images/title/opening3.png",
		WINSIZE_X, WINSIZE_Y, 1, 1);

	D2DMANAGER->loadImageD2D("파티클", L"Resources/Images/title/particle.png",
		44, 44,1,1);
	D2DMANAGER->loadImageD2D("파티클1", L"Resources/Images/title/particle.png",
		44, 44, 1, 1);
	D2DMANAGER->loadImageD2D("파티클2", L"Resources/Images/title/particle.png",
		44, 44, 1, 1);
	D2DMANAGER->loadImageD2D("파티클3", L"Resources/Images/title/particle.png",
		44, 44, 1, 1);

	_new=IMAGEMANAGER->addFrameImage("새게임", "Resources/Images/title/startimg22.bmp",
		130, 60,1,2, true, RGB(255, 0, 255));
	_option=IMAGEMANAGER->addFrameImage("옵션", "Resources/Images/title/optionimg22.bmp",
		130, 60, 1, 2, true, RGB(255, 0, 255));
	_end=IMAGEMANAGER->addFrameImage("끝", "Resources/Images/title/exitimg22.bmp",
		130, 60, 1, 2, true, RGB(255, 0, 255));
	rc1 = RectMakeCenter(WINSIZE_X / 2 , WINSIZE_Y / 3 + 280, 250, 80);
	rc2 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 3 + 350, 250, 80);
	rc3 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 3 + 420, 250, 80);
	clicked = false;

		return S_OK;
}

void OpenScene::release(void)
{


}

void OpenScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		clicked = true;
	}
	_new->setFrameY(0);
	_option->setFrameY(0);
	_end->setFrameY(0);

}

void OpenScene::render(void)
{
	IMAGEMANAGER->render("선택창음영", getMemDC(),WINSIZE_X/2,WINSIZE_Y/3);
	if (clicked)
	{
		IMAGEMANAGER->frameRender("새게임", getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 3 + 270, _new->getFrameX(), _new->getFrameY());
		IMAGEMANAGER->frameRender("옵션", getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 3 + 340, _option->getFrameX(), _option->getFrameY());
		IMAGEMANAGER->frameRender("끝", getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 3 + 410, _end->getFrameX(), _end->getFrameY());

	}
	/*if (KEYMANAGER->isToggleKey(VK_RBUTTON))
	{
		DrawRectMake(getMemDC(), rc1);
		DrawRectMake(getMemDC(), rc2);
		DrawRectMake(getMemDC(), rc3);
	}*/
}

void OpenScene::d2drender(void)
{
	D2DMANAGER->render("타이틀", 0,0 ,0,0);
	D2DMANAGER->render("인물들", 0, 0, 0, 0);

	if (clicked)
	{
		D2DMANAGER->render("인물들2", 0, 0, 0, 0);
	}
	if (clicked && PtInRect(&rc1, _ptMouse))
	{
		_new->setFrameY(1);
	}
	if (clicked && PtInRect(&rc2, _ptMouse))
	{
		_option->setFrameY(1);
	}
	if (clicked && PtInRect(&rc3, _ptMouse))
	{
		_end->setFrameY(1);
	}
	
	D2DMANAGER->render("파티클", 160+cosf(DEGREE_RADIAN(60)), 500+RND->getFromIntTo(100,300), 0, 0);
	D2DMANAGER->render("파티클1", RND->getFromIntTo(300, 400), RND->getFromIntTo(300, 500), 0, 0);
	D2DMANAGER->render("파티클2", RND->getFromIntTo(400, 500), RND->getFromIntTo(200, 600), 0, 0);
	D2DMANAGER->render("파티클3", RND->getFromIntTo(800, 1000), RND->getFromIntTo(400, 700), 0, 0);

	{
	char xar[120];
	wsprintf(xar, "x, y: %d %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 1191, 24, xar, strlen(xar));

	}
}	
	
	

