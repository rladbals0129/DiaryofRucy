#include "Stdafx.h"
#include "ShopMap.h"

HRESULT ShopMap::vInit(void)
{
	_mapName = "상점맵";
	_image = IMAGEMANAGER->addImage("상점방", "Resources/Images/Maps/MapImage/상점방.bmp", WINSIZE_X, WINSIZE_Y);
	_colImg = IMAGEMANAGER->addImage("충-상점방", "Resources/Images/Maps/Collision/충-상점방.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	_imgName = "충-상점방";
	_pImgNameR = "충-상점방";
	_pImgNameL = "충-상점방";
	_isClear = true;

	return S_OK;
}
