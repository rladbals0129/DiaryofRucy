#include "Stdafx.h"
#include "ItemChest.h"

HRESULT ItemChest::init(int grade)
{
	IMAGEMANAGER->addFrameImage("일반상자", "Resources/Images/Object/chest1.bmp", 168, 43, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("중급상자", "Resources/Images/Object/chest2.bmp", 224, 49, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("고급상자", "Resources/Images/Object/chest3.bmp", 256, 60, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("최고급상자", "Resources/Images/Object/chest4.bmp", 296, 69, 4, 1, true, MAGENTA);


	//int rndGrade = RND->getInt(100);

	//if(rndGrade <=  )

	_grade = grade;

	switch (_grade)
	{
	case 1:
		_objImg = IMAGEMANAGER->findImage("일반상자");
		// 아이템 넣어주기
		break;
		
	case 2:
		_objImg = IMAGEMANAGER->findImage("중급상자");
		break;

	case 3:
		_objImg = IMAGEMANAGER->findImage("고급상자");
		break;

	case 4:
		_objImg = IMAGEMANAGER->findImage("최고급상자");
		break;

	default:
		break;
	}

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _objImg->getFrameWidth(), _objImg->getFrameHeight());

	_action = false;

	_currentFrameX = 0;
	_currentFrameY = 0;
	_objImg->setFrameY(_currentFrameY);
	_objImg->setFrameX(_currentFrameX);
	_worldTimeCount = GetTickCount64();

	return S_OK;
}

void ItemChest::release(void)
{

}

void ItemChest::update(void)
{
	if (_action)
	{
		if (_worldTimeCount + 20 < GetTickCount64())
		{
			_worldTimeCount = GetTickCount64();
			_currentFrameX++;
		
			if (_currentFrameX == _objImg->getMaxFrameX())
			{
				_currentFrameX = _objImg->getMaxFrameX();
			}

			_objImg->setFrameX(_currentFrameX);
		}
	}
}

void ItemChest::render(void)
{
	_objImg->frameRender(getMemDC(), _rc.left, _rc.top, _objImg->getFrameX(), _objImg->getFrameY());
}

void ItemChest::openChest()
{
	_worldTimeCount = GetTickCount64();
	_action = true;
}
