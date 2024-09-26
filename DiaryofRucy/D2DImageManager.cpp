#include "Stdafx.h"
#include "D2DImageManager.h"
//#include "Animation.h"


HRESULT D2DImageManager::init(HDC hdc)
{
    D2DInit(_hWnd, 0, 0, &_factory, &_rendTrg);
    WICInit(&_imagingFactory);

    HRESULT hr;
    RECT rc;
    GetClientRect(_hWnd, &rc);
    hr = _rendTrg->BindDC(hdc, &rc);

    SetLayout(hdc, LAYOUT_BITMAPORIENTATIONPRESERVED);

    return S_OK;
}

void D2DImageManager::release(void)
{

}

void D2DImageManager::beginDraw(void)
{
    _rendTrg->BeginDraw();
}

void D2DImageManager::endDraw(void)
{
    _rendTrg->EndDraw();
}

D2DImageInfo* D2DImageManager::loadImageD2D(string key, LPCWSTR lstr, int Width, int Height)
{
   /* D2DImageInfo* img = findImage(key);

    if (img)
    {
        return img;
    }*/
   
     D2DLoadBitmap(lstr, _rendTrg, _imagingFactory, &_pBitmap);
     _img = new D2DImageInfo;
     _img->bitmap = _pBitmap;
     _img->x = 0;
     _img->y = 0;
     _img->width = Width;
     _img->height = Height;

     _mImage.insert({ key, _img });

     return _img;
    


}

D2DImageInfo* D2DImageManager::loadImageD2D(string key, LPCWSTR lstr, int Width, int Height, int maxFrameX, int maxFrameY)
{
   /* D2DImageInfo* img = findImage(key);

    if (img)
    {
        return img;
    }*/
   
    D2DLoadBitmap(lstr, _rendTrg, _imagingFactory, &_pBitmap);
    _img = new D2DImageInfo;
    _img->bitmap = _pBitmap;
    _img->x = 0;
    _img->y = 0;
    _img->width = Width;
    _img->height = Height;
    _img->currentFrameX = 0;
    _img->currentFrameY = 0;
    _img->frameWidth = Width / maxFrameX;
    _img->frameHeight = Height / maxFrameY;
    _img->maxFrameX = maxFrameX - 1;
    _img->maxFrameY = maxFrameY - 1;

    _mImage.insert({ key, _img });

    return _img;

    

}

void D2DImageManager::render(string key, int destX, int destY)
{
    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->width, destY + _mImage[key]->height);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        _mImage[key]->width,
        _mImage[key]->height);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
    //if (_mImage[key]->bitmap) {}

}

void D2DImageManager::render(string key, int destX, int destY, int resizeX, int resizeY)
{
    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + resizeX, destY + resizeY);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        _mImage[key]->width,
        _mImage[key]->height);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
    if (_mImage[key]->bitmap) {}

}

void D2DImageManager::frameRender(string key, int destX, int destY, int currentFrameX, int currentFrameY)
{

    RECT rc;

    _img->currentFrameX = currentFrameX;
    _img->currentFrameY = currentFrameY;


    if (currentFrameX > _img->maxFrameX)
    {
        _img->currentFrameX = _img->maxFrameX;
    }

    if (currentFrameY > _img->maxFrameY)
    {
        _img->currentFrameY = _img->maxFrameY;
    }

    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->frameWidth, destY + _mImage[key]->frameHeight);
    D2D1_RECT_F rect2 = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX, _mImage[key]->frameHeight * currentFrameY,
        _mImage[key]->frameWidth * currentFrameX + _mImage[key]->frameWidth,
        _mImage[key]->frameHeight * currentFrameY + _mImage[key]->frameHeight);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
    if (_mImage[key]->bitmap) {}

}

void D2DImageManager::frameRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, int resizeX, int resizeY)
{

    RECT rc;

    _img->currentFrameX = currentFrameX;
    _img->currentFrameY = currentFrameY;


    if (currentFrameX > _img->maxFrameX)
    {
        _img->currentFrameX = _img->maxFrameX;
    }

    if (currentFrameY > _img->maxFrameY)
    {
        _img->currentFrameY = _img->maxFrameY;
    }


    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + resizeX, destY + resizeY);
    D2D1_RECT_F rect2 = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX, _mImage[key]->frameHeight * currentFrameY,
        _mImage[key]->frameWidth * currentFrameX + _mImage[key]->frameWidth,
        _mImage[key]->frameHeight * currentFrameY + _mImage[key]->frameHeight);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
    if (_mImage[key]->bitmap) {}


}

void D2DImageManager::alphaRender(string key, int destX, int destY, float alpha)
{
    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->width, destY + _mImage[key]->height);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        _mImage[key]->width,
        _mImage[key]->height);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
}

void D2DImageManager::alphaRender(string key, int destX, int destY, int resizeX, int resizeY, float alpha)
{
    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + resizeX, destY + resizeY);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        _mImage[key]->width,
        _mImage[key]->height);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
}

void D2DImageManager::frameAlphaRender(string key, int destX, int destY, int currentFrameX, int currentFrameY,float alpha)
{
    RECT rc;

    _img->currentFrameX = currentFrameX;
    _img->currentFrameY = currentFrameY;


    if (currentFrameX > _img->maxFrameX)
    {
        _img->currentFrameX = _img->maxFrameX;
    }

    if (currentFrameY > _img->maxFrameY)
    {
        _img->currentFrameY = _img->maxFrameY;
    }

    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->frameWidth, destY + _mImage[key]->frameHeight);
    D2D1_RECT_F rect2 = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX, _mImage[key]->frameHeight * currentFrameY,
        _mImage[key]->frameWidth * currentFrameX + _mImage[key]->frameWidth,
        _mImage[key]->frameHeight * currentFrameY + _mImage[key]->frameHeight);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
}

void D2DImageManager::frameAlphaRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, int resizeX, int resizeY, float alpha)
{
    RECT rc;

    _img->currentFrameX = currentFrameX;
    _img->currentFrameY = currentFrameY;


    if (currentFrameX > _img->maxFrameX)
    {
        _img->currentFrameX = _img->maxFrameX;
    }

    if (currentFrameY > _img->maxFrameY)
    {
        _img->currentFrameY = _img->maxFrameY;
    }


    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + resizeX, destY + resizeY);
    D2D1_RECT_F rect2 = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX, _mImage[key]->frameHeight * currentFrameY,
        _mImage[key]->frameWidth * currentFrameX + _mImage[key]->frameWidth,
        _mImage[key]->frameHeight * currentFrameY + _mImage[key]->frameHeight);

    _rendTrg->DrawBitmap(_mImage[key]->bitmap, rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect2);
 
}

void D2DImageManager::rotateRender(string key, int destX, int destY, float angle, float alpha)
{
    float centerX = destX + _mImage[key]->width / 2;
    float centerY = destY + _mImage[key]->height / 2;
    D2D1::Matrix3x2F transPosition = D2D1::Matrix3x2F::Translation(-centerX, -centerY);
    D2D1::Matrix3x2F rotationImage = D2D1::Matrix3x2F::Rotation(angle);
    D2D1::Matrix3x2F transPositionBack = D2D1::Matrix3x2F::Translation(centerX, centerY);

   
    D2D1::Matrix3x2F transform = transPosition * rotationImage * transPositionBack;

  
    D2D1::Matrix3x2F oldTransform;
    _rendTrg->GetTransform(&oldTransform);

    
    _rendTrg->SetTransform(&transform);

    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + _mImage[key]->width, destY + _mImage[key]->height);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        _mImage[key]->width,
        _mImage[key]->height);
    _rendTrg->DrawBitmap(_mImage[key]->bitmap,
        rect,
        alpha,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        rect2);

   
    _rendTrg->SetTransform(&oldTransform);

   
}
void D2DImageManager::rotateRender(string key, int destX, int destY, float angle, int resizeX, int resizeY, float alpha)
{
    float centerX = destX + resizeX/2;
    float centerY = destY + resizeY/2;
    D2D1::Matrix3x2F transPosition = D2D1::Matrix3x2F::Translation(-centerX, -centerY);
    D2D1::Matrix3x2F rotationImage = D2D1::Matrix3x2F::Rotation(angle);
    D2D1::Matrix3x2F transPositionBack = D2D1::Matrix3x2F::Translation(centerX, centerY);


    D2D1::Matrix3x2F transform = transPosition * rotationImage * transPositionBack;


    D2D1::Matrix3x2F oldTransform;
    _rendTrg->GetTransform(&oldTransform);


    _rendTrg->SetTransform(&transform);

    D2D1_RECT_F rect = D2D1::RectF(destX, destY, destX + resizeX, destY +  resizeY);
    D2D1_RECT_F rect2 = D2D1::RectF(0.f, 0.f,
        resizeX,
        resizeY);
    _rendTrg->DrawBitmap(_mImage[key]->bitmap,
        rect,
        alpha,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        rect2);


    _rendTrg->SetTransform(&oldTransform);
}
//float centerX = (destX + (destX + _mImage[key]->width)) / 2;
// float centerY = (destY + (destY + _mImage[key]->height))/ 2;
void D2DImageManager::frameRotateRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, float angle, float alpha)
{
 
    float centerX = destX + _mImage[key]->frameWidth / 2;
    float centerY = destY + _mImage[key]->frameHeight / 2;
    D2D1::Matrix3x2F transPosition = D2D1::Matrix3x2F::Translation(-centerX, -centerY);
    D2D1::Matrix3x2F rotationImage = D2D1::Matrix3x2F::Rotation(angle);
    D2D1::Matrix3x2F transPositionBack = D2D1::Matrix3x2F::Translation(centerX, centerY);


    D2D1::Matrix3x2F transform = transPosition * rotationImage * transPositionBack;


    D2D1::Matrix3x2F oldTransform;
    _rendTrg->GetTransform(&oldTransform);


    _rendTrg->SetTransform(&transform);

    D2D1_RECT_F rectDest = D2D1::RectF(destX, destY, destX + _mImage[key]->frameWidth, destY + _mImage[key]->frameHeight);

    D2D1_RECT_F rectSrc = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX,
        _mImage[key]->frameHeight * currentFrameY,
        (currentFrameX + 1) * _mImage[key]->frameWidth,
        (currentFrameY + 1) * _mImage[key]->frameHeight);
    _rendTrg->DrawBitmap(_mImage[key]->bitmap,
        rectDest,
        alpha,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        rectSrc);


    _rendTrg->SetTransform(&oldTransform);

}

void D2DImageManager::frameRotateRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, int resizeX, int resizeY, float angle, float alpha)
{
    float centerX = destX + resizeX / 2;
    float centerY = destY + resizeY / 2;
    D2D1::Matrix3x2F transPosition = D2D1::Matrix3x2F::Translation(-centerX, -centerY);
    D2D1::Matrix3x2F rotationImage = D2D1::Matrix3x2F::Rotation(angle);
    D2D1::Matrix3x2F transPositionBack = D2D1::Matrix3x2F::Translation(centerX, centerY);


    D2D1::Matrix3x2F transform = transPosition * rotationImage * transPositionBack;


    D2D1::Matrix3x2F oldTransform;
    _rendTrg->GetTransform(&oldTransform);


    _rendTrg->SetTransform(&transform);

    D2D1_RECT_F rectDest = D2D1::RectF(destX, destY, destX + resizeX, destY + resizeY);

    D2D1_RECT_F rectSrc = D2D1::RectF(_mImage[key]->frameWidth * currentFrameX,
        _mImage[key]->frameHeight * currentFrameY,
        (currentFrameX + 1) * _mImage[key]->frameWidth,
        (currentFrameY + 1) * _mImage[key]->frameHeight);
    _rendTrg->DrawBitmap(_mImage[key]->bitmap,
        rectDest,
        alpha,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        rectSrc);


    _rendTrg->SetTransform(&oldTransform);
}

HRESULT D2DImageManager::D2DInit(HWND hwnd, int width, int height, ID2D1Factory** factory, ID2D1DCRenderTarget** rt)
{
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory);

    if (SUCCEEDED(hr)) {
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(
                DXGI_FORMAT_B8G8R8A8_UNORM,
                D2D1_ALPHA_MODE_IGNORE),
            0,
            0,
            D2D1_RENDER_TARGET_USAGE_NONE,
            D2D1_FEATURE_LEVEL_DEFAULT
        );

        RECT rc;
        GetClientRect(hwnd, &rc);
        hr = (*factory)->CreateDCRenderTarget(&props, rt);
    }
    return hr;
}

HRESULT D2DImageManager::WICInit(IWICImagingFactory** factory)
{
    CoInitialize(0);

    return CoCreateInstance(CLSID_WICImagingFactory,
        0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory));
}

HRESULT D2DImageManager::D2DLoadBitmap(LPCWSTR fileName, ID2D1DCRenderTarget* target,
    IWICImagingFactory* factory, ID2D1Bitmap** bitmap)
{
    HRESULT hr;


    IWICBitmapDecoder* decoder = 0;
    hr = factory->CreateDecoderFromFilename(fileName,
        0,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &decoder
    );

    if (FAILED(hr))
        return hr;


    IWICBitmapFrameDecode* frameDecode = 0;

    hr = decoder->GetFrame(0, &frameDecode);
    if (FAILED(hr))
    {
        decoder->Release();
        return hr;
    }


    IWICFormatConverter* converter = 0;
    hr = factory->CreateFormatConverter(&converter);
    if (FAILED(hr))
    {
        decoder->Release();
        return hr;
    }

    hr = converter->Initialize(
        frameDecode,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        NULL, 0.0f, WICBitmapPaletteTypeCustom
    );

    if (FAILED(hr))
    {
        decoder->Release();
        frameDecode->Release();
        converter->Release();

        return hr;
    }


    hr = target->CreateBitmapFromWicBitmap(converter, 0, bitmap);


    decoder->Release();
    frameDecode->Release();
    converter->Release();

    _pBitmap = *bitmap;
    return hr;

}

D2DImageInfo* D2DImageManager::findImage(string strKey)
{
    auto key = _mImage.find(strKey);

   
    if (key != _mImage.end())
    {
        return key->second;
    }

    return nullptr;
}


D2DImageManager::D2DImageManager() : _factory(NULL),
_rendTrg(NULL),
_pBitmap(NULL),
_imagingFactory(NULL)
{
}




