#pragma once
#include "GameNode.h"

class Potal : public GameNode
{
private:
	float _x, _y;
	D2DImageInfo* _d2dObjectImage;
	RECT _rcObject;
	float _frameWorldTime;
	float _frameTime;
	int _frameX;
	int _frameY;


public:
	HRESULT init();
	void release(void);
	void update(void);
	void d2drender(void);



	int getDistanceWithPlayer() { return _d2dObjectImage->frameWidth; }

	POINT getPosition() { return { (long)_x, (long)_y }; }

	Potal() {}
	~Potal() {}
};

