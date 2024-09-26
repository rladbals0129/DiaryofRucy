#pragma once
#include "GameNode.h"
struct Shadow
{
	RECT rcshadow;
	int x;
	int y;
};
class item : public GameNode
{
private:

	GImage* _wstaff;
	GImage* _wbow;
	GImage* _wsword;
	GImage* _shadow;

	RECT rcwstaff;
	RECT rcwbow;
	RECT rcwsword;
	RECT rcshadow;

	int hp;
	int mp;
	int count;
public:

	HRESULT init(void);
	void release(void);
	void shadow(RECT rc);
	void update(void);
	void render(void);
	void d2drender(void);

};

