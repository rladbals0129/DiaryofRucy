#pragma once
#include "GameNode.h"
#define BULLETS_COUNT 4.0f
#define DELAY_DURATION 0.5f


struct tagEnemyBullet
{
	D2DImageInfo* img;
	RECT rc;
	int radius;
	int previewCnt, previewY;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	int frameCnt;
	int frameMaxCnt;
	bool fire;
	float alpha;
    int fireTime;
	bool reverse;
	float returnAngle;
	bool isDelayOver;
	bool isMoving;
	int frameX, frameY;

	float initialAngle;
	float currentAngle;
};

class EnemyBullet : public GameNode
{
private:
	vector<tagEnemyBullet> _vBullet;
	vector<tagEnemyBullet>::iterator _viBullet;

	string _imageName;
	int _bulletMax;
	//bool _rangeOver;

	std::function<void(float,float)> _bulletRemovedCallback;
	float _range;

	int _moveType;
	
public:
	HRESULT init(string imageName, int bulletMax, float range,int moveType);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float angle, float speed);
	
	void draw(void);
	void move(void);
	void move2(void);
	void removeBullet(int arrNum);

	vector<tagEnemyBullet> getBullet(void) { return _vBullet; }
	void setBulletRemovedCallback(std::function<void(float,float)> callback);
	//bool getRanegeOver(void) { return _rangeOver; }




	EnemyBullet(void) {}
	virtual ~EnemyBullet() {}
};


class PoisonBullet : public GameNode
{
private:
	vector<tagEnemyBullet> _vBullet;
	vector<tagEnemyBullet>::iterator _viBullet;

	string _imageName;
	int _bulletMax;


	float _range;

public:
	HRESULT init(string imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float angle, float speed);

	void draw(void);
	void move(void);
	void removeBullet(int arrNum);

	vector<tagEnemyBullet> getBullet(void) { return _vBullet; }


	PoisonBullet(void) {}
	virtual ~PoisonBullet() {}
};

class Thorn 
{
private:
	vector<tagEnemyBullet> _vBullet;
	vector<tagEnemyBullet>::iterator _viBullet;

	string _imageName;
	int _bulletMax;


	float _lifeTime;
	float _frameCount;
	float _range;



public:
	HRESULT init(string imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float frameMaxCnt);
	void fire(float x, float y, float angle, float radius,float frameMaxCnt);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);

	vector<tagEnemyBullet> getBullet(void) { return _vBullet; }


	Thorn(void) {}
	virtual ~Thorn() {}

};



class EspBullet : public GameNode
{
private:
	vector<tagEnemyBullet> _vBullet;
	vector<tagEnemyBullet>::iterator _viBullet;

	string _imageName;
	int _bulletMax;


	float _range;

public:
	HRESULT init(string imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);

	void updateAngle(int playerX, int playerY);


	vector<tagEnemyBullet> getBullet(void) { return _vBullet; }


	EspBullet(void) {}
	virtual ~EspBullet() {}
};


class BubbleBullet
{
private:
	vector<tagEnemyBullet> _vBullet;
	vector<tagEnemyBullet>::iterator _viBullet;

	string _imageName;
	int _bulletMax;


	float _range;

public:
	HRESULT init(string imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum);

	vector<tagEnemyBullet> getBullet(void) { return _vBullet; }


	BubbleBullet(void) {}
	virtual ~BubbleBullet() {}

};