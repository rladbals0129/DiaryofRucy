#pragma once
#include "Skill.h"


class WindScar : public Skill
{
private:
	D2DImageInfo* _frameImage;

	int _radius;
	float _angle;
	float _speed;
	float _range;
public:

	HRESULT init(void);
	void shot(float x, float y, float fireX, float fireY);
	void animation(void);
	void draw(void);
	void move(void);


	WindScar() {}
	~WindScar() {}

};

