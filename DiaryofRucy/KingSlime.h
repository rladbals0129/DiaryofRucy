#pragma once
#include "GameNode.h"
#include "EnemyBullets.h"
#include "BigSlime.h"
#include "Slime.h"

class Player;

class KingSlime : public GameNode
{
private:
	enum AnimDirectionSlime
	{
		DOWN, LEFT,
		RIGHT, UP
	};

	enum StateSlime
	{
		IDLE, ATTACK,
		MOVE, DIE
	};

	AnimDirectionSlime _direction;
	StateSlime _state;

private:
	Player* _player;
	EnemyBullet* _bubble;
	BubbleBullet* _bubbleBullet;
private:
	vector<BigSlime*> _vBigSlime;
	vector<BigSlime*>::iterator _viBigSlime;

	bool _slimeCreate;
	vector<Slime*> _vSlime;
	vector<Slime*>::iterator _viSlime;
	
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
	int _nextPageNum;

	//ªÁ∏¡¿Ã∆Â∆Æ
	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;
	// ≈¨∏ÆæÓ¿Ã∆Â∆Æ
	int _clearEffectFrameX;
	int _clearEffectFrameY;
	bool _clearEffectPlaying;
	int _clearEffectCount;
	bool _clear;

	bool _isHit;
	//¿Ãµø
	bool _safeDistance;
	//∞¯∞›
	int _attackCount;
	bool _canAttack;
	bool _fireAngleInit;
	float _fireAngle;

	bool _bossBgm;

private:
	int _idleFrameCount;
	int _moveFrameCount;
	int _idleFrame;
	int _moveFrame;



private:
	int _page;


private:
	void bossBulletFire();
	void bossDirectionTracking();
	void bossPositionTracking();

	void slimeBulletFire();
	void slimeDirectionTracking();
	void slimePositionTracking();


public:
	HRESULT init(POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void animation();
	void stateUpdate();
	void d2drender(void);
	void setBigSlime(POINT position);

	void collision(void);
	void rangeInPlayer(void);
	void slimeRanegeInPlayer(void);

	void playDieEffect(void);

	void resetIdleCount();
	void resetMoveCount();
	void resetIdleFrame();
	void resetMoveFrame();

	void removeBigSlime(int arrNum);
	void removeSlime(int arrNum);
	


	inline RECT getRect(void) { return _rc; }
	inline POINT getCenter(void) { return _center; }
	inline void setDmg(int dmg) 
	{
		_hp -= dmg; 
		if (_hp < 0) _hp = 0;
	}
	inline bool getDie() { return _die; }
	inline bool getIsHit() { return _isHit; }	
	inline int  getHP() { return _hp; }	
	inline int  getHPMax() { return _hpMax; }	
	inline void setIsHit(bool isHit) { _isHit = isHit; }


	inline bool getClear() { return _clear; }
	inline bool getClearEffectPlaying() { return _clearEffectPlaying; }
	inline bool getCanAttack() { return _canAttack; }
	inline void setCanAttack(bool canAttack) { _canAttack = canAttack; }


	inline void setPlayerMemoryAddress(Player* player) { _player = player; }


	inline vector<BigSlime*> getBigSlime() { return _vBigSlime; }
	inline vector<Slime*> getSlime() { return _vSlime; }
	inline EnemyBullet* getBubble() { return _bubble; }
	inline BubbleBullet* getBubbleBullet() { return _bubbleBullet; }


	KingSlime() {}
	~KingSlime() {}
};

