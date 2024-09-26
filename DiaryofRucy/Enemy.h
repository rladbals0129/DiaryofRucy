#pragma once
#include "GameNode.h"
#include "EnemyBullets.h"

namespace enemyAnimDirection
{
	enum AnimDirection
	{
		DOWN, LEFT,
		RIGHT, UP
	};

}

namespace enemyState
{
	enum State
	{
		IDLE, ATTACK,
		ATTACK2, ATTACK3,
		MOVE, DIE
	};
}

using namespace enemyAnimDirection;
using namespace enemyState;
class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;
	AnimDirection _direction;
	State _state;
	int _currentFrameX;
	int _currentFrameY;
	int _frameCount;




	float _x, _y;
	
	float _fireCount;
	float _bulletFireCount;

	float _angle;
	float _startAngle;

	float _animDirectionAngle;

	int _hp;
	bool _die;

	POINT _center;
	bool _safeDistance;


	//bool _attackReady; //사정거리 안에있으면 공격
	int _attackCount;
	
protected:
	//이펙트
	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;

protected:
	//상태변경변수
	int _idleFrameCount;
	int _moveFrameCount;
	int _rndIdleFrame;
	int _rndMoveFrame;
	bool _rndAngleInit;

	float _rndRandomAngle;
	bool _canAttack;
	
	bool _isCanHit;


	bool _createTurret;
	

protected:
	//공격관련
	EnemyBullet* _smallBullet;
	EnemyBullet* _bigBullet;
	PoisonBullet* _poisonBullet;
	Thorn* _thorn;


	float _fireAngle;
	bool _fireAngleInit;
	bool _dieSound;

	POINT _thornPos;


	
public:

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void d2drender(void);

	virtual void stateUpdate(void);
	virtual void draw(void);
	virtual void animation(void);
	virtual bool bulletCountFire(void);

	void resetIdleCount();
	void resetMoveCount();

	void resetRndIdleFrame();
	void resetRndMoveFrame();
	//void resetAttackTime();



	inline RECT getRect(void) { return _rc; }
	inline bool getDie() { return _die; }
	inline float getAnimDirectionAngle() { return _animDirectionAngle; }
	//inline float getAttackDistance() { return _attackReady; }
	int getAttackCount() { return _attackCount; }
	inline POINT getCenterPos() { return _center; }

	inline bool getDirectionAngleRndInit() { return _rndAngleInit; }
	inline float getRndRandomAngle() { return _rndRandomAngle; }
	inline float getFireAngle() { return _fireAngle; }
	inline bool getFireAngleInit() { return _fireAngleInit; }
	inline bool getCanAttack() { return _canAttack; }
	inline POINT getThornPos() { return _thornPos; }
	inline bool getIsCanHit() { return _isCanHit; }
	inline bool getCreateTurret() { return _createTurret; }

	inline EnemyBullet* getSmallBullet() { return _smallBullet; }
	inline EnemyBullet* getBigBullet() { return _bigBullet; }
	//inline EnemyBullet* getEspBullet() { return _espBullet; }
	inline PoisonBullet* getPoisonBullet() { return _poisonBullet; }
	inline Thorn* getThorn() { return _thorn; }


	//inline void setAttackDistance(bool attackReady) { _attackReady = attackReady; }
	inline void setDmg(int damage) 
	{ 
		_hp -= damage;
		SOUNDMANAGER->play("몬스터피격음", 0.1f);
	}
	inline void setAngle(float angle) { _angle = angle; }
	inline void setAnimDirectionAngle(float angle) { _animDirectionAngle = angle; }
	inline void setSafeDistance(bool safeDistance) { _safeDistance = safeDistance; }
	inline void setDirectionAngleRndInit(bool rndAngleInit) { _rndAngleInit = rndAngleInit; }
	inline void setRndRandomAngle(float rndRandomAngle) { _rndRandomAngle = rndRandomAngle; }
	inline void setFireAngle(float fireAngle) { _fireAngle = fireAngle; }
	inline void setFireAngleInit(bool fireAngleInit) { _fireAngleInit = fireAngleInit; }
	inline void setCanAttack(bool canAttack) { _canAttack = canAttack; }
	inline void setThornPos(POINT thornPos) { _thornPos = thornPos; }
	inline void setIsCanHit(bool isHit) { _isCanHit = isHit; }
	inline void setCreateTurret(bool createTurret) { _createTurret = createTurret; }
	void playDieEffect();

	void setAnimDirection(AnimDirection direction) { _direction = direction; }
	void setState(State newState) { _state = newState; }
	State getState() { return _state; }

	

	Enemy(void);
	~Enemy(void) {};


};

