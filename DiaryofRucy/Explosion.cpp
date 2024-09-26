#include "Stdafx.h"
#include "Explosion.h"


HRESULT Explosion::init(void)
{
	_iconImage = D2DMANAGER->findImage("익스플로전아이콘");
	_frameImage1 = D2DMANAGER->findImage("익스플로전1");
	_frameImage2 = D2DMANAGER->findImage("익스플로전2");
	_skill1End = false;
	_coolTime = 30;
	_manaCost = 6;
	_damageMultiple = 17;
	return S_OK;
}

void Explosion::shot(float x, float y, float fireX, float fireY)
{
	if (_isCoolTimeOn) return;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_isSkillShoot = true;
	_fireX = fireX;
	_fireY = fireY;
	_x = x;
	_y = y;
	_rc = { (int)x - 300, (int)y - 300, (int)x + 300, (int)y + 100 };
	_frameCount = 0;
	_isCoolTimeOn = true;
	
}

void Explosion::animation(void)
{
	if (_isSkillShoot)
	{
		_frameCount++;
		if ((_frameX == 1) && (_frameY == 0))
		{
			// SD : 익스플로전 사운드 추가 
			SOUNDMANAGER->play("익스플로전", 0.1f);
		}
		if ((_frameX == 4) && (_frameY == 0) && (_frameCount % 2 == 0))
		{
			_isSkillCollision = true;
			
		}
		else
		{
			_isSkillCollision = false;
		}
		if (_frameCount % 2 == 0)
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

void Explosion::draw(void)
{
	if (_isSkillShoot)
	{
		D2DMANAGER->frameRender("익스플로전1", _rc.left-100, _rc.top- 300, _frameX, _frameY, 800, 800);
		D2DMANAGER->frameRender("익스플로전2", _rc.left-100, _rc.top- 300, _frameX, _frameY, 800, 800);
	}
}
