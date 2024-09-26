#pragma once
#include "GameNode.h"

class Skill : public GameNode
{
protected:
	D2DImageInfo* _iconImage;
	// 프레임 이미지는 하위 클래스에서 생성
	string _name;
	RECT _rc;

	float _x, _y;
	float _fireX, _fireY;
	float _worldTimeCount;
	float _skillCastCount;
	bool _isSkillCastOn;
	float _coolTime;
	bool _isCoolTimeOn;
	int _manaCost;
	float _damageMultiple;
	bool _isSkillShoot;
	bool _isSkillCollision;

	int _frameCount;
	int	  _frameX;
	int	  _frameY;

	int	  _skillCastframeX;
	int	  _skillCastframeY;
public:
	virtual HRESULT init(void);
	void release(void);
	void update(void);
	void d2drender(void);

	void coolTimeUpdate();
	void skillCastAnimation(void);
	void skillCastRender(void);

	virtual void shot(float x, float y) {}
	virtual void shot(float x, float y, float fireX, float fireY) {}
	virtual void animation(void) {}
	virtual void draw(void) {}
	virtual void move(void) {}


	D2DImageInfo* getIconImage(void) { return this->_iconImage; }
	RECT getRect(void) { return this->_rc; }
	float getCoolTime(void) { return _worldTimeCount + _coolTime - TIMEMANAGER->getWorldTime(); }
	bool getIsCoolTimeOn(void) { return this->_isCoolTimeOn; }
	float getDamageMultiple(void) { return this->_damageMultiple; }
	int getManaCost(void) { return this->_manaCost; }
	bool getIsSkillShoot(void) { return this->_isSkillShoot; }
	bool getIsSkillCollision(void) { return this->_isSkillCollision; }
	int getFrameCount(void) { return this->_frameCount; }
	bool getSkillCast(void) { return this->_isSkillCastOn; }

	void setSkillCast(bool state) 
	{ 
		this->_isSkillCastOn = state; 
		_skillCastCount = TIMEMANAGER->getWorldTime();
	}


	Skill();
	virtual ~Skill() {}
};

