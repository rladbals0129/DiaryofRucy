#include "Stdafx.h"
#include "UI.h"
#include "Player.h"
#include "KingSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"
#include "Stage.h"
#include "Ability.h"

HRESULT UI::init(void)
{
	_steminaProgressBar.baseUI.d2dImage = D2DMANAGER->findImage("스테미나게이지UI");
	_steminaProgressBar.baseUI.x = WINSIZE_X / 2 - 8;
	_steminaProgressBar.baseUI.y = WINSIZE_Y - 80;
	_steminaProgressBar.baseUI.rc = RectMakeCenter(_steminaProgressBar.baseUI.x, _steminaProgressBar.baseUI.y, _steminaProgressBar.baseUI.d2dImage->width, _steminaProgressBar.baseUI.d2dImage->height);
	_steminaProgressBar.gauge = _player->getStemina();

	_expProgressBar.baseUI.d2dImage = D2DMANAGER->findImage("경험치게이지UI");
	_expProgressBar.baseUI.x = WINSIZE_X / 2 +15;
	_expProgressBar.baseUI.y = WINSIZE_Y - 98;
	_expProgressBar.baseUI.rc = RectMakeCenter(_expProgressBar.baseUI.x, _expProgressBar.baseUI.y, _expProgressBar.baseUI.d2dImage->width, _expProgressBar.baseUI.d2dImage->height);
	_expProgressBar.gauge = _player->getExp();
	
	_stemina.d2dImage = D2DMANAGER->findImage("스테미나UI");
	_stemina.x = WINSIZE_X / 2;
	_stemina.y = WINSIZE_Y - 110;
	_stemina.rc = RectMakeCenter(_stemina.x, _stemina.y, _stemina.d2dImage->width, _stemina.d2dImage->height);

	_level.d2dImage = D2DMANAGER->findImage("레벨UI");
	_level.x = WINSIZE_X / 2 - 100;
	_level.y = WINSIZE_Y - 100;
	_level.rc = RectMakeCenter(_level.x, _level.y, _level.d2dImage->frameWidth, _level.d2dImage->frameHeight);
	_level.pframe = _player->getLevel();

	_goldG.d2dImage = D2DMANAGER->findImage("골드UI");
	_goldG.x = WINSIZE_X - 30;
	_goldG.y = 30;
	_goldG.rc = RectMakeCenter(_goldG.x, _goldG.y, _goldG.d2dImage->width, _goldG.d2dImage->height);

	_goldNumber1.d2dImage = D2DMANAGER->findImage("골드숫자UI");
	_goldNumber1.x = WINSIZE_X - 50;
	_goldNumber1.y = 30;
	_goldNumber1.rc = RectMakeCenter(_goldNumber1.x, _goldNumber1.y, _goldNumber1.d2dImage->frameWidth, _goldNumber1.d2dImage->frameHeight);
	_goldNumber1.pframe = _player->getGold();							

	_goldNumber10.d2dImage = D2DMANAGER->findImage("골드숫자UI");
	_goldNumber10.x = WINSIZE_X - 65;
	_goldNumber10.y = 30;
	_goldNumber10.rc = RectMakeCenter(_goldNumber10.x, _goldNumber10.y, _goldNumber10.d2dImage->frameWidth, _goldNumber10.d2dImage->frameHeight);
	_goldNumber10.pframe = _player->getGold();						

	_weaponSlot.baseUI.d2dImage = D2DMANAGER->findImage("무기슬롯A");
	_weaponSlot.baseUI.x = WINSIZE_X - 70;
	_weaponSlot.baseUI.y = WINSIZE_Y - 70;
	_weaponSlot.baseUI.rc = RectMakeCenter(_weaponSlot.baseUI.x, _weaponSlot.baseUI.y, _weaponSlot.baseUI.d2dImage->width, _weaponSlot.baseUI.d2dImage->height);
	_weaponSlot.slotChange = _player->getWeaponSlot();
	_weaponSlot.currentWeapon = _player->getWeaponType();

	_potionSlot.baseUI.d2dImage = D2DMANAGER->findImage("포션슬롯");
	_potionSlot.baseUI.x = WINSIZE_X - 140;
	_potionSlot.baseUI.y = WINSIZE_Y - 65;
	_potionSlot.baseUI.rc = RectMakeCenter(_potionSlot.baseUI.x, _potionSlot.baseUI.y, _potionSlot.baseUI.d2dImage->width, _potionSlot.baseUI.d2dImage->height);

	for (int i = 0; i < MAXHP; i++)
	{
		tagBaseUI setMaxHpUI;
		setMaxHpUI.d2dImage = D2DMANAGER->findImage("체력UI");
		setMaxHpUI.frame = 0;
		setMaxHpUI.x = WINSIZE_X / 2 - 60 - i*25;
		setMaxHpUI.y = WINSIZE_Y- 120;
		setMaxHpUI.rc = RectMakeCenter(setMaxHpUI.x, setMaxHpUI.y, setMaxHpUI.d2dImage->frameWidth, setMaxHpUI.d2dImage->frameHeight);
		_vMaxHP.push_back(setMaxHpUI);

		tagBaseUI setcurrentHpUI;
		setcurrentHpUI.d2dImage = D2DMANAGER->findImage("체력UI");
		setcurrentHpUI.frame = 1;
		setcurrentHpUI.x = WINSIZE_X / 2 - 60 - i * 25;
		setcurrentHpUI.y = WINSIZE_Y - 120;
		setcurrentHpUI.rc = RectMakeCenter(setcurrentHpUI.x, setcurrentHpUI.y, setcurrentHpUI.d2dImage->frameWidth, setcurrentHpUI.d2dImage->frameHeight);
		_vCurrentHP.push_back(setcurrentHpUI);
	}

	for (int i = 0; i < MAXMP; i++)
	{
		tagBaseUI setMaxMpUI;
		setMaxMpUI.d2dImage = D2DMANAGER->findImage("마나UI");
		setMaxMpUI.frame = 0;
		setMaxMpUI.x = WINSIZE_X / 2 + 50 + i * 26;
		setMaxMpUI.y = WINSIZE_Y - 120;
		setMaxMpUI.rc = RectMakeCenter(setMaxMpUI.x, setMaxMpUI.y, setMaxMpUI.d2dImage->frameWidth, setMaxMpUI.d2dImage->frameHeight);
		_vMaxMP.push_back(setMaxMpUI);

		tagBaseUI setcurrentMpUI;
		setcurrentMpUI.d2dImage = D2DMANAGER->findImage("마나UI");
		setcurrentMpUI.frame = 1;
		setcurrentMpUI.x = WINSIZE_X / 2 + 50 + i * 26;
		setcurrentMpUI.y = WINSIZE_Y - 120;
		setcurrentMpUI.rc = RectMakeCenter(setcurrentMpUI.x, setcurrentMpUI.y, setcurrentMpUI.d2dImage->frameWidth, setcurrentMpUI.d2dImage->frameHeight);
		_vCurrentMP.push_back(setcurrentMpUI);
	}

	for (int i = 0; i < 4; i++)
	{
		_skillSlotUI.baseUI[i].x = WINSIZE_X / 2 -10 + cosf(DEGREE_RADIAN(203 + i * 45)) * 60;
		_skillSlotUI.baseUI[i].y = WINSIZE_Y - 140 + sinf(DEGREE_RADIAN(203 + i * 45)) * 60;
		_skillSlotUI.baseUI[i].rc = RectMakeCenter(_skillSlotUI.baseUI[i].x, _skillSlotUI.baseUI[i].y,28,28);

		if (_player->getSkill(i) != nullptr)
		{
			_skillSlotUI.baseUI[i].d2dImage = _player->getSkill(i)->getIconImage();
			_skillSlotUI.manaCost = _player->getSkill(i)->getManaCost();
		}
	}
	_skillSlotUI.currentSkillIndex = _player->getCurrentSkillIndex();
	_skillSlotUI.rcCurrntSkill = RectMakeCenter(WINSIZE_X / 2 - 8, WINSIZE_Y - 143, 32, 32);
	_skillSlotUI.rcCurrntSkillMana = RectMakeCenter(WINSIZE_X / 2 - 7, WINSIZE_Y - 115, 24, 24);

	_miniMap.backGround.d2dImage = D2DMANAGER->findImage("미니맵배경UI");
	_miniMap.backGround.x = WINSIZE_X - 100;
	_miniMap.backGround.y =  125;
	_miniMap.backGround.rc = RectMakeCenter(_miniMap.backGround.x, _miniMap.backGround.y, _miniMap.backGround.d2dImage->width, _miniMap.backGround.d2dImage->height);
	_miniMap.alpha = 0.0f;

	
	_chargeUI.d2dImage = D2DMANAGER->findImage("지팡이차지");
	_chargeUI.pRc = _player->getpRcColision();
	_chargeUI.frameX = 0;
	_chargeUI.frameY = 0;
	_chargeUI.frameCount = 0;
	_chargeUI.isCharging = _player->getIsCharging();

	_chargeBarUI.d2dImageBack = D2DMANAGER->findImage("차지샷배경");
	_chargeBarUI.d2dImageFront = D2DMANAGER->findImage("차지샷게이지");
	_chargeBarUI.gauge = _player->getChargeGauge();
	_chargeBarUI.pX = _player->getpX();
	_chargeBarUI.pY = _player->getpY();
	
	_bossUIHPBar.d2dImageBack = D2DMANAGER->findImage("보스체력배경");
	_bossUIHPBar.d2dImageFront = D2DMANAGER->findImage("보스체력게이지");
	_bossUIHPBar.x = WINSIZE_X / 2;
	_bossUIHPBar.y = 50;
	_bossUIHPBar.rc1 = RectMakeCenter(_bossUIHPBar.x, _bossUIHPBar.y, _bossUIHPBar.d2dImageBack->width, _bossUIHPBar.d2dImageBack->height);
	_bossUIHPBar.rc2 = RectMakeCenter(_bossUIHPBar.x, _bossUIHPBar.y+ _bossUIHPBar.d2dImageBack->height+10, _bossUIHPBar.d2dImageBack->width, _bossUIHPBar.d2dImageBack->height);

	_toggleMap.d2dImage = D2DMANAGER->findImage("토글맵배경");
	_toggleMap.x = WINSIZE_X / 2;
	_toggleMap.y = WINSIZE_Y / 2;
	_toggleMap.rc = RectMakeCenter(_toggleMap.x, _toggleMap.y, _toggleMap.d2dImage->width, _toggleMap.d2dImage->height);
	_toggleMap.currentAlpha = 0.0f;
	_toggleMap.isToggleKeyOn = false;
	_toggleMap.isSelectRoom = false;
	_toggleMap.selectRoomX = _toggleMap.selectRoomY = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_toggleMap.rcMap[j][i] = RectMakeCenter(
				_toggleMap.rc.left + 170 + i * 30, _toggleMap.rc.top + 120 + j * 30, 30, 30);
		}
	}

	// _abilityList;
	// _buffList;

	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
	steminaUpdate();
	expUpdate();
	skillUpdate();
	miniMapUpdate();
	chargeUpdate();
	bossUIUpdate();
	toggleMapUIUpdate();
}

void UI::d2drender(void)
{
	skillRender();
	D2DMANAGER->render("스테미나게이지UI", _steminaProgressBar.baseUI.rc.left, _steminaProgressBar.baseUI.rc.top, _steminaProgressBar.width, _steminaProgressBar.baseUI.d2dImage->height);
	D2DMANAGER->render("경험치게이지UI", _expProgressBar.baseUI.rc.left, _expProgressBar.baseUI.rc.top, _expProgressBar.width, _expProgressBar.baseUI.d2dImage->height);
	D2DMANAGER->render("스테미나UI", _stemina.rc.left, _stemina.rc.top);
	D2DMANAGER->frameRender("레벨UI", _level.rc.left, _level.rc.top, *_level.pframe, 0);
	D2DMANAGER->render("골드UI", _goldG.rc.left, _goldG.rc.top);
	D2DMANAGER->frameRender("골드숫자UI", _goldNumber1.rc.left, _goldNumber1.rc.top, *_goldNumber1.pframe%10, 0);
	D2DMANAGER->frameRender("골드숫자UI", _goldNumber10.rc.left, _goldNumber10.rc.top, *_goldNumber10.pframe/10, 0);
	if (*_weaponSlot.slotChange) D2DMANAGER->render("무기슬롯A", _weaponSlot.baseUI.rc.left, _weaponSlot.baseUI.rc.top);
	else  D2DMANAGER->render("무기슬롯B", _weaponSlot.baseUI.rc.left, _weaponSlot.baseUI.rc.top);
	D2DMANAGER->render("포션슬롯", _potionSlot.baseUI.rc.left, _potionSlot.baseUI.rc.top);
	
	switch (*_weaponSlot.currentWeapon)
	{
	case 1:
		D2DMANAGER->render("검UI", _weaponSlot.baseUI.rc.left+25, _weaponSlot.baseUI.rc.top+20);
		break;
	case 2:
		D2DMANAGER->render("활UI", _weaponSlot.baseUI.rc.left+15, _weaponSlot.baseUI.rc.top+15);
		break;
	case 3:
		D2DMANAGER->render("지팡이UI", _weaponSlot.baseUI.rc.left+25, _weaponSlot.baseUI.rc.top+20);
		break;
	default:
		break;
	}
	
	
	
	HPUpdateRender();
	MPUpdateRender();
	miniMapRender();
	bossUIRender();
	chargeRender();
	toggleMapUIRender();
	abillityUIRender();


}

void UI::UIrender(void)
{
	// 페이드 인 / 아웃 처리
	IMAGEMANAGER->alphaRender("블랙보드", getMemDC(), IMAGEMANAGER->getAlpha());

	for (int i = 0; i < _player->getAbility().size(); i++)
	{
		if (PtInRect(&_abilityUI[i].rc, _ptMouse))
		{
			FONTMANAGER->drawText(getMemDC(), _abilityUI[i].rcDescription.left+10, _abilityUI[i].rcDescription.top+10, 
				_player->getAbility()[i].getName().c_str(), 15, 600);
			FONTMANAGER->drawText(getMemDC(), _abilityUI[i].rcDescription.left + 10, _abilityUI[i].rcDescription.top + 40,
				_player->getAbility()[i].getDescription().c_str(), 13, 500);
		}
	}
}



void UI::steminaUpdate(void)
{
	_steminaProgressBar.width = (*_steminaProgressBar.gauge / 100) * _steminaProgressBar.baseUI.d2dImage->width;
}

void UI::expUpdate(void)
{
	_expProgressBar.width = (*_expProgressBar.gauge / 100) * _expProgressBar.baseUI.d2dImage->width;
}

void UI::skillUpdate(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (_player->getSkill(i) != nullptr)
		{
			if (_player->getSkill(i)->getIsCoolTimeOn())
			{
				_skillSlotUI.coolTime[i] = _player->getSkill(i)->getCoolTime();
			}
		}
	}

}

void UI::miniMapUpdate(void)
{
	RECT rcMiniMapRender = RectMakeCenter(_miniMap.backGround.x, _miniMap.backGround.y, 100, 100);
	// 미니맵업데이트
	_miniMap.miniMap.name = _stage->getMapManagerMemoryAddress()->getCurrentMap()->getImgName();
	// 플레이어 위치 갱신
	_miniMap.playerPoint.x = rcMiniMapRender.left + (_player->getPosition().x / (float)WINSIZE_X) * 100;
	_miniMap.playerPoint.y = rcMiniMapRender.top + (_player->getPosition().y / (float)WINSIZE_Y) * 100;
	_miniMap.playerPoint.rc = RectMakeCenter(_miniMap.playerPoint.x, _miniMap.playerPoint.y, 8, 8);
	
	if (_miniMap.alpha < 0) _miniMap.alpha = 1;
	else _miniMap.alpha -= 0.02;

}

void UI::chargeUpdate(void)
{
	if (*_chargeUI.isCharging && *_chargeBarUI.gauge > 15)
	{
		_chargeUI.frameCount++;
		if (_chargeUI.frameCount % 5 == 0)
		{
			_chargeUI.frameX++;
			if (_chargeUI.frameX > _chargeUI.d2dImage->maxFrameX)
			{
				_chargeUI.frameX = 0;
				_chargeUI.frameY++;
				if (_chargeUI.frameY > _chargeUI.d2dImage->maxFrameY)
				{
					_chargeUI.frameY = 0;
				}
			}
		}
	}
	_chargeBarUI.width = (*_chargeBarUI.gauge / 100) * _chargeBarUI.d2dImageFront->width;
}

void UI::bossUIUpdate(void)
{
	if (_stage->getMapManagerMemoryAddress()->getCurrentMap()->getMapName() == "보스맵")
	{
		switch (_stage->getCurrentStage())
		{
		case 1:
			_bossUIHPBar.hp1 = _kingSlime->getHP();
			_bossUIHPBar.width1 = (_bossUIHPBar.hp1 / _kingSlime->getHPMax()) * _bossUIHPBar.d2dImageBack->width;
			break;
		case 2:
			_bossUIHPBar.hp1 = _megaFlime->getHP();
			_bossUIHPBar.width1 = (_bossUIHPBar.hp1 / _megaFlime->getHPMax()) * _bossUIHPBar.d2dImageBack->width;
			break;
		case 3:
			_bossUIHPBar.hp1 = _mushMamBoss->getHP();
			_bossUIHPBar.width1 = (_bossUIHPBar.hp1 / _mushMamBoss->getHPMax()) * _bossUIHPBar.d2dImageBack->width;
			break;
		default:
			break;
		}
	}
}

void UI::toggleMapUIUpdate(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (!_toggleMap.isToggleKeyOn) _toggleMap.isToggleKeyOn = true;
		else _toggleMap.isToggleKeyOn = false;
	}
	if (_toggleMap.isToggleKeyOn)
	{
		KEYMANAGER->setKeyUp(VK_LBUTTON, true);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (PtInRect(&_toggleMap.rcMap[j][i], _ptMouse))
				{
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						if ((_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j) != nullptr) && (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getIsVisit()))
						{
							_toggleMap.isSelectRoom = true;
							_toggleMap.selectRoomX = i;
							_toggleMap.selectRoomY = j;
						}
					}
				}
			}
		}
	}

	if(_toggleMap.isSelectRoom)
	{
		IMAGEMANAGER->fadeOut();
		if (IMAGEMANAGER->getAlpha() == 255)
		{
			_stage->getMapManagerMemoryAddress()->setCurrentX(_toggleMap.selectRoomX);
			_stage->getMapManagerMemoryAddress()->setCurrentY(_toggleMap.selectRoomY);

			//위치 바꿔주기
			_player->setPosition(WINSIZE_X / 2, WINSIZE_Y / 2);

			_stage->getMapManagerMemoryAddress()->setChangeRoomFadeOut();
			_toggleMap.isSelectRoom = false;
			_toggleMap.isToggleKeyOn = false;
		}
	}
}


void UI::skillRender(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (_player->getSkill(i) != nullptr)
		{
			D2DMANAGER->render("스킬슬롯UI", _skillSlotUI.baseUI[i].rc.left, _skillSlotUI.baseUI[i].rc.top);
			switch (i)
			{
			case 0:
				D2DMANAGER->render("바람의상처아이콘", _skillSlotUI.baseUI[i].rc.left + 8, _skillSlotUI.baseUI[i].rc.top + 8, 24, 24);
				break;
			case 1:
				D2DMANAGER->render("벽력일섬아이콘", _skillSlotUI.baseUI[i].rc.left + 8, _skillSlotUI.baseUI[i].rc.top + 8, 24, 24);
				break;
			case 2:
				D2DMANAGER->render("아이시클스파크아이콘", _skillSlotUI.baseUI[i].rc.left + 8, _skillSlotUI.baseUI[i].rc.top + 8, 24, 24);
				break;
			case 3:
				D2DMANAGER->render("익스플로전아이콘", _skillSlotUI.baseUI[i].rc.left + 8, _skillSlotUI.baseUI[i].rc.top + 8, 24, 24);
				break;
			default:
				break;
			}
		}
	}
	switch (*_skillSlotUI.currentSkillIndex)
	{
	case 0:
		D2DMANAGER->render("바람의상처아이콘", _skillSlotUI.rcCurrntSkill.left, _skillSlotUI.rcCurrntSkill.top, 36, 36);
		D2DMANAGER->render("바람스킬마나UI", _skillSlotUI.rcCurrntSkillMana.left, _skillSlotUI.rcCurrntSkillMana.top);
		break;
	case 1:
		D2DMANAGER->render("벽력일섬아이콘", _skillSlotUI.rcCurrntSkill.left, _skillSlotUI.rcCurrntSkill.top, 36, 36);
		D2DMANAGER->render("번개스킬마나UI", _skillSlotUI.rcCurrntSkillMana.left, _skillSlotUI.rcCurrntSkillMana.top);
		break;
	case 2:
		D2DMANAGER->render("아이시클스파크아이콘", _skillSlotUI.rcCurrntSkill.left, _skillSlotUI.rcCurrntSkill.top, 36, 36);
		D2DMANAGER->render("얼음스킬마나UI", _skillSlotUI.rcCurrntSkillMana.left, _skillSlotUI.rcCurrntSkillMana.top);

		break;
	case 3:
		D2DMANAGER->render("익스플로전아이콘", _skillSlotUI.rcCurrntSkill.left, _skillSlotUI.rcCurrntSkill.top, 36, 36);
		D2DMANAGER->render("불스킬마나UI", _skillSlotUI.rcCurrntSkillMana.left, _skillSlotUI.rcCurrntSkillMana.top);
		break;
	default:
		break;
	}
	D2DMANAGER->frameRender("마나소모량UI", _skillSlotUI.rcCurrntSkillMana.left + 6, _skillSlotUI.rcCurrntSkillMana.top + 3,
		_player->getSkill(*_skillSlotUI.currentSkillIndex)->getManaCost(), 0, 13, 17);
	for (int i = 0; i < 4; i++)
	{
		if (_player->getSkill(i) != nullptr)
		{
			if (_player->getSkill(i)->getIsCoolTimeOn())
			{
				if (_player->getSkill(i)->getCoolTime() > 10)
				{
					D2DMANAGER->frameRender("스킬쿨타임UI", _skillSlotUI.baseUI[i].rc.left + 7, _skillSlotUI.baseUI[i].rc.top + 11,
						(int)_skillSlotUI.coolTime[i] / 10, 0, 14, 18);

					D2DMANAGER->frameRender("스킬쿨타임UI", _skillSlotUI.baseUI[i].rc.left + 19, _skillSlotUI.baseUI[i].rc.top + 11,
						(int)_skillSlotUI.coolTime[i] % 10, 0, 14, 18);
				}
				else
				{
					D2DMANAGER->frameRender("스킬쿨타임UI", _skillSlotUI.baseUI[i].rc.left + 13, _skillSlotUI.baseUI[i].rc.top + 11,
						(int)_skillSlotUI.coolTime[i], 0, 15, 19);
				}

			}
		}
	}
}

void UI::HPUpdateRender(void)
{
	// 최대체력 칸
	for (int i = 0; i <= *_player->getMaxHP() / 2; i++)
	{
		if (*_player->getMaxHP() % 2 == 1)
		{
			if (i == 0)
			{
				RECT rc = RectMakeCenter(_vMaxHP[i].x, _vMaxHP[i].y, _vMaxHP[i].d2dImage->frameWidth * 0.7, _vMaxHP[i].d2dImage->frameHeight * 0.7);
				D2DMANAGER->frameRender("체력UI", rc.left, rc.top, 0, 0, _vMaxHP[i].d2dImage->frameWidth * 0.7, _vMaxHP[i].d2dImage->frameHeight * 0.7);
				continue;
			}
		}
		else if (*_player->getMaxHP() / 2 == i)
		{
			break;
		}
		D2DMANAGER->frameRender("체력UI", _vMaxHP[i].rc.left, _vMaxHP[i].rc.top, 0, 0);
	}

	// 현재체력칸
	if (*_player->getCurrentHP() == 1)
	{
		if (*_player->getMaxHP() % 2 == 1)
		{
			RECT rc = RectMakeCenter(_vMaxHP[*_player->getMaxHP() / 2 ].x, _vMaxHP[*_player->getMaxHP() / 2].y,
				_vMaxHP[0].d2dImage->frameWidth * 0.7, _vMaxHP[0].d2dImage->frameHeight * 0.7);
			D2DMANAGER->frameRender("체력UI", rc.left, rc.top, 1, 0,
				_vCurrentHP[0].d2dImage->frameWidth * 0.7, _vCurrentHP[0].d2dImage->frameHeight * 0.7);
		}
		else
		{
			RECT rc = RectMakeCenter(_vMaxHP[*_player->getMaxHP() / 2-1].x, _vMaxHP[*_player->getMaxHP() / 2-1].y,
				_vMaxHP[0].d2dImage->frameWidth * 0.7, _vMaxHP[0].d2dImage->frameHeight * 0.7);
			D2DMANAGER->frameRender("체력UI", rc.left, rc.top, 1, 0,
				_vCurrentHP[0].d2dImage->frameWidth * 0.7, _vCurrentHP[0].d2dImage->frameHeight * 0.7);
		}
	}
	else
	{
		for (int i = 0; i < *_player->getCurrentHP() / 2; i++)
		{
			if (*_player->getMaxHP() % 2 == 1)
			{
				D2DMANAGER->frameRender("체력UI", _vMaxHP[*_player->getMaxHP() / 2 - i].rc.left, _vMaxHP[*_player->getMaxHP() / 2 - i].rc.top, 1, 0);
				if (*_player->getCurrentHP() % 2 == 1)
				{
					if (i + 1 == *_player->getCurrentHP() / 2)
					{
						RECT rc = RectMakeCenter(_vMaxHP[*_player->getMaxHP() / 2 - 1 - i].x, _vMaxHP[*_player->getMaxHP() / 2 - 1 - i].y,
							_vMaxHP[i].d2dImage->frameWidth * 0.7, _vMaxHP[i].d2dImage->frameHeight * 0.7);
						D2DMANAGER->frameRender("체력UI", rc.left, rc.top, 1, 0,
							_vCurrentHP[i].d2dImage->frameWidth * 0.7, _vCurrentHP[i].d2dImage->frameHeight * 0.7);
					}
				}
			}
			else
			{
				D2DMANAGER->frameRender("체력UI", _vMaxHP[*_player->getMaxHP() / 2 - 1 - i].rc.left, _vMaxHP[*_player->getMaxHP() / 2 - 1 - i].rc.top, 1, 0);
				if (*_player->getCurrentHP() % 2 == 1)
				{
					if (i + 1 == *_player->getCurrentHP() / 2)
					{
						RECT rc = RectMakeCenter(_vMaxHP[*_player->getMaxHP() / 2 - 1 - i - 1].x, _vMaxHP[*_player->getMaxHP() / 2 - 1 - i - 1].y,
							_vMaxHP[i].d2dImage->frameWidth * 0.7, _vMaxHP[i].d2dImage->frameHeight * 0.7);
						D2DMANAGER->frameRender("체력UI", rc.left, rc.top, 1, 0,
							_vCurrentHP[i].d2dImage->frameWidth * 0.7, _vCurrentHP[i].d2dImage->frameHeight * 0.7);
					}
				}
			}
		}
	}
}

void UI::MPUpdateRender(void)
{
	for (int i = 0; i < *_player->getMaxMP(); i++)
	{
		D2DMANAGER->frameRender("마나UI", _vMaxMP[i].rc.left, _vMaxMP[i].rc.top, 0, 0);
	}
	for (int i = 0; i < *_player->getCurrentMP(); i++)
	{
		D2DMANAGER->frameRender("마나UI", _vMaxMP[i].rc.left, _vMaxMP[i].rc.top, 1, 0);
	}
}

void UI::miniMapRender(void)
{
	// 미니맵 렌더
	D2DMANAGER->render("미니맵배경UI", _miniMap.backGround.rc.left, _miniMap.backGround.rc.top);
	RECT rcMiniMapRender = RectMakeCenter(_miniMap.backGround.x, _miniMap.backGround.y, 100, 100);
	if (_miniMap.miniMap.name == "충-시작&출구")
	{
		D2DMANAGER->render("시작&출구", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방1")
	{
		D2DMANAGER->render("노멀방1", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방2")
	{
		D2DMANAGER->render("노멀방2", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방3")
	{
		D2DMANAGER->render("노멀방3", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방4")
	{
		D2DMANAGER->render("노멀방4", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방5")
	{
		D2DMANAGER->render("노멀방5", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방6")
	{
		D2DMANAGER->render("노멀방6", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방7")
	{
		D2DMANAGER->render("노멀방7", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방8")
	{
		D2DMANAGER->render("노멀방8", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방9")
	{
		D2DMANAGER->render("노멀방9", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방10")
	{
		D2DMANAGER->render("노멀방10", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-노멀방11")
	{
		D2DMANAGER->render("노멀방11", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-보스방")
	{
		D2DMANAGER->render("보스방", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-분수&석상방")
	{
		D2DMANAGER->render("분수&석상방", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-상자방")
	{
		D2DMANAGER->render("상자방", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}
	else if (_miniMap.miniMap.name == "충-상점방")
	{
		D2DMANAGER->render("상점방", rcMiniMapRender.left, rcMiniMapRender.top, 100, 100);
	}

	// 플레이어 위치 표기
	D2DMANAGER->frameRender("미니맵위치UI", _miniMap.playerPoint.x, _miniMap.playerPoint.y, 1, 0);

	// 에너미 위치 표기
	if (_stage->getMapManagerMemoryAddress()->getCurrentMap()->getMapName() == "노멀맵")
	{
		for (int i = 0; i < _stage->getEnemyManagerMemoryAddress()->getSlime().size(); i++)
		{
			int x = _stage->getEnemyManagerMemoryAddress()->getSlime()[i]->getCenterPos().x;
			int y = _stage->getEnemyManagerMemoryAddress()->getSlime()[i]->getCenterPos().y;
			D2DMANAGER->frameRender("미니맵위치UI", rcMiniMapRender.left + (x / (float)WINSIZE_X) * 100, rcMiniMapRender.top + (y / (float)WINSIZE_Y) * 100, 6, 0);
		}
		for (int i = 0; i < _stage->getEnemyManagerMemoryAddress()->getFlime().size(); i++)
		{
			int x = _stage->getEnemyManagerMemoryAddress()->getFlime()[i]->getCenterPos().x;
			int y = _stage->getEnemyManagerMemoryAddress()->getFlime()[i]->getCenterPos().y;
			D2DMANAGER->frameRender("미니맵위치UI", rcMiniMapRender.left + (x / (float)WINSIZE_X) * 100, rcMiniMapRender.top + (y / (float)WINSIZE_Y) * 100, 6, 0);
		}
		for (int i = 0; i < _stage->getEnemyManagerMemoryAddress()->getMushMam().size(); i++)
		{
			int x = _stage->getEnemyManagerMemoryAddress()->getMushMam()[i]->getCenterPos().x;
			int y = _stage->getEnemyManagerMemoryAddress()->getMushMam()[i]->getCenterPos().y;
			D2DMANAGER->frameRender("미니맵위치UI", rcMiniMapRender.left + (x / (float)WINSIZE_X) * 100, rcMiniMapRender.top + (y / (float)WINSIZE_Y) * 100, 6, 0);
		}
		for (int i = 0; i < _stage->getEnemyManagerMemoryAddress()->getSnake().size(); i++)
		{
			int x = _stage->getEnemyManagerMemoryAddress()->getSnake()[i]->getCenterPos().x;
			int y = _stage->getEnemyManagerMemoryAddress()->getSnake()[i]->getCenterPos().y;
			D2DMANAGER->frameRender("미니맵위치UI", rcMiniMapRender.left + (x / (float)WINSIZE_X) * 100, rcMiniMapRender.top + (y / (float)WINSIZE_Y) * 100, 6, 0);
		}
	}


	// 다음 맵 위치 표기
	if (_stage->getMapManagerMemoryAddress()->getCurrentMap()->getIsClear())
	{

		// 왼쪽 방 확인
		if ((_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY()) != nullptr) && _stage->getMapManagerMemoryAddress()->getCurrentX() > 0)
		{
			if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "노멀맵")
			{
				if (!_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getIsClear())
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left - 15, rcMiniMapRender.top + 50, 4, 0, _miniMap.alpha);
				}
				else
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left - 15, rcMiniMapRender.top + 50, 3, 0, _miniMap.alpha);
				}
			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "시작맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "이벤트맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "엔드맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "상자맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left - 15, rcMiniMapRender.top + 50, 2, 0, _miniMap.alpha);

			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() - 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "보스맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left - 15, rcMiniMapRender.top + 50, 5, 0, _miniMap.alpha);

			}
		}


		// 윗 방 확인
		if ((_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1) != nullptr) && _stage->getMapManagerMemoryAddress()->getCurrentY() > 0)
		{
			if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "노멀맵")
			{
				if (!_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getIsClear())
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.top - 15, 4, 0, _miniMap.alpha);
				}
				else
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.top - 15, 3, 0, _miniMap.alpha);
				}
			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "시작맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "이벤트맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "엔드맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "상자맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.top - 15, 2, 0, _miniMap.alpha);

			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() - 1)->getMapName() == "보스맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.top - 15, 5, 0, _miniMap.alpha);

			}
		}

		// 아랫 방 확인
		if ((_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1) != nullptr) && _stage->getMapManagerMemoryAddress()->getCurrentY() < 3)
		{
			if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "노멀맵")
			{
				if (!_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getIsClear())
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.bottom + 10, 4, 0, _miniMap.alpha);
				}
				else
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.bottom + 10, 3, 0, _miniMap.alpha);
				}
			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "시작맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "이벤트맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "엔드맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "상자맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.bottom + 10, 2, 0, _miniMap.alpha);

			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX(), _stage->getMapManagerMemoryAddress()->getCurrentY() + 1)->getMapName() == "보스맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.left + 50, rcMiniMapRender.bottom + 10, 5, 0, _miniMap.alpha);

			}
		}

		// 오른쪽 방 확인
		if ((_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY()) != nullptr) && _stage->getMapManagerMemoryAddress()->getCurrentX() < 4)
		{
			if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "노멀맵")
			{
				if (!_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getIsClear())
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.right + 10, rcMiniMapRender.top + 50, 4, 0, _miniMap.alpha);
				}
				else
				{
					D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.right + 10, rcMiniMapRender.top + 50, 3, 0, _miniMap.alpha);
				}
			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "시작맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "이벤트맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "엔드맵" ||
				_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "상자맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.right + 10, rcMiniMapRender.top + 50, 2, 0, _miniMap.alpha);

			}
			else if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(_stage->getMapManagerMemoryAddress()->getCurrentX() + 1, _stage->getMapManagerMemoryAddress()->getCurrentY())->getMapName() == "보스맵")
			{
				D2DMANAGER->frameAlphaRender("미니맵위치UI", rcMiniMapRender.right + 10, rcMiniMapRender.top + 50, 5, 0, _miniMap.alpha);

			}
		}
		
	}
}

void UI::chargeRender(void)
{
	if (*_chargeUI.isCharging && *_chargeBarUI.gauge> 15)
	{
		D2DMANAGER->frameRender("지팡이차지", (*_chargeUI.pRc).left - 83, (*_chargeUI.pRc).top - 100, _chargeUI.frameX, _chargeUI.frameY);
	}

	if (*_chargeUI.isCharging && *_chargeBarUI.gauge > 15)
	{
		D2DMANAGER->render("차지샷배경", *_chargeBarUI.pX - 36, *_chargeBarUI.pY - 50);
		D2DMANAGER->render("차지샷게이지", *_chargeBarUI.pX - 33, *_chargeBarUI.pY - 48, _chargeBarUI.width, _chargeBarUI.d2dImageFront->height);
	}

}

void UI::bossUIRender(void)
{
	if (_stage->getMapManagerMemoryAddress()->getCurrentMap()->getMapName() == "보스맵")
	{
		D2DMANAGER->render("보스체력게이지", _bossUIHPBar.rc1.left, _bossUIHPBar.rc1.top, _bossUIHPBar.width1, _bossUIHPBar.d2dImageBack->height);
		D2DMANAGER->render("보스체력배경", _bossUIHPBar.rc1.left, _bossUIHPBar.rc1.top);
	}
}

void UI::toggleMapUIRender(void)
{
	if (_toggleMap.isToggleKeyOn)
	{
		_toggleMap.currentAlpha += 0.04;
		if (_toggleMap.currentAlpha >= 1) _toggleMap.currentAlpha = 0.5;

		D2DMANAGER->render("토글맵배경", _toggleMap.rc.left, _toggleMap.rc.top);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j) != nullptr)
				{
					if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getIsVisit())
					{
						if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "노멀맵") D2DMANAGER->render("토글맵확인방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "시작맵") D2DMANAGER->render("토글맵시작방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "이벤트맵") D2DMANAGER->render("토글맵특수방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "상자맵") D2DMANAGER->render("토글맵상자방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "상점맵") D2DMANAGER->render("토글맵상점방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "보스맵") D2DMANAGER->render("토글맵보스방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						else if(_stage->getMapManagerMemoryAddress()->getTotalStageMap(i,j)->getMapName() == "엔드맵") D2DMANAGER->render("토글맵목표방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);

					}
					else if (!_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j)->getIsVisit() &&
						(
							(i>0 && (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i - 1, j) != nullptr) && _stage->getMapManagerMemoryAddress()->getTotalStageMap(i - 1, j)->getIsVisit()) ||
							(i<5 && (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i + 1, j) != nullptr) && _stage->getMapManagerMemoryAddress()->getTotalStageMap(i + 1, j)->getIsVisit()) ||
							(j>0 && (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j - 1) != nullptr) && _stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j - 1)->getIsVisit()) ||
							(j<4&& (_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j + 1) != nullptr) &&_stage->getMapManagerMemoryAddress()->getTotalStageMap(i, j + 1)->getIsVisit())  )
						)
					{
						D2DMANAGER->render("토글맵미확인방", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
						D2DMANAGER->render("토글맵미확인아이콘", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top);
					}
					if ((_stage->getMapManagerMemoryAddress()->getCurrentX() == i) && (_stage->getMapManagerMemoryAddress()->getCurrentY() == j))
					{
						D2DMANAGER->alphaRender("현재맵표시", _toggleMap.rcMap[j][i].left, _toggleMap.rcMap[j][i].top, _toggleMap.currentAlpha);

					}
				}
			}
		}
	}
}

void UI::abillityUIRender(void)
{
	for (int i = 0; i < _player->getAbility().size(); i++)
	{
		_abilityUI[i].d2dImage = _player->getAbility()[i].getImage();
		_abilityUI[i].x = WINSIZE_X / 2 - 100 + i * 45;
		_abilityUI[i].y = WINSIZE_Y - 40;
		_abilityUI[i].rc = RectMakeCenter(_abilityUI[i].x, _abilityUI[i].y, _abilityUI[i].d2dImage->width, _abilityUI[i].d2dImage->height);
		_abilityUI[i].rcDescription = RectMakeCenter(_abilityUI[i].x, _abilityUI[i].y-50, 200, 60);

		D2DMANAGER->render(_player->getAbility()[i].getName(), _abilityUI[i].rc.left, _abilityUI[i].rc.top);
		if (PtInRect(&_abilityUI[i].rc, _ptMouse))
		{
			D2DMANAGER->render("성물설명창", _abilityUI[i].rcDescription.left, _abilityUI[i].rcDescription.top);
		}
	}
}
