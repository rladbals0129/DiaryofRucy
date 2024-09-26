#include "Stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(void)
{
	
	IMAGEMANAGER->addImage("블랙",
		"Resources/Images/title/black.bmp",
		WINSIZE_X, WINSIZE_Y);

	D2DMANAGER->loadImageD2D("루시의일기", L"Resources/Images/title/loading6.png",
		140, 59);

	_Loadimg = IMAGEMANAGER->addFrameImage("로딩아이콘",
		"Resources/Images/title/loading.bmp",
		300 * 2, 312 * 2, 1, 4, true, RGB(255, 0, 255));

	D2DMANAGER->loadImageD2D("tip11", L"Resources/Images/title/tip0.png",
		720, 47);
	D2DMANAGER->loadImageD2D("tip22", L"Resources/Images/title/tip1.png",
		720, 47);
	D2DMANAGER->loadImageD2D("tip33", L"Resources/Images/title/tip2.png",
		720, 47);

	count = index = 0;
	speed = 2;
	alpha = 255;
	rcLoad = RectMakeCenter(WINSIZE_X - 450, WINSIZE_Y - 90, 300, 74);

	

	RandNum();

	
	return S_OK;
}
void LoadingScene::RandNum()
{
	_setPattern = static_cast<EPattern>(rand() % 3);
}

void LoadingScene::release(void)
{
}

void LoadingScene::update(void)
{
	count++;
	if (count % 16 == 0)
	{
		if (index >= 4)
		{
			index = 0;
		}
		_Loadimg->setFrameY(index);
		index++;
		speed++;
	}

	count1++;
	if (count % 3 == 0)
	{
		if (alpha <= 1)
		{
			alpha = 1;
		}
		alpha -= 1.5;

	} //fadeIn
	cout << count << endl;
	if (count1 > 250)
	{
		SCENEMANAGER->chanegeScene("스테이지씬");
	}
}

void LoadingScene::render(void)
{
	IMAGEMANAGER->render("블랙",getMemDC(),0, 0);
	IMAGEMANAGER->frameRender("로딩아이콘", getMemDC(), rcLoad.left + speed, rcLoad.top, _Loadimg->getFrameX(), _Loadimg->getFrameY());

}

void LoadingScene::d2drender(void)
{
	D2DMANAGER->render("루시의일기", WINSIZE_X-220, 100, 140, 59);
	switch (_setPattern)
	{
	case PATTERN1:
		D2DMANAGER->render("tip11", WINSIZE_X / 2-400, WINSIZE_Y - 90, 720 * (1.1), 50);
	
		break;
	case PATTERN2:
		D2DMANAGER->render("tip22", WINSIZE_X / 2-400, WINSIZE_Y - 90, 720 * (1.1), 50);
		
		break;
	case PATTERN3:
		D2DMANAGER->render("tip33", WINSIZE_X / 2-400, WINSIZE_Y - 90, 720 * (1.1), 50);
	
		break;
	default:
		
		break;
	}
}

void LoadingScene::UIrender(void)
{

	IMAGEMANAGER->alphaRender("블랙", getMemDC(), 0, 0, alpha);
}

