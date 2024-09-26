#pragma once
#include "GameNode.h"
class GameOverScene : public GameNode
{
private:
	GImage* _image;
	GImage* _new;
	GImage* _end;
	GImage* _text;

	RECT rc1;
	RECT rc2;
	RECT es1;
	RECT es2;
	RECT text;
	char text1[20];
	int alpha;
	int alpha1;

	int count;
	int count1;
	int speed;
	int width;
	bool clicked;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);
	GameOverScene() {}
	~GameOverScene() {}
};

