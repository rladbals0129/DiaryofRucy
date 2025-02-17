#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{

	//! Do Nothing
	
	return S_OK;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	GImage* img = findImage(strKey);
	
	if (img) return img;

	// 이미지가 없다..
	// 없으니까 새로 만든다
	img = new GImage;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	// 
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	// 재귀함수로 사용시 무한증식
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++
		// ㄴ 지역
		// 
		// 1. 함수반환값 데이터형을 확인함(FAILED가 nullptr을 모름)
		// return nullptr;
		// 2. 바로 61번으로 빠져나감
		return NULL;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	// 
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	// 재귀함수로 사용시 무한증식
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++
		// ㄴ 지역
		// 
		// 1. 함수반환값 데이터형을 확인함(FAILED가 nullptr을 모름)
		// return nullptr;
		// 2. 바로 61번으로 빠져나감
		return NULL;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	// 
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	// 재귀함수로 사용시 무한증식
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++
		// ㄴ 지역
		// 
		// 1. 함수반환값 데이터형을 확인함(FAILED가 nullptr을 모름)
		// return nullptr;
		// 2. 바로 61번으로 빠져나감
		return NULL;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	// 
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	// 재귀함수로 사용시 무한증식
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++
		// ㄴ 지역
		// 
		// 1. 함수반환값 데이터형을 확인함(FAILED가 nullptr을 모름)
		// return nullptr;
		// 2. 바로 61번으로 빠져나감
		return NULL;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	// 
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	// 검색한 키를 찾은 경우
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	// 검색한 키를 찾은 경우
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_RELEASE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		// 이미지가 있다면
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mImageList.clear();
	return true;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX,  destY,  sourX,  sourY,  sourWidth,  sourHeight);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int destWidt, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, destWidt, destHeight, sourX, sourY, sourWidth, sourHeight);
}


void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc,  destX,  destY,  sourX,  sourY,  sourWidth,  sourHeight,  alpha);
}



void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);

}

void ImageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);

}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	GImage* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);

}
void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
