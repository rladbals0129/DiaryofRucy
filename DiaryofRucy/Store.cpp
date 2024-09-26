#include "Stdafx.h"
#include "Store.h"

HRESULT Store::init(void)
{
	//_store = IMAGEMANAGER->addFrameImage("상점", "Resources/Images/UI/상점연습.bmp",
	//	594, 149, 2, 1, true, RGB(255, 0, 255));

	//_rcStore = RectMakeCenter(WINSIZE_X - 500, WINSIZE_Y / 10, 14, 20);
	return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
	//sCount++;
	//if (sCount % 16 == 0)
	//{
	//	if (sIndex > 1)
	//	{
	//		sIndex = 0;
	//	}
	//	_store->setFrameY(0);
	//	sIndex++;
	//}
}

void Store::render(void)
{
	//IMAGEMANAGER->frameRender("상점", getMemDC(), _rcStore.left, _rcStore.top, _store->getFrameX(), _store->getFrameY());
}

void Store::d2drender(void)
{
}
