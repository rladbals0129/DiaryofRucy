#pragma once
#include "GameNode.h"
class Statue : public GameNode
{
private:

	struct tagStatue
	{
		GImage* _objImg;
		RECT _rc;

		float _x, _y;

		int _currentFrameX;
		int _currentFrameY;
		float _worldTimeCount;

		bool _off;
	};

	int _statueTypeR;
	int _statueTypeL;

	tagStatue _statue[2];

public:
	HRESULT init(int statueTypeR, int statueTypeL);
	void release(void);
	void update(void);
	void render(void);

	void statueOff();

	bool getOff1() { return _statue[0]._off; }
	bool getOff2() { return _statue[1]._off; }

	POINT getLeftPosition() { return { (long)_statue[0]._x , (long)_statue[0]._y }; }
	POINT getRightPosition() { return { (long)_statue[1]._x , (long)_statue[1]._y }; }

	int getLeftDistanceWithPlayer() { return _statue[1]._objImg->getFrameWidth(); }
	int getRightDistanceWithPlayer() { return _statue[0]._objImg->getFrameWidth(); }

	Statue() {}
	~Statue() {}
};

