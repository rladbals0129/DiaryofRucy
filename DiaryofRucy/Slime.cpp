#include "Stdafx.h"
#include "Slime.h"

HRESULT Slime::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);
	_speed = 1.f;

	_hp = 100;
	_attackCount = 2;
    return S_OK;
}

void Slime::release(void)
{
}

void Slime::update(void)
{
	Enemy::update();
	//_hp--;
	if (_hp <= 0)
	{
		playDieEffect();
	}
	else
	{
		stateUpdate();
	}
}

void Slime::render(void)
{
	if (!_die)
	{
		draw();
		if (_hp > 0)
		{
			animation();
		}
		else
		{
			_state = DIE;
			//SD: 슬라임 죽는사운드 
			if (!_dieSound)
			{

				SOUNDMANAGER->play("슬라임사망", 0.1f);
				_dieSound = true;
			}
		}
	}

}

void Slime::draw(void)
{
	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("슬라임IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("슬라임ATTACK");
		break;
	case ATTACK2:
		_image = IMAGEMANAGER->findImage("슬라임ATTACK2");
		break;
	case MOVE:
		_image = IMAGEMANAGER->findImage("슬라임MOVE");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("슬라임DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, 0,0);
		break;
	default:
		break;
	}

	if (_state != DIE)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
	}

}

void Slime::d2drender(void)
{	
	Enemy::d2drender();
}

void Slime::stateUpdate()
{
	switch (_state)
	{
	case IDLE:

		break;
	case ATTACK:
	
		break;

	case ATTACK2:

		break;
	case MOVE:

		if (_safeDistance)
		{
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
		}

		break;
	case DIE:

		break;
	}
}

void Slime::animation()
{
	if (!_canAttack)
	{
		int tempSpeed;
		switch (_state)
		{
		case IDLE:
			if (_idleFrameCount < _rndIdleFrame)
			{

				tempSpeed = 500;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_currentFrameX = 0;
						_idleFrameCount++;
					}
					_image->setFrameX(_currentFrameX);
				}
			}
			else
			{
				setState(MOVE);
				resetIdleCount();
				resetRndIdleFrame();
			}

			break;
		case MOVE:
			if (_moveFrameCount < _rndMoveFrame)
			{
				tempSpeed = 500;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_moveFrameCount++;
						_currentFrameX = 0;
					}
					_image->setFrameX(_currentFrameX);
				}

			}
			else
			{

				_rndAngleInit = false;
				setState(IDLE);
				resetMoveCount();
				resetRndMoveFrame();
			}

			break;
		case DIE:
			_currentFrameX = 0;
			break;
		}
	}




	else
	{
		int tempSpeed;
		switch (_state)
		{
		case IDLE:
			if (_idleFrameCount < 2)
			{

				tempSpeed = 500;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_currentFrameX = 0;
						_idleFrameCount++;
					}
					_image->setFrameX(_currentFrameX);
				}
			}
			else
			{
				setState(MOVE);
				resetIdleCount();
				resetRndIdleFrame();
			}

			break;
		case ATTACK:
			if (_attackCount == 2)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_currentFrameX == 0)
					{				
						//SD: 슬라임 공격사운드 1 (뾱)
						SOUNDMANAGER->play("슬라임공격준비", 0.1f);
					}
					else if (_currentFrameX == 2)
					{
						//SD: 슬라임 공격사운드 1 (뾱)
						SOUNDMANAGER->play("슬라임공격준비", 0.1f);

					}
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						//SD: 슬라임 공격사운드 1 (뾱)
						SOUNDMANAGER->play("슬라임공격준비", 0.1f);

						_attackCount--;
						float angleStep = PI / 10;
						for (int i = 0; i < 20; ++i)
						{
							float fireangle = i * angleStep;

							_smallBullet->fire(_x, _y, fireangle, 3.f);


						}
							_currentFrameX = 0;
						_image->setFrameX(_currentFrameX);
					}
				}
			}
				else
				{
			
					setState(IDLE);
				}
				break;
		case ATTACK2:
			if (_attackCount == 1)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						
						_attackCount--;
						float fireStartAngle = _fireAngle - (15 * PI / 180);
						float fireEndAngle = _fireAngle + (15 * PI / 180);
						_bigBullet->fire(_x, _y, fireStartAngle, 3);
						_bigBullet->fire(_x, _y, fireEndAngle, 3);
						_bigBullet->fire(_x, _y, _fireAngle, 3);
						//SD: 슬라임 공격사운드 1 (뾱)
						SOUNDMANAGER->play("슬라임공격준비", 0.1f);

					
						_currentFrameX = 0;
						_image->setFrameX(_currentFrameX);
					}
					
				}
			}
			else
			{
				setState(IDLE);
			}
			break;
		case MOVE:
			if (_moveFrameCount < 1)
			{
				tempSpeed = 500;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_moveFrameCount++;
						_currentFrameX = 0;
					}
					_image->setFrameX(_currentFrameX);
				}

			}
			else
			{
				
				

				_fireAngleInit = false;
				if (_attackCount == 2)
				{
					setState(ATTACK);
				}
				else if (_attackCount == 1)
				{
					setState(ATTACK2);
				}
				else
				{
					setState(ATTACK);
					_attackCount = 2;
				}

				resetMoveCount();
				resetRndMoveFrame();
			}

			break;
		case DIE:
			_currentFrameX = 0;
			break;

			
		}
	}
}


bool Slime::bulletCountFire()
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_attackCount--;
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 0.6f;
		return true;
	}
	return false;
}
