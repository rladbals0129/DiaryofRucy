#pragma once
#include "GameNode.h"
#include "EndingScene.h"

class EndingScene : public GameNode
{
private:
	int alpha;
	int alpha1;
	int count;
	int count1;

	int palpha;
	int pcount;
	int pindex;

	int endcount;

	GImage* _end;
	GImage* _piano;
	RECT rcEndText;
	RECT piano;
	bool clicked;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);

	EndingScene() {}
	~EndingScene() {}
};
