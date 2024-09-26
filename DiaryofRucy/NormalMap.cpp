#include "Stdafx.h"
#include "NormalMap.h"



HRESULT NormalMap::vInit()
{
    _mapName = "노멀맵";
    randMap = RND->getFromIntTo(1, 11);

    switch (randMap)
    {
    case 1:
        _image = IMAGEMANAGER->addImage("노멀방1", "Resources/Images/Maps/MapImage/노멀방1.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방1", "Resources/Images/Maps/Collision/충-노멀방1.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방1";
        

        break;

    case 2:
        _image = IMAGEMANAGER->addImage("노멀방2", "Resources/Images/Maps/MapImage/노멀방2.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방2", "Resources/Images/Maps/Collision/충-노멀방2.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방2";
        break;

    case 3:
        _image = IMAGEMANAGER->addImage("노멀방3", "Resources/Images/Maps/MapImage/노멀방3.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방3", "Resources/Images/Maps/Collision/충-노멀방3.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방3";
        break;

    case 4:
        _image = IMAGEMANAGER->addImage("노멀방4", "Resources/Images/Maps/MapImage/노멀방4.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방4", "Resources/Images/Maps/Collision/충-노멀방4.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방4";

        break;

    case 5:
        _image = IMAGEMANAGER->addImage("노멀방5", "Resources/Images/Maps/MapImage/노멀방5.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방5", "Resources/Images/Maps/Collision/충-노멀방5.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
        
        _imgName = "충-노멀방5";
        break;

    case 6:
        _image = IMAGEMANAGER->addImage("노멀방6", "Resources/Images/Maps/MapImage/노멀방6.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방6", "Resources/Images/Maps/Collision/충-노멀방6.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방6";
        break;

    case 7:
        _image = IMAGEMANAGER->addImage("노멀방7", "Resources/Images/Maps/MapImage/노멀방7.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방7", "Resources/Images/Maps/Collision/충-노멀방7.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방7";
        break;

    case 8:
        _image = IMAGEMANAGER->addImage("노멀방8", "Resources/Images/Maps/MapImage/노멀방8.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방8", "Resources/Images/Maps/Collision/충-노멀방8.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방8";
        break;

    case 9:
        _image = IMAGEMANAGER->addImage("노멀방9", "Resources/Images/Maps/MapImage/노멀방9.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방9", "Resources/Images/Maps/Collision/충-노멀방9.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방9";
        break;

    case 10:
        _image = IMAGEMANAGER->addImage("노멀방10", "Resources/Images/Maps/MapImage/노멀방10.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방10", "Resources/Images/Maps/Collision/충-노멀방10.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방10";
        break;

    case 11:
        _image = IMAGEMANAGER->addImage("노멀방11", "Resources/Images/Maps/MapImage/노멀방11.bmp", WINSIZE_X, WINSIZE_Y);
        _colImg = IMAGEMANAGER->addImage("충-노멀방11", "Resources/Images/Maps/Collision/충-노멀방11.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

        _imgName = "충-노멀방11";
        break;
    }
    _em = new EnemyManager;
    _em->init();
    _em->setPlayerMemoryAddress(_player);


    _pImgNameL = _imgName;
    _pImgNameR = _imgName;
    //_em->setMushMam(600,400);
    
    int rndSpownNum = RND->getFromIntTo(3,6);
    for (int i = 0; i < rndSpownNum; i++)
    {
        switch (RND->getInt(4))
        {
        case 0:
            _em->setSnake(RND->getFromIntTo(WINSIZE_X/2-200,WINSIZE_X/2+200), RND->getFromIntTo(WINSIZE_Y / 2 -150, WINSIZE_Y / 2 + 150));
            break;
        case 1:
            _em->setMushMam(RND->getFromIntTo(WINSIZE_X / 2 - 200, WINSIZE_X / 2 + 200), RND->getFromIntTo(WINSIZE_Y / 2 - 150, WINSIZE_Y / 2 + 150));
            break;
        case 2:
            _em->setSlime(RND->getFromIntTo(WINSIZE_X / 2 - 200, WINSIZE_X / 2 + 200), RND->getFromIntTo(WINSIZE_Y / 2 - 150, WINSIZE_Y / 2 + 150));
            break;
        case 3:
            _em->setFlime(RND->getFromIntTo(WINSIZE_X / 2 - 200, WINSIZE_X / 2 + 200), RND->getFromIntTo(WINSIZE_Y / 2 - 150, WINSIZE_Y / 2 + 150));
            break;
        default:
            break;
        }
    }



    _isClear = false;
    return S_OK;

}

void NormalMap::release(void)
{
    SAFE_DELETE(_em);
}

void NormalMap::enemyUpdate(void)
{
    if (_em != nullptr)
    {
        if (IMAGEMANAGER->getAlpha() == 0) _em->update();
        if ((_em->getSnake().size() == 0) && (_em->getSlime().size() == 0) && (_em->getFlime().size() == 0) && (_em->getMushMam().size() == 0) && (_em->getTurret().size() == 0))
        {
            _isClear = true;
        }
    }
    if (_isClear)
    {
        for (int i = 0; i < _em->getSnake().size(); i++)  _em->removeSnake(i);
        for (int i = 0; i < _em->getSlime().size(); i++)  _em->removeSlime(i);
        for (int i = 0; i < _em->getFlime().size(); i++)  _em->removeFlime(i);
        for (int i = 0; i < _em->getMushMam().size(); i++)  _em->removeMushMam(i);
        for (int i = 0; i < _em->getTurret().size(); i++)  _em->removeTurret(i);
    }
}

void NormalMap::enemyRender(void)
{
    _em->render();
}

void NormalMap::d2dEnemyRender(void)
{
   _em->d2drender();
}

void NormalMap::d2dObjectRender(void)
{
    if (!_isClear)
    {
        // 카메라 구현 전 까지는 어려울듯
        //D2DMANAGER->render("벽-상", WINSIZE_X / 2 - D2DMANAGER->findImage("벽-상")->width / 2, -D2DMANAGER->findImage("벽-상")->height + 180);
    }

}
