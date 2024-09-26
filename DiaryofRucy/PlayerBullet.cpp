#include "Stdafx.h"
#include "PlayerBullet.h"

#pragma region 활 불릿
HRESULT Arrow::init(float range)
{
	_range = range;

	return S_OK;
}

void Arrow::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->d2dImage);
	}
	_vBullet.clear();
}

void Arrow::update(void)
{
	move();
}

void Arrow::render(void)
{
}

void Arrow::d2drender(void)
{
	draw();
}

void Arrow::fire(float x, float y, float angle, float speed, int boundary)
{
	_Boundary = boundary;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.d2dImage = D2DMANAGER->findImage("애로우");
	bullet.speed = 20 * speed;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage("애로우")->width+ _Boundary*2, D2DMANAGER->findImage("애로우")->height+ _Boundary*2);
	bullet.rcCollision = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage("애로우")->width + _Boundary * 2, D2DMANAGER->findImage("애로우")->height-30 + _Boundary);
	bullet.angle = angle;

	_vBullet.push_back(bullet);
}

void Arrow::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		// 리사이즈 되면 크기 보정해주기
		D2DMANAGER->rotateRender("애로우", _viBullet->rc.left, _viBullet->rc.top, -_viBullet->angle * 180 / PI,
			D2DMANAGER->findImage("애로우")->width + _Boundary * 2,
			D2DMANAGER->findImage("애로우")->height + _Boundary * 2);
		_viBullet->count++;
	}
}

void Arrow::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, D2DMANAGER->findImage("애로우")->width + _Boundary * 2, D2DMANAGER->findImage("애로우")->height + _Boundary * 2);
		_viBullet->rcCollision = RectMakeCenter(_viBullet->x, _viBullet->y,
			D2DMANAGER->findImage("애로우")->width + _Boundary * 2, D2DMANAGER->findImage("애로우")->height - 40 + _Boundary);
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void Arrow::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
#pragma endregion

#pragma region 지팡이 불릿

HRESULT MagicBall::init(float range)
{
	_range = range;

	return S_OK;
}

void MagicBall::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->d2dImage);
	}
	_vBullet.clear();
}

void MagicBall::update(void)
{
	move();
}

void MagicBall::render(void)
{
	//draw();
}
void MagicBall::d2drender(void)
{
	draw();
}
void MagicBall::fire(float x, float y, float angle, float speed, int boundary)
{
	_Boundary = boundary;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.d2dImage = D2DMANAGER->findImage("스태프불릿");
	bullet.speed = 15 * speed;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage("스태프불릿")->width + _Boundary*2, D2DMANAGER->findImage("스태프불릿")->height + _Boundary*2);
	bullet.angle = angle;

	_vBullet.push_back(bullet);
}

void MagicBall::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		D2DMANAGER->render("스태프불릿", _viBullet->rc.left, _viBullet->rc.top, D2DMANAGER->findImage("스태프불릿")->width + _Boundary * 2, D2DMANAGER->findImage("스태프불릿")->height + _Boundary * 2);
		_viBullet->count++;
	}
}

void MagicBall::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, D2DMANAGER->findImage("스태프불릿")->width+ _Boundary*2, D2DMANAGER->findImage("스태프불릿")->height+ _Boundary*2);

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}



void MagicBall::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
#pragma endregion


#pragma region 지팡이 차지샷

HRESULT ChargingMagicBall::init(float range)
{
	_range = range;
	_hitSwitch = false;

	return S_OK;
}

void ChargingMagicBall::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->d2dImage);
	}
	_vBullet.clear();
}

void ChargingMagicBall::update(void)
{
	move();
}

void ChargingMagicBall::render(void)
{
}
void ChargingMagicBall::d2drender(void)
{
	draw();

}
void ChargingMagicBall::fire(float x, float y, float angle, float speed, int boundary)
{
	_Boundary = boundary;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.d2dImage = D2DMANAGER->findImage("스태프불릿");
	bullet.speed = 4 * speed;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage("스태프불릿")->width*3+ _Boundary*3, D2DMANAGER->findImage("스태프불릿")->height*3+ _Boundary*3);
	bullet.angle = angle;

	_vBullet.push_back(bullet);
}

void ChargingMagicBall::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		D2DMANAGER->render("스태프불릿", _viBullet->rc.left, _viBullet->rc.top, D2DMANAGER->findImage("스태프불릿")->width * 3+ _Boundary*3, D2DMANAGER->findImage("스태프불릿")->height * 3+ _Boundary*3);
		_viBullet->count++;
	}
}

void ChargingMagicBall::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, D2DMANAGER->findImage("스태프불릿")->width * 3+ _Boundary*3, D2DMANAGER->findImage("스태프불릿")->height * 3+ _Boundary*3);

		if (GetTickCount64() % 10 == 0)
		{
			_hitSwitch = true;
		}
		else
		{
			_hitSwitch = false;
		}

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}



void ChargingMagicBall::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
#pragma endregion

#pragma region 검 공격판정
HRESULT Sword1::init(void)
{
	_frameImage = D2DMANAGER->findImage("검1");
	_Boundary = 1;
	_isAttack = false;
	return S_OK;
}

void Sword1::update(void)
{
	if (_isAttack)
	{
		_frameCount++;
		if (_frameCount == 1)
		{
			_rcCollision = { _rc.left + 20 , _rc.top + 50, _rc.right - 20, _rc.bottom - 50 };
		}
		else
		{
			_rcCollision = { 0,0,0,0 };
		}
		if (_frameCount % 3 == 0)
		{
			_frameX++;
			if (_frameX > _frameImage->maxFrameX)
			{
				_frameX = 0;
				_frameY++;
				if (_frameY > _frameImage->maxFrameY)
				{
					_frameX = 0;
					_frameY = 0;
					_frameCount = 0;
					//_rcCollision = { 0,0,0,0 };
					_isAttack = false;
				}
			}
		}
		if (_frameX == 4 && _frameY == 1)
		{
			_frameX = 0;
			_frameY = 0;
			_frameCount = 0;
			_rcCollision = { 0,0,0,0 };
			_isAttack = false;
		}
	}
}

void Sword1::d2drender(void)
{
	draw();
}

void Sword1::fire(float fireX, float fireY, float angle, float boundary)
{
	if (!_isAttack)
	{
		_Boundary = boundary;
		_angle = angle;
		_fireX = fireX;
		_fireY = fireY;
		_fireX += -cosf(_angle) * 70;
		_fireY += sinf(_angle) * 70;
		_rc = RectMakeCenter(_fireX, _fireY, D2DMANAGER->findImage("검1")->frameWidth + _Boundary * 2, D2DMANAGER->findImage("검1")->frameHeight + _Boundary * 2);
		_rcCollision = { 0,0,0,0 };
		_frameCount = 0;
		_frameX = 0;
		_frameY = 0;
		_isAttack = true;
	}
}

void Sword1::draw(void)
{
	if (_isAttack) D2DMANAGER->frameRotateRender("검1", _rc.left, _rc.top, _frameX, _frameY,_frameImage->frameWidth+_Boundary*2, _frameImage->frameHeight+_Boundary*2, -_angle * 180 / PI - 45);
}


HRESULT Sword2::init(void)
{
	_frameImage = D2DMANAGER->findImage("검2");
	_Boundary = 1;
	_isAttack = false;

	return S_OK;
}

void Sword2::update(void)
{
	if (_isAttack)
	{
		if (_frameCount == 1)
		{
			_rcCollision = { _rc.left + 20 , _rc.top + 50, _rc.right - 20, _rc.bottom - 50 };
		}
		else
		{
			_rcCollision = { 0,0,0,0 };
		}
		_frameCount++;
		if (_frameCount % 3 == 0)
		{
			_frameX++;
			if (_frameX > _frameImage->maxFrameX)
			{
				_frameX = 0;
				_frameY++;
				if (_frameY > _frameImage->maxFrameY)
				{
					_frameX = 0;
					_frameY = 0;
					_frameCount = 0;
					_rcCollision = { 0,0,0,0 };
					_isAttack = false;
				}
			}
		}
		if (_frameX == 4 && _frameY == 1)
		{
			_frameX = 0;
			_frameY = 0;
			_frameCount = 0;
			_rcCollision = { 0,0,0,0 };
			_isAttack = false;
		}
	}

}

void Sword2::d2drender(void)
{
	draw();
}

void Sword2::fire(float fireX, float fireY, float angle, float boundary)
{
	if (!_isAttack)
	{
		_Boundary = boundary;
		_angle = angle;
		_fireX = fireX;
		_fireY = fireY;
		_fireX += -cosf(_angle) * 70;
		_fireY += sinf(_angle) * 70;
		_rc = RectMakeCenter(_fireX, _fireY, D2DMANAGER->findImage("검2")->frameWidth + _Boundary * 2, D2DMANAGER->findImage("검2")->frameHeight + _Boundary * 2);
		_rcCollision = { 0,0,0,0 };
		_frameCount = 0;
		_frameX = 0;
		_frameY = 0;
		_isAttack = true;
	}

}

void Sword2::draw(void)
{
	if (_isAttack) D2DMANAGER->frameRotateRender("검2", _rc.left, _rc.top, _frameX, _frameY, _frameImage->frameWidth + _Boundary * 2, _frameImage->frameHeight + _Boundary * 2, -_angle * 180 / PI - 45);
}


HRESULT Sword3::init(void)
{
	_frameImage = D2DMANAGER->findImage("검3");
	_Boundary = 1;
	_isAttack = false;

	return S_OK;
}

void Sword3::update(void)
{
	if (_isAttack)
	{
		_frameCount++;
		if (_frameCount == 1)
		{
			_rcCollision = { _rc.left + 20 , _rc.top + 50, _rc.right - 20, _rc.bottom - 50 };
		}
		else
		{
			_rcCollision = { 0,0,0,0 };
		}
		if (_frameCount % 3 == 0)
		{
			_frameX++;
			if (_frameX > _frameImage->maxFrameX)
			{
				_frameX = 0;
				_frameY++;
				if (_frameY > _frameImage->maxFrameY)
				{
					_frameX = 0;
					_frameY = 0;
					_frameCount = 0;
					_rcCollision = { 0,0,0,0 };
					_isAttack = false;
				}
			}
		}
		if (_frameX == 4 && _frameY == 1)
		{
			_frameX = 0;
			_frameY = 0;
			_frameCount = 0;
			_rcCollision = { 0,0,0,0 };
			_isAttack = false;
		}
	}

}

void Sword3::d2drender(void)
{
	draw();
}

void Sword3::fire(float fireX, float fireY, float angle, float boundary)
{
	if (!_isAttack)
	{
		_Boundary = boundary;
		_angle = angle;
		_fireX = fireX;
		_fireY = fireY;
		_fireX += -cosf(_angle) * 70;
		_fireY += sinf(_angle) * 70;
		_rc = RectMakeCenter(_fireX, _fireY, D2DMANAGER->findImage("검3")->frameWidth + _Boundary * 2, D2DMANAGER->findImage("검3")->frameHeight + _Boundary * 2);
		_rcCollision = { 0,0,0,0 };
		_frameCount = 0;
		_frameX = 0;
		_frameY = 0;
		_isAttack = true;
	}
}

void Sword3::draw(void)
{
	if (_isAttack) D2DMANAGER->frameRotateRender("검3", _rc.left, _rc.top, _frameX, _frameY, _frameImage->frameWidth + _Boundary * 2, _frameImage->frameHeight + _Boundary * 2, -_angle * 180 / PI - 90);
}

#pragma endregion


HRESULT SlashSword::init(void)
{
	_frameImage = D2DMANAGER->findImage("검3");
	_Boundary = 1;
	_frameX = 0;
	_frameY = 0;
	_frameCount = 0;
	_isAttack = false;
	return S_OK;
}

void SlashSword::update(void)
{
	if (_isAttack)
	{
		_frameCount++;
		if (_frameCount % 2 == 0)
		{
			_frameX++;
			if (_frameX > _frameImage->maxFrameX)
			{
				_frameX = 0;
				_frameY++;
				if (_frameY > _frameImage->maxFrameY)
				{
					_frameX = 0;
					_frameY = 0;
					_frameCount = 0;
					_rcCollision = { 0,0,0,0 };
					_isAttack = false;
				}
			}
		}
		if (_frameX == 4 && _frameY == 1)
		{
			_frameX = 0;
			_frameY = 0;
			_frameCount = 0;
			_rcCollision = { 0,0,0,0 };
			_isAttack = false;
		}
	}

}

void SlashSword::d2drender(void)
{
	draw();
}

void SlashSword::fire(float fireX, float fireY, float angle, float boundary)
{
	_Boundary = boundary;
	_angle = angle;
	_fireX = fireX;
	_fireY = fireY;
	_fireX += -cosf(_angle) * 70;
	_fireY += sinf(_angle) * 70;
	_rc = RectMakeCenter(_fireX, _fireY, D2DMANAGER->findImage("검3")->frameWidth + _Boundary * 2, D2DMANAGER->findImage("검3")->frameHeight + _Boundary * 2);
	_isAttack = true;

}

void SlashSword::draw(void)
{
	if(_isAttack) D2DMANAGER->frameRotateRender("검3", _rc.left, _rc.top, _frameX, _frameY, _frameImage->frameWidth + _Boundary * 2, _frameImage->frameHeight + _Boundary * 2, -_angle * 180 / PI - 90);
}

void SlashSword::setCollisionRect(POINT startLocation, POINT endLocation)
{
	_rcCollision = RectMakeCenter(
		startLocation.x + 130.0f * cosf(getAngle(startLocation.x, startLocation.y, endLocation.x, endLocation.y)),
		startLocation.y + 130.0f * -sinf(getAngle(startLocation.x, startLocation.y, endLocation.x, endLocation.y)),
		260, 80);
}
