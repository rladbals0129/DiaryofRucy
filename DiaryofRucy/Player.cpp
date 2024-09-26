#include "Stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "UI.h"
#include "KingSlime.h"
#include "BigSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"
#include "Explosion.h"
#include "WindScar.h"
#include "IcicleSpark.h"
#include "ThunderFlash.h"


HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->findImage("루시걷기");
	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;
	_ptXY = { 0,0 };
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_direction = ERucyDirection::DOWN;
	_avoidDirection = ERucyDirection::DOWN;
	_alpha = 255;

	_frame = 1;
	_preFrame = 0;
	_currentMoveFrameX = 0;
	_currentAvoidFrameX = 0;
	_preAvoidFrameX = 0;
	_currentAttackFrameX = 0;
	_hitFrameX = 0;
	_hitFrameY = 0;
	_run = true;
	_isCharging = false;
	_weaponSlot = true;
	_weaponType = EWeaponType::NOMAL;
	_staffGauge = 0;
	_swordCombo = 1;
	_canSlash = false;
	_canTripleShot = false;
	_avoidManaRecovery = false;
	_invincible = false;
	_damagedInvincible = false;
	_invincibilityTime = 0.0f;
	_skillCastWorldTime = 0.0f;
	_skillCastFrame = 0;
	_invincibilityCount = 0;
	_bBehaviorType.set(STOP);

	_level = 1;
	_maxExp = 100;
	_currentExp = 0; 
	_maxHp = 8;
	_maxMp = 3;
	_currentHp = _maxHp;
	_currentMp = _maxMp;
	_stemina = 100;
	_balance = 0.0f;
	_attackDamage = 10.0f;
	_attackSpeed = 100.0f;
	_magicDamage = 11.0f;
	_coolTimeReduce = 0.0f;
	_moveSpeed = 1.0f;
	_critical = 0;
	_gold = 28;

	
	_abilityAttackDamage = 0;
	_abilityMagicDamage = 0;
	_swordStack = 0;
	_bowStack = 0;
	_staffStack = 0;

	_currentSkill = 0;
	_avoidDistance = 10.0f;
	_attackBoundary = 0.0f;
	_attackRange = 400.0f;
	_bulletSpeed = 1.0f;

	
	_arrow = new Arrow;
	_arrow->init(_attackRange);
	_magicBall = new MagicBall;
	_magicBall->init(_attackRange);
	_chargingMagicBall = new ChargingMagicBall;
	_chargingMagicBall->init(_attackRange);
	_sword1 = new Sword1;
	_sword1->init();
	_sword2 = new Sword2;
	_sword2->init();
	_sword3 = new Sword3;
	_sword3->init();
	_slashSword = new SlashSword;
	_slashSword->init();
	for (int i = 0; i < 4; i++)
	{
		_SkillSlot[i] = nullptr;
	}

	setSkill(new WindScar);
	return S_OK;
}

void Player::release(void)
{
	_arrow->release();
	_magicBall->release();
	_chargingMagicBall->release();
	_sword1->release();
	_sword2->release();
	_sword3->release();
	_slashSword->release();
	for (int i = 0; i < 4; i++)
	{
		if(_SkillSlot != nullptr) _SkillSlot[i]->release();
	}

}

void Player::update(void)
{
	if (!_bBehaviorType.test(DIE))
	{
		if (!_bBehaviorType.test(DAMAGED) && !_bBehaviorType.test(SKILL))
		{
			if (!_bBehaviorType.test(AVOID) && !_bBehaviorType.test(SLASH_ATTACK))
			{
				move();
				attack();
				skillShot();
			}
			slashAttack();
			avoid();
		}
		inputKey();
		pixelCollision();
		bulletUpdate();
		skillUpdate();
		damagedAnimation();
	}
	stateUpdate();

	if (_stemina < 100 && !_bBehaviorType.test(AVOID) && !_bBehaviorType.test(SWORDATTACK) && !_bBehaviorType.test(BOWATTACK) && !_bBehaviorType.test(STAFFATTACK) && !_isCharging)
	{
		_stemina += 0.5;
	}
	if (KEYMANAGER->isStayKeyDown('U')) _currentExp += 5;
}

void Player::render(void)
{
	draw();
#pragma region 디버그용 렉트렌더
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRectMake(getMemDC(), _rcCollision);
		//for (int i = 0; i < _em->getSnake().size(); i++)
		//{
		//	for (int j = 0; j < _magicBall->getBullet().size(); j++)
		//	{
		//		DrawRectMake(getMemDC(), _em->getSnake()[i]->getRect());
		//		DrawRectMake(getMemDC(), _magicBall->getBullet()[j].rc);
		//	}
		//}
		//for (int i = 0; i < _arrow->getBullet().size(); i++)
		//{
			//DrawRectMake(getMemDC(), CollisionAreaResizing(_arrow->getBullet()[i].rc, 0, 25));
			//OBBDrawRotatedRect(getMemDC(), CollisionAreaResizing(_arrow->getBullet()[i].rc, 0, 25), -_arrow->getBullet()[i].angle);
		//}
		//if (_SkillSlot[_currentSkill] != nullptr) DrawRectMake(getMemDC(), _SkillSlot[_currentSkill]->getRect());
		//DrawRectMake(getMemDC(), _sword1->getRect());
		//DrawRectMake(getMemDC(), _sword1->getCollisionRect());
		//OBBDrawRotatedRect(getMemDC(), _sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90));
		//OBBDrawRotatedRect(getMemDC(), _sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90));
		//OBBDrawRotatedRect(getMemDC(), _sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90));
		//OBBDrawRotatedRect(getMemDC(), _sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90));

		//for (int j = 0; j < _em->getMushMam().size(); j++)
		//{
			//OBBDrawRotatedRect(getMemDC(), _em->getMushMam()[j]->getRect(), 0);
			//DrawRectMake(getMemDC(), _em->getSnake()[j]->getRect());
		//}

		//DrawRectMake(getMemDC(), RectMakeCenter(_ptSlashStartXY.x + 200.0f * cosf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y)),
		//	_ptSlashStartXY.y + 200.0f * -sinf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y)), 30, 30));


		//if(_slashSword->getFrameCount() == 1) OBBDrawRotatedRect(getMemDC(), _slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y));
		////DrawRectMake(getMemDC(), _SkillSlot[3]->getRect());
		//if(_SkillSlot[3]->getIsSkillCollision()) OBBDrawRotatedRect(getMemDC(), _SkillSlot[3]->getRect(), -getAngle(_x, _y, _ptMouse.x, _ptMouse.y));

	}	

		//for (int i = 0; i < 4; i++)
		//{
		//		DrawRectMake(getMemDC(), RectMakeCenter(
		//		_x + i * 60 * cosf(getAngle(_x, _y, _ptMouse.x, _ptMouse.y)),
		//		_y + i * 60 * -sinf(getAngle(_x, _y, _ptMouse.x, _ptMouse.y)),
		//		40, 40));
		//}
	//for (int i = 0; i < _arrow->getBullet().size(); i++)
	//{
	//	//DrawRectMake(getMemDC(), CollisionAreaResizing(_arrow->getBullet()[i].rc, 0, 25));
	//	//OBBDrawRotatedRect(getMemDC(), _arrow->getBullet()[i].rcCollision, -_arrow->getBullet()[i].angle);
	//}
#pragma endregion
}

void Player::d2drender(void)
{
	D2DMANAGER->render("그림자", _rcCollision.left, _rcCollision.top+3);
	bulletRender();
	skillRender();
	hitEffect();
	damageBoxRender();
}


float Player::finalDamage(float attackDamage,
	float magicDamage,
	float weaponAttackDamage,
	float weaponMagicDamage,
	float abilityAttackDamage,
	float abilityMagicDamage,
	float skillDamageMultiple)
{
	float finalDamage = (attackDamage + magicDamage + weaponAttackDamage + weaponMagicDamage + abilityAttackDamage + abilityMagicDamage) * skillDamageMultiple;
	if (_canSlash) finalDamage *= 1.5;
	finalDamage += RND->getFromIntTo(-5, 10);
	if (RND->getInt(100) <= _critical)
	{
		finalDamage *= 2;
	}	
	// 데미지 밸런스 조정해야함
	return finalDamage;
}

void Player::pixelCollision(void)
{
	if (_bPixelCollision.test(0)) _x+= 0.5;
	if (_bPixelCollision.test(1)) _y+= 0.5;
	if (_bPixelCollision.test(2)) _x-= 0.5;
	if (_bPixelCollision.test(3)) _y-= 0.5;
	_rcCollision = rucyCollisionAreaResizing(_rc, 80, 90);
}

void Player::move(void)
{
	enemyCollision();
	if (_bBehaviorType.test(BOWATTACK))
	{
		if (KEYMANAGER->isStayKeyDown('A') && !_bPixelCollision.test(0)) _x -= _moveSpeed;
		if (KEYMANAGER->isStayKeyDown('W') && !_bPixelCollision.test(1)) _y -= _moveSpeed;
		if (KEYMANAGER->isStayKeyDown('D') && !_bPixelCollision.test(2)) _x += _moveSpeed;
		if (KEYMANAGER->isStayKeyDown('S') && !_bPixelCollision.test(3)) _y += _moveSpeed;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	else if (!_bBehaviorType.test(STAFFATTACK) && !_bBehaviorType.test(SWORDATTACK))
	{
		if (KEYMANAGER->isStayKeyDown('W') && !_bPixelCollision.test(1) && !_bEnemyCollision.test(1))
		{
			_bBehaviorType.reset();
			_bBehaviorType.set(MOVE);
			if (_run)_y -= _moveSpeed * 3;
			else	 _y -= _moveSpeed;
			_direction = ERucyDirection::UP;
			moveAnimation();
		}
		if (KEYMANAGER->isStayKeyDown('S') && !_bPixelCollision.test(3) && !_bEnemyCollision.test(3))
		{
			_bBehaviorType.reset();
			_bBehaviorType.set(MOVE);
			if (_run) _y += _moveSpeed * 3;
			else	  _y += _moveSpeed;
			_direction = ERucyDirection::DOWN;
			moveAnimation();
		}
		if (KEYMANAGER->isStayKeyDown('A') &&!_bPixelCollision.test(0) && !_bEnemyCollision.test(0))
		{
			_bBehaviorType.reset();
			_bBehaviorType.set(MOVE);
			if (_run) _x -= _moveSpeed * 3;
			else	  _x -= _moveSpeed;
			_direction = ERucyDirection::LEFT;
			if (GetAsyncKeyState('W') & 0x8000) _direction = ERucyDirection::LEFTUP;
			if (GetAsyncKeyState('S') & 0x8000) _direction = ERucyDirection::LEFTDOWN;
			moveAnimation();
		}
		if (KEYMANAGER->isStayKeyDown('D') && !_bPixelCollision.test(2) && !_bEnemyCollision.test(2))
		{
			_bBehaviorType.reset();
			_bBehaviorType.set(MOVE);
			if (_run) _x += _moveSpeed * 3;
			else	  _x += _moveSpeed;
			_direction = ERucyDirection::RIGHT;
			if (GetAsyncKeyState('W') & 0x8000) _direction = ERucyDirection::RIGHTUP;
			if (GetAsyncKeyState('S') & 0x8000) _direction = ERucyDirection::RIGHTDOWN;
			moveAnimation();
		}
		// 이동을 안할 시 멈춤
		if (KEYMANAGER->checkMoveKeyDown('W', 'A', 'S', 'D'))
		{
			_bBehaviorType.reset();
			_bBehaviorType.set(STOP);
		}
		if (_bBehaviorType.test(STOP))
		{
			_image = IMAGEMANAGER->findImage("루시걷기");
			_image->setFrameX(1);
		}
		else if (_bBehaviorType.test(MOVE))
		{
			if (_run) _image = IMAGEMANAGER->findImage("루시달리기");
			else _image = IMAGEMANAGER->findImage("루시걷기");
		}
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

void Player::attack(void)
{
	if (_ui->getIsToggleKeyOn()) return;
	switch (_weaponType)
	{
	case EWeaponType::NOMAL:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_bBehaviorType.test(STAFFATTACK))
		{
			if (_stemina < 5) return;
			_image = IMAGEMANAGER->findImage("루시기본공격");
			_ptXY = _ptMouse;
			setAttackDirectionAngle();
			// SD : 공격 사운드 추가
			SOUNDMANAGER->play("지팡이기본공격", 10.0f);
		}
		break;
	case EWeaponType::SWORD:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_bBehaviorType.test(SWORDATTACK) && !_canSlash)
		{
			if (_stemina < 5) return;
			_image = IMAGEMANAGER->findImage("루시검공격");
			_ptXY = _ptMouse;
			setAttackDirectionAngle();
		}
		break; 
	case EWeaponType::BOW:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_bBehaviorType.test(BOWATTACK))
		{
			if (_stemina < 5) return;
			_image = IMAGEMANAGER->findImage("루시활공격");
			_ptXY = _ptMouse;
			setAttackDirectionAngle();
		}
		break;
	case EWeaponType::STAFF:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_bBehaviorType.test(STAFFATTACK))
		{
			if (_stemina < 5) return;
			if (_staffGauge < 100)
			{
				_isCharging = true;
				_staffGauge++;
				_stemina -= 0.1;
				if (_staffGauge == 10)
				{
					SOUNDMANAGER->play("지팡이차지", 0.1f);
				}
				else if (_staffGauge == 60)
				{
					SOUNDMANAGER->play("지팡이차지", 0.1f);
				}
			}
		}	
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && !_bBehaviorType.test(STAFFATTACK))
		{
			_isCharging = false;
			if (_staffGauge < 100) _image = IMAGEMANAGER->findImage("루시기본공격");
			else _image = IMAGEMANAGER->findImage("루시차지샷");
			_ptXY = _ptMouse;
			setAttackDirectionAngle();
			// SD : 공격 사운드 추가
			SOUNDMANAGER->play("지팡이기본공격", 0.1f);
		}
		break;
	default:
		break;
	}
	attackAnimation();
}

void Player::slashAttack(void)
{
	if (_weaponType == EWeaponType::SWORD)
	{
		if (_canSlash && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_image = IMAGEMANAGER->findImage("루시검공격");
			_ptXY = _ptMouse;			     // 목표지점방향을 구할 좌표
			_ptSlashStartXY = getPosition(); // 시작위치
			setAttackDirectionAngle();
			_currentAvoidFrameX = 0;
			_vAvoidAfterImage.clear();
			_invincible = true;
			_slashSword->setCollisionRect(_ptSlashStartXY, _ptXY);
			// SD : 대쉬공격 사운드 추가 (검 회피 후 돌진하는 특수공격 사운드)
			SOUNDMANAGER->play("회피공격", 10.0f);

		}
		if (_bBehaviorType.test(SLASH_ATTACK))
		{
			// 회피 시 setCanSlash 해줘야함 
			if (getDistance(
				_x, 																											//현재 x
				_y,																												//현재 y
				_ptSlashStartXY.x + 200.0f * cosf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y)), 			//목표지점 x
				_ptSlashStartXY.y + 200.0f * -sinf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y))) >= 10)	//목표지점 y
			{
				_image->setFrameX(7);
				_x += 15.0f * cosf(getAngle(_x, _y, _ptXY.x, _ptXY.y));		// x, y 업데이트	
				_y -= 15.0f * sinf(getAngle(_x, _y, _ptXY.x, _ptXY.y));		// x, y 업데이트	
				_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
				_slashSword->fire(_x, _y, getAngle(_ptXY.x, _ptXY.y, _ptSlashStartXY.x, _ptSlashStartXY.y), _attackBoundary);
			}
			else
			{
				_invincible = false;
				_canSlash = false;
				_bBehaviorType.reset();
			}
		}
	}
}

void Player::skillUpdate(void)
{
	skillCast();
	skillCollision();
	for (int i = 0; i < 4; i++)
	{
		if (_SkillSlot[i] != nullptr) _SkillSlot[i]->update();
	}
}

void Player::skillRender(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (_SkillSlot[i] != nullptr)
		{
			_SkillSlot[i]->d2drender();
		}
	}
}

void Player::skillShot(void)
{
	if (_SkillSlot[_currentSkill] != nullptr)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			if (_SkillSlot[_currentSkill]->getIsCoolTimeOn() || _currentMp < _SkillSlot[_currentSkill]->getManaCost()) return;
			_currentMp -= _SkillSlot[_currentSkill]->getManaCost();
			setAttackDirectionAngle();
			if (!_SkillSlot[_currentSkill]->getIsSkillShoot())
			{
				_SkillSlot[_currentSkill]->setSkillCast(true);
				_SkillSlot[_currentSkill]->shot(_ptMouse.x, _ptMouse.y, _x, _y);
			}
			_ptXY = _ptMouse;
			_ptSlashStartXY = getPosition();
			_bBehaviorType.reset();
			_bBehaviorType.set(SKILL);
			_invincibilityTime = TIMEMANAGER->getWorldTime();
			_skillCastWorldTime = TIMEMANAGER->getWorldTime();
			// SD : 스킬 사용 전 효과음(삥~ 하는 소리)
			SOUNDMANAGER->play("스킬캐스팅", 0.1f);
		}
	}
}

void Player::skillCast(void)
{
	if (_bBehaviorType.test(SKILL))
	{
		invincibilityTimer(0.5);
		_image = IMAGEMANAGER->findImage("루시검공격");
		if (_skillCastWorldTime + 0.5 > TIMEMANAGER->getWorldTime())
		{
			_currentAttackFrameX = 7;
			_image->setFrameX(_currentAttackFrameX);
		}
		else
		{
			_SkillSlot[_currentSkill]->setSkillCast(false);
			_bBehaviorType.reset();
			if (_currentSkill == 1)
			{
				_image = IMAGEMANAGER->findImage("루시검공격");
				_ptXY = _ptMouse;
				_ptSlashStartXY = getPosition();
				_currentAvoidFrameX = 0;
				_vAvoidAfterImage.clear();
				_invincible = true;
			}
		}
	}
}

void Player::avoid(void)
{
	if (!_bBehaviorType.test(AVOID))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//_canSlash = true;
			//_canTripleShot = true;
			_stemina -= 10;
			_invincibilityTime = TIMEMANAGER->getWorldTime();
			_bBehaviorType.reset();
			_bBehaviorType.set(AVOID);
			_image = IMAGEMANAGER->findImage("루시회피");
			_currentMoveFrameX = 0;
			// SD : 저스트회피 사운드 추가
			SOUNDMANAGER->play("회피", 10.0f);
		}
	}
	else
	{
		avoidAnimation();
		invincibilityTimer(0.4);
		if (_bPixelCollision.test(0)) _x += 5;
		if (_bPixelCollision.test(1)) _y += 5;
		if (_bPixelCollision.test(2)) _x -= 5;
		if (_bPixelCollision.test(3)) _y -= 5;
	}
}

void Player::invincibilityTimer(float time)
{
	if (_invincibilityTime + time >= TIMEMANAGER->getWorldTime())
	{
		_invincible = true;
	}
	else
	{
		_invincibilityTime = 0;
		_invincible = false;
		_damagedInvincible = false;
	}
}

void Player::bulletUpdate(void)
{
	_arrow->update();
	_magicBall->update();
	_chargingMagicBall->update();
	_sword1->update();
	_sword2->update();
	_sword3->update();
	_slashSword->update();
	bulletCollision();

}

void Player::bulletRender(void)
{
	if (_weaponType == EWeaponType::BOW)
	{
		_arrow->d2drender();
	}
	else if (_weaponType == EWeaponType::STAFF || _weaponType == EWeaponType::NOMAL)
	{	
		_magicBall->d2drender();
		_chargingMagicBall->d2drender();
	}
	else if (_weaponType == EWeaponType::SWORD)
	{
		if(_sword1->getSwordAttack()) _sword1->d2drender();
		if(_sword2->getSwordAttack()) _sword2->d2drender();
		if(_sword3->getSwordAttack()) _sword3->d2drender();
		if(_slashSword->getSwordAttack()) _slashSword->d2drender();
		_magicBall->d2drender();
	}
}

void Player::moveAnimation(void)
{
	int changeFrame;
	if (_run) changeFrame = 120;
	else changeFrame = 200;
	if (changeFrame + _frame <= GetTickCount64())
	{
		_frame = GetTickCount64();
		_currentMoveFrameX++;
		
		// SD : 발자국 소리 추가
		int footWalk = RND->getInt(4);
		_runSoundCnt++;
		if (_runSoundCnt % 2 == 0)
		{

			switch (footWalk)
			{
			case 0:
				SOUNDMANAGER->play("달리기1", 0.1f);
				break;
			case 1:
				SOUNDMANAGER->play("달리기2", 0.1f);
				break;
			case 2:
				SOUNDMANAGER->play("달리기3", 0.1f);
				break;
			case 3:
				SOUNDMANAGER->play("달리기4", 0.1f);
				break;
			}
			_runSoundCnt = 0;
		}
		if (_image->getMaxFrameX() < _currentMoveFrameX)
		{
			_currentMoveFrameX = 0;
		}
		_image->setFrameX(_currentMoveFrameX);
	}
}

void Player::attackAnimation(void)
{
	if (_bBehaviorType.test(STAFFATTACK))
	{
		float correction;
		if (_staffGauge == 100) correction = 100;
		else correction = 1;
		if (_attackSpeed + _frame + correction <= GetTickCount64())
		{
			if (_currentAttackFrameX <= _image->getMaxFrameX())
			{
				_frame = GetTickCount64();
				_currentAttackFrameX++;
				_image->setFrameX(_currentAttackFrameX);
				if (_currentAttackFrameX >= _image->getMaxFrameX())
				{
					_stemina -= 2;
					if (_staffGauge < 100) _magicBall->fire(_x, _y, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed, _attackBoundary);
					else _chargingMagicBall->fire(_x, _y, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed, _attackBoundary);
					_bBehaviorType.reset(STAFFATTACK);
					_staffGauge = 0;
				}
			}
		}
	}
	else if (_bBehaviorType.test(BOWATTACK))
	{
		if (_attackSpeed + _frame <= GetTickCount64())
		{
			if (_currentAttackFrameX <= _image->getMaxFrameX())
			{
				_frame = GetTickCount64();
				_image->setFrameX(_currentAttackFrameX);
				_currentAttackFrameX++;
				if (KEYMANAGER->checkMoveKeyDown('W', 'A', 'S', 'D')) _image->setFrameX(1);
				if (_image->getMaxFrameX() < _currentAttackFrameX)
				{
					// SD : 활공격
					SOUNDMANAGER->play("활시위소리", 0.3f);
					_stemina -= 2;
					_arrow->fire(_x, _y, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed, _attackBoundary);
					if (_canTripleShot)
					{
						_arrow->fire(_x, _y, getAngle(_x, _y, _ptXY.x, _ptXY.y)-0.2, _bulletSpeed,_attackBoundary);
						_arrow->fire(_x, _y, getAngle(_x, _y, _ptXY.x, _ptXY.y)+0.2, _bulletSpeed,_attackBoundary);
						_canTripleShot = false;
					}
					_bBehaviorType.reset(BOWATTACK);
					_currentAttackFrameX = 0;
				}
			}
		}
	}
	else if (_bBehaviorType.test(SWORDATTACK))
	{
		int attackSound = 0;
		if (_currentAttackFrameX == 1)
		{
			_sword1->fire(_x, _y, getAngle(_ptXY.x, _ptXY.y, _x, _y), _attackBoundary);
			attackSound = 1;
		}
		else if (_currentAttackFrameX == 4)
		{
			_sword2->fire(_x, _y, getAngle(_ptXY.x, _ptXY.y, _x, _y), _attackBoundary);
			attackSound = 2;
		}
		else if (_currentAttackFrameX == 7)
		{
			_sword3->fire(_x, _y, getAngle(_ptXY.x, _ptXY.y, _x, _y), _attackBoundary);
			attackSound = 3;
		}
		if (_attackSpeed + _frame <= GetTickCount64())
		{
			// 공격시 이동
			_y -= 2.5f * sinf(getAngle(_x, _y, _ptMouse.x, _ptMouse.y));
			_x += 2.5f * cosf(getAngle(_x, _y, _ptMouse.x, _ptMouse.y));
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			if (_currentAttackFrameX <= _image->getMaxFrameX())
			{
				// SD : 공격 사운드 추가
				if (_currentAttackFrameX == 0) SOUNDMANAGER->play("검1타", 0.5f);
				else if (_currentAttackFrameX == 3) SOUNDMANAGER->play("검3타", 0.5f);
				else if (_currentAttackFrameX == 6)SOUNDMANAGER->play("검5타", 0.5f);

				_frame = GetTickCount64();
				_currentAttackFrameX++;
				_image->setFrameX(_currentAttackFrameX);

				if (_currentAttackFrameX % 3 == 0)
				{
					if (_stemina < 5)
					{
						_bBehaviorType.reset(SWORDATTACK);
						return;
					}
					_ptXY = _ptMouse;
					_swordCombo++;
					_stemina -= 3;
					float attackDirection = 135 - (180 * (getAngle(_x, _y, _ptMouse.x, _ptMouse.y)) / PI);
					for (int i = 0; i <= 7; i++)
					{
						if (attackDirection < 0) attackDirection += 360;
						if (getAbsRange((45 * i), 22.5, attackDirection))
						{
							_direction = (ERucyDirection)i;
							break;
						}
					}
					if ((!GetAsyncKeyState(VK_LBUTTON) & 0x8001) || _currentAttackFrameX == 9)
					{
						_bBehaviorType.reset(SWORDATTACK);
						_swordCombo = 1;
					}
				}
			}
		}
	}
}

void Player::avoidAnimation(void)
{
	if (GetAsyncKeyState('W') & 0x8001) _avoidDirection = ERucyDirection::UP;
	if (GetAsyncKeyState('S') & 0x8001) _avoidDirection = ERucyDirection::DOWN;
	if (GetAsyncKeyState('A') & 0x8001)
	{
		_avoidDirection = ERucyDirection::LEFT;
		if (GetAsyncKeyState('W') & 0x8001) _avoidDirection = ERucyDirection::LEFTUP;
		if (GetAsyncKeyState('S') & 0x8001) _avoidDirection = ERucyDirection::LEFTDOWN;
	}
	if (GetAsyncKeyState('D') & 0x8001)
	{
		_avoidDirection = ERucyDirection::RIGHT;
		if (GetAsyncKeyState('W') & 0x8001) _avoidDirection = ERucyDirection::RIGHTUP;
		if (GetAsyncKeyState('S') & 0x8001) _avoidDirection = ERucyDirection::RIGHTDOWN;
	}
	if (_bBehaviorType.test(AVOID))
	{
		int avoidDirection = ((int)_avoidDirection + 5) % 8;
		_x += cosf(DEGREE_RADIAN((float)avoidDirection * 45.0f)) * 4.0f;
		_y += sinf(DEGREE_RADIAN((float)avoidDirection * 45.0f)) * 4.0f;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		if (70 + _frame <= GetTickCount64())
		{
			_frame = GetTickCount64();
			_currentAvoidFrameX++;
			if (_image->getMaxFrameX()+1 < _currentAvoidFrameX)
			{
				_canSlash = false;
				_currentAvoidFrameX = 0;
				_bBehaviorType.reset();
				if (_image->getMaxFrameX()-1 == _currentAvoidFrameX) _vAvoidAfterImage.clear();
			}
			_image->setFrameX(_currentAvoidFrameX);

			tagAvoidAfterImage vAvoidAfterImage;
			vAvoidAfterImage.frameX = _currentAvoidFrameX;
			vAvoidAfterImage.rc = _rc;
			vAvoidAfterImage.time = TIMEMANAGER->getWorldTime();
			_vAvoidAfterImage.push_back(vAvoidAfterImage);
		}

	}
}

void Player::damagedAnimation(void)
{
	if (_bBehaviorType.test(DAMAGED))
	{
		IMAGEMANAGER->findImage("루시피격")->setFrameX(_image->getFrameX());
		_image = IMAGEMANAGER->findImage("루시피격");

		int damagedDirection = ((int)_direction + 5) % 8;
		_x -= cosf(DEGREE_RADIAN((float)damagedDirection * 45.0f)) *0.5;
		_y -= sinf(DEGREE_RADIAN((float)damagedDirection * 45.0f)) *0.5;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	if (_damagedInvincible)
	{
		invincibilityTimer(2);
		if (_invincibilityTime + 0.3 <= TIMEMANAGER->getWorldTime()) _bBehaviorType.reset(DAMAGED);
		_invincibilityCount++;
		if (_invincibilityCount % 8 < 4) _alpha = 40;
		else _alpha = 255;
	}
	else
	{
		_alpha = 255;
	}
}

void Player::draw(void)
{
	// 플레이어 렌더
	_image->frameAlphaRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), (int)_direction, _alpha);
	if (_bBehaviorType.test(DIE)) _image->render(getMemDC(), _rc.left, _rc.top);
	// 회피 렌더 + 잔상효과
	_viAvoidAfterImage = _vAvoidAfterImage.begin();
	for (; _viAvoidAfterImage != _vAvoidAfterImage.end(); ++_viAvoidAfterImage)
	{
		if (_viAvoidAfterImage->time + 0.2 > TIMEMANAGER->getWorldTime())
		{
			IMAGEMANAGER->frameAlphaRender("루시회피", getMemDC(), _viAvoidAfterImage->rc.left, _viAvoidAfterImage->rc.top,
				_viAvoidAfterImage->frameX, (int)_avoidDirection, 100);
		}
	}

}

void Player::inputKey(void)
{
	// 달리기 / 걷기
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		if (_run)
		{
			_image = IMAGEMANAGER->findImage("루시걷기");
			_run = false;
		}
		else
		{
			_image = IMAGEMANAGER->findImage("루시달리기");
			_run = true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (_weaponSlot) _weaponSlot = false;
		else _weaponSlot = true;
		if (_weaponType == EWeaponType::NOMAL)
		{
			_weaponType = EWeaponType::SWORD;
		}
		else if (_weaponType == EWeaponType::SWORD)
		{
			_weaponType = EWeaponType::BOW;
		}
		else if (_weaponType == EWeaponType::BOW)
		{
			_weaponType = EWeaponType::STAFF;
		}
		else if (_weaponType == EWeaponType::STAFF)
		{
			_weaponType = EWeaponType::NOMAL;
		}
	}


	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		if (_SkillSlot[0] != nullptr)
		{
			_currentSkill = 0; 
		}
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		if (_SkillSlot[1] != nullptr)
		{
			_currentSkill = 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		if (_SkillSlot[2] != nullptr)
		{
			_currentSkill = 2;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		if (_SkillSlot[3] != nullptr)
		{
			_currentSkill = 3;
		}
	}
}

void Player::setAttackDirectionAngle(void)
{
	_currentAttackFrameX = 0;
	_frame = GetTickCount64();
	_image->setFrameX(_currentAttackFrameX);
	_bBehaviorType.reset();
	switch (_weaponType)
	{
	case EWeaponType::NOMAL:
		_bBehaviorType.set(STAFFATTACK);
		break;
	case EWeaponType::SWORD:
		if(!_canSlash) _bBehaviorType.set(SWORDATTACK);
		else if(_canSlash) _bBehaviorType.set(SLASH_ATTACK);
		break;
	case EWeaponType::BOW:
		_image->setFrameX(1);
		_bBehaviorType.set(BOWATTACK);
		break;
	case EWeaponType::STAFF:
		_bBehaviorType.set(STAFFATTACK);
		break;
	default:
		break;
	}
	float attackDirection = 135 - (180 * (getAngle(_x, _y, _ptMouse.x, _ptMouse.y)) / PI);
	for (int i = 0; i <= 7; i++)
	{
		if (attackDirection < 0) attackDirection += 360;
		if (getAbsRange((45 * i), 22.5, attackDirection))
		{
			_direction = (ERucyDirection)i;
			break;
		}
	}
}

void Player::stateUpdate(void)
{
	// 레벨업
	if (_currentExp >= 100)
	{
		_currentExp -= 100;
		_level++;
		_maxHp++;
		_maxMp++;
		_currentHp = _maxHp;
		_currentMp = _maxMp;

		SOUNDMANAGER->play("레벨업", 0.1f);

		switch (_level)
		{
		case 2:
			setSkill(new ThunderFlash);
			break;
		case 3:
			setSkill(new IcicleSpark);
			break;
		case 4:
			setSkill(new Explosion);
			break;
		default:
			break;
		}
	}
	// 피격시 스택초기화
	if (_bBehaviorType.test(DAMAGED))
	{
		_swordStack = 0;
		_bowStack = 0;
		_staffStack = 0;
	}
	// 회피상태 아닐경우 회피 마나회복 불값 초기화
	if (!_bBehaviorType.test(AVOID))
	{
		_avoidManaRecovery = false;
	}
	//죽음처리
	if (_bBehaviorType.test(DIE))
	{
		cout << "사망?" << endl;
		_image = IMAGEMANAGER->findImage("루시사망");
		//IMAGEMANAGER->fadeOut();

	}
}

void Player::damageBoxRender(void)
{
	for (int i = 0; i < _qDamageBox.size(); i++)
	{
		// 프론트 가져오기
		tagDamageBox damageBox = _qDamageBox.front();
		_qDamageBox.pop();

		//데미지표기 올리기
		damageBox.pt.y--;
		damageBox.count--;

		//렌더
		if (damageBox.damage < 10)
		{
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x, damageBox.pt.y - 30, damageBox.damage, 0);
		}
		else if (damageBox.damage < 100)
		{
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x-10, damageBox.pt.y - 30, damageBox.damage/10, 0);
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x+10, damageBox.pt.y - 30, damageBox.damage%10, 0);
		}
		else
		{
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x - 17, damageBox.pt.y - 30, damageBox.damage / 100, 0);
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x     , damageBox.pt.y - 30, damageBox.damage % 100 / 10, 0);
			D2DMANAGER->frameRender("대미지표기넘버", damageBox.pt.x + 17, damageBox.pt.y - 30, damageBox.damage % 10, 0);
		}

		if (damageBox.count > 0)
		{
			_qDamageBox.push(damageBox);
		}

	}
}

void Player::hitEffect(void)
{
	for (int i = 0; i < _qHitEffect.size(); i++)
	{
		// 프론트 가져오기
		tagHitEffect hitEffect = _qHitEffect.front();
		_qHitEffect.pop();

		// 애니메이션
		if (hitEffect.worldTime + 0.01 < TIMEMANAGER->getWorldTime())
		{
			hitEffect.worldTime = TIMEMANAGER->getWorldTime();
			hitEffect.frameX++;
			if (hitEffect.frameX > D2DMANAGER->findImage("히트이펙트")->maxFrameX)
			{
				hitEffect.frameX = 0;
				hitEffect.frameY++;
			}
		}
		//렌더
		D2DMANAGER->frameRender("히트이펙트", hitEffect.rc.left, hitEffect.rc.top, hitEffect.frameX, hitEffect.frameY);

		//다시추가 애니메이션 완료 후에는 삭제
		if (hitEffect.frameY < D2DMANAGER->findImage("히트이펙트")->maxFrameY)
		{
			_qHitEffect.push(hitEffect);
		}
	}	
}

void Player::abilityIncrease(void)
{
	_maxHp += _vAbillity.back().getHpIncrease();
	_maxMp += _vAbillity.back().getMpIncrease();
	_attackSpeed -= _vAbillity.back().getAttackSpeedIncerease();
	_abilityAttackDamage += _vAbillity.back().getAttackDamageIncerease();
	_abilityMagicDamage += _vAbillity.back().getMagicDamageIncerease();
	_attackBoundary += _vAbillity.back().getAttackBoundaryIncerease();
}


