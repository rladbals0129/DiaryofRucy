#pragma once
#include "Enemy.h"
class Slime : public Enemy
{
private:

	int _speed;
	//bool attackInit;

	bool _slimeAttackSound;



public:

	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void d2drender(void);
	void stateUpdate();
	void animation();

	bool bulletCountFire();

	Slime(State snakeState = IDLE) {}
	~Slime() {}
};

