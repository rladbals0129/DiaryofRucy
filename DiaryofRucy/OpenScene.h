#pragma once
#include "GameNode.h"
class OpenScene : public GameNode
{
private:
	GImage* _image;
	GImage* _new;
	GImage* _option;
	GImage* _end;

	RECT rc1;
	RECT rc2;
	RECT rc3;
	bool clicked;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	OpenScene() {}
	~OpenScene() {}
};
