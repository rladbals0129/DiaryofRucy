#pragma once
#include "Player.h"
#define MAP_WIDTH 1280
#define MAP_HEIGHT 720
class Camera
{
private:
    POINT _cameraPos;
    float _zoomLevel;

public:
    HRESULT init();
    void update(Player* player);
   

    void setZoomLevel(float zoomLevel){ this->_zoomLevel = zoomLevel; }

    POINT getCameraPosition() { return this->_cameraPos; }
    float getZoomLevel() { return this->_zoomLevel; }


};

