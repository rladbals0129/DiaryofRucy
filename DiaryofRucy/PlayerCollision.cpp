#include "Stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "KingSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"



void Player::skillCollision(void)
{
	// 일반적
	if (_em != nullptr)
	{
		if (_SkillSlot[_currentSkill] != nullptr)
		{
			if (_SkillSlot[_currentSkill]->getIsSkillCollision())
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getSnake()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						if (_currentSkill == 0)
						{
							if (_em->getSnake()[j]->getIsCanHit())
							{
								_em->getSnake()[j]->setIsCanHit(false);
								_em->getSnake()[j]->setDmg(damage);

								tagDamageBox damageBox;
								damageBox.damage = damage;
								damageBox.pt = _em->getSnake()[j]->getCenterPos();
								_qDamageBox.push(damageBox);
							}
						}
						else
						{
							_em->getSnake()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getSnake()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
						}
					}
				}
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getFlime()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						if (_currentSkill == 0)
						{
							if (_em->getFlime()[j]->getIsCanHit())
							{
								_em->getFlime()[j]->setIsCanHit(false);
								_em->getFlime()[j]->setDmg(damage);

								tagDamageBox damageBox;
								damageBox.damage = damage;
								damageBox.pt = _em->getFlime()[j]->getCenterPos();
								_qDamageBox.push(damageBox);
							}
						}
						else
						{
							_em->getFlime()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getFlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
						}
					}
				}
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getMushMam()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						if (_currentSkill == 0)
						{
							if (_em->getMushMam()[j]->getIsCanHit())
							{
								_em->getMushMam()[j]->setIsCanHit(false);
								_em->getMushMam()[j]->setDmg(damage);

								tagDamageBox damageBox;
								damageBox.damage = damage;
								damageBox.pt = _em->getMushMam()[j]->getCenterPos();
								_qDamageBox.push(damageBox);
							}
						}
						else
						{
							_em->getMushMam()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getMushMam()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
						}
					}
				}
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						if (_currentSkill == 0)
						{
							if (_em->getSlime()[j]->getIsCanHit())
							{
								_em->getSlime()[j]->setIsCanHit(false);
								_em->getSlime()[j]->setDmg(damage);

								tagDamageBox damageBox;
								damageBox.damage = damage;
								damageBox.pt = _em->getSlime()[j]->getCenterPos();
								_qDamageBox.push(damageBox);
							}
						}
						else
						{
							_em->getSlime()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getSlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
						}
					}
				}
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getTurret()[j]->getRect()))
					{
						_em->getTurret()[j]->setDmg(finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple()));
					}
				}
			}

			// 스킬 불릿충돌
			if ((_currentSkill == 0) || (_currentSkill == 2))
			{
				if (_SkillSlot[_currentSkill]->getIsSkillShoot())
				{
					for (int i = 0; i < _em->getSnake().size(); i++)
					{
						for (int j = 0; j < _em->getSnake()[i]->getSmallBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getSnake()[i]->getSmallBullet()->getBullet()[j].rc))
							{
								_em->getSnake()[i]->getSmallBullet()->removeBullet(j);
								break;
							}
						}
					}

					for (int i = 0; i < _em->getSlime().size(); i++)
					{
						for (int j = 0; j < _em->getSlime()[i]->getSmallBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getSlime()[i]->getSmallBullet()->getBullet()[j].rc))
							{
								_em->getSlime()[i]->getSmallBullet()->removeBullet(j);
								break;
							}
						}
					}

					for (int i = 0; i < _em->getSlime().size(); i++)
					{
						for (int j = 0; j < _em->getSlime()[i]->getBigBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getSlime()[i]->getBigBullet()->getBullet()[j].rc))
							{
								_em->getSlime()[i]->getBigBullet()->removeBullet(j);
								break;
							}
						}
					}

					for (int i = 0; i < _em->getFlime().size(); i++)
					{
						for (int j = 0; j < _em->getFlime()[i]->getPoisonBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getFlime()[i]->getPoisonBullet()->getBullet()[j].rc))
							{
								_em->getFlime()[i]->getPoisonBullet()->removeBullet(j);
								break;
							}
						}
					}

					for (int i = 0; i < _em->getEspBullet()->getBullet().size(); i++)
					{
						for (int j = 0; j < _em->getEspBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getEspBullet()->getBullet()[j].rc))
							{
								_em->getEspBullet()->removeBullet(j);
								break;
							}
						}
					}

					for (int i = 0; i < _em->getBigBullet()->getBullet().size(); i++)
					{
						for (int j = 0; j < _em->getBigBullet()->getBullet().size(); j++)
						{
							RECT rc;
							if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_em->getBigBullet()->getBullet()[j].rc))
							{
								_em->getBigBullet()->removeBullet(j);
								break;
							}
						}
					}					
				}
			}
		}
	}

	// 보스
	if (_SkillSlot[_currentSkill] != nullptr)
	{
		if (_SkillSlot[_currentSkill]->getIsSkillCollision())
		{			
			if (_kingSlime != nullptr)
			{
				RECT rc;
				if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_kingSlime->getRect()))
				{
					int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
					_kingSlime->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getCenter();
					_qDamageBox.push(damageBox);
				}
				for (int j = 0; j < _kingSlime->getBigSlime().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_kingSlime->getBigSlime()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_kingSlime->getBigSlime()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
					}
				}
				for (int j = 0; j < _kingSlime->getSlime().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_kingSlime->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_kingSlime->getSlime()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
					}
				}
			}
			else if (_megaFlime != nullptr)
			{
				RECT rc;
				if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_megaFlime->getRect()))
				{
					int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());

					_megaFlime->setDmg(damage);

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _megaFlime->getCenter();
					_qDamageBox.push(damageBox);

				}
			}
			else if (_mushMamBoss != nullptr)
			{
				RECT rc;
				if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_mushMamBoss->getRect()))
				{
					int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
					_mushMamBoss->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getCenter();
					_qDamageBox.push(damageBox);
				}
				for (int j = 0; j < _mushMamBoss->getGreenTurret().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_mushMamBoss->getGreenTurret()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
					}
				}
				for (int j = 0; j < _mushMamBoss->getPurpleTurret().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_mushMamBoss->getPurpleTurret()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가

					}
				}
				for (int j = 0; j < _mushMamBoss->getMiniTurret().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_mushMamBoss->getMiniTurret()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
					

					}
				}
				for (int j = 0; j < _mushMamBoss->getMintTurret().size(); j++)
				{
					if (IntersectRect(&rc, &_SkillSlot[_currentSkill]->getRect(), &_mushMamBoss->getMintTurret()[j]->getRect()))
					{
						int damage = finalDamage(0, _magicDamage, 0, 0, 0, _abilityMagicDamage, _SkillSlot[_currentSkill]->getDamageMultiple());
						_mushMamBoss->getMintTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가

					}
				}
			}
		}
	}

	if (_SkillSlot[1] != nullptr)
	{
		if (_SkillSlot[1]->getIsSkillShoot() && _SkillSlot[1]->getFrameCount() < 20)
		{
			if (getDistance(
				_x, 																											//현재 x
				_y,																												//현재 y
				_ptSlashStartXY.x + 200.0f * cosf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y)), 			//목표지점 x
				_ptSlashStartXY.y + 200.0f * -sinf(getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y))) >= 10)	//목표지점 y
			{
				_image = IMAGEMANAGER->findImage("루시검공격");
				_image->setFrameX(7);
				_x += 15.0f * cosf(getAngle(_x, _y, _ptXY.x, _ptXY.y));		// x, y 업데이트	
				_y -= 15.0f * sinf(getAngle(_x, _y, _ptXY.x, _ptXY.y));		// x, y 업데이트	
				_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			}
			else
			{
				_invincible = false;
				_bBehaviorType.reset();
			}
		}
	}
}

void Player::bulletCollision(void)
{
	if (_em != nullptr)
	{
		switch (_weaponType)
		{
		case EWeaponType::NOMAL:
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSnake()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSnake()[j]->setDmg(damage);
						// SD : 무기 없을 때 타격 사운드 추가


						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSnake()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getFlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getFlime()[j]->setDmg(damage);
						// SD : 무기 없을 때 타격 사운드 추가

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getFlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getMushMam()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getMushMam()[j]->setDmg(damage);
						// SD : 무기 없을 때 타격 사운드 추가

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getMushMam()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSlime()[j]->setDmg(damage);
						// SD : 무기 없을 때 타격 사운드 추가
	
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getTurret()[j]->setDmg(damage);
						// SD : 무기 없을 때 타격 사운드 추가
			
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			break;
		case EWeaponType::SWORD:

			for (int j = 0; j < _em->getSnake().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _em->getSnake()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSnake()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
			
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSnake()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _em->getSnake()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSnake()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
			
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSnake()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _em->getSnake()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSnake()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSnake()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _em->getSnake()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSnake()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSnake()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _em->getFlime().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _em->getFlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getFlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getFlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _em->getFlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getFlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getFlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _em->getFlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getFlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getFlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _em->getFlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getFlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getFlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _em->getMushMam().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _em->getMushMam()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getMushMam()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getMushMam()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _em->getMushMam()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getMushMam()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getMushMam()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _em->getMushMam()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getMushMam()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getMushMam()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _em->getMushMam()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getMushMam()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getMushMam()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _em->getSlime().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _em->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
			
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _em->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _em->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _em->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
			
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _em->getTurret().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _em->getTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _em->getTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _em->getTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _em->getTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_em->getTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
				
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _em->getTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}

			// 1타 반사
			for (int i = 0; i < _em->getSnake().size(); i++)
			{
				for (int j = 0; j < _em->getSnake()[i]->getSmallBullet()->getBullet().size(); j++)
				{
					if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90),
						_em->getSnake()[i]->getSmallBullet()->getBullet()[j].rc, 0))
					{
						float reflexfireX = _em->getSnake()[i]->getSmallBullet()->getBullet()[j].x;
						float reflexfireY = _em->getSnake()[i]->getSmallBullet()->getBullet()[j].y;
						_magicBall->fire(reflexfireX, reflexfireY, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed,_attackBoundary);

						_em->getSnake()[i]->getSmallBullet()->removeBullet(j);
						break;
					}
				}
			}
			for (int i = 0; i < _em->getSlime().size(); i++)
			{
				for (int j = 0; j < _em->getSlime()[i]->getSmallBullet()->getBullet().size(); j++)
				{
					if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90),
						_em->getSlime()[i]->getSmallBullet()->getBullet()[j].rc, 0))
					{
						float reflexfireX = _em->getSlime()[i]->getSmallBullet()->getBullet()[j].x;
						float reflexfireY = _em->getSlime()[i]->getSmallBullet()->getBullet()[j].y;
						_magicBall->fire(reflexfireX, reflexfireY, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed, _attackBoundary);

						_em->getSlime()[i]->getSmallBullet()->removeBullet(j);
						break;
					}
				}
			}
			for (int i = 0; i < _em->getSlime().size(); i++)
			{
				for (int j = 0; j < _em->getSlime()[i]->getBigBullet()->getBullet().size(); j++)
				{
					if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90),
						_em->getSlime()[i]->getBigBullet()->getBullet()[j].rc, 0))
					{
						float reflexfireX = _em->getSlime()[i]->getBigBullet()->getBullet()[j].x;
						float reflexfireY = _em->getSlime()[i]->getBigBullet()->getBullet()[j].y;
						_magicBall->fire(reflexfireX, reflexfireY, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed,_attackBoundary);

						_em->getSlime()[i]->getBigBullet()->removeBullet(j);
						break;
					}
				}
			}
			for (int j = 0; j < _em->getEspBullet()->getBullet().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90),
					_em->getEspBullet()->getBullet()[j].rc, 0))
				{
					float reflexfireX = _em->getEspBullet()->getBullet()[j].x;
					float reflexfireY = _em->getEspBullet()->getBullet()[j].y;
					_magicBall->fire(reflexfireX, reflexfireY, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed,_attackBoundary);

					_em->getEspBullet()->removeBullet(j);
					break;
				}
			}
			for (int j = 0; j < _em->getBigBullet()->getBullet().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90),
					_em->getBigBullet()->getBullet()[j].rc, 0))
				{
					float reflexfireX = _em->getBigBullet()->getBullet()[j].x;
					float reflexfireY = _em->getBigBullet()->getBullet()[j].y;
					_magicBall->fire(reflexfireX, reflexfireY, getAngle(_x, _y, _ptXY.x, _ptXY.y), _bulletSpeed,_attackBoundary);

					_em->getBigBullet()->removeBullet(j);
					break;
				}
			}
			
			// 반사 불릿
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSnake()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSnake()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSnake()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getFlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getFlime()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getFlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getMushMam()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getMushMam()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getMushMam()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSlime()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getTurret()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			break;
		case EWeaponType::BOW:
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _em->getSnake()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_em->getSnake()[j]->setDmg(damage);
						// SD : 화살 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSnake()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _em->getFlime()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_em->getFlime()[j]->setDmg(damage);
						// SD : 화살 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getFlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _em->getMushMam()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_em->getMushMam()[j]->setDmg(damage);
						// SD : 화살 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getMushMam()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _em->getSlime()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_em->getSlime()[j]->setDmg(damage);
						// SD : 화살 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _em->getTurret()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_em->getTurret()[j]->setDmg(damage);
						// SD : 화살 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			break;
		case EWeaponType::STAFF:
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSnake()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSnake()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSnake()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getFlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getFlime()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getFlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getMushMam()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getMushMam()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getMushMam()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getSlime()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_em->getTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_em->getTurret()[j]->setDmg(damage);
						// SD : 스태프 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _em->getTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}

			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSnake().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_em->getSnake()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_em->getSnake()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getSnake()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_em->getSnake()[j]->getCenterPos().x, _em->getSnake()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getFlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_em->getFlime()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_em->getFlime()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getFlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_em->getFlime()[j]->getCenterPos().x, _em->getFlime()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getMushMam().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_em->getMushMam()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_em->getMushMam()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getMushMam()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_em->getMushMam()[j]->getCenterPos().x, _em->getMushMam()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_em->getSlime()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_em->getSlime()[j]->setDmg(damage);

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getSlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_em->getSlime()[j]->getCenterPos().x, _em->getSlime()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _em->getTurret().size(); j++)
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_em->getTurret()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							_em->getTurret()[j]->setDmg(damage);
							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _em->getTurret()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_em->getTurret()[j]->getCenterPos().x, _em->getTurret()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}

	// 보스 충돌처리
	switch (_weaponType)
	{
	case EWeaponType::SWORD:
		if (_kingSlime != nullptr)
		{
			if (_kingSlime->getHP() > 0)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _kingSlime->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->setDmg(damage);

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _kingSlime->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _kingSlime->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _kingSlime->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->setDmg(damage);
					// SD : 타격 사운드 추가

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _kingSlime->getBigSlime().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _kingSlime->getBigSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getBigSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _kingSlime->getBigSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getBigSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _kingSlime->getBigSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getBigSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _kingSlime->getBigSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getBigSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}

			}
			for (int j = 0; j < _kingSlime->getSlime().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _kingSlime->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _kingSlime->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _kingSlime->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getSlime()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _kingSlime->getSlime()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_kingSlime->getSlime()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
		}
		if (_megaFlime != nullptr)
		{
			if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _megaFlime->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_megaFlime->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _megaFlime->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
				_qHitEffect.push(hitEffect);
				
				// SD : 타격 사운드 추가
				
			}
			if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _megaFlime->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_megaFlime->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _megaFlime->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
				_qHitEffect.push(hitEffect);
				// SD : 타격 사운드 추가
				
			}
			if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _megaFlime->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_megaFlime->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _megaFlime->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
				_qHitEffect.push(hitEffect);
				// SD : 타격 사운드 추가
				
			}
			if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _megaFlime->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_megaFlime->setDmg(damage);
				// SD : 타격 사운드 추가
				

				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _megaFlime->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
				_qHitEffect.push(hitEffect);
			}
		}
		if (_mushMamBoss != nullptr)
		{
			if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_mushMamBoss->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _mushMamBoss->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
				_qHitEffect.push(hitEffect);
				// SD : 타격 사운드 추가
				
			}
			if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_mushMamBoss->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _mushMamBoss->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
				_qHitEffect.push(hitEffect);
				// SD : 타격 사운드 추가
				
			}
			if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_mushMamBoss->setDmg(damage);
				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _mushMamBoss->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
				_qHitEffect.push(hitEffect);
				// SD : 타격 사운드 추가
				
			}
			if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _mushMamBoss->getRect(), 0))
			{
				int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
				_mushMamBoss->setDmg(damage);
				// SD : 타격 사운드 추가
				

				tagDamageBox damageBox;
				damageBox.damage = damage;
				damageBox.pt = _mushMamBoss->getCenter();
				_qDamageBox.push(damageBox);

				tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
				_qHitEffect.push(hitEffect);
			}
			for (int j = 0; j < _mushMamBoss->getGreenTurret().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getGreenTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getGreenTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getGreenTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _mushMamBoss->getGreenTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _mushMamBoss->getPurpleTurret().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getPurpleTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getPurpleTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getPurpleTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
					// SD : 타격 사운드 추가
					
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _mushMamBoss->getPurpleTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _mushMamBoss->getMiniTurret().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMiniTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMiniTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMiniTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _mushMamBoss->getMiniTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
			for (int j = 0; j < _mushMamBoss->getMintTurret().size(); j++)
			{
				if (_sword1->getSwordAttack() && isOBBCollision(_sword1->getCollisionRect(), -DEGREE_RADIAN(_sword1->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMintTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMintTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword2->getSwordAttack() && isOBBCollision(_sword2->getCollisionRect(), -DEGREE_RADIAN(_sword2->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMintTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMintTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_sword3->getSwordAttack() && isOBBCollision(_sword3->getCollisionRect(), -DEGREE_RADIAN(_sword3->getSwordAngle() * 180 / PI - 90), _mushMamBoss->getMintTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMintTurret()[j]->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);
					// SD : 타격 사운드 추가
					

					tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
				if (_slashSword->getFrameCount() == 1 && isOBBCollision(_slashSword->getCollisionRect(), -getAngle(_ptSlashStartXY.x, _ptSlashStartXY.y, _ptXY.x, _ptXY.y), _mushMamBoss->getMintTurret()[j]->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_mushMamBoss->getMintTurret()[j]->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
					_qHitEffect.push(hitEffect);
				}
			}
		}
		break;

	case EWeaponType::BOW:
		if (_kingSlime != nullptr)
		{
			if (_kingSlime->getHP() > 0)
			{
				for (int i = 0; i < _arrow->getBullet().size(); i++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _kingSlime->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_kingSlime->setDmg(damage);
						// SD : 타격 사운드 추가
						
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getCenter();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getBigSlime().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _kingSlime->getBigSlime()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_kingSlime->getBigSlime()[j]->setDmg(damage);
						// SD : 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getSlime().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _kingSlime->getSlime()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_kingSlime->getSlime()[j]->setDmg(damage);
						// SD : 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
		}
		if (_megaFlime != nullptr)
		{
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _megaFlime->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_arrow->removeBullet(i);
					_megaFlime->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _megaFlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
					_qHitEffect.push(hitEffect);
					break;
				}
			}
		}
		if (_mushMamBoss != nullptr)
		{
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _mushMamBoss->getRect(), 0))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_arrow->removeBullet(i);
					_mushMamBoss->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
					_qHitEffect.push(hitEffect);
					break;
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getGreenTurret().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _mushMamBoss->getGreenTurret()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getPurpleTurret().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _mushMamBoss->getPurpleTurret()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMiniTurret().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _mushMamBoss->getMiniTurret()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _arrow->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMintTurret().size(); j++)
				{
					if (isOBBCollision(CollisionAreaResizing(_arrow->getBullet()[i].rcCollision, 0, 25), -_arrow->getBullet()[i].angle, _mushMamBoss->getMintTurret()[j]->getRect(), 0))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_arrow->removeBullet(i);
						_mushMamBoss->getMintTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
		}
		break;

	case EWeaponType::STAFF:
		if (_kingSlime != nullptr)
		{
			if (_kingSlime->getHP() > 0)
			{
				for (int i = 0; i < _magicBall->getBullet().size(); i++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_kingSlime->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_kingSlime->setDmg(damage);
						// SD : 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getCenter();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getBigSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_kingSlime->getBigSlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_kingSlime->getBigSlime()[j]->setDmg(damage);
						// SD : 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_kingSlime->getSlime()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_kingSlime->getSlime()[j]->setDmg(damage);
						// SD : 타격 사운드 추가
						

						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			if (_kingSlime->getHP() > 0)
			{
				for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_kingSlime->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_kingSlime->setDmg(damage);
							// SD : 타격 사운드 추가
							

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _kingSlime->getCenter();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_kingSlime->getCenter().x, _kingSlime->getCenter().y);
							_qHitEffect.push(hitEffect);

						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getBigSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_kingSlime->getBigSlime()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_kingSlime->getBigSlime()[j]->setDmg(damage);
							// SD : 타격 사운드 추가
							

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _kingSlime->getBigSlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_kingSlime->getBigSlime()[j]->getCenterPos().x, _kingSlime->getBigSlime()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _kingSlime->getSlime().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_kingSlime->getSlime()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_kingSlime->getSlime()[j]->setDmg(damage);
							// SD : 타격 사운드 추가
							

							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _kingSlime->getSlime()[j]->getCenterPos();
							_qDamageBox.push(damageBox);

							tagHitEffect hitEffect(_kingSlime->getSlime()[j]->getCenterPos().x, _kingSlime->getSlime()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
						}
					}
				}
			}

		}
		if (_megaFlime != nullptr)
		{
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				RECT rc;
				if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_megaFlime->getRect()))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_magicBall->removeBullet(i);
					_megaFlime->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _megaFlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
					_qHitEffect.push(hitEffect);
					break;
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				RECT rc;
				if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_megaFlime->getRect()))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_megaFlime->setDmg(damage);
					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _megaFlime->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_megaFlime->getCenter().x, _megaFlime->getCenter().y);
					_qHitEffect.push(hitEffect);

				}
			}
		}
		if (_mushMamBoss != nullptr)
		{
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				RECT rc;
				if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_mushMamBoss->getRect()))
				{
					int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
					_magicBall->removeBullet(i);
					_mushMamBoss->setDmg(damage);
					// SD : 타격 사운드 추가
					

					tagDamageBox damageBox;
					damageBox.damage = damage;
					damageBox.pt = _mushMamBoss->getCenter();
					_qDamageBox.push(damageBox);

					tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
					_qHitEffect.push(hitEffect);
					break;
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getGreenTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_mushMamBoss->getGreenTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i);
						_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						


						tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getPurpleTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_mushMamBoss->getPurpleTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i); 
						_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMiniTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_mushMamBoss->getMiniTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i); 
						_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _magicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMintTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_magicBall->getBullet()[i].rc, &_mushMamBoss->getMintTurret()[j]->getRect()))
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_magicBall->removeBullet(i); 
						_mushMamBoss->getMintTurret()[j]->setDmg(damage);
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
						_qDamageBox.push(damageBox);
						// SD : 타격 사운드 추가
						

						tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}


			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				RECT rc;
				if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_mushMamBoss->getRect()))
				{
					if (_chargingMagicBall->getHitSwith())
					{
						int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
						_mushMamBoss->setDmg(damage);
						// SD : 타격 사운드 추가
						
						tagDamageBox damageBox;
						damageBox.damage = damage;
						damageBox.pt = _mushMamBoss->getCenter();
						_qDamageBox.push(damageBox);

						tagHitEffect hitEffect(_mushMamBoss->getCenter().x, _mushMamBoss->getCenter().y);
						_qHitEffect.push(hitEffect);
						break;
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getGreenTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_mushMamBoss->getGreenTurret()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_mushMamBoss->getGreenTurret()[j]->setDmg(damage);
							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _mushMamBoss->getGreenTurret()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
							// SD : 타격 사운드 추가
							

							tagHitEffect hitEffect(_mushMamBoss->getGreenTurret()[j]->getCenterPos().x, _mushMamBoss->getGreenTurret()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
							break;
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getPurpleTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_mushMamBoss->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_mushMamBoss->getPurpleTurret()[j]->setDmg(damage);
							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _mushMamBoss->getPurpleTurret()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
							// SD : 타격 사운드 추가
							

							tagHitEffect hitEffect(_mushMamBoss->getPurpleTurret()[j]->getCenterPos().x, _mushMamBoss->getPurpleTurret()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
							break;
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMiniTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_mushMamBoss->getMiniTurret()[j]->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_mushMamBoss->getMiniTurret()[j]->setDmg(damage);
							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _mushMamBoss->getMiniTurret()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
							// SD : 타격 사운드 추가
							

							tagHitEffect hitEffect(_mushMamBoss->getMiniTurret()[j]->getCenterPos().x, _mushMamBoss->getMiniTurret()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
							break;
						}
					}
				}
			}
			for (int i = 0; i < _chargingMagicBall->getBullet().size(); i++)
			{
				for (int j = 0; j < _mushMamBoss->getMintTurret().size(); j++)
				{
					RECT rc;
					if (IntersectRect(&rc, &_chargingMagicBall->getBullet()[i].rc, &_mushMamBoss->getRect()))
					{
						if (_chargingMagicBall->getHitSwith())
						{
							int damage = finalDamage(_attackDamage, 0, 0, 0, _abilityAttackDamage, _abilityMagicDamage);
							_mushMamBoss->getMintTurret()[j]->setDmg(damage);
							tagDamageBox damageBox;
							damageBox.damage = damage;
							damageBox.pt = _mushMamBoss->getMintTurret()[j]->getCenterPos();
							_qDamageBox.push(damageBox);
							// SD : 타격 사운드 추가
							

							tagHitEffect hitEffect(_mushMamBoss->getMintTurret()[j]->getCenterPos().x, _mushMamBoss->getMintTurret()[j]->getCenterPos().y);
							_qHitEffect.push(hitEffect);
							break;
						}
					}
				}
			}

		}
		break;
	default:
		break;
	}


}

void Player::enemyCollision()
{
	if (_em != nullptr)
	{
		bool leftCollision = false;
		for (int i = 0; i < _em->getSnake().size(); i++)
		{
			if (_em->getSnake()[i]->getRect().right > _rcCollision.left && _em->getSnake()[i]->getRect().top < _y && _em->getSnake()[i]->getRect().bottom >  _y && _em->getSnake()[i]->getRect().right < _rcCollision.right) leftCollision = true;
		}
		for (int i = 0; i < _em->getSlime().size(); i++)
		{
			if (_em->getSlime()[i]->getRect().right > _rcCollision.left && _em->getSlime()[i]->getRect().top < _y && _em->getSlime()[i]->getRect().bottom >  _y && _em->getSlime()[i]->getRect().right < _rcCollision.right) leftCollision = true;
		}
		for (int i = 0; i < _em->getFlime().size(); i++)
		{
			if (_em->getFlime()[i]->getRect().right > _rcCollision.left && _em->getFlime()[i]->getRect().top < _y && _em->getFlime()[i]->getRect().bottom >  _y && _em->getFlime()[i]->getRect().right < _rcCollision.right) leftCollision = true;
		}
		for (int i = 0; i < _em->getMushMam().size(); i++)
		{
			if (_em->getMushMam()[i]->getRect().right > _rcCollision.left && _em->getMushMam()[i]->getRect().top < _y && _em->getMushMam()[i]->getRect().bottom >  _y && _em->getMushMam()[i]->getRect().right < _rcCollision.right) leftCollision = true;
		}
		if (leftCollision)
		{
			_bEnemyCollision.set(0);
			_bBehaviorType.set(STOP);
		}
		else
		{
			_bEnemyCollision.reset(0);
		}

		bool topCollision = false;
		for (int i = 0; i < _em->getSnake().size(); i++)
		{
			if (_em->getSnake()[i]->getRect().right > _x && _em->getSnake()[i]->getRect().bottom > _rcCollision.top && _em->getSnake()[i]->getRect().bottom < _rcCollision.bottom && _em->getSnake()[i]->getRect().left < _x) topCollision = true;
		}
		for (int i = 0; i < _em->getSlime().size(); i++)
		{
			if (_em->getSlime()[i]->getRect().right > _x && _em->getSlime()[i]->getRect().bottom > _rcCollision.top && _em->getSlime()[i]->getRect().bottom < _rcCollision.bottom && _em->getSlime()[i]->getRect().left < _x) topCollision = true;
		}
		for (int i = 0; i < _em->getFlime().size(); i++)
		{
			if (_em->getFlime()[i]->getRect().right > _x && _em->getFlime()[i]->getRect().bottom > _rcCollision.top && _em->getFlime()[i]->getRect().bottom < _rcCollision.bottom && _em->getFlime()[i]->getRect().left < _x) topCollision = true;
		}
		for (int i = 0; i < _em->getMushMam().size(); i++)
		{
			if (_em->getMushMam()[i]->getRect().right > _x && _em->getMushMam()[i]->getRect().bottom > _rcCollision.top && _em->getMushMam()[i]->getRect().bottom < _rcCollision.bottom && _em->getMushMam()[i]->getRect().left < _x) topCollision = true;
		}
		if (topCollision)
		{
			_bEnemyCollision.set(1);
			_bBehaviorType.set(STOP);
		}
		else
		{
			_bEnemyCollision.reset(1);
		}

		bool rightCollision = false;
		for (int i = 0; i < _em->getSnake().size(); i++)
		{
			if (_em->getSnake()[i]->getRect().left < _rcCollision.right && _em->getSnake()[i]->getRect().top < _y && _em->getSnake()[i]->getRect().bottom >  _y && _em->getSnake()[i]->getRect().left > _rcCollision.left) rightCollision = true;
		}
		for (int i = 0; i < _em->getSlime().size(); i++)
		{
			if (_em->getSlime()[i]->getRect().left < _rcCollision.right && _em->getSlime()[i]->getRect().top < _y && _em->getSlime()[i]->getRect().bottom >  _y && _em->getSlime()[i]->getRect().left > _rcCollision.left) rightCollision = true;
		}
		for (int i = 0; i < _em->getFlime().size(); i++)
		{
			if (_em->getFlime()[i]->getRect().left < _rcCollision.right && _em->getFlime()[i]->getRect().top < _y && _em->getFlime()[i]->getRect().bottom >  _y && _em->getFlime()[i]->getRect().left > _rcCollision.left) rightCollision = true;
		}
		for (int i = 0; i < _em->getMushMam().size(); i++)
		{
			if (_em->getMushMam()[i]->getRect().left < _rcCollision.right && _em->getMushMam()[i]->getRect().top < _y && _em->getMushMam()[i]->getRect().bottom >  _y && _em->getMushMam()[i]->getRect().left > _rcCollision.left) rightCollision = true;
		}
		if (rightCollision)
		{
			_bEnemyCollision.set(2);
			_bBehaviorType.set(STOP);
		}
		else
		{
			_bEnemyCollision.reset(2);
		}

		bool bottomCollision = false;
		for (int i = 0; i < _em->getSnake().size(); i++)
		{
			if (_em->getSnake()[i]->getRect().right > _x && _em->getSnake()[i]->getRect().top < _rcCollision.bottom && _em->getSnake()[i]->getRect().top > _rcCollision.top && _em->getSnake()[i]->getRect().left < _x) bottomCollision = true;
		}
		for (int i = 0; i < _em->getSlime().size(); i++)
		{
			if (_em->getSlime()[i]->getRect().right > _x && _em->getSlime()[i]->getRect().top < _rcCollision.bottom && _em->getSlime()[i]->getRect().top > _rcCollision.top && _em->getSlime()[i]->getRect().left < _x) bottomCollision = true;
		}
		for (int i = 0; i < _em->getFlime().size(); i++)
		{
			if (_em->getFlime()[i]->getRect().right > _x && _em->getFlime()[i]->getRect().top < _rcCollision.bottom && _em->getFlime()[i]->getRect().top > _rcCollision.top && _em->getFlime()[i]->getRect().left < _x) bottomCollision = true;
		}
		for (int i = 0; i < _em->getMushMam().size(); i++)
		{
			if (_em->getMushMam()[i]->getRect().right > _x && _em->getMushMam()[i]->getRect().top < _rcCollision.bottom && _em->getMushMam()[i]->getRect().top > _rcCollision.top && _em->getMushMam()[i]->getRect().left < _x) bottomCollision = true;
		}
		if (bottomCollision)
		{
			_bEnemyCollision.set(3);
			_bBehaviorType.set(STOP);
		}
		else
		{
			_bEnemyCollision.reset(3);
		}
	}
}
