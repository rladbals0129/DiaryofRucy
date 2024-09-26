#include "Stdafx.h"
#include "PurpleTurret.h"

HRESULT PurpleTurret::init(const char* imageName, POINT position)
{
	Turret::init(imageName, position);
	
	_fireTime = 8.f;
	return S_OK;
}

bool PurpleTurret::bulletCountFire()
{
	if (_fireTime + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireTime = 8.f;
		return true;
	}
	return false;
}
