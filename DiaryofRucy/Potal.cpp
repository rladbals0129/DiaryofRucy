#include "Stdafx.h"
#include "Potal.h"

HRESULT Potal::init()
{

	_d2dObjectImage = D2DMANAGER->findImage("스테이지포탈");
    _x = WINSIZE_X / 2;
    _y = WINSIZE_Y / 2;
	_rcObject = RectMakeCenter(_x, _y, _d2dObjectImage->frameWidth, _d2dObjectImage->frameHeight);
	_frameWorldTime = TIMEMANAGER->getWorldTime();
	_frameTime = 0.05;
	_frameX = _frameY = 0;


	return S_OK;
}

void Potal::release(void)
{
    SAFE_DELETE(_d2dObjectImage);
}

void Potal::update(void)
{
    if (_frameWorldTime + _frameTime < TIMEMANAGER->getWorldTime())
    {
        _frameWorldTime = TIMEMANAGER->getWorldTime();
        _frameX++;
        if (_frameX > _d2dObjectImage->maxFrameX)
        {
            _frameY++;
            _frameX = 0;
            if (_frameY > _d2dObjectImage->maxFrameY)
            {
                _frameY = 0;
            }
        }
    }
}

void Potal::d2drender(void)
{
    D2DMANAGER->frameRender("스테이지포탈", _rcObject.left, _rcObject.top, _frameX, _frameY);
}
