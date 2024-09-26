#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{

public:
	void drawText(HDC hdc, int destX, int destY, const char* printString, int fontSize = 30, int fontWeight = 600,
		 COLORREF color = RGB(255,255,255), char* fontName = "น่นฮ");

	FontManager() {}
	~FontManager() {}
};