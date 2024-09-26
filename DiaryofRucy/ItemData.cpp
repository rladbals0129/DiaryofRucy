#include "Stdafx.h"
#include "ItemData.h"

void ItemData::init(string name, string fileLocation, string ex, float x, float y, int width, int height
	, bool RGB, float atk, float mpk, float Mhp, float Mmp, int page, bool activeFlg)
{

	_name = name;
	_fileLocation = fileLocation;
	_ex = ex;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_RGB = RGB;
	_atk = atk;
	_mpk = mpk;
	_Mhp = Mhp;
	_Mmp = Mmp;
	_page = page;
	_activeFlg = activeFlg;

}

void ItemData::tier1(string tier, string category, float balance, string ability, float addNum)
{
	_tier = tier;
	_category = category;
	_balance = balance;
	_ability = ability;
	_addNum = addNum;
}

void ItemData::tier2(string tier, string category, float balance, string ability, float addNum, string ability2, float addNum2)
{
	_tier = tier;
	_category = category;
	_balance = balance;
	_ability = ability;
	_addNum = addNum;
	_ability2 = ability2;
	_addNum2 = addNum2;
}

void ItemData::tier3(string tier, string category, float balance, string ability, float addNum, string ability2, float addNum2, string ability3, float addNum3)
{
	_tier = tier;
	_category = category;
	_balance = balance;
	_ability = ability;
	_addNum = addNum;
	_ability2 = ability2;
	_addNum2 = addNum2;
	_ability3 = ability3;
	_addNum3 = addNum3;
}

