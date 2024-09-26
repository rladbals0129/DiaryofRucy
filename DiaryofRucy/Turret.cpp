#include "Stdafx.h"
#include "Turret.h"

Turret::Turret(void) : _rc(RectMake(0,0,0,0)),
_x(0.f),
_y(0.f),
_bulletFireCount(0.f),
_fireCount(0),
_fireTime(0.f)
{
}


HRESULT Turret::init(const char* imageName, POINT position)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_center = position;


	
	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_die = false;
	_hp = 50;

	return S_OK;
}

void Turret::release(void)
{
	SAFE_DELETE(_image);
}

void Turret::update(void)
{
	if (_hp <= 0)
	{
		_die = true;
	}
}

void Turret::render(void)
{
	if (!_die)
	{
		draw();
	}
}

void Turret::d2drender(void)
{
}

bool Turret::bulletCountFire()
{
	return false;
}

void Turret::draw(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

