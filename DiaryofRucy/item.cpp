#include "Stdafx.h"
#include "item.h"

HRESULT item::init(void)
{
	//_wstaff = IMAGEMANAGER->addImage("나무지팡이", "Resources/Images/item/wood_staff.bmp",
	//	24, 24, true, RGB(255, 0, 255));
	//_wbow = IMAGEMANAGER->addImage("나무활", "Resources/Images/item/wood_staff.bmp",
	//	24, 24, true, RGB(255, 0, 255));
	//_wsword = IMAGEMANAGER->addImage("나무칼", "Resources/Images/item/wood_sword.bmp",
	//	29, 31, true, RGB(255, 0, 255));
	//_shadow = IMAGEMANAGER->addImage("그림자", "Resources/Images/item/shadow.bmp",
	//	20, 20, true, RGB(255, 0, 255));
	//rcwstaff = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 3 , 24, 24);

	//shadow(rcwstaff);
	//shadow(rcwbow);
	//shadow(rcwsword);



	return S_OK;
}

void item::release(void)
{
}

void item::shadow(RECT rc)
{

	//rcshadow = RectMakeCenter(rc->left, rc->top + 20, rc->left + rc->right, rc->bottom + rc->top);
}

void item::update(void)
{
	
}

void item::render(void)
{
//	_wstaff->render(getMemDC(), rcwstaff.left, rcwstaff.top);

}


void item::d2drender(void)
{
}
