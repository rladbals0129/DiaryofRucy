#pragma once
#include "Skill.h"


class IcicleSpark : public Skill
{
private:
	D2DImageInfo* _frameImage1;
	D2DImageInfo* _frameImage2;
	bool _skill1End;
public:

	HRESULT init(void);
	void shot(float x, float y, float fireX, float fireY);
	void animation(void);
	void draw(void);


	IcicleSpark() {}
	~IcicleSpark() {}

};

