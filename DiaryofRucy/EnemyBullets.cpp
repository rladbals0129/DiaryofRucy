#include "Stdafx.h"
#include "EnemyBullets.h"

HRESULT EnemyBullet::init(string imageName, int bulletMax, float range,int moveType)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;
	_moveType = moveType;
	return S_OK;
}

void EnemyBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void EnemyBullet::update(void)
{
	if (_moveType == 0)
	{
		move();
	}
	else if (_moveType == 1)
	{
		move2();
	}

}

void EnemyBullet::render()
{
	
}

void EnemyBullet::d2drender(void)
{

	draw();
}

void EnemyBullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;
	
	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;
	
	bullet.initialAngle = angle;
	bullet.currentAngle = 0;

	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage(_imageName)->width, D2DMANAGER->findImage(_imageName)->height);

	_vBullet.push_back(bullet);
 }



void EnemyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		D2DMANAGER->render(_imageName, _viBullet->rc.left, _viBullet->rc.top);

	}
}



void EnemyBullet::setBulletRemovedCallback(std::function<void(float,float)> callback)
{
	_bulletRemovedCallback = callback;
}


void EnemyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->width,
			_viBullet->img->height);

		if (_range <= getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			float deleteX = _viBullet->x;
			float deleteY = _viBullet->y;
			_viBullet = _vBullet.erase(_viBullet);
			if (_bulletRemovedCallback) 
			{
				_bulletRemovedCallback(deleteX, deleteY);
			}
	
		}
		else
		{
			++_viBullet;
			
		}
	}
}

void EnemyBullet::move2(void)
{
	float rotateSpeed = 0.03f; // 회전 속도

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->currentAngle += rotateSpeed;

	
		float radiusG = _viBullet->speed * (_viBullet->currentAngle / rotateSpeed);
		_viBullet->x += cos(_viBullet->initialAngle + _viBullet->currentAngle) * (radiusG * 1.2f);
		_viBullet->y -= sin(_viBullet->initialAngle + _viBullet->currentAngle + 0.3f) * (radiusG * 1.2f);

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->width,
			_viBullet->img->height);

		if (_range <= getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;

		}
	}


}



void EnemyBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);

}




HRESULT PoisonBullet::init(string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void PoisonBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void PoisonBullet::update(void)
{
	move();
}

void PoisonBullet::render(void)
{
}

void PoisonBullet::d2drender(void)
{
	draw();
}


void PoisonBullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	//D2DMANAGER->findImage(_imageName);
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;

	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage(_imageName)->frameWidth+80, D2DMANAGER->findImage(_imageName)->frameHeight+80);
	bullet.alpha = 1.f;
	_vBullet.push_back(bullet);
}

void PoisonBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		D2DMANAGER->frameAlphaRender(_imageName, _viBullet->rc.left ,_viBullet->rc.top,
			_viBullet->frameX,_viBullet->frameY,120,120,_viBullet->alpha);

		_viBullet->count++;

		if (_viBullet->count % 6 == 0)
		{
			_viBullet->frameX++;


			if (_viBullet->frameX >= D2DMANAGER->findImage(_imageName)->maxFrameX)
			{
			
				if (_viBullet->frameY >= D2DMANAGER->findImage(_imageName)->maxFrameY)
				{
					_viBullet->frameY = _viBullet->img->maxFrameY;
					_viBullet->frameX = _viBullet->img->maxFrameX;
				}
				else
				{
					_viBullet->frameY++;
					_viBullet->frameX = 0;
				}
		
			}
			_viBullet->count = 0;
		}
	}

}

void PoisonBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->frameWidth+80,
			_viBullet->img->frameHeight+80);

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{		
			_viBullet = _vBullet.erase(_viBullet);	
		}
		else 
		{
			++_viBullet;
		}
	}
}

void PoisonBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Thorn::init(string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_lifeTime = 300;
	_range = range;
	return S_OK;
}

void Thorn::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Thorn::update(void)
{
	move();
}

void Thorn::render(void)
{
	
}

void Thorn::d2drender(void)
{
	draw();
}

void Thorn::fire(float x, float y, float frameMaxCnt)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	//D2DMANAGER->findImage(_imageName);
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.count = 0;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	//bullet.rc = RectMakeCenter(bullet.x, bullet.y,
	//	D2DMANAGER->findImage(_imageName)->frameWidth, D2DMANAGER->findImage(_imageName)->frameHeight);
	bullet.previewCnt = 0;
	bullet.alpha = 1.f;
	bullet.frameCnt = 1;
	bullet.frameMaxCnt = frameMaxCnt;
	_vBullet.push_back(bullet);

}

void Thorn::fire(float x, float y, float angle, float radius,float frameMaxCnt)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	//D2DMANAGER->findImage(_imageName);
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;
	bullet.previewCnt = 0;
	bullet.speed = radius;
	bullet.frameCnt = 1;
	bullet.frameMaxCnt = frameMaxCnt;
	bullet.x = bullet.fireX =x + cos(angle) * radius;
	bullet.y = bullet.fireY =y + sinf(angle) * radius;
	//bullet.rc = RectMakeCenter(bullet.x, bullet.y,
	//	D2DMANAGER->findImage(_imageName)->frameWidth, D2DMANAGER->findImage(_imageName)->frameHeight);
	bullet.alpha = 1.f;
	_vBullet.push_back(bullet);
}

void Thorn::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->previewCnt++;
		if (_viBullet->previewCnt < 30)
		{
			D2DMANAGER->render("가시미리보기", _viBullet->x - 32, _viBullet->y- 32);
		}
		else
		{
			D2DMANAGER->frameAlphaRender(_imageName, _viBullet->rc.left, _viBullet->rc.top,
				_viBullet->frameX, _viBullet->frameY, _viBullet->alpha);

			_viBullet->count++;

			
			if (_viBullet->count % 15 == 0)
			{
				_viBullet->frameX++;
				if (_viBullet->frameX >= D2DMANAGER->findImage(_imageName)->maxFrameX)
				{			
					//SD: 가시 생성 사운드
					if(_viBullet->frameX == 4 && _viBullet->frameY == 0) SOUNDMANAGER->play("플라임가시생성", 0.1f);

					if (_viBullet->frameY >= D2DMANAGER->findImage(_imageName)->maxFrameY)
					{
						_viBullet->frameY = _viBullet->img->maxFrameY;
						_viBullet->frameX = _viBullet->img->maxFrameX - 1;


					}
					else
					{
						_viBullet->frameY++;
						_viBullet->frameX = 0;
					}

				}
				
				_viBullet->count = 0;
			}
		}
	

		
	}
}

void Thorn::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->previewCnt >= 30)
		{
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->frameWidth,
				_viBullet->img->frameHeight);
			_viBullet->frameCnt++;
		}
		if (_viBullet->frameY == D2DMANAGER->findImage(_imageName)->maxFrameY && _viBullet->frameCnt % _viBullet->frameMaxCnt == 0)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}

	
	}
}

void Thorn::removeBullet(int arrNum)
{
}


HRESULT EspBullet::init(string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void EspBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void EspBullet::update(void)
{
	move();
}

void EspBullet::render(void)
{
}

void EspBullet::d2drender(void)
{
	draw();
}

void EspBullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	//D2DMANAGER->findImage(_imageName);
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;
	bullet.fireTime = 0;
	bullet.isDelayOver = false;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.isMoving = true;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage(_imageName)->width, D2DMANAGER->findImage(_imageName)->height);

	_vBullet.push_back(bullet);
}

void EspBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		float degrees = -(_viBullet->angle) * (180 / PI);

		D2DMANAGER->rotateRender(_imageName, _viBullet->rc.left, _viBullet->rc.top, degrees+ 90);

	}
}

void EspBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		float destroyRange = _range + 350;	
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			if (!_viBullet->isDelayOver) 
			{
				_viBullet->isMoving = false;
				//cout << _viBullet->fireTime << endl;
				//_viBullet->angleConversion = true;
				_viBullet->fireTime++;
				if (_viBullet->fireTime % 50 == 0)
				{
					_viBullet->isMoving = true;
					_viBullet->isDelayOver = true;
				}
			}
		}
		

		if (_viBullet->isMoving)
		{
			_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		}
		
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->width,
			_viBullet->img->height);
		if (destroyRange < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{

			++_viBullet;
		}
	}
}

void EspBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void EspBullet::updateAngle(int playerX, int playerY)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		if (!_viBullet->isMoving)
		{
			_viBullet->angle = getAngle(_viBullet->x, _viBullet->y, playerX, playerY);
		}
	}

}

HRESULT BubbleBullet::init(string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void BubbleBullet::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void BubbleBullet::update(void)
{
	move();
}

void BubbleBullet::render(void)
{
}

void BubbleBullet::d2drender(void)
{
	draw();
}

void BubbleBullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	//D2DMANAGER->findImage(_imageName);
	bullet.img = D2DMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;

	bullet.speed = speed;
	bullet.reverse = false;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		D2DMANAGER->findImage(_imageName)->width, D2DMANAGER->findImage(_imageName)->height);

	_vBullet.push_back(bullet);
}

void BubbleBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		D2DMANAGER->render(_imageName, _viBullet->rc.left, _viBullet->rc.top);

	}
}

void BubbleBullet::move(void)
{
	float rotateSpeed = 0.03f;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//cout << _viBullet->reverse << endl;
	
		if (!_viBullet->reverse)
		{
			_viBullet->angle += rotateSpeed;
			_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		}
		else
		{
			_viBullet->angle -= rotateSpeed;
			_viBullet->x -= cos(_viBullet->angle) * _viBullet->speed;
			_viBullet->y -= -sinf(_viBullet->angle) * _viBullet->speed;

		/*	float dx = _viBullet->fireX - _viBullet->x;
			float dy = _viBullet->fireY - _viBullet->y;
			float returnAngle = atan2(dy, dx);

			 returnAngle += rotateSpeed;
			_viBullet->x += cos(returnAngle) * _viBullet->speed;
			_viBullet->y += sin(returnAngle) * _viBullet->speed;*/
		}


		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->width,
			_viBullet->img->height);

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->reverse = true;
			
		}



		if( 10 > getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) && _viBullet->reverse)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void BubbleBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
