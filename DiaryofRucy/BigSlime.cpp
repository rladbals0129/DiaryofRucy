#include "Stdafx.h"
#include "BigSlime.h"
#include "Player.h"


HRESULT BigSlime::init(POINT position)
{
	_image = IMAGEMANAGER->findImage("킹슬라임분열IDLE");
	_hpMax = 50;
	_hp = _hpMax;
	_die = false;
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_speed = 1.f;
	_bigBullet = new EnemyBullet;
	_bigBullet->init("큰일반탄", 500, 300,0);
	_dieNum = 0;
	_effectPlaying = false;
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	_safeDistance = true;
	_idleFrameCount = 0;
	_moveFrameCount = 0;
	_idleFrame = RND->getFromIntTo(2, 3);
	_canAttack = true;
	_attackCount = 1;
	return S_OK;
}

void BigSlime::release(void)
{
	_bigBullet->release();
	SAFE_DELETE(_image);

}

void BigSlime::update(void)
{
	if (_hp <= 0 && !_die)
	{
		playDieEffect();
	}
	else
	{
		//_hp--;
		stateUpdate();
	}

	if (!_die)
	{
		_rc = RectMakeCenter(_x, _y,
			_image->getFrameWidth(), _image->getFrameHeight());
		_center.x = _x;
		_center.y = _y;

		_bigBullet->update();
	}
}

void BigSlime::render(void)
{
	if (!_die)
	{

		draw();
	}
	if (_hp > 0)
	{
		animation();
	}
	else
	{
		_state = PAGE2DIE;
		//SD: 적 죽는사운드

	}
}
void BigSlime::d2drender(void)
{
	if (_effectPlaying)
	{
		if (_effectPlaying)
		{
			D2DMANAGER->frameRender("적사망이펙트", _x - D2DMANAGER->findImage("적사망이펙트")->frameWidth / 2, _y - D2DMANAGER->findImage("적사망이펙트")->frameHeight / 2,
				_effectCurrentFrameX, _effectCurrentFrameY);

			_effectCurrentFrameX++;
			if (D2DMANAGER->findImage("적사망이펙트")->maxFrameX < _effectCurrentFrameX)
			{
				_effectCurrentFrameX = 0;
				_effectCurrentFrameY++;
				if (D2DMANAGER->findImage("적사망이펙트")->maxFrameY < _effectCurrentFrameY)
				{
					_dieNum++;
					
					_die = true;
					_effectPlaying = false;
				}
			}
		}
	}

	if (!_die)
	{
		_bigBullet->d2drender();
	}
}
void BigSlime::draw(void)
{
	switch (_state)
	{
	case PAGE2IDLE:
		_image = IMAGEMANAGER->findImage("킹슬라임분열IDLE");
		break;
	case PAGE2ATTACK:
		_image = IMAGEMANAGER->findImage("킹슬라임분열ATTACK");
		break;
	case PAGE2MOVE:
		_image = IMAGEMANAGER->findImage("킹슬라임분열MOVE");
		break;
	case PAGE2DIE:
		_image = IMAGEMANAGER->findImage("킹슬라임분열DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	default:
		break;
	}

	if (_state != PAGE2DIE)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
	}
}

void BigSlime::animation()
{
	int tempSpeed;
	switch (_state)
	{
	case PAGE2IDLE:
		if (_idleFrameCount < _idleFrame)
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
			_state = PAGE2MOVE;
			resetIdleCount();
			resetIdleFrame();
		}

		break;
	case PAGE2ATTACK:

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
					float angleStep = PI / 10;
					for (int i = 0; i < 20; ++i)
					{
						float fireangle = i * angleStep;

						_bigBullet->fire(_x, _y, fireangle, 3.f);
						//SD: 슬라임 공격사운드
						SOUNDMANAGER->play("슬라임공격", 0.5f);

					}
					_currentFrameX = 0;
					_image->setFrameX(_currentFrameX);

				}
				
			}
		}
		else
		{
			_state = PAGE2IDLE;
		}
		break;
	case PAGE2MOVE:
		if (_moveFrameCount < _moveFrame)
		{
			tempSpeed = 400;
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
			_state = PAGE2ATTACK;
			_attackCount = 1;
			resetMoveCount();
			resetMoveFrame();
		}
		break;
	case PAGE2DIE:
		_currentFrameX = 0;
		break;
	}
}

void BigSlime::stateUpdate()
{
	switch (_state)
	{
	case PAGE2IDLE:

		break;
	case PAGE2ATTACK:
		if (_safeDistance)
		{
			_x += cosf(_angle) * 2;
			_y += -sinf(_angle) * 2;
		}

		break;
	case PAGE2MOVE:

		if (_safeDistance)
		{
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
		}

		break;
	case PAGE2DIE:

		break;
	}
}






void BigSlime::playDieEffect(void)
{
	if (!_effectPlaying)
	{
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;
	}
}

void BigSlime::resetIdleCount()
{
	_idleFrameCount = 0;
}

void BigSlime::resetMoveCount()
{
	_moveFrameCount = 0;
}

void BigSlime::resetIdleFrame()
{
	_idleFrame = RND->getFromIntTo(2, 3);
}

void BigSlime::resetMoveFrame()
{
	_moveFrame = RND->getFromIntTo(1, 2);
}

