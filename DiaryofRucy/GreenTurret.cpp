#include "Stdafx.h"
#include "GreenTurret.h"

HRESULT GreenTurret::init(const char* imageName, POINT position)
{
	Turret::init(imageName, position);
	_fireTime = 2.5f;
	return S_OK;
}

bool GreenTurret::bulletCountFire()
{
	if (_fireTime + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireTime = 2.5f;
		return true;
	}
	return false;
}
