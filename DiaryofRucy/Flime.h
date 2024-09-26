#pragma once
#include "Enemy.h"
class Flime : public Enemy
{
private:
	//SnakeState _snakeState;
	int _speed;
	bool attackInit;

	int _thornTime;
	int _thornCount;




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

	Flime(State snakeState = IDLE) {}
	~Flime() {}
};

