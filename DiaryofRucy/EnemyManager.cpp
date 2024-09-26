#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Snake.h"
#include "Slime.h"
#include "Flime.h"
#include "MushMam.h"
#include "MiniGreenTurret.h"
HRESULT EnemyManager::init(void)
{
    
    _espBullet = new EspBullet;
    _espBullet->init("유도탄", 100, 150);
    _bigBullet = new EnemyBullet;
    _bigBullet->init("큰일반탄", 100, 400,0);


   // setSnake(400,400);
   // setMushMam(500,400);
   // setSlime(600,400);
   // setFlime(700,400);


    return S_OK;
}

void EnemyManager::release(void)
{
    _espBullet->release();
    _bigBullet->release();
    for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
    {
        (*_viSnake)->release();
        SAFE_DELETE(*_viSnake);
    }
    for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
    {
        (*_viSlime)->release();
        SAFE_DELETE(*_viSlime);
    }
    for (_viMushMam = _vMushMam.begin(); _viMushMam != _vMushMam.end(); ++_viMushMam)
    {
        (*_viMushMam)->release();
        SAFE_DELETE(*_viMushMam);
    }
    for (_viFlime = _vFlime.begin(); _viFlime != _vFlime.end(); ++_viFlime)
    {
        (*_viFlime)->release();
        SAFE_DELETE(*_viFlime);
    }
}

void EnemyManager::update(void)
{
    for (int i = 0; i < _vSnake.size(); i++)
    {
        if (_vSnake[i]->getDie())
        {
            removeSnake(i);
            _player->setExp(9);
        }
        else
        {
            _vSnake[i]->update();               
        }
    }

    for (int i = 0; i < _vSlime.size(); i++)
    {
        if (_vSlime[i]->getDie())
        {
            removeSlime(i);
            _player->setExp(9);
        }
        else
        {
            _vSlime[i]->update();
        }
    }

    for (int i = 0; i < _vMushMam.size(); i++)
    {
        if (_vMushMam[i]->getDie())
        {
            removeMushMam(i);
            _player->setExp(9);
        }
        else
        {
            _vMushMam[i]->update();
            if (_vMushMam[i]->getCreateTurret())
            {
                setTurret(_vMushMam[i]->getCenterPos().x, _vMushMam[i]->getCenterPos().y + 30);
                _vMushMam[i]->setCreateTurret(false);
            }
        }
    }

    for (int i = 0; i < _vFlime.size(); i++)
    {
        if (_vFlime[i]->getDie())
        {
            removeFlime(i);
            _player->setExp(9);
        }
        else
        {
            _vFlime[i]->update();  
        }
    }
    for (int i = 0; i < _vTurret.size(); i++)
    {
        if (_vTurret[i]->getDie()&&!_vTurret[i]->getLastFire())
        {
            removeTurret(i);
            _player->setExp(9);
        }
        else
        {
            _vTurret[i]->update();
        }
    }


    turretBulletFire();
    _espBullet->update();
    _espBullet->updateAngle(_player->getPosition().x, _player->getPosition().y);
    _bigBullet->update();
    rangeInPlayer(_vSnake, _viSnake);
    rangeInPlayer(_vSlime, _viSlime);
    rangeInPlayer(_vMushMam, _viMushMam);
    rangeInPlayer(_vFlime, _viFlime);
    collision();


}

void EnemyManager::render(void)
{
    for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
    {
        (*_viSnake)->render();
    }
    for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
    {
        (*_viSlime)->render();
    }
    for (_viMushMam = _vMushMam.begin(); _viMushMam != _vMushMam.end(); ++_viMushMam)
    {
        (*_viMushMam)->render();
    }
    for (_viFlime = _vFlime.begin(); _viFlime != _vFlime.end(); ++_viFlime)
    {
        (*_viFlime)->render();
    }
    for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); ++_viTurret)
    {
        (*_viTurret)->render();
    }



    for (int i = 0; i < _espBullet->getBullet().size(); i++)
    {
        if (KEYMANAGER->isToggleKey(VK_F1))
        {
           // DrawRectMake(getMemDC(),)
            OBBDrawRotatedRect(getMemDC(), CollisionAreaResizing(_espBullet->getBullet()[i].rc, 10, 10), -(_espBullet->getBullet()[i].angle));
        }
    }

}

void EnemyManager::d2drender(void)
{
    for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
    {
        (*_viSnake)->d2drender();
    }
    for (_viSlime = _vSlime.begin(); _viSlime != _vSlime.end(); ++_viSlime)
    {
        (*_viSlime)->d2drender();
    }
    for (_viMushMam = _vMushMam.begin(); _viMushMam != _vMushMam.end(); ++_viMushMam)
    {
        (*_viMushMam)->d2drender();
    }
    for (_viFlime = _vFlime.begin(); _viFlime != _vFlime.end(); ++_viFlime)
    {
        (*_viFlime)->d2drender();
    }
    for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); ++_viTurret)
    {
        (*_viTurret)->d2drender();
    }
    _espBullet->d2drender();
    _bigBullet->d2drender();
}

void EnemyManager::setSnake(int x, int y)
{
 
     Enemy* snake = new Snake(State::IDLE);
     snake->init("뱀IDLE", PointMake(x, y));

     _vSnake.push_back(snake);

}

void EnemyManager::setSlime(int x, int y)
{
    Enemy* slime = new Slime(State::IDLE);
    slime->init("슬라임IDLE", PointMake(x, y));

    _vSlime.push_back(slime);
}

void EnemyManager::setFlime(int x, int y)
{
    Enemy* flime = new Flime(State::IDLE);
    flime->init("꽃IDLE", PointMake(x, y));

    _vFlime.push_back(flime);
}

void EnemyManager::setMushMam(int x, int y)
{

    Enemy* mushmam = new MushMam(State::IDLE);
    mushmam->init("머쉬맘IDLE", PointMake(x, y));

    _vMushMam.push_back(mushmam);
}

void EnemyManager::setTurret(int x, int y)
{
    Turret* miniGreen = new MiniGreenTurret;
    miniGreen->init("초록포탑", PointMake(x, y));
    _vTurret.push_back(miniGreen);
}

void EnemyManager::turretBulletFire()
{
    for (_viTurret = _vTurret.begin(); _viTurret != _vTurret.end(); ++_viTurret)
    {
        if ((*_viTurret)->bulletCountFire())
        {
            RECT rc = (*_viTurret)->getRect();
            _espBullet->fire(rc.left + (rc.right  -rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2,
                getAngle(rc.left + (rc.right  -rc.left) / 2,
                    rc.bottom + (rc.top - rc.bottom) / 2,
                    _player->getPosition().x,
                    _player->getPosition().y), 3.f);
        }

        if ((*_viTurret)->getLastFire())
        {
            RECT rc = (*_viTurret)->getRect();
            float angleStep = PI / 10;
            for (int i = 0; i < 20; ++i)
            {
                float fireangle = i * angleStep;
                _bigBullet->fire(rc.left + (rc.right + -rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, fireangle, 3.f);
            }

            (*_viTurret)->setLastFire(false);
            (*_viTurret)->setDie(true);

        }
    }
}

void EnemyManager::removeSnake(int arrNum)
{
    SAFE_DELETE(_vSnake[arrNum]);
    _vSnake.erase(_vSnake.begin() + arrNum);
}

void EnemyManager::removeSlime(int arrNum)
{
    SAFE_DELETE(_vSlime[arrNum]);
    _vSlime.erase(_vSlime.begin() + arrNum);
}

void EnemyManager::removeMushMam(int arrNum)
{
    SAFE_DELETE(_vMushMam[arrNum]);
    _vMushMam.erase(_vMushMam.begin() + arrNum);

}

void EnemyManager::removeFlime(int arrNum)
{
    SAFE_DELETE(_vFlime[arrNum]);
    _vFlime.erase(_vFlime.begin() + arrNum);
}

void EnemyManager::removeTurret(int arrNum)
{
    SAFE_DELETE(_vTurret[arrNum]);
    _vTurret.erase(_vTurret.begin() + arrNum);
}


void EnemyManager::collision(void)
{
    for (int i = 0; i < _vSnake.size(); i++)
    {

        for (int j = 0; j < _vSnake[i]->getSmallBullet()->getBullet().size(); j++)
        {
            RECT col;
            if (IntersectRect(&col, &_vSnake[i]->getSmallBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && !_player->getInvincible())
            {
                _vSnake[i]->getSmallBullet()->removeBullet(j);
                _player->setDamaged();

                //SD: 플레이어 피격사운드
                break;
            }
            else if (IntersectRect(&col, &_vSnake[i]->getSmallBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && _player->getBehaviorType(4))
            {
                _player->setAvoidManaRecovery();
            }
        }
    }

    for (int i = 0; i < _vSlime.size(); i++)
    {

        for (int j = 0; j < _vSlime[i]->getSmallBullet()->getBullet().size(); j++)
        {
            RECT col;
            if (IntersectRect(&col, &_vSlime[i]->getSmallBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && !_player->getInvincible())
            {
                _vSlime[i]->getSmallBullet()->removeBullet(j);
                _player->setDamaged();
                //SD: 플레이어 피격사운드
                break;
            }
            else if (IntersectRect(&col, &_vSlime[i]->getSmallBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && _player->getBehaviorType(4))
            {
                _player->setAvoidManaRecovery();
            }

        }
    }

    for (int i = 0; i < _vSlime.size(); i++)
    {

        for (int j = 0; j < _vSlime[i]->getBigBullet()->getBullet().size(); j++)
        {
            RECT col;
            if (IntersectRect(&col, &_vSlime[i]->getBigBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && !_player->getInvincible())
            {
                _vSlime[i]->getBigBullet()->removeBullet(j);
                _player->setDamaged();
                //SD: 플레이어 피격사운드
                break;
            }
            else if (IntersectRect(&col, &_vSlime[i]->getBigBullet()->getBullet()[j].rc,
                &_player->getCollisionRect()) && _player->getBehaviorType(4))
            {
                _player->setAvoidManaRecovery();
            }


        }
    }


    for (int i = 0; i < _vFlime.size(); i++)
    {

        for (int j = 0; j < _vFlime[i]->getPoisonBullet()->getBullet().size(); j++)
        {
            RECT col;
            if (IntersectRect(&col, &CollisionAreaResizing(_vFlime[i]->getPoisonBullet()->getBullet()[j].rc,30,30),
                &_player->getCollisionRect()) && !_player->getInvincible())
            {
            
                _player->setDamaged();
                //SD: 플레이어 피격사운드
                break;
            }
            else if (CollisionAreaResizing(_vFlime[i]->getPoisonBullet()->getBullet()[j].rc, 30, 30),
                &_player->getCollisionRect() && _player->getBehaviorType(4))
            {
                _player->setAvoidManaRecovery();
            }

        }
    }

    for (int i = 0; i < _vFlime.size(); i++)
    {

        for (int j = 0; j < _vFlime[i]->getThorn()->getBullet().size(); j++)
        {
            RECT col;
            if (IntersectRect(&col, &CollisionAreaResizing(_vFlime[i]->getThorn()->getBullet()[j].rc,128,128),
                &_player->getCollisionRect()) && !_player->getInvincible())
            {
    
                _player->setDamaged(2);
                //SD: 플레이어 피격사운드
                break;
            }
            else if (IntersectRect(&col, &CollisionAreaResizing(_vFlime[i]->getThorn()->getBullet()[j].rc, 128, 128),
                &_player->getCollisionRect()) && _player->getBehaviorType(4))
            {
                _player->setAvoidManaRecovery();
            }

        }
    }
    for (int i = 0; i < _espBullet->getBullet().size(); i++)
    {
        if (isOBBCollision(CollisionAreaResizing(_espBullet->getBullet()[i].rc, 0, 0),
            _espBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f)
            && !_player->getInvincible())
        {
            _espBullet->removeBullet(i);
            _player->setDamaged();
            //SD: 플레이어 피격사운드
        }   
        else if (isOBBCollision(CollisionAreaResizing(_espBullet->getBullet()[i].rc, 0, 0),
            _espBullet->getBullet()[i].angle, _player->getCollisionRect(), 0.f) && _player->getBehaviorType(4))
        {
            _player->setAvoidManaRecovery();
        }
    }

    for (int i = 0; i < _bigBullet->getBullet().size(); i++)
    {
        RECT rc;
        if (IntersectRect(&rc, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 30, 30),
            &_player->getCollisionRect()) && !_player->getInvincible())
        {
            _bigBullet->removeBullet(i);
            _player->setDamaged();
            //SD: 플레이어 피격사운드
        }
        else if (IntersectRect(&rc, &CollisionAreaResizing(_bigBullet->getBullet()[i].rc, 30, 30),
            &_player->getCollisionRect()) && _player->getBehaviorType(4))
        {
            _player->setAvoidManaRecovery();
        }

    }
    

}

void EnemyManager::enemyBulletFire(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName)
{
    (*viEnemyName)->setCanAttack(true);
    if (!(*viEnemyName)->getFireAngleInit())
    {
        float startX = (*viEnemyName)->getCenterPos().x;
        float startY = (*viEnemyName)->getCenterPos().y;
        float endX = _player->getPosition().x;
        float endY = _player->getPosition().y;

        (*viEnemyName)->setThornPos(PointMake(_player->getPosition().x, _player->getPosition().y));
       
        (*viEnemyName)->setFireAngle(getAngle(startX, startY, endX, endY));

        (*viEnemyName)->setFireAngleInit(true);

    }   
}

void EnemyManager::enemyDirectionTracking(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName)
{
 

        (*viEnemyName)->setAnimDirectionAngle(getAngle((*viEnemyName)->getCenterPos().x,
            (*viEnemyName)->getCenterPos().y,
            _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
            _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) - 0.785f);

       // cout << (*_viSnake)->getAnimDirectionAngle() << endl;
        if ((*viEnemyName)->getState() == MOVE || (*viEnemyName)->getState() == IDLE)
        {
            if ((*viEnemyName)->getAnimDirectionAngle() >= 0.f && (*viEnemyName)->getAnimDirectionAngle() < 1.543f)
            {
                (*viEnemyName)->setAnimDirection(UP);
            }
            if ((*viEnemyName)->getAnimDirectionAngle() >= 1.543f && (*viEnemyName)->getAnimDirectionAngle() < 3.113f)
            {
                (*viEnemyName)->setAnimDirection(LEFT);
            }
            if ((*viEnemyName)->getAnimDirectionAngle() >= 3.113f && (*viEnemyName)->getAnimDirectionAngle() < 4.656f)
            {
                (*viEnemyName)->setAnimDirection(DOWN);
            }
            if ((*viEnemyName)->getAnimDirectionAngle() >= 4.656f && (*viEnemyName)->getAnimDirectionAngle() < 6.28f ||
                (*viEnemyName)->getAnimDirectionAngle() < 0 && (*viEnemyName)->getAnimDirectionAngle() > -0.785f)
            {
                (*viEnemyName)->setAnimDirection(RIGHT);
            }
        }
       

        //  for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
  // {
       //getRect().left + ((*_viSnake)->getRect().right - (*_viSnake)->getRect().left) / 2
       //getRect().top + ((*_viSnake)->getRect().bottom - (*_viSnake)->getRect().top) / 2
 //   }



}

void EnemyManager::enemyPositionTracking(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName)
{
   
        //(*viEnemyName)->setAngle(getAngle((*viEnemyName)->getRect().left + ((*viEnemyName)->getRect().right - (*viEnemyName)->getRect().left) / 2,
        //    (*viEnemyName)->getRect().top + ((*viEnemyName)->getRect().bottom - (*viEnemyName)->getRect().top) / 2,
        //    _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
        //    _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2));

        if (getDistance((*viEnemyName)->getRect().left + ((*viEnemyName)->getRect().right - (*viEnemyName)->getRect().left) / 2,
            (*viEnemyName)->getRect().top + ((*viEnemyName)->getRect().bottom - (*viEnemyName)->getRect().top) / 2,
            _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
            _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) < 50.f)
        {
            (*viEnemyName)->setSafeDistance(false);
        }
        else if (getDistance((*viEnemyName)->getRect().left + ((*viEnemyName)->getRect().right - (*viEnemyName)->getRect().left) / 2,
            (*viEnemyName)->getRect().top + ((*viEnemyName)->getRect().bottom - (*viEnemyName)->getRect().top) / 2,
            _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2,
            _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2) > 50.f)
        {
            (*viEnemyName)->setSafeDistance(true);
        }
    
       
        //  for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
//   {
   // }



}

void EnemyManager::rangeInPlayer(vector<Enemy*> vEnemyName, vector<Enemy*>::iterator viEnemyName)
{
    for (viEnemyName = vEnemyName.begin(); viEnemyName != vEnemyName.end(); ++viEnemyName)
    {
        float playerX = _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2;
        float playerY = _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2;

        if (getDistance((*viEnemyName)->getCenterPos().x, (*viEnemyName)->getCenterPos().y,
            playerX,
            playerY) < 400.f)
        {
            float angle = getAngle((*viEnemyName)->getCenterPos().x, (*viEnemyName)->getCenterPos().y,
                playerX,
                playerY);
            (*viEnemyName)->setAngle(angle);
            enemyPositionTracking(vEnemyName, viEnemyName);
            enemyDirectionTracking(vEnemyName, viEnemyName);
            enemyBulletFire(vEnemyName, viEnemyName);
  
        }
        else if (getDistance((*viEnemyName)->getCenterPos().x, (*viEnemyName)->getCenterPos().y,
            playerX,
            playerY) >= 400.f  && (*viEnemyName)->getState() == MOVE)
        {
          //  cout << (*viEnemyName)->getDirectionAngleRndInit() << endl;
            if (!(*viEnemyName)->getDirectionAngleRndInit())
            {
                (*viEnemyName)->setDirectionAngleRndInit(true);
                float randomAngle = RND->getFromFloatTo(-0.785f, 5.795f);
                (*viEnemyName)->setRndRandomAngle(randomAngle);
            //    cout << (*viEnemyName)->getRndRandomAngle() << endl;
               
                if ((*viEnemyName)->getRndRandomAngle() >= 0.f && (*viEnemyName)->getRndRandomAngle() < 1.543f)
                {
                    (*viEnemyName)->setAnimDirection(UP);
                }
                if ((*viEnemyName)->getRndRandomAngle() >= 1.543f && (*viEnemyName)->getRndRandomAngle() < 3.113f)
                {
                    (*viEnemyName)->setAnimDirection(LEFT);
                }
                if ((*viEnemyName)->getRndRandomAngle() >= 3.113f && (*viEnemyName)->getRndRandomAngle() < 4.656f)
                {
                    (*viEnemyName)->setAnimDirection(DOWN);
                }
                if ((*viEnemyName)->getRndRandomAngle() >= 4.656f && (*viEnemyName)->getRndRandomAngle() < 5.795f ||
                    (*viEnemyName)->getRndRandomAngle() < 0 && (*viEnemyName)->getRndRandomAngle() >= -0.785f)
                {
                    (*viEnemyName)->setAnimDirection(RIGHT);
                }                            
                (*viEnemyName)->setAngle((*viEnemyName)->getRndRandomAngle() + 0.785f);
            }
    
        }

    }


    for (viEnemyName = vEnemyName.begin(); viEnemyName != vEnemyName.end(); ++viEnemyName)
    {
        float playerX = _player->getRect().left + (_player->getRect().right - _player->getRect().left) / 2;
        float playerY = _player->getRect().top + (_player->getRect().bottom - _player->getRect().top) / 2;
        if (getDistance((*viEnemyName)->getCenterPos().x, (*viEnemyName)->getCenterPos().y,
            playerX,
            playerY) > 400.f && (*viEnemyName)->getState() != ATTACK && (*viEnemyName)->getState() != ATTACK2 && (*viEnemyName)->getState() != ATTACK3)
        {

            (*viEnemyName)->setCanAttack(false);
           // (*viEnemyName)->setState(IDLE);
        }
    }
 
}


