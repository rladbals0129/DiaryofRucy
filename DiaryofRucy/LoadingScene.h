#pragma once
#include "GameNode.h"
#include "Animation.h"
enum EPattern
{
	PATTERN1, PATTERN2, PATTERN3
};
class LoadingScene : public GameNode
{
private:
	GImage* _Loadimg;
	GImage* _tipImage;
	Animation* _Loading;
	EPattern _setPattern;
	RECT rcLoad;
	int count;
	int count1;
	int index;
	int speed;
	int alpha;
	int randNum;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);
	void RandNum();

	LoadingScene() {}
	~LoadingScene() {}

};

