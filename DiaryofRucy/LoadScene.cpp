#include "Stdafx.h"
#include "LoadScene.h"

HRESULT LoadScene::init(void)
{
	IMAGEMANAGER->addImage("블랙",
		"Resources/Images/title/black.bmp",
		WINSIZE_X, WINSIZE_Y,true,RGB(255,0,255));
	_Loadimg =IMAGEMANAGER->addFrameImage("로딩아이콘",
		"Resources/Images/title/loading.bmp",
		300*2, 312*2, 1, 4, true, RGB(255, 0, 255));
	count = index = 0;
	speed = 1;
	alpha = 0;
	rc1 = RectMakeCenter(WINSIZE_X - 450, WINSIZE_Y - 90, 300, 74);
	return S_OK;
}

void LoadScene::release(void)
{
	SAFE_DELETE(_Loadimg);
}

void LoadScene::update(void)
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
	if (count % 3 == 0)
	{
		if (alpha >= 255)
		{
			alpha = 0;
		}
		alpha += 20;

	}
}

void LoadScene::render(void)
{
	IMAGEMANAGER->alphaRender("블랙", getMemDC(),WINSIZE_X,WINSIZE_Y,alpha);
	IMAGEMANAGER->frameRender("로딩아이콘", getMemDC(),rc1.left+speed,rc1.top ,_Loadimg->getFrameX(), _Loadimg->getFrameY());
}

void LoadScene::d2drender(void)
{

}
