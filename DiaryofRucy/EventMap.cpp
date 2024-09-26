#include "Stdafx.h"
#include "EventMap.h"
#include "Player.h"

HRESULT EventMap::vInit(void)
{
	_mapName = "이벤트맵";
	_image = IMAGEMANAGER->addImage("분수&석상방", "Resources/Images/Maps/MapImage/분수&석상방.bmp", WINSIZE_X, WINSIZE_Y);
	_colImg = IMAGEMANAGER->addImage("충-분수&석상방", "Resources/Images/Maps/Collision/충-분수&석상방.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	
	_imgName = "충-분수&석상방";
	_pImgNameL = "충-분수&석상방";
	_pImgNameR = "충-분수&석상방";

	_rndEvent = RND->getInt(2);
	//_rndEvent = 0;

	if (_rndEvent == 0)
	{
		_fountainType = RND->getInt(2);
		//_fountainType = 1;

		if (_fountainType == 0) // 블루
		{
			_fountain = new Fountain;
			_fountain->init(1);
		}
		else // 레드
		{
			_fountain = new Fountain;
			_fountain->init(2);
		}
	}
	if (_rndEvent == 1)
	{
		_statueRightType = RND->getFromIntTo(1, 4);
		_statueLeftType = RND->getFromIntTo(1, 4);

		//_statueType = 0;
		// 석상 일때

		_statue = new Statue;
		_statue->init(_statueLeftType, _statueRightType);
	}
	_isClear = true;

	return S_OK;
}

void EventMap::release(void)
{
	SAFE_DELETE(_fountain);
	SAFE_DELETE(_statue);
}

void EventMap::objectUpdate(void)
{
	if (_rndEvent == 0) // 분수이벤트 일때
	{
		if (!_fountain->getOff()) // 분수가 켜져있다면
		{
			_fountain->update(); //프레임을 돌린다

			// 플레이어가 공격 했을 때
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_fountain->fountainOff();
				//SD: 오브젝트 분수, 석상 공격시 평타 타격음 추가
				if (_fountainType == 0)
				{
					SOUNDMANAGER->play("오브젝트마나", 0.5f);
					while (*_player->getCurrentMP() < *_player->getMaxMP())
					{
						_player->setCurrentMP(1);
					}
				}
				else if (_fountainType == 1)
				{
					SOUNDMANAGER->play("오브젝트체력", 0.5f);
					while (*_player->getCurrentHP() < *_player->getMaxHP())
					{
						_player->setCurrentHP(1);
					}
				}
			}
		}
	}
	else if (_rndEvent == 1)// 석상 이벤트 일때
	{
		if (!_statue->getOff1() || !_statue->getOff2()) // 석상이 켜져 있다면
		{
			_statue->update(); // 프레임을 돌린다.

			if (KEYMANAGER->isOnceKeyDown('F')) // 플레이어가 공격시
			{
				if (getDistance(_player->getPosition().x, _player->getPosition().y, _statue->getRightPosition().x, _statue->getRightPosition().y) < _statue->getRightDistanceWithPlayer())
				{
					_statue->statueOff(); // 석상을 끈다.

					switch (_statueRightType)
					{
					case 1:
						SOUNDMANAGER->play("오브젝트마나", 0.1f);
						_player->setMaxMP(2);
						break;

					case 2:
						SOUNDMANAGER->play("루시피격음", 0.1f);
						_player->setMaxMP(-2);
						if (_player->getMaxMP() < _player->getCurrentMP())
						{
							_player->setCurrentMP(-2);
						}
						break;

					case 3:
						SOUNDMANAGER->play("오브젝트체력", 0.1f);
						_player->setMaxHP(2);
						break;

					case 4:
						SOUNDMANAGER->play("루시피격음", 0.1f);
						_player->setMaxHP(-2);
						if (_player->getMaxHP() < _player->getCurrentHP())
						{
							_player->setCurrentHP(-2);
						}
						break;

					default:
						break;
					}
				}
				else
				{
					_statue->statueOff(); // 석상을 끈다.

					switch (_statueLeftType)
					{
					case 1:
						SOUNDMANAGER->play("오브젝트마나", 0.1f);
						_player->setMaxMP(2);
						break;

					case 2:
						SOUNDMANAGER->play("루시피격음", 0.1f);
						_player->setMaxMP(-2);
						if (_player->getMaxMP() < _player->getCurrentMP())
						{
							_player->setCurrentMP(-2);
						}
						break;

					case 3:
						SOUNDMANAGER->play("오브젝트체력", 0.1f);
						_player->setMaxHP(2);
						break;

					case 4:
						SOUNDMANAGER->play("루시피격음", 0.1f);
						_player->setMaxHP(-2);
						if (_player->getMaxHP() < _player->getCurrentHP())
						{
							_player->setCurrentHP(-2);
						}
						break;

					default:
						break;
					}
				}
				/*
				 공격한 석상이
				 -> 체력 / 마나
				 -> 천사 / 악마
				 경우에 따라 발동될 행동을 써준다.
				*/
			}
		}
	}
}

void EventMap::objectRender(void)
{
	if (_rndEvent == 0)
	{
		_fountain->render();
	}
	else
	{
		_statue->render();
	}
}
