#include "Stdafx.h"
#include "MegaFlime.h"
#include "Player.h"



HRESULT MegaFlime::init(POINT position)
{
	_image = IMAGEMANAGER->findImage("메가플라임IDLE");
	_hpMax = 500;
	_hp = _hpMax;
	_die = false;
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_speed = 1.f;
	_bigBullet = new EnemyBullet;
	_bigBullet->init("큰일반탄", 300, 300,1);
	_thorn = new Thorn;
	_thorn->init("가시", 500, 500);
	_poisonBullet = new PoisonBullet;
	_poisonBullet->init("독탄", 50, 300);
	_smallBullet = new EnemyBullet;
	_smallBullet->init("큰일반탄", 300, 300, 0);


	_effectPlaying = false;
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	_idleFrameCount = 0;
	_idleFrame = RND->getFromIntTo(2, 3);
	_canAttack = true;
	_attackCount = 3;
	_thornCount = 3;
	_attackDeleyTime = GetTickCount();
	_fireAngleInit = false;
	_fireAngle = 0.f;
	return S_OK;
}

void MegaFlime::release(void)
{
	_bigBullet->release();
	_thorn->release();
	_poisonBullet->release();
	_smallBullet->release();

	SAFE_DELETE(_image);
}

void MegaFlime::update(void)
{

	if (_hp <= 0 && !_die)
	{
		playDieEffect();
	}

	if (!_die)
	{
		_rc = RectMakeCenter(_x, _y,
			_image->getFrameWidth(), _image->getFrameHeight());
		_center.x = _x;
		_center.y = _y;

		_bigBullet->update();
		_poisonBullet->update();
		_thorn->update();
		_smallBullet->update();
		rangeInPlayer();
		collision();
	}
}

void MegaFlime::render(void)
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
			//SD: 적 죽는사운드
		
		}
	}

}

void MegaFlime::draw(void)
{
	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("메가플라임IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("메가플라임ATTACK2");
		break;
	case ATTACK2:
		_image = IMAGEMANAGER->findImage("메가플라임ATTACK1");
		break;
	case ATTACK3:
		_image = IMAGEMANAGER->findImage("메가플라임ATTACK2");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("메가플라임DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	default:
		break;
	}

	if (_state != DIE)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
	}
}

void MegaFlime::d2drender(void)
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
					_die = true;
					_effectPlaying = false;
				}
			}
		}
	}

	if (!_die)
	{
		_poisonBullet->d2drender();
		_thorn->d2drender();
		_bigBullet->d2drender();
		_smallBullet->d2drender();
	}

	if (_die && !_clear)
	{

		_clearEffectPlaying = true;
		D2DMANAGER->frameRender("보스사망이펙트", 0, 0, _clearEffectFrameX, _clearEffectFrameY, WINSIZE_X, WINSIZE_Y);
		_clearEffectCount++;
		if (_clearEffectCount == 1)
		{
	
		}
		if (_clearEffectCount % 2 == 0)
		{
			_clearEffectFrameX++;
			if (D2DMANAGER->findImage("보스사망이펙트")->maxFrameX < _clearEffectFrameX)
			{
				_clearEffectFrameX = 0;
				_clearEffectFrameY++;
				if (D2DMANAGER->findImage("보스사망이펙트")->maxFrameY < _clearEffectFrameY)
				{
					SOUNDMANAGER->play("스테이지시작", 0.1f);
					_clear = true;
					_clearEffectPlaying = false;

				}
			}
		}
	}
}



void MegaFlime::animation()
{
	if (!_canAttack)
	{
		int tempSpeed;
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
					_idleFrameCount++;
				}
				_image->setFrameX(_currentFrameX);
			}
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
				resetIdleCount();
				resetIdleFrame();

				_fireAngleInit = false;
				if (_attackCount == 3)
				{
					_state = ATTACK;
				}
				else if (_attackCount == 2)
				{
					_state = ATTACK2;
				}
				else if (_attackCount == 1)
				{
					_state = ATTACK3;
				}
				else
				{
					_state = ATTACK;
					_attackCount = 3;
				}
			}

			break;
		case ATTACK:
			if (_attackCount == 3)
			{
				tempSpeed = 300;	
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{		
						if (_thornTime == 0)
						{
							if (_thornCount == 3)
							{
								//SD: 뿌리 내딪는 소리 플라임공격사운드
								SOUNDMANAGER->play("플라임가시생성", 0.1f);

								float angleStep = PI * 2 / 6;
								float radiusStep = 50; 
								float rotationOffset = PI / 30; 

								for (int i = 0; i < 6; ++i) 
								{
									float baseAngle = i * angleStep;
									for (int j = 0; j < 7; ++j) 
									{ 
										float fireangle = baseAngle + j * rotationOffset;
										float radiusG = (j + 2) * radiusStep;
										_thorn->fire(_x, _y, fireangle, radiusG, 530);
									}
								}
							}
							
						}
						_thornTime++;
						if (_thornCount == 2)
						{
							float angleStep = PI * 2 / 6;
							float speed = 0.06f;

							for (int i = 0; i < 6; ++i)
							{
							

								float baseAngle = i * angleStep;
								_bigBullet->fire(_x, _y, baseAngle, speed);
						
							}

						}

						if (_thornTime % 10 == 0)
						{
							
							_thornCount--;
							_thornTime = 0;
							if (_thornCount <= 0)
							{
								_attackCount--;
								_currentFrameX = 0;
							}
						}
					
						
						_image->setFrameX(_currentFrameX);
					}
				}
			}
			else
			{
				_state = IDLE;
				_thornCount = 3;
				_thornTime = 0;
			}
			break;
		case ATTACK2:
			if (_attackCount == 2)
			{		
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						_fireAngleInit = false;

						if (_thornTime == 0)
						{
							//SD: 독뿌리는소리 사아악... 플라임공격
							SOUNDMANAGER->play("플라임독발사", 0.1f);
							if (_thornCount == 3)
							{
								float angleStep = PI / 5;
								for (int i = 0; i < 10; ++i)
								{
									float fireangle = i * angleStep;
									_smallBullet->fire(_x, _y, fireangle, 2.f);
								}
							}
							else if (_thornCount == 2)
							{
								float angleStep = PI / 5;
								for (int i = 0; i < 10; ++i)
								{
									float fireangle = i * angleStep;
									_smallBullet->fire(_x, _y, fireangle, 2.f);
								}

							
								for (int i = 0; i < 10; ++i)
								{
									float fireangle = i * angleStep;
									_poisonBullet->fire(_x, _y, fireangle, 1.f);
								}
							}
							else if (_thornCount == 1)
							{
								float angleStep = PI / 5;
								for (int i = 0; i < 10; ++i)
								{
									float fireangle = i * angleStep;
									_smallBullet->fire(_x, _y, fireangle, 2.f);
								}
							}

						}

						_thornTime++;
						if (_thornTime % 2 == 0)
						{
							_thornCount--;
							_thornTime = 0;
							if (_thornCount <= 0)
							{
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
				_state = IDLE;
				_thornCount = 3;
				_thornTime = 0;
			}
			break;

		case ATTACK3:
			if (_attackCount == 1)
			{
				//cout << _thornCount << endl;
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						if (_thornTime == 0)
						{
							if (_thornCount == 3)
							{
								
								SOUNDMANAGER->play("플라임가시생성", 0.1f);

								float radiusIncrement = 100; 
								for (int i = 1; i <= 2; ++i)
								{
									float angleIncrement = (PI * 2) / (10 * i); 
									float radius = radiusIncrement * i;

									for (float angle = 0; angle < PI * 2; angle += angleIncrement)
									{
										_thorn->fire(_thornPos.x + cos(angle) * radius, _thornPos.y + sin(angle) * radius, 64);
									}
								}


							}
							else if (_thornCount == 2)
							{
								
								SOUNDMANAGER->play("플라임가시생성", 0.1f);

								float radiusIncrement = 150;
								for (int i = 0; i <= 1; ++i)
								{
									float radius = radiusIncrement * i;

									if (i == 0) 
									{
										_thorn->fire(_thornPos.x, _thornPos.y, 64);
									}
									else 
									{
										float angleIncrement = (PI * 2) / (20 * i);
										for (float angle = 0; angle < PI * 2; angle += angleIncrement)
										{
											_thorn->fire(_thornPos.x + cos(angle) * radius, _thornPos.y + sin(angle) * radius, 64);
										}
									}
								}
							}
							else if (_thornCount == 1)
							{
								
								SOUNDMANAGER->play("플라임가시생성", 0.1f);

								float radiusIncrement = 100;
								for (int i = 1; i <= 2; ++i)
								{
									float angleIncrement = (PI * 2) / (10 * i);
									float radius = radiusIncrement * i;

									for (float angle = 0; angle < PI * 2; angle += angleIncrement)
									{
										_thorn->fire(_thornPos.x + cos(angle) * radius, _thornPos.y + sin(angle) * radius, 64);
									}
								}
							}

						}




						_thornTime++;
						if (_thornTime % 8 == 0)
						{
							_thornCount--;
							_thornTime = 0;
							if (_thornCount <= 0)
							{
								_currentFrameX = 0;
								_attackCount--;
								_fireAngleInit = false;

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
				_state = IDLE;
				_thornCount = 3;
				_thornTime = 0;
			}
			break;

		case DIE:
			_currentFrameX = 0;
			break;
		}
	}
}

void MegaFlime::collision(void)
{
	for (int i = 0; i < _poisonBullet->getBullet().size(); i++)
	{
		RECT col;
		if (IntersectRect(&col, &CollisionAreaResizing(_poisonBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{

			//SD: 플레이어 피격 사운드
			_player->setDamaged(1);
			break;
		}
		else if (IntersectRect(&col, &CollisionAreaResizing(_poisonBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}
	for (int i = 0; i < _bigBullet->getBullet().size(); i++)
	{
		RECT col;
		if (IntersectRect(&col, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_bigBullet->removeBullet(i);
			_player->setDamaged(1);
			break;
		}
		else if (IntersectRect(&col, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}
	for (int i = 0; i < _smallBullet->getBullet().size(); i++)
	{
		RECT col;
		if (IntersectRect(&col, &CollisionAreaResizing(_smallBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_smallBullet->removeBullet(i);
			_player->setDamaged(1);
			break;
		}
		else if (IntersectRect(&col, &CollisionAreaResizing(_smallBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}
	for (int i = 0; i < _thorn->getBullet().size(); i++)
	{
		RECT col;
		if (IntersectRect(&col, &CollisionAreaResizing(_thorn->getBullet()[i].rc, 128, 128),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{

			//SD: 플레이어 피격 사운드
			_player->setDamaged(2);
			break;
		}
		else if (IntersectRect(&col, &CollisionAreaResizing(_thorn->getBullet()[i].rc, 128, 128),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}
}
void MegaFlime::bossBulletFire()
{
	if (!_fireAngleInit)
	{
		float startX = _x;
		float startY = _y;
		float endX = _player->getPosition().x;
		float endY = _player->getPosition().y;
		_fireAngle = getAngle(startX, startY, endX, endY);
		_thornPos = PointMake(_player->getPosition().x, _player->getPosition().y);



		_fireAngleInit = true;
	}
}
void MegaFlime::rangeInPlayer(void)
{
	_angle = getAngle(_x, _y, _player->getPosition().x, _player->getPosition().y);
	bossBulletFire();
}

void MegaFlime::resetIdleCount()
{
	_idleFrameCount = 0;
}

void MegaFlime::resetIdleFrame()
{
	_idleFrame = 3;
}

void MegaFlime::playDieEffect()
{
	if (!_effectPlaying)
	{
		//SD: 클리어 이펙트 사운드
		SOUNDMANAGER->play("보스클리어", 0.1f);
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;
		
	}
}
