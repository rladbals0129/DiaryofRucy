#include "Stdafx.h"
#include "Statue.h"

HRESULT Statue::init(int statueTypeR, int statueTypeL)
{
	IMAGEMANAGER->addFrameImage("블루천사", "Resources/Images/Object/statue-blue1.bmp", 288, 192, 3, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("블루악마", "Resources/Images/Object/statue-blue2.bmp", 288, 192, 3, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("레드천사", "Resources/Images/Object/statue-red1.bmp", 288, 192, 3, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("레드악마", "Resources/Images/Object/statue-red2.bmp", 288, 192, 3, 2, true, MAGENTA);

	_statueTypeR = statueTypeR;
	_statueTypeL = statueTypeL;

	switch (_statueTypeL)
	{
	case 1:
		_statue[0]._objImg = IMAGEMANAGER->findImage("블루천사");
		break;

	case 2:
		_statue[0]._objImg = IMAGEMANAGER->findImage("블루악마");
		break;

	case 3:
		_statue[0]._objImg = IMAGEMANAGER->findImage("레드천사");
		break;

	case 4:
		_statue[0]._objImg = IMAGEMANAGER->findImage("레드악마");
		break;

	default:
		break;
	}
	_statue[0]._x = WINSIZE_X / 2 - 50;
	_statue[0]._y = WINSIZE_Y / 2;
	_statue[0]._rc = RectMakeCenter(_statue[0]._x, _statue[0]._y, _statue[0]._objImg->getFrameWidth(), _statue[0]._objImg->getFrameHeight());
	_statue[0]._currentFrameX = 0;
	_statue[0]._currentFrameY = 0;
	_statue[0]._worldTimeCount = GetTickCount64();
	_statue[0]._off = false;

	switch (_statueTypeR)
	{
	case 1:
		_statue[1]._objImg = IMAGEMANAGER->findImage("블루천사");
		break;

	case 2:
		_statue[1]._objImg = IMAGEMANAGER->findImage("블루악마");
		break;

	case 3:
		_statue[1]._objImg = IMAGEMANAGER->findImage("레드천사");
		break;

	case 4:
		_statue[1]._objImg = IMAGEMANAGER->findImage("레드악마");
		break;


	default:
		break;
	}

	_statue[1]._x = WINSIZE_X / 2 + 50;
	_statue[1]._y = WINSIZE_Y / 2;
	_statue[1]._rc = RectMakeCenter(_statue[1]._x, _statue[1]._y, _statue[1]._objImg->getFrameWidth(), _statue[1]._objImg->getFrameHeight());
	_statue[1]._currentFrameX = 0;
	_statue[1]._currentFrameY = 0;
	_statue[1]._worldTimeCount = GetTickCount64();
	_statue[1]._off = false;

	

	return S_OK;

}

void Statue::release(void)
{
}

void Statue::update(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (!(_statue[i]._off))
		{
			if (_statue[i]._worldTimeCount + 30 < GetTickCount64())
			{
				_statue[i]._worldTimeCount = GetTickCount64();

				_statue[i]._currentFrameX++;

				if (_statue[i]._currentFrameX > 2)
				{
					_statue[i]._currentFrameX = 0;
				}
			}
		}
		else
		{
			_statue[i]._currentFrameY = 1;
		}

	_statue[i]._objImg->setFrameX(_statue[i]._currentFrameX);
	_statue[i]._objImg->setFrameY(_statue[i]._currentFrameY);
	}


}

void Statue::render(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			DrawRectMake(getMemDC(), _statue[i]._rc);
		}
		_statue[i]._objImg->frameRender(getMemDC(), _statue[i]._rc.left, _statue[i]._rc.top, _statue[i]._objImg->getFrameX(), _statue[i]._objImg->getFrameY());
	}
}

void Statue::statueOff()
{
	for (int i = 0; i < 2; i++)
	{
		_statue[i]._off = true;
		_statue[i]._objImg->setFrameX(2);
		_statue[i]._objImg->setFrameY(1);
	}
}
