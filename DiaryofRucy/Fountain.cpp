#include "Stdafx.h"
#include "Fountain.h"

HRESULT Fountain::init(int fountainType)
{
	IMAGEMANAGER->addFrameImage("레드분수", "Resources/Images/Object/fountain_red.bmp", 192, 720, 2, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("블루분수", "Resources/Images/Object/fountain_blue.bmp", 192, 720, 2, 5, true, MAGENTA);

	_fountainType = fountainType;

	switch (_fountainType)
	{
	case 1:
		_objImg = IMAGEMANAGER->findImage("블루분수");
		break;

	case 2:
		_objImg = IMAGEMANAGER->findImage("레드분수");
		break;

	default:
		break;
	}

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _objImg->getFrameWidth(), _objImg->getFrameHeight());

	_off = false;

	_currentFrameX = 0;
	_currentFrameY = 0;

	_objImg->setFrameX(_currentFrameX);
	_objImg->setFrameY(_currentFrameY);

	_worldTimeCount = GetTickCount64();

	return S_OK;
}

void Fountain::release(void)
{
}

void Fountain::update(void)
{
	if (!_off)
	{
		if (_worldTimeCount + 30 < GetTickCount64())
		{
			_worldTimeCount = GetTickCount64();
			_currentFrameX++;

			if (_currentFrameX > 1)
			{
				_currentFrameY++;

				if (_currentFrameY > 3 && _currentFrameX > 1)
				{
					_currentFrameX = 0;

					_currentFrameY = 0;
				}
			}
		}
	}
	else
	{

	}

	_objImg->setFrameX(_currentFrameX);
	_objImg->setFrameY(_currentFrameY);
}

void Fountain::render(void)
{
	_objImg->frameRender(getMemDC(), _rc.left, _rc.top, _objImg->getFrameX(), _objImg->getFrameY());
}

void Fountain::fountainOff()
{
	_off = true;
	_objImg->setFrameX(0);
	_objImg->setFrameY(4);
}	
