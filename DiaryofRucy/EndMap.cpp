#include "Stdafx.h"
#include "EndMap.h"
#include "StageScene.h"

HRESULT EndMap::vInit(void)
{
	_mapName = "엔드맵";
	_image = IMAGEMANAGER->addImage("시작&출구방", "Resources/Images/Maps/MapImage/시작&출구.bmp", WINSIZE_X, WINSIZE_Y);
	_colImg = IMAGEMANAGER->addImage("충-시작&출구", "Resources/Images/Maps/Collision/충-시작&출구.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	_potal = new Potal;
	_potal->init();

	_imgName = "충-시작&출구";
	_pImgNameR = "충-시작&출구";
	_pImgNameL = "충-시작&출구";
	_isClear = true;
	_soundPotal = false;
	
	return S_OK;
}

void EndMap::release(void)
{
	_potal->release();
}

void EndMap::objectUpdate(void)
{
	_potal->update();;
	if (getDistance(_player->getPosition().x, _player->getPosition().y, _potal->getPosition().x, _potal->getPosition().y) < 50)
	{
		cout << "왜안댐?" << endl;
		if (!_soundPotal)
		{
			SOUNDMANAGER->play("스테이지끝", 0.1f);
			_soundPotal = true;
		}
		
		IMAGEMANAGER->fadeOut();
		if (*_stage == 1)
		{
			if (IMAGEMANAGER->getAlpha() == 255)
			{
				*_stage = 2;
				_player->setPosition(WINSIZE_X / 2, WINSIZE_Y / 2);
				return;
			}
		}
		if (*_stage == 2)
		{
			if (IMAGEMANAGER->getAlpha() == 255)
			{
				*_stage = 3;
				_player->setPosition(WINSIZE_X / 2, WINSIZE_Y / 2);
				return;
			}
		}
		if (*_stage == 3)
		{
			if (IMAGEMANAGER->getAlpha() == 255)
			{
				SCENEMANAGER->chanegeScene("엔딩씬");
				return;
			}

		}
	}

}

void EndMap::d2dObjectRender(void)
{
	_potal->d2drender();
}
