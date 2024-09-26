#pragma once
#include "Skill.h"

// obb충돌 만들고생각해보기

class ThunderFlash : public Skill
{
private:
	D2DImageInfo* _frameImage;
	RECT _rcThunder[4];
	int _thunderFrameCount[4];
	int _frameX[4];
	int _frameY[4];



	float _angle;
	float _speed;
	float _range;

	bitset<4> _bThunderFire;

public:

	HRESULT init(void);
	void shot(float x, float y, float fireX, float fireY);
	void animation(void);
	void draw(void);

	ThunderFlash() {}
	~ThunderFlash() {}

};

