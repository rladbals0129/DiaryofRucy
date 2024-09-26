#include "Stdafx.h"
#include "Map.h"
#include "Player.h"


// 맵 이미지와 충돌처리 이미지를 init하여 정보를 가지고 있는다.

//Map::Map() :_image(nullptr), _colImg(nullptr), _objImg(nullptr), _imgName(""), _rc(RectMake(0, 0, 0, 0)), _x(0.0f), _y(0.0f), _currentFrameX(0), _currentFrameY(0), _rndTimeCount(0.0), _worldTimeCount(0.0), _indexX(0), _indexY(0)
//{
//
//}


HRESULT Map::init(int* stage)
{
	_stage = stage;
	vInit();
	_camera = new Camera();
	_camera->init();
	_save = false;
	return S_OK;
}

HRESULT Map::vInit(void)
{
	return S_OK;
}

void Map::release(void)
{

}

void Map::update(void)
{
	if (_player != nullptr)
	{
		this->_camera->update(_player);
	}
	objectUpdate();
	enemyUpdate();
	bossUpdate();
}



void Map::render(void)
{
	draw();
	objectRender();
	enemyRender();
	bossRender();
}

void Map::d2drender(void)
{
	//d2dplayerRender();
	//_em->d2drender();
	d2dEnemyRender();
	d2dBossRender();
	d2dObjectRender();
}


void Map::draw()
{
	//_image->cameraRender(getMemDC(), 0 - _camera->getCameraPosition().x, 0 - _camera->getCameraPosition().y,_camera->getZoomLevel());
	_image->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		if (!(_colImg == nullptr))
		{
			_colImg->render(getMemDC());
		}
	}
}



/*
	HDC hdcSrc = CreateCompatibleDC(getHDC());
	RECT srcRect = { _camera->getCameraPosition().x,_camera->getCameraPosition().y, _camera->getCameraPosition().x + WINSIZE_X,_camera->getCameraPosition().y + WINSIZE_Y };
	RECT destRect = { 0,0,WINSIZE_X * _camera->getZoomLevel(),WINSIZE_Y * _camera->getZoomLevel() };

	SelectObject(hdcSrc, getMemBitmap());

	StretchBlt(getHDC(), destRect.left, destRect.top,
		destRect.right - destRect.left, destRect.bottom - destRect.top,
		hdcSrc, srcRect.left, srcRect.top,
		srcRect.right - srcRect.left, srcRect.bottom - srcRect.top,
		SRCCOPY);

	DeleteDC(hdcSrc);
*/