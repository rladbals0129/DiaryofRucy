#pragma once
#include "GameNode.h"
#include "EnemyBullets.h"

class Player;
enum AnimDirectionBigSlime
{
	PAGE2DOWN, PAGE2LEFT,
	PAGE2RIGHT, PAGE2UP
};

enum StateBigSlime
{
	PAGE2IDLE, PAGE2ATTACK,
	PAGE2MOVE, PAGE2DIE
};
class BigSlime : public GameNode
{
private:


	AnimDirectionBigSlime _direction;
	StateBigSlime _state;

private:
	EnemyBullet* _bigBullet;
private:
	

private:
	GImage* _image;
	RECT _rc;
	float _x, _y;
	POINT _center;
	float _speed;

	int _dieNum;
	int _currentFrameX;
	int _currentFrameY;
	int _frameCount;
	float _angle;
	float _animDirectionAngle;
	int _hp;
	int _hpMax;
	bool _die;
	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;
	bool _isHit;
	//이동
	bool _safeDistance;
	//공격
	int _attackCount;
	bool _canAttack;
	bool _fireAngleInit;
	float _fireAngle;

private:
	int _idleFrameCount;
	int _moveFrameCount;
	int _idleFrame;
	int _moveFrame;

public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void animation();
	void stateUpdate();
	void d2drender(void);
	void playDieEffect(void);

	void resetIdleCount();
	void resetMoveCount();
	void resetIdleFrame();
	void resetMoveFrame();


	inline RECT getRect(void) { return _rc; }
	inline POINT getCenterPos(void) { return _center; }
	inline void setDmg(int dmg) 
	{
		_hp -= dmg; 
		if (_hp < 0) _hp = 0;
	}
	inline bool getHP() { return _hp; }
	inline bool getHPMax() { return _hpMax; }
	inline bool getIsHit() { return _isHit; }
	inline void setIsHit(bool isHit) { _isHit = isHit; }
	inline bool getDie() { return _die; }
	inline bool getIsDieEffect() { return _effectPlaying; }
	int getAttackCount() { return _attackCount; }
	inline EnemyBullet* getBigBullet() { return _bigBullet; }
	inline float getAnimDirectionAngle() { return _animDirectionAngle; }
	inline float getFireAngle() { return _fireAngle; }
	inline bool getFireAngleInit() { return _fireAngleInit; }

	inline void setAngle(float angle) { _angle = angle; }
	inline void setAnimDirectionAngle(float angle) { _animDirectionAngle = angle; }
	inline void setSafeDistance(bool safeDistance) { _safeDistance = safeDistance; }
	inline void setFireAngle(float fireAngle) { _fireAngle = fireAngle; }
	inline void setFireAngleInit(bool fireAngleInit) { _fireAngleInit = fireAngleInit; }

	void setAnimDirection(AnimDirectionBigSlime direction) { _direction = direction; }
	void setState(StateBigSlime newState) { _state = newState; }
	StateBigSlime getState() { return _state; }

	BigSlime() {}
	~BigSlime() {}
};

