#pragma once
#include "GameNode.h"
#include "EnemyBullets.h"
class Player;


class MegaFlime : public GameNode
{
private:
	enum StateFlime
	{
		IDLE, ATTACK,
		ATTACK2, ATTACK3,
		DIE
	};
	
	StateFlime _state;
private:
	Player* _player;
	PoisonBullet* _poisonBullet;
	Thorn* _thorn;
	EnemyBullet* _bigBullet;
	EnemyBullet* _smallBullet;
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
	bool _canAttack;
	int _attackCount;

	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;


	bool _isHit;


private:
	int _idleFrameCount;
	int _idleFrame;

	bool _clear;
	
	bool _clearEffectPlaying;
	int _clearEffectCount;
	int _clearEffectFrameX;
	int _clearEffectFrameY;

private:

	bool _fireAngleInit;
	float _fireAngle;

	int _thornTime;
	int _thornCount;
	POINT _thornPos;

	float _attackDeleyTime;

private:
	void bossBulletFire();


public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void d2drender(void);
	//void stateUpdate();
	void animation();

	void collision(void);
	void rangeInPlayer(void);




	void resetIdleCount();
	void resetIdleFrame();

	void playDieEffect();




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


	MegaFlime() {}
	~MegaFlime() {}

};

