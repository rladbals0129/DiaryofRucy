#include "Stdafx.h"
#include "Flime.h"

HRESULT Flime::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);
	_speed = 1.f;

	_hp = 100;
	_attackCount = 2;
	_thornCount = 3;
	return S_OK;
}

void Flime::release(void)
{
}

void Flime::update(void)
{
	Enemy::update();

	if (_hp <= 0)
	{
		playDieEffect();
	}
	else
	{
		stateUpdate();
	}
}

void Flime::render(void)
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
			//SD: 플라임 죽는사운드 
			if (_hp <= 0)
			{
				if (!_dieSound)
				{

					SOUNDMANAGER->play("스네이크&플라임사망", 0.1f);
					_dieSound = true;
				}
			}
		}
	}

}

void Flime::draw(void)
{
	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("꽃IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("꽃ATTACK");
		break;
	case ATTACK2:
		_image = IMAGEMANAGER->findImage("꽃ATTACK2");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("꽃DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
		break;
	default:
		break;
	}

	if (_state != DIE)
	{
		if (!_canAttack)
		{
			_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, DOWN);
		}
		else
		{
			_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
		}
	}
	
}

void Flime::d2drender(void)
{
	Enemy::d2drender();
}

void Flime::stateUpdate()
{
	switch (_state)
	{
	case IDLE:

		break;
	case ATTACK:

		break;
	case ATTACK2:

		break;
	case DIE:

		break;
	}
}

void Flime::animation()
{
	int tempSpeed;
	if (!_canAttack)
	{
		setState(IDLE);
		switch (_state)
		{
		case IDLE:
			tempSpeed = 500;
			if (tempSpeed + _frameCount <= GetTickCount64())
			{
				_frameCount = GetTickCount64();
				_currentFrameX++;

				if (_image->getMaxFrameX() < _currentFrameX)
				{
					_currentFrameX = 0;

				}
				_image->setFrameX(_currentFrameX);
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
			if (_idleFrameCount < 3)
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
				//setState(MOVE);
				resetIdleCount();
				resetRndIdleFrame();

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
					if (_image->getMaxFrameX() < _currentFrameX)
					{
				
						_attackCount--;
						float angleStep = PI / 5;
						SOUNDMANAGER->play("플라임독발사", 0.1f);
						for (int i = 0; i < 10; ++i)
						{
							float fireangle = i * angleStep;
				
							_poisonBullet->fire(_x, _y, fireangle, 1.f);
						

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
				//cout << _thornCount << endl;
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_fireAngleInit = false;
						_thornTime++;
						if (_thornTime % 5 == 0)
						{
							_thornTime = 0;
							_thornCount--;
							_thorn->fire(_thornPos.x, _thornPos.y,300);
							if (_thornCount <= 0)
							{
								//SD: 가시 발사 사운드 (땅에 뿌리 딪는소리)
								SOUNDMANAGER->play("플라임가시생성", 0.1f);
								_currentFrameX = 0;
								_attackCount--;
							
							}
						}
						
					}
					else
					{
						_currentFrameX++;
					}
					_image->setFrameX(_currentFrameX);
					
				}
			}
			else
			{
				setState(IDLE);
				_thornCount = 3;
			}
			break;
		case DIE:
			_currentFrameX = 0;
			break;
		}
	}
}

bool Flime::bulletCountFire()
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_attackCount--;
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 0.6f;
		if (_attackCount < 0)
		{
			//	attackInit = false;
		}
		return true;
	}
	return false;
}
