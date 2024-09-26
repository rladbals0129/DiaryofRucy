#pragma once
#include "Turret.h"
class MintTurret : public Turret
{
private:



public:
	HRESULT init(const char* imageName, POINT position);

	bool bulletCountFire();
	MintTurret() {}
	~MintTurret() {}
};

