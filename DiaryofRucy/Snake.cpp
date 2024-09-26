#include "Stdafx.h"
#include "Snake.h"

HRESULT Snake::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);
	_speed = 1.f;
	
	_hp = 100;
	_attackCount = 3;
	//attackInit = false;

	return S_OK;
}

void Snake::release(void)
{
}

void Snake::update(void)
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
	//_state = MOVE;
}

void Snake::render(void)
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
			if (!_dieSound)
			{
				SOUNDMANAGER->play("스네이크&플라임사망", 0.1f);
				_dieSound = true;
			}
		}
	
	}

}

void Snake::draw(void)
{

	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("뱀IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("뱀ATTACK");
		break;
	case MOVE:
		_image = IMAGEMANAGER->findImage("뱀MOVE");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("뱀DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	default:
		break;
	}

	if (_state != DIE)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
	}
}

void Snake::d2drender(void)
{
	Enemy::d2drender();

}

void Snake::stateUpdate()
{

	switch (_state)
	{
	case IDLE:
		break;
	case ATTACK:
		if (_safeDistance)
		{
			_x += cosf(_fireAngle) * _speed;
			_y += -sinf(_fireAngle) * _speed;
		}
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

void Snake::animation()
{
	bool die;
	die = false;
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
			if (_attackCount > 0)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{
						//_shoot = true;
						_attackCount--;
				
						switch (_attackCount)
						{
						case 0:
						{
							//SD: 스네이크 공격사운드  (훅)
							SOUNDMANAGER->play("스네이크공격", 0.1f);
							float fireStartAngle = _fireAngle - (15 * PI / 180);
							float fireEndAngle = _fireAngle + (15 * PI / 180);
							_smallBullet->fire(_x, _y, fireStartAngle, 3);
							_smallBullet->fire(_x, _y, fireEndAngle, 3);
							_smallBullet->fire(_x, _y, _fireAngle, 3);
							
							break;
						}
						case 1:
						{
							float fireStartAngle = _fireAngle - (10 * PI / 180);
							float fireEndAngle = _fireAngle + (10 * PI / 180);
							_smallBullet->fire(_x, _y, fireStartAngle, 3);
							_smallBullet->fire(_x, _y, fireEndAngle, 3);
						
							
							break;
						}
						case 2:
						{
							//SD: 스네이크 공격사운드  (훅)
							SOUNDMANAGER->play("스네이크공격", 0.1f);
							float fireStartAngle = _fireAngle - (15 * PI / 180);
							float fireEndAngle = _fireAngle + (15 * PI / 180);
							_smallBullet->fire(_x, _y, fireStartAngle, 3);
							_smallBullet->fire(_x, _y, fireEndAngle, 3);
							_smallBullet->fire(_x, _y, _fireAngle, 3);
							break;
						}
						default:
							break;
						}
					
						_currentFrameX = 0;
					}
					_image->setFrameX(_currentFrameX);
				}
				//_shoot = false;
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
				_attackCount = 3;
				_rndAngleInit = false;
				
				_fireAngleInit = false;
				setState(ATTACK);
				resetMoveCount();
				resetRndMoveFrame();
			}

			break;
		case DIE:
			die = true;
			_currentFrameX = 0;

			break;
		}
	}
}

bool Snake::bulletCountFire()
{
	int tempSpeed;
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		//_attackCount--;
		_bulletFireCount = TIMEMANAGER->getWorldTime();

		
		if (_attackCount < 0)
		{
		
			_fireCount = 0.8f;
			//_fireAngleInit = false;
			return false;
		}
		return true;
	}
	return false;

	//if (_state == ATTACK)
	//{
	//	tempSpeed = 300;
	//	if (tempSpeed + _frameCount <= GetTickCount64())
	//	{
	//		_frameCount = GetTickCount64();

	//		if (_image->getMaxFrameX() < _currentFrameX)
	//		{
	//			return true;
	//		}
	//	
	//	}
	//
	//}


	//return false;

}
