#include "Stdafx.h"
#include "MapManager.h"
#include "Map.h"
#include "Player.h"

// 플레이어 픽셀 충돌
// 신호를 플레이어로 보내는가
// 플레이어의 정보를 받아서 움직임을 멈추어야 하는가
// 1 = top , 2 = bottom, 3 = left, 4 = right

int MapManager::pixelCollision(RECT object, string imageName)
{
	_colTop = false;
	_colBottom = false;
	_colLeft = false;
	_colRight = false;

	for (int j = object.top-5; j < object.top; j++)
	{
		for (int i = object.left; i < object.right; i++)
		{
			COLORREF _color1 = GetPixel(IMAGEMANAGER->findImage(imageName)->getMemDC(), i, j);

			int r1 = GetRValue(_color1);
			int g1 = GetGValue(_color1);
			int b1 = GetBValue(_color1);

			if (r1 == 255 && g1 == 0 && b1 == 0)
			{
				_colTop = true;

				break;
			}
			else
			{
				_colTop = 0;
			}
		}
	}

	for (int j = object.bottom; j < object.bottom + 5; j++)
	{
		for (int i = object.left; i < object.right; i++)
		{
			COLORREF _color2 = GetPixel(IMAGEMANAGER->findImage(imageName)->getMemDC(), i, j);
			int r2 = GetRValue(_color2);
			int g2 = GetGValue(_color2);
			int b2 = GetBValue(_color2);

			if (r2 == 255 && g2 == 0 && b2 == 0)
			{
				_colBottom = true;
				break;
			}
			else
			{
				_colBottom = false;
			}
		}
	}

	for (int i = object.left - 5; i < object.left; i++)
	{
		for (int j = object.top; j < object.bottom; j++)
		{
			COLORREF _color3 = GetPixel(IMAGEMANAGER->findImage(imageName)->getMemDC(), i, j);
			int r3 = GetRValue(_color3);
			int g3 = GetGValue(_color3);
			int b3 = GetBValue(_color3);

			if (r3 == 255 && g3 == 0 && b3 == 0)
			{
				_colLeft = true;
				break;
			}
			else
			{
				_colLeft = false;
			}
		}
	}


	for (int i = object.right; i < object.right + 5; i++)
	{
		for (int j = object.top; j < object.bottom; j++)
		{
			COLORREF _color4 = GetPixel(IMAGEMANAGER->findImage(imageName)->getMemDC(), i, j);
			int r4 = GetRValue(_color4);
			int g4 = GetGValue(_color4);
			int b4 = GetBValue(_color4);

			if (r4 == 255 && g4 == 0 && b4 == 0)
			{
				_colRight = true;
				break;
			}
			else
			{
				_colRight = false;
			}
		}
	}
	if (_colLeft)
	{
		_colSign = 0;
		_player->setPixelColTrue(0);
		//cout << "왼쪽 충돌" << endl;

	}
	else
	{
		_player->setPixelColFalse(0);
	}

	if (_colRight)
	{
		_colSign = 2;
		_player->setPixelColTrue(2);
	//	cout << "오른쪽 충돌" << endl;
	}
	else
	{
		_player->setPixelColFalse(2);
	}

	if (_colTop)
	{
		_colSign = 1;
		_player->setPixelColTrue(1);
		//cout << "위쪽 충돌" << endl;

	}
	else
	{
		_player->setPixelColFalse(1);
	}

	if (_colBottom)
	{
		_colSign = 3;
		_player->setPixelColTrue(3);
	//	cout << "아래쪽 충돌" << endl;

	}
	else
	{
		_player->setPixelColFalse(3);
	}

	return _colSign;
}




//
//int MapManager::EnemyPixelCollision(RECT object)
//{
//	_colSign = 5;
//
//	_colTop = false;
//	_colBottom = false;
//	_colLeft = false;
//	_colRight = false;
//
//	for (int j = object.top + 47; j < object.top + 50; j++)
//	{
//		for (int i = object.left; i < object.right; i++)
//		{
//			COLORREF _color1 = GetPixel(IMAGEMANAGER->findImage("임시충돌")->getMemDC(), i, j);
//
//			int r1 = GetRValue(_color1);
//			int g1 = GetGValue(_color1);
//			int b1 = GetBValue(_color1);
//
//			if (r1 == 255 && g1 == 0 && b1 == 0)
//			{
//				_colTop = true;
//
//				break;
//			}
//			else
//			{
//				_colTop = 0;
//			}
//		}
//	}
//
//	for (int j = object.bottom; j < object.bottom + 3; j++)
//	{
//		for (int i = object.left; i < object.right; i++)
//		{
//			COLORREF _color2 = GetPixel(IMAGEMANAGER->findImage("임시충돌")->getMemDC(), i, j);
//			int r2 = GetRValue(_color2);
//			int g2 = GetGValue(_color2);
//			int b2 = GetBValue(_color2);
//
//			if (r2 == 255 && g2 == 0 && b2 == 0)
//			{
//				_colBottom = true;
//				break;
//			}
//			else
//			{
//				_colBottom = false;
//			}
//		}
//	}
//
//	for (int i = object.left - 3; i < object.left; i++)
//	{
//		for (int j = object.top + 50; j < object.bottom; j++)
//		{
//			COLORREF _color3 = GetPixel(IMAGEMANAGER->findImage("임시충돌")->getMemDC(), i, j);
//			int r3 = GetRValue(_color3);
//			int g3 = GetGValue(_color3);
//			int b3 = GetBValue(_color3);
//
//			if (r3 == 255 && g3 == 0 && b3 == 0)
//			{
//				_colLeft = true;
//				break;
//			}
//			else
//			{
//				_colLeft = false;
//			}
//		}
//	}
//
//
//	for (int i = object.right; i < object.right + 3; i++)
//	{
//		for (int j = object.top + 50; j < object.bottom; j++)
//		{
//			COLORREF _color4 = GetPixel(IMAGEMANAGER->findImage("임시충돌")->getMemDC(), i, j);
//			int r4 = GetRValue(_color4);
//			int g4 = GetGValue(_color4);
//			int b4 = GetBValue(_color4);
//
//			if (r4 == 255 && g4 == 0 && b4 == 0)
//			{
//				_colRight = true;
//				break;
//			}
//			else
//			{
//				_colRight = false;
//			}
//		}
//	}
//	if (_colLeft)
//	{
//		_colSign = 1;
//	}
//
//	if (_colRight)
//	{
//		_colSign = 2;
//	}
//
//	if (_colTop)
//	{
//		_colSign = 3;
//	}
//
//	if (_colBottom)
//	{
//		_colSign = 0;
//	}
//
//	return _colSign;
//}
//
