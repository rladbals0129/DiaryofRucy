#include "Stdafx.h"
#include "IcicleSpark.h"

// 수정필요

HRESULT IcicleSpark::init(void)
{
	_iconImage = D2DMANAGER->findImage("아이시클스파크아이콘");
	_frameImage1 = D2DMANAGER->findImage("아이시클스파크1");
	_frameImage2 = D2DMANAGER->findImage("아이시클스파크2");
	_skill1End = false;
	_coolTime = 20;
	_manaCost = 5;
	_damageMultiple = 10;
	return S_OK;
}

void IcicleSpark::shot(float x, float y, float fireX, float fireY)
{
	if (_isCoolTimeOn) return;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_isSkillShoot = true;
	_fireX = fireX;
	_fireY = fireY;
	_x = fireX;
	_y = fireY;
	_rc = RectMakeCenter(fireX, fireY, _frameImage2->frameWidth+300, _frameImage2->frameHeight+300);
	_frameCount = 0;
	_isSkillShoot = true;
	_isCoolTimeOn = true;

}

void IcicleSpark::animation(void)
{
	if (_isSkillShoot)
	{
		_frameCount++;
		if ((_frameX == 4) && (_frameY == 0) && (_frameCount % 2 == 0))
		{
			_isSkillCollision = true;
		}
		else
		{
			_isSkillCollision = false;
		}

		if (_frameCount == 1)
		{
			// SD : 아이시클스파크 사운드 추가 
			SOUNDMANAGER->play("아이시슬스파크", 0.1f);
		}
		
	
		if (_frameCount % 3 == 0)
		{
			_frameX++;

			if (_frameImage2->maxFrameX < _frameX)
			{
				_frameX = 0;
				_frameY++;

				if (_frameImage2->maxFrameY < _frameY)
				{
					_frameX = 0;
					_frameY = 0;
					_skill1End = false;
					_isSkillShoot = false;
				}
				if (_frameImage1->maxFrameY < _frameY)
				{
					_skill1End = true;
				}
			}
		}
	}
}

void IcicleSpark::draw(void)
{
	if (_isSkillShoot)
	{
		D2DMANAGER->frameRender("아이시클스파크1", _rc.left+20-100, _rc.top-50-100, _frameX, _frameY, _frameImage2->frameWidth + 500, _frameImage2->frameHeight + 500);
		D2DMANAGER->frameRender("아이시클스파크2", _rc.left-100, _rc.top-100, _frameX, _frameY, _frameImage2->frameWidth + 500, _frameImage2->frameHeight + 500);
		DrawRectMake(getMemDC(), _rc);
	}
}

