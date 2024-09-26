#pragma once
#include "GImage.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
    HDC _hdc;
    bool _managerInit;
   

public:
    virtual HRESULT init(void);
    virtual HRESULT init(bool managerInit);
    virtual void release(void);
    virtual void update(void);
    virtual void render(void);
    virtual void d2drender(void);
    virtual void UIrender(void);

    // 순수가상 함수 은 결합도가 높아지기에 사용하지 않는다.
    // 가상함수와 순수가상함수는 혼용할 수 없음
    //virtual void IFunction() PURE;  

    GImage* getBackBuffer(void) { return _backBuffer; }
   
    HBITMAP getMemBitmap() { return _backBuffer->getBit(); }
    HDC getMemDC() { return _backBuffer->getMemDC(); }
    HDC getHDC() { return _hdc; }

    LRESULT  MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


    GameNode() {}
    virtual ~GameNode() {}
};

