#include "Stdafx.h"
#include "ChestMap.h"
#include "Player.h"
#include "Ability.h"

HRESULT ChestMap::vInit(void)
{
	_mapName = "상자맵";
	_image = IMAGEMANAGER->addImage("상자방", "Resources/Images/Maps/MapImage/상자방.bmp", WINSIZE_X, WINSIZE_Y);
	_colImg = IMAGEMANAGER->addImage("충-상자방", "Resources/Images/Maps/Collision/충-상자방.bmp", WINSIZE_X, WINSIZE_Y, true, MAGENTA);

	_imgName = "충-상자방";
	_pImgNameR = "충-상자방";
	_pImgNameL = "충-상자방";
	_itemChest = new ItemChest;

	_itemChest->init(RND->getFromIntTo(1, 4));

	_isClear = true;

	return S_OK;
}

void ChestMap::objectUpdate(void)
{
	if (getDistance(_player->getPosition().x, _player->getPosition().y, _itemChest->getPosition().x, _itemChest->getPosition().y) < _itemChest->getDistanceWithPlayer())
	{
		if (!_itemChest->getAction())
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_itemChest->openChest();
				switch (*_stage)
				{
				case 1:
					_player->setAbility(Ability(D2DMANAGER->findImage("냄뚜"), "냄뚜", "최대체력, 마나 +1", 1, 1, 0, 0, 0, 0));
					break;
				case 2:
					_player->setAbility(Ability(D2DMANAGER->findImage("보름달"), "보름달", "마법공격력 +10, 탄막크기 증가", 0, 0, 0, 10, 0, 30));
					break;
				case 3:
					_player->setAbility(Ability(D2DMANAGER->findImage("신성한유물"), "신성한유물", "공격력 +4 공격속도 +50%", 0, 0, 4, 0, 25, 0));
					break;
				default:
					break;
				}

				//SD: 상자 열릴때 효과음 추가(보라색 상자는 또롱 하는 소리가 하나 더 있다.)
				SOUNDMANAGER->play("상자열림", 0.1f);

			}
		}
	}

	if (_itemChest->getAction() == true)
	{
		_itemChest->update();
	}

}

void ChestMap::objectRender(void)
{
	_itemChest->render();
}
