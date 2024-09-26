#include "Stdafx.h"
#include "MintTurret.h"

HRESULT MintTurret::init(const char* imageName, POINT position)
{
	Turret::init(imageName, position);
	
	_fireTime = 4.f;
	return S_OK;
}

bool MintTurret::bulletCountFire()
{
	if (_fireTime + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireTime = 4.f;
		return true;
	}
	return false;
}
