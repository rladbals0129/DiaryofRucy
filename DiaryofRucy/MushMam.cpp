#include "Stdafx.h"
#include "MushMam.h"


HRESULT MushMam::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);

	_speed = 1.f;

	_hp = 100;
	_attackCount = 1;

	

	return S_OK;
}

void MushMam::release(void)
{
}

void MushMam::update(void)
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

void MushMam::render(void)
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
			//SD: 버섯 죽는사운드 
			if (!_dieSound)
			{
				SOUNDMANAGER->play("머쉬맨사망", 0.1f);
				_dieSound = true;
			}
		}
	}
}

void MushMam::draw(void)
{
	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("머쉬맘IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("머쉬맘ATTACK");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	case MOVE:
		_image = IMAGEMANAGER->findImage("머쉬맘MOVE");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("머쉬맘DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	default:
		break;
	}

	if (_state != DIE && _state != ATTACK && _state != ATTACK2 && _state != ATTACK3)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
	}
	
}
void MushMam::d2drender(void)
{
	Enemy::d2drender();
}

void MushMam::stateUpdate()
{
	switch (_state)
	{
	case IDLE:

		break;
	case ATTACK:

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

void MushMam::animation()
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
						//SD: 버섯 공격 사운드 (우으아!)
						SOUNDMANAGER->play("머쉬맨공격", 0.1f);
						_attackCount--;
						_createTurret = true;
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
				_attackCount = 1;
				_rndAngleInit = false;
				_fireAngleInit = false;
				setState(ATTACK);
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

bool MushMam::bulletCountFire()
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

//void MushMam::setGreenTurret(int x, int y)
//{
//	Turret* greenMini = new MiniGreenTurret;
//	greenMini->init("초록포탑", PointMake(x, y));
//	_vTurret.push_back(greenMini);
//}

//void MushMam::removeTurret(int arrNum)
//{
//}
