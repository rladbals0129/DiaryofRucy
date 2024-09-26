#include "Stdafx.h"
#include "Skill.h"
#include "EnemyManager.h"
#include "Player.h"


Skill::Skill() :
	_iconImage(nullptr),
	_name(""),
	_rc(RectMakeCenter(0, 0, 0, 0)),
	_x(0), _y(0),
	_worldTimeCount(0.0f),
	_skillCastCount(0.0f),
	_isSkillCastOn(false),
	_coolTime(0.0f),
	_isCoolTimeOn(false),
	_manaCost(0),
	_damageMultiple(0.0f),
	_frameCount(0),
	_frameX(0),
	_frameY(0),
	_isSkillShoot(false),
	_isSkillCollision(false),
	_skillCastframeX(0),
	_skillCastframeY(0)
{
}

HRESULT Skill::init(void)
{
	return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
	skillCastAnimation();
	if (!_isSkillCastOn)
	{
		animation();
		move();
	}
	coolTimeUpdate();
}


void Skill::d2drender(void)
{
	skillCastRender();
	if (!_isSkillCastOn) draw();
}

void Skill::coolTimeUpdate()
{
	if (_isCoolTimeOn)
	{
		if (_worldTimeCount + _coolTime < TIMEMANAGER->getWorldTime())
		{
			_isCoolTimeOn = false;
		}
	}
}

void Skill::skillCastAnimation(void)
{
	if (_isSkillCastOn)
	{
		if (_skillCastframeY < 2)
		{
			if (_skillCastCount + 0.07 < TIMEMANAGER->getWorldTime())
			{
				_skillCastCount = TIMEMANAGER->getWorldTime();
				_skillCastframeX++;
				if (_skillCastframeX > D2DMANAGER->findImage("스킬캐스팅")->maxFrameX)
				{
					_skillCastframeY++;
				}
			}
		}
		else
		{
			_skillCastframeX = 0;
			_skillCastframeY = 0;
			_isSkillCastOn = false;
		}
	}
}

void Skill::skillCastRender(void)
{
	if (_isSkillCastOn) D2DMANAGER->frameRender("스킬캐스팅", _fireX-100, _fireY-100, _skillCastframeX, _skillCastframeY);
}

//
//void Skill::shot(float x, float y)
//{
//
//}
//
//void Skill::shot(float x, float y, float fireX, float fireY)
//{
//}
//
//void Skill::animation(void)
//{
//}
//
//void Skill::draw(void)
//{
//}
//
//void Skill::move(void)
//{
//}
