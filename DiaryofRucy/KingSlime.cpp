#include "Stdafx.h"
#include "KingSlime.h"
#include "Player.h"



HRESULT KingSlime::init(POINT position)
{
	_image = IMAGEMANAGER->findImage("킹슬라임IDLE");
	_hpMax = 500;
	_hp = _hpMax;
	_die = false;
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_speed = 1.f;

	_bubble = new EnemyBullet;
	_bubble->init("버블", 100, 270,0);
	_bubbleBullet = new BubbleBullet;
	_bubbleBullet->init("큰일반탄", 500, 130);

	_effectPlaying = false;
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	_safeDistance = true;
	_page = 0;
	_idleFrameCount = 0;
	_moveFrameCount = 0;

	_canAttack = true;
	_attackCount = 1;


	function<void(float, float)> callback = [this](float X,float Y)
	{
		float angleStep = PI / 5;
		for (int i = 0; i < 10; ++i)
		{
			float fireangle = i * angleStep;
			this->_bubbleBullet->fire(X, Y, fireangle, 2);
		}
	};
	this->_bubble->setBulletRemovedCallback(callback);
	

	return S_OK;
}


void KingSlime::release(void)
{
	SAFE_DELETE(_image);
	_bubble->release();
	_bubbleBullet->release();
}

void KingSlime::update(void)
{
	//if (!_bossBgm)
	//{
	//	SOUNDMANAGER->stop("스테이지시작");
	//	SOUNDMANAGER->play("보스브금", 0.1f);
	//	_bossBgm = true;
//	}
	if (_page == 0)
	{
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
	else if (_page == 1)
	{

		for (_viBigSlime = _vBigSlime.begin(); _viBigSlime != _vBigSlime.end(); ++_viBigSlime)
		{
			(*_viBigSlime)->update();
		

		}
	
	
		for (int i = 0; i < _vBigSlime.size(); i++)
		{
			if (_vBigSlime[i]->getDie())
			{	
				_slimeCreate = true;

				for (int j = 0; j < 2; j++)
				{
					Slime* slime = new Slime(State::IDLE);
					slime->init("슬라임IDLE", PointMake(_vBigSlime[i]->getCenterPos().x - (j*20), _vBigSlime[i]->getCenterPos().y +10));
					_vSlime.push_back(slime);
				}
				removeBigSlime(i);
			}
		}
		
		if (_vBigSlime.empty())
		{
			_page = 2;
		}

	}
	else if (_page == 2)
	{
		if (_vSlime.empty() && !_clear)
		{
			_die = true;
		}
	}

	if (_slimeCreate)
	{
		slimeRanegeInPlayer();

		for (int i = 0; i < _vSlime.size(); i++)
		{
			if (_vSlime[i]->getDie())
			{
				removeSlime(i);
			}
			else
			{
				_vSlime[i]->update();
			}
		}
	}

	if (!_die)
	{
		collision();
		_rc = RectMakeCenter(_x, _y,
			_image->getFrameWidth(), _image->getFrameHeight());
		_center.x = _x;
		_center.y = _y;

		_bubble->update();
		_bubbleBullet->update();
		rangeInPlayer();
	}


}

void KingSlime::render(void)
{
	if (!_die)
	{
		if (_page == 0)
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
		else if (_page == 1)
		{
			for (_viBigSlime = _vBigSlime.begin(); _viBigSlime != _vBigSlime.end(); ++_viBigSlime)
			{
				(*_viBigSlime)->render();
			}

		}

		else if (_page == 2)
		{
		}
		if (_slimeCreate)
		{
			for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
			{
				(*_viSlime)->render();
			}
		}
	
	}
}

void KingSlime::draw(void)
{

	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("킹슬라임IDLE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("킹슬라임ATTACK");
		break;
	case MOVE:
		_image = IMAGEMANAGER->findImage("킹슬라임MOVE");
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("킹슬라임DIE");
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

void KingSlime::d2drender(void)
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
					if (_page == 0)
					{
						_page++;
						setBigSlime(PointMake(_x-50, _y));
						setBigSlime(PointMake(_x+50, _y));					
					}
					_effectPlaying = false;
				}
			}
		}
	}

	if (!_die)
	{
		_bubble->d2drender();
		_bubbleBullet->d2drender();
	}
	if (_page == 1)
	{
		for (_viBigSlime = _vBigSlime.begin(); _viBigSlime != _vBigSlime.end(); ++_viBigSlime)
		{
			(*_viBigSlime)->d2drender();
		}
	}
	else if (_page == 2)
	{
		

	}
	if (_slimeCreate)
	{
		for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
		{
			(*_viSlime)->d2drender();
		}
	}


	if (_die && !_clear)
	{
		
		_clearEffectPlaying = true;
		D2DMANAGER->frameRender("보스사망이펙트", 0, 0, _clearEffectFrameX, _clearEffectFrameY, WINSIZE_X, WINSIZE_Y);
		_clearEffectCount++;

		if (_clearEffectCount == 1)
		{
			SOUNDMANAGER->play("보스클리어", 0.1f);
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

void KingSlime::setBigSlime(POINT position)
{
	BigSlime* bigSlime = new BigSlime;
	bigSlime->init(position);
	_vBigSlime.push_back(bigSlime);
}

void KingSlime::stateUpdate()
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

void KingSlime::animation()
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
				_state = MOVE;
				resetIdleCount();
				resetIdleFrame();
			}

			break;
		case ATTACK:
		
			if (_attackCount == 1)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_currentFrameX == 0)
					{
						//SD: 슬라임 공격사운드
						SOUNDMANAGER->play("슬라임공격", 0.8f);
					}
					if (_currentFrameX == 2)
					{
						//SD: 슬라임 공격사운드
						SOUNDMANAGER->play("슬라임공격", 0.8f);
					}


					if (_image->getMaxFrameX() < _currentFrameX)
					{
						
						_attackCount--;
						//SD: 슬라임 공격사운드
						SOUNDMANAGER->play("슬라임공격", 0.8f);
						float angleStep = PI / 5;
						for (int i = 0; i < 10; ++i)
						{
							float fireangle = i * angleStep;
							_bubble->fire(_x, _y, fireangle, 3.f);
						}
						_currentFrameX = 0;
						_image->setFrameX(_currentFrameX);
					
					}
					
				}
			}
			else
			{
				_state = IDLE;
			}
			break;
		case MOVE:
			if (_moveFrameCount < 2)
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
				_state = ATTACK;
				_attackCount = 1;
				resetMoveCount();
				resetMoveFrame();
			}
			break;
		case DIE:
			_currentFrameX = 0;
			break;
		}
	}
}

void KingSlime::collision(void)
{
	for (int i = 0; i < _vSlime.size(); i++)
	{
		for (int j = 0; j < _vSlime[i]->getBigBullet()->getBullet().size(); j++)
		{
			RECT col;
			if (IntersectRect(&col, &_vSlime[i]->getBigBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && !_player->getInvincible())
			{
				//SD: 플레이어 피격 사운드
				_vSlime[i]->getBigBullet()->removeBullet(j);
				_player->setDamaged();
				break;
			}
			else if (IntersectRect(&col, &_vSlime[i]->getBigBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && _player->getBehaviorType(4))
			{
				_player->setAvoidManaRecovery();
			}

		}
	}

	for (int i = 0; i < _vSlime.size(); i++)
	{
		for (int j = 0; j < _vSlime[i]->getSmallBullet()->getBullet().size(); j++)
		{
			RECT col;
			if (IntersectRect(&col, &_vSlime[i]->getSmallBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && !_player->getInvincible())
			{
				//SD: 플레이어 피격 사운드
				_vSlime[i]->getSmallBullet()->removeBullet(j);
				_player->setDamaged();
				break;
			}
			else if (IntersectRect(&col, &_vSlime[i]->getSmallBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && _player->getBehaviorType(4))
			{
				_player->setAvoidManaRecovery();
			}
		}
	}

	for (int i = 0; i < _vBigSlime.size(); i++)
	{
		for (int j = 0; j < _vBigSlime[i]->getBigBullet()->getBullet().size(); j++)
		{
			RECT col;
			if (IntersectRect(&col, &_vBigSlime[i]->getBigBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && !_player->getInvincible())
			{
				//SD: 플레이어 피격 사운드
				_vBigSlime[i]->getBigBullet()->removeBullet(j);
				_player->setDamaged();
				break;
			}
			else if (IntersectRect(&col, &_vBigSlime[i]->getBigBullet()->getBullet()[j].rc,
				&_player->getCollisionRect()) && _player->getBehaviorType(4))
			{
				_player->setAvoidManaRecovery();
			}
		}
	}

	for (int i = 0; i < _bubbleBullet->getBullet().size(); i++)
	{
		RECT col;
		if (IntersectRect(&col, &CollisionAreaResizing(_bubbleBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_bubbleBullet->removeBullet(i);
			_player->setDamaged(1);
			break;
		}
		else if (IntersectRect(&col, &CollisionAreaResizing(_bubbleBullet->getBullet()[i].rc, 1, 1),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}

}


void KingSlime::bossBulletFire()
{
	//_canAttack = true;
	switch (_page)
	{
	case 0:
		if (!_fireAngleInit)
		{
			float startX = _x;
			float startY = _y;
			float endX = _player->getPosition().x;
			float endY = _player->getPosition().y;
			//플라임 가시 여기포지션 조정 (*viEnemyName)->setThornPos(PointMake(_player->getPosition().x, _player->getPosition().y));
			_fireAngle = getAngle(startX, startY, endX, endY);
			_fireAngleInit = true;
		}
		break;

	case 1:
		if ((*_viBigSlime)->getFireAngleInit())
		{
			float startX = (*_viBigSlime)->getCenterPos().x;
			float startY = (*_viBigSlime)->getCenterPos().y;
			float endX = _player->getPosition().x;
			float endY = _player->getPosition().y;
			(*_viBigSlime)->setFireAngle(getAngle(startX, startY, endX, endY));
			(*_viBigSlime)->setFireAngleInit(true);
		}
		break;

	case 2:

		
		break;

	default:
		break;
	}

	



}

void KingSlime::bossDirectionTracking()
{


	switch (_page)
	{
	case 0:
		_animDirectionAngle = getAngle(_x, _y, _player->getPosition().x, _player->getPosition().y) - 0.785f;

		if (_state == MOVE || _state == IDLE)
		{
			if (_animDirectionAngle >= 0.f && _animDirectionAngle < 1.543f)
			{
				_direction = UP;
			}
			else if (_animDirectionAngle >= 1.543f && _animDirectionAngle < 3.113f)
			{
				_direction = LEFT;
			}
			else if (_animDirectionAngle >= 3.113f && _animDirectionAngle < 4.656f)
			{
				_direction = DOWN;
			}
			else if (_animDirectionAngle >= 4.656f && _animDirectionAngle < 6.28f ||
				_animDirectionAngle < 0 && _animDirectionAngle > -0.785f)
			{
				_direction = RIGHT;
			}

		}

		break;
	case 1:
		(*_viBigSlime)->setAnimDirectionAngle(getAngle((*_viBigSlime)->getCenterPos().x,
			(*_viBigSlime)->getCenterPos().y,
			_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
			_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) - 0.785f);
		if ((*_viBigSlime)->getState() == PAGE2MOVE || (*_viBigSlime)->getState() == PAGE2IDLE)
		{
			if ((*_viBigSlime)->getAnimDirectionAngle() >= 0.f && (*_viBigSlime)->getAnimDirectionAngle() < 1.543f)
			{
				(*_viBigSlime)->setAnimDirection(PAGE2UP);
			}
			if ((*_viBigSlime)->getAnimDirectionAngle() >= 1.543f && (*_viBigSlime)->getAnimDirectionAngle() < 3.113f)
			{
				(*_viBigSlime)->setAnimDirection(PAGE2LEFT);
			}
			if ((*_viBigSlime)->getAnimDirectionAngle() >= 3.113f && (*_viBigSlime)->getAnimDirectionAngle() < 4.656f)
			{
				(*_viBigSlime)->setAnimDirection(PAGE2DOWN);
			}
			if ((*_viBigSlime)->getAnimDirectionAngle() >= 4.656f && (*_viBigSlime)->getAnimDirectionAngle() < 6.28f ||
				(*_viBigSlime)->getAnimDirectionAngle() < 0 && (*_viBigSlime)->getAnimDirectionAngle() > -0.785f)
			{
				(*_viBigSlime)->setAnimDirection(PAGE2RIGHT);
			}
		}

		break;
	case 2:

		break;
	default:
		break;
	}










}

void KingSlime::bossPositionTracking()
{
	switch (_page)
	{
	case 0:
		if (getDistance(_x, _y, _player->getPosition().x, _player->getPosition().y) < 50.f)
		{
			_safeDistance = false;
		}
		else if (getDistance(_x, _y, _player->getPosition().x, _player->getPosition().y) > 50.f)
		{
			_safeDistance = true;
		}
		break;
	case 1:
		if (getDistance((*_viBigSlime)->getRect().left + ((*_viBigSlime)->getRect().right - (*_viBigSlime)->getRect().left) / 2,
			(*_viBigSlime)->getRect().top + ((*_viBigSlime)->getRect().bottom - (*_viBigSlime)->getRect().top) / 2,
			_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
			_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) < 50.f)
		{
			(*_viBigSlime)->setSafeDistance(false);
		}
		else if (getDistance((*_viBigSlime)->getRect().left + ((*_viBigSlime)->getRect().right - (*_viBigSlime)->getRect().left) / 2,
			(*_viBigSlime)->getRect().top + ((*_viBigSlime)->getRect().bottom - (*_viBigSlime)->getRect().top) / 2,
			_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
			_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) > 50.f)
		{
			(*_viBigSlime)->setSafeDistance(true);
		}
		break;
	case 2:
		
		break;
	default:
		break;
	}



}

void KingSlime::slimeBulletFire()
{
	//cout << (*_viSlime)->getFireAngle() << endl;
	(*_viSlime)->setCanAttack(true);
	if (!(*_viSlime)->getFireAngleInit())
	{
		float startX = (*_viSlime)->getCenterPos().x;
		float startY = (*_viSlime)->getCenterPos().y;
		float endX = _player->getPosition().x;
		float endY = _player->getPosition().y;
		(*_viSlime)->setFireAngle(getAngle(startX, startY, endX, endY));
		(*_viSlime)->setFireAngleInit(true);
	}
}

void KingSlime::slimeDirectionTracking()
{
	(*_viSlime)->setAnimDirectionAngle(getAngle((*_viSlime)->getCenterPos().x,
		(*_viSlime)->getCenterPos().y,
		_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
		_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) - 0.785f);
	if ((*_viSlime)->getState() == enemyState::MOVE || (*_viSlime)->getState() == enemyState::IDLE)
	{
		if ((*_viSlime)->getAnimDirectionAngle() >= 0.f && (*_viSlime)->getAnimDirectionAngle() < 1.543f)
		{
			(*_viSlime)->setAnimDirection(enemyAnimDirection::UP);
		}
		if ((*_viSlime)->getAnimDirectionAngle() >= 1.543f && (*_viSlime)->getAnimDirectionAngle() < 3.113f)
		{
			(*_viSlime)->setAnimDirection(enemyAnimDirection::LEFT);
		}
		if ((*_viSlime)->getAnimDirectionAngle() >= 3.113f && (*_viSlime)->getAnimDirectionAngle() < 4.656f)
		{
			(*_viSlime)->setAnimDirection(enemyAnimDirection::DOWN);
		}
		if ((*_viSlime)->getAnimDirectionAngle() >= 4.656f && (*_viSlime)->getAnimDirectionAngle() < 6.28f ||
			(*_viSlime)->getAnimDirectionAngle() < 0 && (*_viSlime)->getAnimDirectionAngle() > -0.785f)
		{
			(*_viSlime)->setAnimDirection(enemyAnimDirection::RIGHT);
		}
	}
}

void KingSlime::slimePositionTracking()
{
	if (getDistance((*_viSlime)->getRect().left + ((*_viSlime)->getRect().right - (*_viSlime)->getRect().left) / 2,
		(*_viSlime)->getRect().top + ((*_viSlime)->getRect().bottom - (*_viSlime)->getRect().top) / 2,
		_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
		_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) < 50.f)
	{
		(*_viSlime)->setSafeDistance(false);
	}
	else if (getDistance((*_viSlime)->getRect().left + ((*_viSlime)->getRect().right - (*_viSlime)->getRect().left) / 2,
		(*_viSlime)->getRect().top + ((*_viSlime)->getRect().bottom - (*_viSlime)->getRect().top) / 2,
		_player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
		_player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) > 50.f)
	{
		(*_viSlime)->setSafeDistance(true);
	}
}

void KingSlime::rangeInPlayer(void)
{
	switch (_page)
	{
	case 0:
		_angle = getAngle(_x, _y, _player->getPosition().x, _player->getPosition().y);

		bossBulletFire();
		bossDirectionTracking();
		bossPositionTracking();
		break;
	case 1:
		for (_viBigSlime = _vBigSlime.begin(); _viBigSlime != _vBigSlime.end(); ++_viBigSlime)
		{
			float angle = getAngle((*_viBigSlime)->getCenterPos().x, (*_viBigSlime)->getCenterPos().y,
				_player->getPosition().x, _player->getPosition().y);
			(*_viBigSlime)->setAngle(angle);
			bossBulletFire();
			bossDirectionTracking();
			bossPositionTracking();
		}
		break;
	default:
		break;
	}
	


	
}

void KingSlime::slimeRanegeInPlayer(void)
{
	for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
	{
		float angle = getAngle((*_viSlime)->getCenterPos().x, (*_viSlime)->getCenterPos().y,
			_player->getPosition().x, _player->getPosition().y);
		(*_viSlime)->setAngle(angle);
		slimeBulletFire();
		slimeDirectionTracking();
		slimePositionTracking();
	}
}

void KingSlime::playDieEffect(void)
{
	if (!_effectPlaying)
	{
		//SD: 클리어 이펙트 사운드
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;

	}

}



void KingSlime::resetIdleCount()
{
	_idleFrameCount = 0;
}

void KingSlime::resetMoveCount()
{
	_moveFrameCount = 0;
}

void KingSlime::resetIdleFrame()
{
	_idleFrame = 3;

}

void KingSlime::resetMoveFrame()
{
	_moveFrame = 3;
}

void KingSlime::removeBigSlime(int arrNum)
{
	SAFE_DELETE(_vBigSlime[arrNum]);
	_vBigSlime.erase(_vBigSlime.begin() + arrNum);
}

void KingSlime::removeSlime(int arrNum)
{
	SAFE_DELETE(_vSlime[arrNum]);
	_vSlime.erase(_vSlime.begin() + arrNum);
}
