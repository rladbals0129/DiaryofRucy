#include "Stdafx.h"
#include "ThunderFlash.h"


HRESULT ThunderFlash::init(void)
{
	_iconImage = D2DMANAGER->findImage("벽력일섬아이콘");
	_frameImage = D2DMANAGER->findImage("벽력일섬");
	for (int i = 0; i < 4; i++)
	{
		_thunderFrameCount[i] = 0;
	}
	_frameCount = 0;
	_coolTime = 10;
	_manaCost = 4;
	_damageMultiple = 9;
	_isSkillShoot = false;
	_bThunderFire.reset();

	return S_OK;
}

void ThunderFlash::shot(float x, float y, float fireX, float fireY)
{
	if (_isCoolTimeOn) return;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_x = x;
	_y = y;
	//_angle = getAngle(fireX, fireY, x, y);
	_fireX = fireX; /*-cosf(_angle) * 70; */
	_fireY = fireY; /*+ sinf(_angle) * 70;*/
	_rc = RectMakeCenter(
		fireX + 130.0f * cosf(getAngle( _fireX, _fireY, _x, _y)),
		fireY + 130.0f * -sinf(getAngle(_fireX, _fireY, _x, _y)),
		260, 80);
	_frameCount = 0;
	_isSkillCollision = false;
	for (int i = 0; i < 4; i++)
	{
		_bThunderFire.reset();
		_rcThunder[i] = RectMakeCenter(
			fireX + i * 70 *  cosf(getAngle(fireX, fireY, _x, _y)),
			fireY + i * 70 * -sinf(getAngle(fireY, fireY, _x, _y)),
			40, 40);
	}
	_isSkillShoot = true;
	_isCoolTimeOn = true;
	// SD : 벽력일섬 사운드 추가 
	SOUNDMANAGER->play("스킬일섬1", 0.1f);
}

void ThunderFlash::animation(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (_frameCount == (i + 1) * 10)
		{
			_bThunderFire.set(i);
			// SD : 혹시 번개떨어지는 소리가 따로 있다면 여기에 추가
			SOUNDMANAGER->play("번개소리", 0.1f);
			
		}
	}

	if (_isSkillShoot)
	{
		_frameCount++;
		if (_frameCount == 50) _isSkillCollision = true;
		else _isSkillCollision = false;

		for (int i = 0; i < 4; i++)
		{
			if (_bThunderFire.test(i))
			{
				if (_frameCount % 2 == 0)
				{
					_frameX[i]++;
					if (_frameImage->maxFrameX < _frameX[i])
					{
						_frameX[i] = 0;
						_frameY[i]++;
						if (_frameImage->maxFrameY < _frameY[i])
						{
							_frameX[i] = 0;
							_frameY[i] = 0;
							_bThunderFire.reset(i);
							if (i == 3)
							{				
								_isSkillShoot = false;
							}
						}
					}
				}
			}
		}
		
	}
	//cout << _frameCount << endl;
}

void ThunderFlash::draw(void)
{
	for (int i = 0; i < 4; i++)
	{
		if(_bThunderFire.test(i)) D2DMANAGER->frameRender("벽력일섬", _rcThunder[i].left - 80, _rcThunder[i].bottom + 30  - _frameImage->frameHeight, _frameX[i], _frameY[i]);
	}
	
}
