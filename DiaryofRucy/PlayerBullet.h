#pragma once
#include "GameNode.h"

struct tagBullet
{
	D2DImageInfo* d2dImage;
	RECT rc;
	RECT rcCollision;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};

class Arrow : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _Boundary;

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float angle, float speed, int boundary);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);

	Arrow() {}
	~Arrow() {}
};



class MagicBall : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _Boundary;

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed, int boundary);
	void draw(void);
	void move(void);
	void d2drender(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	void removeBullet(int arrNum);
	
	MagicBall() {}
	~MagicBall() {}
};

class ChargingMagicBall : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	bool _hitSwitch;
	int _Boundary;
public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed, int _Boundary);
	void draw(void);
	void move(void);
	void d2drender(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }
	bool getHitSwith(void) { return _hitSwitch; }

	void removeBullet(int arrNum);

	ChargingMagicBall() {}
	~ChargingMagicBall() {}
};


class Sword1 : public GameNode
{
private:
	D2DImageInfo* _frameImage;
	RECT _rc;
	RECT _rcCollision;
	int _Boundary;
	int _frameCount;
	float _fireX;
	float _fireY;
	int _frameX;
	int _frameY;
	float _angle;
	bool _isAttack;

public:

	HRESULT init();
	void update(void);
	void d2drender(void);

	void fire(float fireX, float fireY, float angle, float boundary);
	void draw(void);

	RECT getRect(void) { return _rc; }
	RECT getCollisionRect(void) { return _rcCollision; }
	float getSwordAngle(void) { return _angle; }
	bool getSwordAttack(void) { return _isAttack; }

	Sword1() {}
	~Sword1() {}
};

class Sword2 : public GameNode
{
private:
	D2DImageInfo* _frameImage;
	RECT _rc;
	RECT _rcCollision;
	int _Boundary;
	int _frameCount;
	float _fireX;
	float _fireY;
	int _frameX;
	int _frameY;
	float _angle;
	bool _isAttack;

public:

	HRESULT init();
	void update(void);
	void d2drender(void);

	void fire(float fireX, float fireY, float angle, float boundary);
	void draw(void);

	RECT getRect(void) { return _rc; }
	RECT getCollisionRect(void) { return _rcCollision; }
	float getSwordAngle(void) { return _angle; }
	bool getSwordAttack(void) { return _isAttack; }

	Sword2() {}
	~Sword2() {}
};

class Sword3 : public GameNode
{
private:
	D2DImageInfo* _frameImage;
	RECT _rc;
	RECT _rcCollision;
	int _Boundary;
	int _frameCount;
	float _fireX;
	float _fireY;
	int _frameX;
	int _frameY;
	float _angle;
	bool _isAttack;

public:

	HRESULT init();
	void update(void);
	void d2drender(void);

	void fire(float fireX, float fireY, float angle, float boundary);
	void draw(void);

	RECT getRect(void) { return _rc; }
	RECT getCollisionRect(void) { return _rcCollision; }
	float getSwordAngle(void) { return _angle; }
	bool getSwordAttack(void) { return _isAttack; }

	Sword3() {}
	~Sword3() {}
};


class SlashSword : public GameNode
{
private:
	D2DImageInfo* _frameImage;
	RECT _rc;
	RECT _rcCollision;
	int _Boundary;
	int _frameCount;
	float _fireX;
	float _fireY;
	int _frameX;
	int _frameY;
	float _angle;
	bool _isAttack;

public:

	HRESULT init();
	void update(void);
	void d2drender(void);

	void fire(float fireX, float fireY, float angle, float boundary);
	void draw(void);

	RECT getRect(void) { return _rc; }
	RECT getCollisionRect(void) { return _rcCollision; }
	float getSwordAngle(void) { return _angle; }
	bool getSwordAttack(void) { return _isAttack; }
	int getFrameCount(void) { return _frameCount; }

	void setCollisionRect(POINT startLocation, POINT endLocation);


	SlashSword() {}
	~SlashSword() {}
};