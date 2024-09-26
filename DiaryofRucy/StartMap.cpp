#include "Stdafx.h"
#include "StartMap.h"

HRESULT StartMap::vInit(void)
{
    _mapName = "시작맵";

    _image = IMAGEMANAGER->addImage("시작&출구방", "Resources/Images/Maps/MapImage/시작&출구.bmp", WINSIZE_X, WINSIZE_Y);
    _colImg = IMAGEMANAGER->addImage("충-시작&출구", "Resources/Images/Maps/Collision/충-시작&출구.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
    _d2dObjectImage = D2DMANAGER->findImage("시작포탈");
    _rcObject = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, _d2dObjectImage->frameWidth, _d2dObjectImage->frameHeight);
    _frameWorldTime = TIMEMANAGER->getWorldTime() + 1.0f;
    _frameTime = 0.5;
    _isVisit = true;
    _startImage = false;
    _startImageAlpha = 2.0f;

    _imgName = "충-시작&출구";
    _pImgNameR = "충-시작&출구";
    _pImgNameL = "충-시작&출구";
    // 기본 아이템 3개 이미지 배치
    _isClear = true;



    return S_OK;
}

void StartMap::objectUpdate()
{
    if (_frameWorldTime < TIMEMANAGER->getWorldTime()) _startImage = true;
    if (_startImage)
    {
        if (_startImageAlpha > 0)
        {
            _startImageAlpha -= 0.02;
            if (IMAGEMANAGER->getAlpha() > 0) IMAGEMANAGER->fadeIn();
        }
    }
}

void StartMap::d2dObjectRender(void)
{
    D2DMANAGER->frameRender("시작포탈", _rcObject.left, _rcObject.top, 1, 0);
    D2DMANAGER->alphaRender("반딧불이숲", WINSIZE_X / 3+60, WINSIZE_Y / 5, _startImageAlpha);

    switch (*_stage)
    {
    case 1:
        D2DMANAGER->alphaRender("1층", WINSIZE_X / 3+60, WINSIZE_Y / 5, _startImageAlpha);
        break;
    case 2:
        D2DMANAGER->alphaRender("2층", WINSIZE_X / 3+60, WINSIZE_Y / 5, _startImageAlpha);
        break;
    case 3:
        D2DMANAGER->alphaRender("3층", WINSIZE_X / 3+60, WINSIZE_Y / 5, _startImageAlpha);
        break;
    default:
        break;
    }
}


