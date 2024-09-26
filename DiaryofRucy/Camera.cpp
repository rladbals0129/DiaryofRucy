#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init()
{
    _cameraPos = { 0, 0 };
    _zoomLevel = 1.5f;
    return S_OK;
}

void Camera::update(Player* player)
{
    const int halfWinWidth = static_cast<int>(WINSIZE_X / 2 * _zoomLevel);
    const int halfWinHeight = static_cast<int>(WINSIZE_Y / 2 * _zoomLevel);

    POINT playerPos = player->getPosition();


    _cameraPos.x = min(max(playerPos.x - halfWinWidth, 0), MAP_WIDTH - WINSIZE_X);
    _cameraPos.y = min(max(playerPos.y - halfWinHeight, 0), MAP_HEIGHT - WINSIZE_Y);

    if (_cameraPos.x + WINSIZE_X > MAP_WIDTH)
    {
        _cameraPos.x = MAP_WIDTH - WINSIZE_X;
    }
       
    if (_cameraPos.y + WINSIZE_Y > MAP_HEIGHT)
    {
        _cameraPos.y = MAP_HEIGHT - WINSIZE_Y;
    }
      
}
