#pragma once
#include "GameNode.h"
#include "Turret.h"
#include "EnemyBullets.h"

class Player;


class MushMamBoss : public GameNode
{
private:
	enum AnimDirectionMushmam
	{
		DOWN, LEFT,
		RIGHT, UP
	};

	enum StateMushmam
	{
		IDLE, ATTACK,
		ATTACK2, ATTACK3,
		ATTACK4,
		MOVE, DIE
	};
	AnimDirectionMushmam _direction;
	StateMushmam _state;
private:
	Player* _player;
private:
	typedef vector<Turret*> vTurret;
	typedef vector<Turret*>::iterator viTurret;

private:
	vTurret _vMiniTurret;
	viTurret _viMiniTurret;
	vTurret _vGreenTurret;
	viTurret _viGreenTurret;
	vTurret _vPurpleTurret;
	viTurret _viPurpleTurret;
	vTurret _vMintTurret;
	viTurret _viMintTurret;


private:
	float _fireCount;			//터렛
	float _bulletFireCount;

private:
	EspBullet* _espBullet;
	EspBullet* _greenEspBullet;
	EnemyBullet* _bigBullet;
	PoisonBullet* _poisonBullet;

private:
	GImage* _image;
	RECT _rc;
	float _x, _y;
	POINT _center;
	float _speed;

	int _currentFrameX;
	int _currentFrameY;
	int _frameCount;
	float _angle;
	float _animDirectionAngle;
	int _hpMax;
	int _hp;
	bool _die;

	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;


	bool _isHit;
	//이동
	bool _safeDistance;
	//공격
	int _attackCount;
	bool _fireAngleInit;
	bool _rndAngleInit;

	float _fireAngle;

private:
	bool _canAttack;
	bool _clear;


	bool _clearEffectPlaying;
	int _clearEffectFrameX;
	int _clearEffectFrameY;
	int _clearEffectCount;


private:
	int _idleFrameCount;
	int _idleFrame;
	int _moveFrameCount;
	int _moveFrame;

private:
	void bossBulletFire();
	void bossDirectionTracking();
	void bossPositionTracking();


public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void d2drender(void);
	void stateUpdate();
	void animation();

	void collision(void);
	void rangeInPlayer(void);


	void resetIdleCount();
	void resetMoveCount();
	void resetIdleFrame();
	void resetMoveFrame();


	void playDieEffect(void);

public:
	void setMiniTurret(int x, int y);
	void setGreenTurret(int x, int y);
	void setPurpleTurret(int x, int y);
	void setMintTurret(int x, int y);

	void removeMiniTurret(int arrNum);
	void removeGreenTurret(int arrNum);
	void removePurpleTurret(int arrNum);
	void removeMintTurret(int arrNum);

	void turretBulletFire();

public:

	inline vTurret getMiniTurret() { return _vMiniTurret; }
	inline vTurret getGreenTurret() { return _vGreenTurret; }
	inline vTurret getPurpleTurret() { return _vPurpleTurret; }
	inline vTurret getMintTurret() { return _vMintTurret; }




	inline void setPlayerMemoryAddress(Player* player) { _player = player; }

	inline bool getCanAttack() { return _canAttack; }
	inline void setCanAttack(bool canAttack) { _canAttack = canAttack; }
	inline RECT getRect(void) { return _rc; }
	inline POINT getCenter(void) { return _center; }
	inline void setDmg(int dmg)
	{
		_hp -= dmg;
		if (_hp < 0) _hp = 0;
	}
	inline int getHP() { return _hp; }
	inline int getHPMax() { return _hpMax; }	
	inline bool getDie() { return _die; }
	inline bool getIsHit() { return _isHit; }
	inline void setIsHit(bool isHit) { _isHit = isHit; }
	inline bool getClear() { return _clear; }
	inline bool getClearEffectPlaying() { return _clearEffectPlaying; }
	
	
	
	MushMamBoss() {}
	~MushMamBoss() {}
};

