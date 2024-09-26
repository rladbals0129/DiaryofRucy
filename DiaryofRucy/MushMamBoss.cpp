#include "Stdafx.h"
#include "MushMamBoss.h"
#include "Player.h"
#include "MiniGreenTurret.h"
#include "GreenTurret.h"
#include "PurpleTurret.h"
#include "MintTurret.h"

HRESULT MushMamBoss::init(POINT position)
{
	_image = IMAGEMANAGER->findImage("머쉬맘보스IDLE");
	_hpMax = 500;
	_hp = _hpMax;
	_die = false;
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_speed = 1.f;
	//_bigBullet = new EnemyBullet;
	//_bigBullet->init("큰일반탄", 500, 300, 0);
	_espBullet = new EspBullet;
	_espBullet->init("유도탄", 100, 150);
	_greenEspBullet = new EspBullet;
	_greenEspBullet->init("유도탄", 100, 50);
	_bigBullet = new EnemyBullet;
	_bigBullet->init("큰일반탄", 100, 400, 0);
	_poisonBullet = new PoisonBullet;
	_poisonBullet->init("독탄", 300, 800);

	
	_effectPlaying = false;
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	_safeDistance = true;
	_idleFrameCount = 0;
	_moveFrameCount = 0;
	_idleFrame = RND->getFromIntTo(2, 3);
	_canAttack = true;
	_attackCount = 4;
	_fireCount = 0.6f;
	return S_OK;
}

void MushMamBoss::release(void)
{
	_espBullet->release();
	_greenEspBullet->release();
	_bigBullet->release();
	_poisonBullet->release();

	for (_viMiniTurret = _vMiniTurret.begin(); _viMiniTurret != _vMiniTurret.end(); ++_viMiniTurret)
	{
		(*_viMiniTurret)->release();
	}
	for (_viGreenTurret = _vGreenTurret.begin(); _viGreenTurret != _vGreenTurret.end(); ++_viGreenTurret)
	{
		(*_viGreenTurret)->release();
	}
	for (_viPurpleTurret = _vPurpleTurret.begin(); _viPurpleTurret != _vPurpleTurret.end(); ++_viPurpleTurret)
	{
		(*_viPurpleTurret)->release();
	}
	for (_viMintTurret = _vMintTurret.begin(); _viMintTurret != _vMintTurret.end(); ++_viMintTurret)
	{
		(*_viMintTurret)->release();
	}

	SAFE_DELETE(_image);
}

void MushMamBoss::update(void)
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


		_espBullet->update();
		_espBullet->updateAngle(_player->getPosition().x, _player->getPosition().y);
		_greenEspBullet->update();
		_greenEspBullet->updateAngle(_player->getPosition().x, _player->getPosition().y);
		_poisonBullet->update();
		_bigBullet->update();
		rangeInPlayer();
		collision();
		turretBulletFire();

		for (int i = 0; i < _vMiniTurret.size(); i++)
		{
			if (_vMiniTurret[i]->getDie() && !_vMiniTurret[i]->getLastFire())
			{
				removeMiniTurret(i);
			}
			else
			{
				_vMiniTurret[i]->update();


			}
		}
		for (int i = 0; i < _vGreenTurret.size(); i++)
		{
			if (_vGreenTurret[i]->getDie())
			{
				removeGreenTurret(i);
			}
			else
			{
				_vGreenTurret[i]->update();
				
			}
		}
		for (int i = 0; i < _vPurpleTurret.size(); i++)
		{
			if (_vPurpleTurret[i]->getDie() )
			{
				removePurpleTurret(i);
			}
			else
			{
				_vPurpleTurret[i]->update();
			}
		}
		for (int i = 0; i < _vMintTurret.size(); i++)
		{
			if (_vMintTurret[i]->getDie())
			{
				removeMintTurret(i);
			}
			else
			{
				_vMintTurret[i]->update();
			}
		}

	}
}

void MushMamBoss::render(void)
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


		for (int i = 0; i < _vMiniTurret.size(); i++)
		{
		
			_vMiniTurret[i]->render();
			
		}

		for (int i = 0; i < _vGreenTurret.size(); i++)
		{
		
			_vGreenTurret[i]->render();
			
		}

		for (int i = 0; i < _vPurpleTurret.size(); i++)
		{
		
			
			_vPurpleTurret[i]->render();

		}

		for (int i = 0; i < _vMintTurret.size(); i++)
		{
		
			_vMintTurret[i]->render();
			
		}

	}
}

void MushMamBoss::draw(void)
{
	switch (_state)
	{
	case IDLE:
		_image = IMAGEMANAGER->findImage("머쉬맘보스IDLE");
		break;
	case MOVE:
		_image = IMAGEMANAGER->findImage("머쉬맘보스MOVE");
		break;
	case ATTACK:
		_image = IMAGEMANAGER->findImage("머쉬맘보스ATTACK1");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	case ATTACK2:
		_image = IMAGEMANAGER->findImage("머쉬맘보스ATTACK1");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	case ATTACK3:
		_image = IMAGEMANAGER->findImage("머쉬맘보스ATTACK2");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	case ATTACK4:
		_image = IMAGEMANAGER->findImage("머쉬맘보스ATTACK3");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, 0);
		break;
	case DIE:
		_image = IMAGEMANAGER->findImage("머쉬맘보스DIE");
		_image->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	default:
		break;
	}

	if (_state != DIE && _state != ATTACK && _state != ATTACK2 && _state != ATTACK3 && _state != ATTACK4)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _direction);
	}
}

void MushMamBoss::d2drender(void)
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
		_espBullet->d2drender();
		_bigBullet->d2drender();
		_greenEspBullet->d2drender();
	
		for (int i = 0; i < _vMiniTurret.size(); i++)
		{
			_vMiniTurret[i]->d2drender();
		}
		for (int i = 0; i < _vGreenTurret.size(); i++)
		{
			_vGreenTurret[i]->d2drender();
		}

		for (int i = 0; i < _vPurpleTurret.size(); i++)
		{
			_vPurpleTurret[i]->d2drender();
		}

		for (int i = 0; i < _vMintTurret.size(); i++)
		{
			_vMintTurret[i]->d2drender();
		}
	}

	if (_die && !_clear)
	{

		_clearEffectPlaying = true;
		D2DMANAGER->frameRender("보스사망이펙트", 0, 0, _clearEffectFrameX, _clearEffectFrameY, WINSIZE_X, WINSIZE_Y);
		_clearEffectCount++;

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

void MushMamBoss::stateUpdate()
{
	switch (_state)
	{
	case MOVE:
		if (_safeDistance)
		{
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
		}
		else
		{
			_x -= cosf(_angle) * _speed;
			_y -= -sinf(_angle) * _speed;
		}

		break;
	case DIE:

		break;
	}
}

void MushMamBoss::animation()
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
				_state = MOVE;
				_rndAngleInit = false;
				//_fireAngleInit = false;
		
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
				_rndAngleInit = false;
				resetMoveCount();
				resetMoveFrame();
				_fireAngleInit = false;
				if (_attackCount == 4)
				{
					_state = ATTACK;
				}
				else if (_attackCount == 3)
				{
					_state = ATTACK2;
				}
				else if (_attackCount == 2)
				{
					_state = ATTACK3;
				}
				else if (_attackCount == 1)
				{
					_state = ATTACK4;
				}
				else
				{
					_state = ATTACK;
					_attackCount = 4;
				}
			
			}
			break;
		case ATTACK:
			if (_attackCount == 4)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();
					_currentFrameX++;
					if (_image->getMaxFrameX() < _currentFrameX)
					{			
						//SD: 버섯 공격사운드 (우으아!)
						SOUNDMANAGER->play("머쉬맨공격", 0.1f);

						_attackCount--;
						_currentFrameX = 0;
						setMiniTurret(_x, _y + 50);
						setMiniTurret(_x-30, _y + 50);
						setMiniTurret(_x+30, _y + 50);
					}
						_image->setFrameX(_currentFrameX);
				}
			}
			else
			{
				_state = IDLE;
			}
			break;
		case ATTACK2:
			if (_attackCount == 3)
			{
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						//SD: 버섯 공격사운드 (우으아!)
						SOUNDMANAGER->play("머쉬맨공격", 0.1f);

						_fireAngleInit = false;
						_currentFrameX = 0;
						setGreenTurret(_x, _y + 50);
						_attackCount--;
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
			}
			break;

		case ATTACK3:
			if (_attackCount == 2)
			{	
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						//SD: 버섯 공격사운드 (우으아!)
						SOUNDMANAGER->play("머쉬맨공격", 0.1f);

						_currentFrameX = 0;
						_attackCount--;
						setPurpleTurret(_x, _y + 50);
						_fireAngleInit = false;
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
			}
			break;

		case ATTACK4:
			if (_attackCount == 1)
			{
			
				tempSpeed = 300;
				if (tempSpeed + _frameCount <= GetTickCount64())
				{
					_frameCount = GetTickCount64();

					if (_image->getMaxFrameX() < _currentFrameX)
					{
						//SD: 버섯 공격사운드 (우으아!)
						SOUNDMANAGER->play("머쉬맨공격", 0.1f);

						setMintTurret(_x, _y + 50);
						_fireAngleInit = false;
						_currentFrameX = 0;
						_attackCount--;
						
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
			}
			break;
		case DIE:
			_currentFrameX = 0;
			break;
		}
	



	}
}

void MushMamBoss::collision(void)
{
	for (int i = 0; i < _espBullet->getBullet().size(); i++)
	{
		if (isOBBCollision(CollisionAreaResizing(_espBullet->getBullet()[i].rc, 0, 0),
			_espBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f)
			&& !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_espBullet->removeBullet(i);
			_player->setDamaged();
			break;
		}
		else if (isOBBCollision(CollisionAreaResizing(_espBullet->getBullet()[i].rc, 0, 0),
			_espBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}

	for (int i = 0; i < _greenEspBullet->getBullet().size(); i++)
	{
		if (isOBBCollision(CollisionAreaResizing(_greenEspBullet->getBullet()[i].rc, 0, 0),
			_greenEspBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f)
			&& !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_greenEspBullet->removeBullet(i);
			_player->setDamaged();
			break;
		}
		else if (isOBBCollision(CollisionAreaResizing(_greenEspBullet->getBullet()[i].rc, 0, 0),
			_greenEspBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}

	for (int i = 0; i < _bigBullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_bigBullet->removeBullet(i);
			_player->setDamaged();
			break;
		}
		else if (IntersectRect(&rc, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}

	for (int i = 0; i < _poisonBullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_poisonBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && !_player->getInvincible())
		{
			//SD: 플레이어 피격 사운드
			_player->setDamaged();
			break;
		}
		else if (IntersectRect(&rc, &CollisionAreaResizing(_poisonBullet->getBullet()[i].rc, 30, 30),
			&_player->getCollisionRect()) && _player->getBehaviorType(4))
		{
			_player->setAvoidManaRecovery();
		}
	}


}


void MushMamBoss::resetIdleCount()
{
	_idleFrameCount = 0;
}

void MushMamBoss::resetMoveCount()
{
	_moveFrameCount = 0;
}

void MushMamBoss::resetIdleFrame()
{
	_idleFrame = 3;
}

void MushMamBoss::resetMoveFrame()
{
	_moveFrame = 3;
}

void MushMamBoss::playDieEffect(void)
{
	if (!_effectPlaying)
	{
		SOUNDMANAGER->play("보스클리어", 0.1f);
		//SD: 클리어 이펙트 사운드
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;
	}
}


void MushMamBoss::setMiniTurret(int x, int y)
{
	Turret* miniGreen = new MiniGreenTurret;
	miniGreen->init("초록포탑", PointMake(x, y));
	_vMiniTurret.push_back(miniGreen);
}

void MushMamBoss::setGreenTurret(int x, int y)
{
	Turret* green = new GreenTurret;
	green->init("큰초록포탑", PointMake(x, y));
	_vGreenTurret.push_back(green);
}

void MushMamBoss::setPurpleTurret(int x, int y)
{
	Turret* purple = new PurpleTurret;
	purple->init("큰보라포탑", PointMake(x, y));
	_vPurpleTurret.push_back(purple);
}

void MushMamBoss::setMintTurret(int x, int y)
{
	Turret* mint = new MintTurret;
	mint->init("큰민트포탑", PointMake(x, y));
	_vMintTurret.push_back(mint);
}

void MushMamBoss::removeMiniTurret(int arrNum)
{
	SAFE_DELETE(_vMiniTurret[arrNum]);
	_vMiniTurret.erase(_vMiniTurret.begin() + arrNum);
}

void MushMamBoss::removeGreenTurret(int arrNum)
{
	SAFE_DELETE(_vGreenTurret[arrNum]);
	_vGreenTurret.erase(_vGreenTurret.begin() + arrNum);
}

void MushMamBoss::removePurpleTurret(int arrNum)
{
	SAFE_DELETE(_vPurpleTurret[arrNum]);
	_vPurpleTurret.erase(_vPurpleTurret.begin() + arrNum);
}

void MushMamBoss::removeMintTurret(int arrNum)
{
	SAFE_DELETE(_vMintTurret[arrNum]);
	_vMintTurret.erase(_vMintTurret.begin() + arrNum);
}

void MushMamBoss::turretBulletFire()
{
	for (_viMiniTurret = _vMiniTurret.begin(); _viMiniTurret != _vMiniTurret.end(); ++_viMiniTurret)
	{
		if ((*_viMiniTurret)->bulletCountFire())
		{
			RECT rc = (*_viMiniTurret)->getRect();
			_espBullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
				getAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_player->getPosition().x,
					_player->getPosition().y), 3.f);
		}

		if ((*_viMiniTurret)->getLastFire())
		{
			RECT rc = (*_viMiniTurret)->getRect();
			float angleStep = PI / 10;
			for (int i = 0; i < 20; ++i)
			{
				float fireangle = i * angleStep;
				_bigBullet->fire(rc.left + (rc.right + -rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, fireangle, 3.f);
			}

			(*_viMiniTurret)->setLastFire(false);
			(*_viMiniTurret)->setDie(true);

		}
	}

	for (_viGreenTurret = _vGreenTurret.begin(); _viGreenTurret != _vGreenTurret.end(); ++_viGreenTurret)
	{
		if ((*_viGreenTurret)->bulletCountFire())
		{
			_greenEspBullet->fire((*_viGreenTurret)->getPos().x, (*_viGreenTurret)->getPos().y,
				getAngle((*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y,
					(*_viGreenTurret)->getPos().x - 50,
					(*_viGreenTurret)->getPos().y), 3.f);
			_greenEspBullet->fire((*_viGreenTurret)->getPos().x, (*_viGreenTurret)->getPos().y,
				getAngle((*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y,
					(*_viGreenTurret)->getPos().x + 50,
					(*_viGreenTurret)->getPos().y), 3.f);
			_greenEspBullet->fire((*_viGreenTurret)->getPos().x, (*_viGreenTurret)->getPos().y,
				getAngle((*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y,
					(*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y - 50), 3.f);
			_greenEspBullet->fire((*_viGreenTurret)->getPos().x, (*_viGreenTurret)->getPos().y,
				getAngle((*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y,
					(*_viGreenTurret)->getPos().x,
					(*_viGreenTurret)->getPos().y + 50), 3.f);
		}
	}

	for (_viPurpleTurret = _vPurpleTurret.begin(); _viPurpleTurret != _vPurpleTurret.end(); ++_viPurpleTurret)
	{
		if ((*_viPurpleTurret)->bulletCountFire())
		{
			float angleStep = PI / 4;
			for (int i = 0; i < 8; ++i)
			{
				float fireangle = i * angleStep;
				_poisonBullet->fire((*_viPurpleTurret)->getPos().x, (*_viPurpleTurret)->getPos().y, fireangle, 1.f);
			}
		}
	}


	for (_viMintTurret = _vMintTurret.begin(); _viMintTurret != _vMintTurret.end(); ++_viMintTurret)
	{
		if ((*_viMintTurret)->bulletCountFire())
		{
			float angleStep = PI / 6;
			for (int i = 0; i < 12; ++i)
			{
				float fireangle = i * angleStep;
				_bigBullet->fire((*_viMintTurret)->getPos().x, (*_viMintTurret)->getPos().y, fireangle, 2.f);
			}
		}
	}




}


void MushMamBoss::bossBulletFire()
{

	if (!_fireAngleInit)
	{
		float startX = _x;
		float startY = _y;
		float endX = _player->getPosition().x;
		float endY = _player->getPosition().y;
		_fireAngle = getAngle(startX, startY, endX, endY);
		_fireAngleInit = true;
	}

}

void MushMamBoss::bossDirectionTracking()
{
	

	//if (_state == MOVE && !_rndAngleInit)
	//{
	//	_rndAngleInit = true;
	//	_animDirectionAngle = RND->getFromFloatTo(-0.785f, 5.795f);
	//	if (_animDirectionAngle >= 0.f && _animDirectionAngle < 1.543f)
	//	{
	//		_direction = UP;
	//	}
	//	else if (_animDirectionAngle >= 1.543f && _animDirectionAngle < 3.113f)
	//	{
	//		_direction = LEFT;
	//	}
	//	else if (_animDirectionAngle >= 3.113f && _animDirectionAngle < 4.656f)
	//	{
	//		_direction = DOWN;
	//	}
	//	else if (_animDirectionAngle >= 4.656f && _animDirectionAngle < 6.28f ||
	//		_animDirectionAngle < 0 && _animDirectionAngle > -0.785f)
	//	{
	//		_direction = RIGHT;
	//	}

	//}
	if (_safeDistance)
	{
		if (_state == MOVE || _state == IDLE)
		{

			_animDirectionAngle = getAngle(_x, _y, _player->getPosition().x, _player->getPosition().y) - 0.785f;
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
	}
	else
	{
		if (_state == MOVE )
		{

			_animDirectionAngle = getAngle(_x, _y, _player->getPosition().x, _player->getPosition().y) - 0.785f;
			if (_animDirectionAngle >= 0.f && _animDirectionAngle < 1.543f)
			{
				_direction = DOWN;
			}
			else if (_animDirectionAngle >= 1.543f && _animDirectionAngle < 3.113f)
			{
				_direction = RIGHT;
			}
			else if (_animDirectionAngle >= 3.113f && _animDirectionAngle < 4.656f)
			{
				_direction = UP;
			}
			else if (_animDirectionAngle >= 4.656f && _animDirectionAngle < 6.28f ||
				_animDirectionAngle < 0 && _animDirectionAngle > -0.785f)
			{
				_direction = LEFT;
			}

		}

	}


	/*
	
	*/
}

void MushMamBoss::bossPositionTracking()
{
	if (!_rndAngleInit)
	{
		_rndAngleInit = true;
		if (getDistance(_x, _y, _player->getPosition().x, _player->getPosition().y) < 150.f)
		{
			_safeDistance = false;
		}
		else if (getDistance(_x, _y, _player->getPosition().x, _player->getPosition().y) > 150.f)
		{
			_safeDistance = true;
		}
	}

}

void MushMamBoss::rangeInPlayer(void)
{
	_angle = _animDirectionAngle + 0.785f;

	bossBulletFire();
	bossPositionTracking();
	bossDirectionTracking();
}
