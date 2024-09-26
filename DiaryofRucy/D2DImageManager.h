#pragma once
#include "SingletonBase.h"

//class Animation;

struct D2DImageInfo
{
	ID2D1Bitmap* bitmap;
	float x;
	float y;
	int width;
	int height;
	int currentFrameX;
	int currentFrameY;

	int frameWidth;
	int frameHeight;
	int maxFrameX;
	int maxFrameY;
};
class D2DImageManager :public SingletonBase<D2DImageManager>
{
private:
	ID2D1Factory* _factory;
	ID2D1DCRenderTarget* _rendTrg;
	ID2D1Bitmap* _pBitmap;
	IWICImagingFactory* _imagingFactory;

	D2DImageInfo* _img;

	map<string, D2DImageInfo*> _mImage;
	map<string, D2DImageInfo*>::iterator _miImage;

	UINT _width, _height, _frame, _maxFrame;
	int _destX, _destY;
	int _currentFrameX, _currentFrameY;



public:
	HRESULT init(HDC hdc);
	void release(void);

	void beginDraw(void);
	void endDraw(void);

	D2DImageInfo* loadImageD2D(string key, LPCWSTR lstr, int Width, int Height);
	D2DImageInfo* loadImageD2D(string key, LPCWSTR lstr, int Width, int Height, int maxFrameX, int maxFrameY);


	void render(string key, int destX, int destY);
	void render(string key, int destX, int destY, int resizeX, int resizeY);
	void frameRender(string key, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, int resizeX, int resizeY);

	void alphaRender(string key, int destX, int destY,float alpha);
	void alphaRender(string key, int destX, int destY, int resizeX, int resizeY, float alpha);

	void frameAlphaRender(string key, int destX, int destY, int currentFrameX, int currentFrameY,float alpha);
	void frameAlphaRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, int resizeX, int resizeY,float alpha);

	void rotateRender(string key, int destX, int destY, float angle, float alpha = 1.0f);
	void rotateRender(string key, int destX, int destY, float angle, int resizeX, int resizeY, float alpha = 1.0f);
	void frameRotateRender(string key, int destX, int destY, int currentFrameX, int currentFrameY, float angle, float alpha = 1.0f);
	void frameRotateRender(string key, int destX, int destY,int currentFrameX, int currentFrameY,  int resizeX, int resizeY, float angle, float alpha = 1.0f);
	
	//void render(string key, int x, int y, float ac1);
	//void render(string key, int x, int y, float ac1, float opacity);

	HRESULT D2DInit(HWND hwnd, int width, int height,
		ID2D1Factory** factory, ID2D1DCRenderTarget** rt);
	HRESULT WICInit(IWICImagingFactory** factory);
	HRESULT D2DLoadBitmap(LPCWSTR fileName, ID2D1DCRenderTarget* target,
		IWICImagingFactory* factory, ID2D1Bitmap** bitmap);
	D2DImageInfo* findImage(string strKey);


	




	//inline int getFrameWidth(void) { return _img->frameWidth; }

	//inline int getFrameHeight(void) { return _img->frameHeight; }


	//inline int getMaxFrameX(void) { return _img->maxFrameX; }

	//inline int getMaxFrameY(void) { return _img->maxFrameY; }




	D2DImageManager();
	~D2DImageManager() {}
};
