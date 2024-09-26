#pragma once
#include "Turret.h"
class MiniGreenTurret : public Turret
{
private:



public:
	HRESULT init(const char* imageName, POINT position);

	bool bulletCountFire();
	MiniGreenTurret() {}
	~MiniGreenTurret() {}
};

