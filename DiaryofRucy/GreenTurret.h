#pragma once
#include "Turret.h"
class GreenTurret : public Turret
{
private:



public:
	HRESULT init(const char* imageName, POINT position);

	bool bulletCountFire();
	GreenTurret() {}
	~GreenTurret() {} //eeee
};

