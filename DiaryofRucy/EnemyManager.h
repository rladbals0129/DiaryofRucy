#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "EnemyBullets.h"
#include "Turret.h"

class Player;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;
private:
	vEnemy _vSnake;
	viEnemy _viSnake;
	vEnemy _vSlime;
	viEnemy _viSlime;
	vEnemy _vFlime;
	viEnemy _viFlime;
	vEnemy _vMushMam;
	viEnemy _viMushMam;
	/*
	적 객체 추가가능..
	*/
private:
	vector<Turret*> _vTurret;
	vector<Turret*>::iterator _viTurret;
private:
	Player* _player;
	EspBullet* _espBullet;
	EnemyBullet* _bigBullet;

private:
	bitset<4> _bPixelCollision;


private:
	void enemyBulletFire(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName);
	void enemyDirectionTracking(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName);
	void enemyPositionTracking(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void setSnake(int x, int y);
	void setSlime(int x, int y);
	void setFlime(int x, int y);
	void setMushMam(int x, int y);
	void setTurret(int x, int y);

	void turretBulletFire();

	void removeSnake(int arrNum);
	void removeSlime(int arrNum);
	void removeMushMam(int arrNum);
	void removeFlime(int arrNum);
	void removeTurret(int arrNum);
	
	void collision(void);
	void rangeInPlayer(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName);
	

	inline void setPlayerMemoryAddress(Player* player) { _player = player; }
	inline vEnemy getSnake() { return _vSnake; }
	inline vEnemy getSlime() { return _vSlime; }
	inline vEnemy getFlime() { return _vFlime; }
	inline vEnemy getMushMam() { return _vMushMam; }
	inline vector<Turret*> getTurret() { return _vTurret; }
	inline EspBullet* getEspBullet() { return _espBullet; }
	inline EnemyBullet* getBigBullet() { return _bigBullet; }
};

