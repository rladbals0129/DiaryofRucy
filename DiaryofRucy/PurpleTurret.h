#pragma once
#include "Turret.h"
class PurpleTurret : public Turret
{
private:



public:
	HRESULT init(const char* imageName, POINT position);

	bool bulletCountFire();
	PurpleTurret() {}
	~PurpleTurret() {}
};

