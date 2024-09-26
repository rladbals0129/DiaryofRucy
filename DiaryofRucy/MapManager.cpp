#include "Stdafx.h"
#include "MapManager.h"
#include "Player.h"
#include "KingSlime.h"
#include "MegaFlime.h"
#include "MushMamBoss.h"
#include "EnemyManager.h"


#include <typeinfo>

HRESULT MapManager::init(Player* player, int* stage)
{
    
    // Åë·Î »ý¼º
    _rc[0] = RectMakeCenter(WINSIZE_X / 2, 50, 300, 100);
    _rc[1] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y, 300, 50);
    _rc[2] = RectMakeCenter(0, WINSIZE_Y / 2 + 30, 50, 300);
    _rc[3] = RectMakeCenter(WINSIZE_X , WINSIZE_Y / 2 + 40, 50, 300);

    _player = player;

    _currentStage = stage;

    setStage(*_currentStage);

    _changeRoomFadeOut = false;
    _save = false;

    return S_OK;
}

void MapManager::release(void)
{

}

void MapManager::update(void)
{

    moveRoom();

    _currentMap->update();

    // ÇÈ¼¿Ãæµ¹ Ã³¸®
    _currentMap->setPlayerPosition(_player->getPosition());
    _imageName = _currentMap->getImgName();
    pixelCollision(_player->getCollisionRect(), _imageName);
}

void MapManager::render(void)
{
    _currentMap->render();

    // ´ÙÀ½ Åë·Î ·ºÆ®
    if (KEYMANAGER->isToggleKey(VK_F1))
    {
        DrawRectMake(getMemDC(), _rc[0]);
        DrawRectMake(getMemDC(), _rc[1]);
        DrawRectMake(getMemDC(), _rc[2]);
        DrawRectMake(getMemDC(), _rc[3]);
    }
}

void MapManager::d2drender(void)
{
    _currentMap->d2drender();
}


void MapManager::setStage(int stage)
{
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            switch (stage)
            {
            case 1:
                if (_stage1[y][x] != nullptr)
                {
                    _stage1[y][x]->setPlayerMemoryAddress(_player);
                    _stage1[y][x]->init(_currentStage);
                    if (_stage1[y][x]->getMapName() == "³ë¸Ö¸Ê")
                    {
                        NormalMap* dNomalMap = dynamic_cast<NormalMap*>(_stage1[y][x]);
                        _em = dNomalMap->getEnemyManagerMemoryAddress();
                    }
                    else if (_stage1[y][x]->getMapName() == "º¸½º¸Ê")
                    {
                        BossMap* dBossMap = dynamic_cast<BossMap*>(_stage1[y][x]);
                        _kingSlime = dBossMap->getKingSlimeMemoryAddress();
                    }
                    else if (_stage1[y][x]->getMapName() == "½ÃÀÛ¸Ê")
                    {
                        _currentX = x;
                        _currentY = y;
                    }
                    _currentMap = _stage1[_currentY][_currentX];
                }
                break;
            case 2:
                if (_stage2[y][x] != nullptr)
                {
                    _stage2[y][x]->setPlayerMemoryAddress(_player);
                    _stage2[y][x]->init(_currentStage);
                    if (_stage2[y][x]->getMapName() == "³ë¸Ö¸Ê")
                    {
                        NormalMap* dNomalMap = dynamic_cast<NormalMap*>(_stage2[y][x]);
                        _em = dNomalMap->getEnemyManagerMemoryAddress();
                    }
                    else if (_stage2[y][x]->getMapName() == "º¸½º¸Ê")
                    {
                        BossMap* dBossMap = dynamic_cast<BossMap*>(_stage2[y][x]);
                        _megaFlime = dBossMap->getMegaFlimeMemoryAddress();
                    }
                    else if (_stage2[y][x]->getMapName() == "½ÃÀÛ¸Ê")
                    {
                        _currentX = x;
                        _currentY = y;
                    }
                    _currentMap = _stage2[_currentY][_currentX];

                }
                break;
            case 3:
                if (_stage3[y][x] != nullptr)
                {
                    _stage3[y][x]->setPlayerMemoryAddress(_player);
                    _stage3[y][x]->init(_currentStage);
                    if (_stage3[y][x]->getMapName() == "³ë¸Ö¸Ê")
                    {
                        NormalMap* dNomalMap = dynamic_cast<NormalMap*>(_stage3[y][x]);
                        _em = dNomalMap->getEnemyManagerMemoryAddress();
                    }
                    else if (_stage3[y][x]->getMapName() == "º¸½º¸Ê")
                    {
                        BossMap* dBossMap = dynamic_cast<BossMap*>(_stage3[y][x]);
                        _mushMamBoss = dBossMap->getMushMamBossMemoryAddress();
                    }
                    else if (_stage3[y][x]->getMapName() == "½ÃÀÛ¸Ê")
                    {
                        _currentX = x;
                        _currentY = y;
                    }
                    _currentMap = _stage3[_currentY][_currentX];
                }
                break;
            default:
            break;            
            }
        }
    }
}


void MapManager::moveRoom()
{
    RECT rc;
    // À§ÂÊ
    if (IntersectRect(&rc, &_player->getCollisionRect(), &_rc[0]))
    {
        if (_currentY > 0)
        {
            if ((*_currentStage == 1) && (_stage1[_currentY-1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY -= 1;
                    _player->setPosition(WINSIZE_X / 2, WINSIZE_Y - 100);
                    _stage1[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if((*_currentStage == 2) && (_stage2[_currentY - 1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY -= 1;
                    _player->setPosition(WINSIZE_X / 2, WINSIZE_Y - 100);
                    _stage2[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if((*_currentStage == 3) && (_stage3[_currentY - 1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY -= 1;
                    _player->setPosition(WINSIZE_X / 2, WINSIZE_Y - 100);
                    _stage3[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
        }
    }
    //¾Æ·¡ÂÊ
    else if (IntersectRect(&rc, &_player->getCollisionRect(), &_rc[1]))
    {
        if (_currentY < 3)
        {
            if ((*_currentStage == 1) && (_stage1[_currentY + 1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY += 1;
                    _player->setPosition(WINSIZE_X / 2, 100);
                    _stage1[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if ((*_currentStage == 2) && (_stage2[_currentY + 1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY += 1;
                    _player->setPosition(WINSIZE_X / 2, 100);
                    _stage2[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if ((*_currentStage == 3) && (_stage3[_currentY + 1][_currentX] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentY += 1;
                    _player->setPosition(WINSIZE_X / 2, 100);
                    _stage3[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
        }
    }
    // ¿ÞÂÊ
    else if (IntersectRect(&rc, &_player->getCollisionRect(), &_rc[2]))
    {
        if (_currentX > 0)
        {
            if ((*_currentStage == 1) && (_stage1[_currentY][_currentX - 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX -= 1;
                    _player->setPosition(WINSIZE_X - 100, WINSIZE_Y / 2 + 80);
                    _stage1[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if ((*_currentStage == 2) && (_stage2[_currentY][_currentX - 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX -= 1;
                    _player->setPosition(WINSIZE_X - 100, WINSIZE_Y / 2 + 80);
                    _stage2[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;

                }
            }
            else if ((*_currentStage == 3) && (_stage3[_currentY][_currentX - 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX -= 1;
                    _player->setPosition(WINSIZE_X - 100, WINSIZE_Y / 2 + 80);
                    _stage3[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }

        }
    }
    // ¿À¸¥ÂÊ
    else if (IntersectRect(&rc, &_player->getCollisionRect(), &_rc[3]))
    {
        if (_currentX < 4)
        {
            if ((*_currentStage == 1) && (_stage1[_currentY][_currentX + 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX += 1;
                    _player->setPosition(100, WINSIZE_Y / 2 + 80);
                    _stage1[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if ((*_currentStage == 2) && (_stage2[_currentY][_currentX + 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX += 1;
                    _player->setPosition(100, WINSIZE_Y / 2 + 80);
                    _stage2[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
            else if ((*_currentStage == 3) && (_stage3[_currentY][_currentX + 1] != nullptr))
            {
                IMAGEMANAGER->fadeOut();
                if (IMAGEMANAGER->getAlpha() == 255)
                {
                    _currentX += 1;
                    _player->setPosition(100, WINSIZE_Y / 2 + 80);
                    _stage3[_currentY][_currentX]->setIsVisit();
                    _changeRoomFadeOut = true;
                    _save = true;
                }
            }
        }
    }
   
    if (_changeRoomFadeOut || _loadGame)
    {
        IMAGEMANAGER->fadeIn();
        if (IMAGEMANAGER->getAlpha() == 0)
        {
            _changeRoomFadeOut = false;
            _loadGame = false;
        }
    }

    switch (*_currentStage)
    {
    case 1:
        _currentMap = _stage1[_currentY][_currentX];
        break;
    case 2:
        _currentMap = _stage2[_currentY][_currentX];
        break;
    case 3:
        _currentMap = _stage3[_currentY][_currentX];
        break;
    default:
        break;
    }

    if (_currentMap->getMapName() == "³ë¸Ö¸Ê")
    {
        NormalMap* dNomalMap = dynamic_cast<NormalMap*>(_currentMap);
        _em = dNomalMap->getEnemyManagerMemoryAddress();
        _player->setEnemyManagerMomoryAddress(_em);
    }
}
