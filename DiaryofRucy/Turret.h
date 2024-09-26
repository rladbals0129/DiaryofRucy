#pragma once
#include "GameNode.h"
#include "EnemyBullets.h"

class Turret : public GameNode
{
protected:

	GImage* _image;
	RECT _rc;
	float _x, _y;
	POINT _center;

	float _fireTime;
	float _bulletFireCount;
	int _fireCount; //°ø°Ý È½¼ö

	int _hp;
	bool _lastFire;
	
	bool _die;

	EnemyBullet* _espBullet;

public:
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void d2drender(void);
	virtual bool bulletCountFire();
	virtual void draw(void);

	inline POINT getCenterPos() { return _center; }
	inline bool getLastFire(void) { return _lastFire; }
	inline RECT getRect(void) { return _rc; }
	inline POINT getPos(void) { return _center; }
	inline bool getDie() { return _die; }
	inline void setDie(bool die) { _die = die; }
	inline void setDmg(int dmg) { _hp -= dmg; }
	inline void setLastFire(bool lastFire) { _lastFire = lastFire; }

	Turret(void);
	~Turret(void) {}
};

