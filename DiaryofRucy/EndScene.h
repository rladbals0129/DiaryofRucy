#pragma once
#include "GameNode.h"
class EndScene : public GameNode
{
private:
	GImage* _image;
	GImage* _new;
	GImage* _end;

	RECT rc1;
	RECT rc2;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	EndScene() {}
	~EndScene() {}

};

