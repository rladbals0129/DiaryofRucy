#pragma once
#include "Map.h"


class StartMap : public Map
{
private:

	D2DImageInfo* _d2dObjectImage;
	RECT _rcObject;
	float _frameWorldTime;
	float _frameTime;

	bool _startImage;
	float _startImageAlpha;
public:
	HRESULT vInit(void);
	void objectUpdate(void);
	void d2dObjectRender(void);




	StartMap() {}
	~StartMap() {}
};

